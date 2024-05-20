
#include "../include/Action.h"
#include "../include/Customer.h"
#include <string> 
#include <iostream>
#include "../include/Volunteer.h"
#include "../include/WareHouse.h"
#include "../include/Order.h"
using namespace std; 
extern WareHouse* backup;

std::string ActionStatusToString(ActionStatus value) {
    switch(value) {
        case ActionStatus::ERROR: return "ERROR";
        case ActionStatus::COMPLETED: return "COMPLETED";
        default: return "";
    }
}

std::string CustomerTypeToString(CustomerType value) {
    switch(value) {
        case CustomerType::Civilian: return "civilian";
        case CustomerType::Soldier: return "soldier";
        default: return "";
    }
}

//BASE ACTION
        BaseAction::BaseAction(): errorMsg(), status(){};
        
        ActionStatus BaseAction:: getStatus() const{
            return status;
        }

        void BaseAction::complete(){
                status = ActionStatus::COMPLETED;
        }

        void BaseAction::error(string errorMsg){
                status = ActionStatus::ERROR;
                this->errorMsg = errorMsg;
        }
        
        string BaseAction::getErrorMsg() const{
                return errorMsg;
         }



//SIMULATE STEP
        SimulateStep::SimulateStep(int numOfSteps): BaseAction(), numOfSteps(numOfSteps){};

        void SimulateStep::act(WareHouse &wareHouse){
            for(int k=0; k<numOfSteps; k++){
                const vector<Order*> &pendingOrders = wareHouse.getPendingOrders();
                for (size_t i=0; i<pendingOrders.size(); i++){
                    if(assignVolunteer(*pendingOrders[i], wareHouse)){
                        wareHouse.addToProcessOrders(pendingOrders[i]);
                        wareHouse.deleteFromPendingOrders(pendingOrders[i]->getId());
                        i--;
                    }
                }
                wareHouse.step();   
        } 
        wareHouse.addAction(clone()); 
    }  

        string SimulateStep::toString() const{
            return "simulateStep "+to_string(numOfSteps)+" "+ActionStatusToString(getStatus());
        }
        
        SimulateStep* SimulateStep::clone() const{
            return new SimulateStep(*this);
        }

        const int SimulateStep::getNumOfSteps() const{
            return numOfSteps;
        }

        bool SimulateStep::assignVolunteer(Order &order, WareHouse &wareHouse){
            const vector<Volunteer*> &volunteers = wareHouse.getVolunteers();
            if(order.getStatus()==OrderStatus::PENDING){
                for(Volunteer *v: volunteers){
                    if(v->map()==0 && v->canTakeOrder(order)){
                        v->acceptOrder(order);
                        order.setCollectorId(v->getId());
                        order.setStatus(OrderStatus::COLLECTING); 
                        return true;
                    }
                }
            }
            else if(order.getStatus()==OrderStatus::COLLECTING){
                for(Volunteer *v: volunteers){
                    if(v->map()==1 && v->canTakeOrder(order)){
                        v->acceptOrder(order);
                        order.setDriverId(v->getId());
                        order.setStatus(OrderStatus::DELIVERING);
                        return true;
                    }
                }
            }
            return false;
        }
        

//ADD ORDER 
        AddOrder::AddOrder(int id): BaseAction(), customerId(id){};


        void AddOrder::act(WareHouse &wareHouse){ 
            Customer &c = wareHouse.getCustomer(customerId);
            if(c.getId()!=-1 && c.canMakeOrder()){
                Order *ord = new Order(wareHouse.getOrderCounter(), customerId, c.getCustomerDistance());
                wareHouse.addOrder(ord);
                c.addOrder(ord->getId());
                complete();
            }
            else{
                error("Error: Cannot place this order.");
                cout << getErrorMsg() << endl;

            }
            wareHouse.addAction(clone());
        }

        string AddOrder::toString() const{
            return "order "+to_string(customerId)+" "+ActionStatusToString(getStatus());
        }
        
        AddOrder *AddOrder::clone() const{
            return new AddOrder(*this);
        }

        const int AddOrder::getCustomerId() const{
            return customerId;
        }


//ADD CUSTOMER

         const CustomerType AddCustomer::getType(const string &type){
            if(type=="soldier"){
                return CustomerType::Soldier;
            }
            return CustomerType::Civilian;
        }

        AddCustomer::AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders): 
            BaseAction(), customerName(customerName), customerType(getType(customerType)), 
            distance(distance), maxOrders(maxOrders) {};

        
        void AddCustomer::act(WareHouse &wareHouse){
            if(customerType==CustomerType::Soldier){
                SoldierCustomer* c = new SoldierCustomer(wareHouse.getCustomerCounter(),
                customerName, distance, maxOrders);
                wareHouse.insertCustomer(c);
            }
            else {
                CivilianCustomer* d = new CivilianCustomer(wareHouse.getCustomerCounter(), 
                customerName,  distance,  maxOrders);
                wareHouse.insertCustomer(d);        
            }
            complete();
            wareHouse.addAction(clone());
        }

        AddCustomer *AddCustomer::clone() const{ 
            return new AddCustomer(*this); 
        }
        
        string AddCustomer::toString() const{
            return "customer "+customerName+" "+CustomerTypeToString(customerType)+" "+to_string(distance)+" "+to_string(maxOrders)+" "
            +ActionStatusToString(getStatus());

        }

        const string AddCustomer::getCustomerName() const{
            return customerName;
        }

        const CustomerType AddCustomer::getCustomerType() const{
            return customerType;
        }

        const int AddCustomer::getDistance() const{
            return distance;
        }

        const int AddCustomer::getMaxOrders() const{
            return maxOrders;
        }

        

//PRINT ORDER STATUS
        PrintOrderStatus::PrintOrderStatus(int id): BaseAction(), orderId(id){};
        
        void PrintOrderStatus::act(WareHouse &wareHouse) {
            Order &ord = wareHouse.getOrder(orderId);
            if(ord.getId()!=-1){
                cout << "OrderId: "+to_string(ord.getId()) << endl;
                cout << "OrderStaus: "+ ord.OrderStatusToString(ord.getStatus()) << endl;
                cout << "CustomerId: "+to_string(ord.getCustomerId()) << endl;
                if(ord.getCollectorId()!=-1){
                    cout << "CollectorId: "+to_string(ord.getCollectorId()) << endl;
                }
                else{
                    cout << "CollectorID: None" << endl;
                }
                if(ord.getDriverId()!=-1){
                    cout << "DriverId: "+to_string(ord.getDriverId()) << endl;
                }
                else{
                    cout << "DriverId: None" << endl;
                }
                complete();
            }
            else{
                error("Error: Order doesn't exist.");
                cout << getErrorMsg() << endl;
            }
            wareHouse.addAction(clone());

        }
        
        PrintOrderStatus *PrintOrderStatus::clone() const{
            return new PrintOrderStatus(*this);
        }
        
        string PrintOrderStatus::toString() const {
            return "orderStatus "+to_string(orderId)+" "+ActionStatusToString(getStatus());

        }

        const int PrintOrderStatus::getOrderId() const{
            return orderId;
        }


//PRINT CUSTOMER STATUS
        PrintCustomerStatus::PrintCustomerStatus(int customerId): BaseAction(), customerId(customerId){};


        void PrintCustomerStatus::act(WareHouse &wareHouse) {
                Customer &c = wareHouse.getCustomer(customerId);
                if(c.getId()==-1){
                        error("Error: Customer does not exist");
                        cout << getErrorMsg() << endl;
                }
                else{
                        cout << "Customer Id:" + to_string(customerId) << endl;   
                        const vector<int> &ordersId = c.getOrdersIds();
                        for (int ordId: ordersId) {
                                std::cout << "OrderId:" + to_string(ordId) << std::endl;
                                Order &order = wareHouse.getOrder(ordId);
                                std::cout << "Order Status:" << order.OrderStatusToString(order.getStatus()) << std::endl;
                        }
                        cout << "Orders Left:" + to_string(c.getMaxOrders() - ordersId.size()) << endl;   
                    complete();
                }  
                wareHouse.addAction(clone());            
        };
        
        PrintCustomerStatus *PrintCustomerStatus::clone() const{
            return new PrintCustomerStatus(*this);

        }
        
        string PrintCustomerStatus::toString() const {
             return "customerStatus "+to_string(customerId)+" "+ActionStatusToString(getStatus());
        }

        const int PrintCustomerStatus::getCustomerId() const{
            return customerId;
        }


//PRINT VOLUNTEER STATUS
        PrintVolunteerStatus::PrintVolunteerStatus(int id): BaseAction(), volunteerId(id){};

        void PrintVolunteerStatus::act(WareHouse &wareHouse) {
            Volunteer &v = wareHouse.getVolunteer(volunteerId);
            if(v.getId()!=-1){
                cout << v.getDetails() << endl;
            }
            else{
                error("Error: Volunteer doesn't exist");
                cout << getErrorMsg() << endl;
            }
            wareHouse.addAction(clone());
        }
        
        PrintVolunteerStatus *PrintVolunteerStatus::clone() const {
            return new PrintVolunteerStatus(*this);
        }
           
        string PrintVolunteerStatus::toString() const {
             return "volunteerStatus "+to_string(volunteerId)+" "+ActionStatusToString(getStatus());
        }

        const int PrintVolunteerStatus::getVolunteerId() const{
            return volunteerId;
        }
        
        
//PRINT ACTIONS LOG
        PrintActionsLog::PrintActionsLog(): BaseAction(){};

        void PrintActionsLog::act(WareHouse &wareHouse) {
            const vector<BaseAction*> &actions = wareHouse.getActions();
            for (BaseAction *action: actions){
                 std::cout << action->toString() << std::endl;
            }
            wareHouse.addAction(clone());
            complete();
        }

        PrintActionsLog *PrintActionsLog::clone() const {
            return new PrintActionsLog(*this);
         }
        
        string PrintActionsLog::toString() const {
            return  "log " + ActionStatusToString(getStatus());
        }

//CLOSE
        Close::Close(): BaseAction(){};
        
        void Close::act(WareHouse &wareHouse) {
            const vector<Order*> &pendingOrders = wareHouse.getPendingOrders();
            const vector<Order*> &processOrders = wareHouse.getProccessOrders();
            const vector<Order*> &completedOrders = wareHouse.getCompletedOrders();
            for (Order *ord: pendingOrders) {
                                std::cout << "Order : " + to_string(ord->getId()) + ", Customer ID: " + to_string(ord->getCustomerId()) + ", Status: " + ord->OrderStatusToString(ord->getStatus()) << std::endl;
            }
            for (Order *ord: processOrders) {
                                std::cout << "Order : " + to_string(ord->getId()) + ", Customer ID: " + to_string(ord->getCustomerId()) + ", Status: " + ord->OrderStatusToString(ord->getStatus())<< std::endl;
            }
            for (Order *ord: completedOrders) {
                                std::cout << "Order : " + to_string(ord->getId()) + ", Customer ID: " + to_string(ord->getCustomerId()) + ", Status: Completed" << std::endl;
            }
            wareHouse.close();
            complete();
        }

        string Close::toString() const {
            return "close "+ActionStatusToString(getStatus());

        }

        Close * Close::clone() const {
            return new Close(*this);
        }


    

//BACKUP WAREHOUSE
        BackupWareHouse::BackupWareHouse(): BaseAction(){};

        void BackupWareHouse::act(WareHouse &wareHouse) {
            complete();
            wareHouse.addAction(clone());
            if(backup!=nullptr){
                delete backup;
            }
            backup = new WareHouse(wareHouse);
        }

        BackupWareHouse * BackupWareHouse::clone() const {
            return new BackupWareHouse(*this);
        }

        string BackupWareHouse::toString() const {
            return "backup "+ActionStatusToString(getStatus());
        }
    

//RESTORE WAREHOUSE
        RestoreWareHouse::RestoreWareHouse(): BaseAction(){};
        
        void RestoreWareHouse::act(WareHouse &wareHouse) {
            if(backup!=nullptr){
                wareHouse=*backup; 
                complete();
            }
            else{
                error("Error: No backup available");
                cout << getErrorMsg() << endl;
            }
        
            wareHouse.addAction(clone());
           

        }

        RestoreWareHouse * RestoreWareHouse::clone() const{
            return new RestoreWareHouse(*this);

        }
        string RestoreWareHouse::toString() const {
            return "restore "+ActionStatusToString(getStatus());
        }