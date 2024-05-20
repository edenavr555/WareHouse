#include "../include/WareHouse.h"
#include "../include/Action.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

        WareHouse::WareHouse(const string &configFilePath):
        isOpen(1), actionsLog(), volunteers(), pendingOrders(),
        inProcessOrders(), completedOrders(), customers(),
        customerCounter(0), volunteerCounter(0), OrderCounter(0), fakeVolunteer(new CollectorVolunteer(-1, "fake", -1)),
        fakeCustomer(new CivilianCustomer(-1, "fake", -1, -1)), fakeOrder(new Order(-1, -1, -1)){
            parse(configFilePath);
        }

        //copy constructor 
        WareHouse:: WareHouse(const WareHouse &other):
        isOpen(other.getIsOpen()), actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(),
        customerCounter(other.getCustomerCounter()), volunteerCounter(other.getVolunteerCounter()),
        OrderCounter(other.getOrderCounter()), fakeVolunteer(new CollectorVolunteer(-1, "fake", -1)),
        fakeCustomer(new CivilianCustomer(-1, "fake", -1, -1)), fakeOrder(new Order(-1, -1, -1)){
            const vector<BaseAction*> & logs = other.getActions();
            for(BaseAction *act: logs){
                actionsLog.push_back(act->clone());
             }
            const vector<Customer*> &otherCustomers = other.getCustomers();
             for(Customer *customer: otherCustomers){
                customers.push_back(customer->clone());
             }
            const vector<Volunteer*> &otherVolunteers = other.getVolunteers();
            for(Volunteer *volunteer: otherVolunteers){
                volunteers.push_back(volunteer->clone());
             }
            const vector<Order*> &penOrders = other.getPendingOrders();
              for(Order *ord: penOrders){
                pendingOrders.push_back(ord->clone());
             }
            const vector<Order*> &prosOrders = other.getProccessOrders();
            for(Order *ord: prosOrders){
                inProcessOrders.push_back(ord->clone());
            }
            const vector<Order*> &compOrders = other.getCompletedOrders();
            for(Order *ord: compOrders){
                completedOrders.push_back(ord->clone());
            }
        }

        WareHouse:: WareHouse(WareHouse &&other):
            isOpen(other.getIsOpen()), actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(),
            customerCounter(other.getCustomerCounter()), volunteerCounter(other.getVolunteerCounter()),
            OrderCounter(other.getOrderCounter()), fakeVolunteer(new CollectorVolunteer(-1, "fake", -1)),
            fakeCustomer(new CivilianCustomer(-1, "fake", -1, -1)), fakeOrder(new Order(-1, -1, -1)){
            actionsLog = std::move(other.actionsLog);
            volunteers = std::move(other.volunteers);
            pendingOrders = std::move(other.pendingOrders);
            inProcessOrders = std::move(other.inProcessOrders);
            completedOrders = std::move(other.completedOrders);
            customers = std::move(other.customers);
        }

        const WareHouse& WareHouse::operator=(const WareHouse &other){
            if(this!= &other){
                isOpen = other.getIsOpen();
                customerCounter = other.getCustomerCounter();
                volunteerCounter = other.getVolunteerCounter();
                OrderCounter = other.getOrderCounter();
                //emptying all vectors
                for (Customer* customer : customers) {delete customer;}
                customers.clear();
                for (Volunteer* volunteer : volunteers) {delete volunteer;}
                volunteers.clear();
                for (Order* order : pendingOrders) {delete order;}
                pendingOrders.clear();
                for (Order* order : inProcessOrders) {delete order;}
                inProcessOrders.clear();
                for (Order* order : completedOrders) {delete order;}
                completedOrders.clear(); 
                for (BaseAction* action : actionsLog) { delete action;}
                actionsLog.clear();
                //copying items between vectors
                for (Customer* customer : other.getCustomers()) {customers.push_back(customer->clone());}
                for (Volunteer* volunteer : other.getVolunteers()) {volunteers.push_back(volunteer->clone());}
                for (Order* order : other.getPendingOrders()) {pendingOrders.push_back(order->clone());}
                for (Order* order : other.getProccessOrders()) {inProcessOrders.push_back(order->clone());}
                for (Order* order : other.getCompletedOrders()) {completedOrders.push_back(order->clone());} 
                for (BaseAction* action : other.getActions()) {actionsLog.push_back(action->clone());}
            }
            return *this;
        }

        WareHouse & WareHouse::operator=(WareHouse &&other){
            for (Customer* customer : customers) {delete customer;}
            customers.clear();
            for (Volunteer* volunteer : volunteers) {delete volunteer;}
            volunteers.clear();
            for (Order* order : pendingOrders) {delete order;}
            pendingOrders.clear();
            for (Order* order : inProcessOrders) {delete order;}
            inProcessOrders.clear();
            for (Order* order : completedOrders) {delete order;}
            completedOrders.clear(); 
            for (BaseAction* action : actionsLog) { delete action;}
            actionsLog.clear();
            isOpen = other.isOpen;
            actionsLog = std::move(other.actionsLog);
            pendingOrders = std::move(other.pendingOrders);
            inProcessOrders = std::move(other.inProcessOrders);
            completedOrders = std::move(other.completedOrders);
            customers = std::move(other.customers);
            customerCounter = other.customerCounter;
            volunteerCounter = other.volunteerCounter;
            OrderCounter = other.OrderCounter;
            return *this;
        }

        WareHouse::~WareHouse() {
        for (Customer* customer : customers) {delete customer;}
        customers.clear();
        for (Volunteer* volunteer : volunteers) {delete volunteer;}
        volunteers.clear();
        for (Order* order : pendingOrders) {delete order;}
        pendingOrders.clear();
        for (Order* order : inProcessOrders) {delete order;}
        inProcessOrders.clear();
        for (Order* order : completedOrders) {delete order;}
        completedOrders.clear(); 
        for (BaseAction* action : actionsLog) { delete action;}
        actionsLog.clear();
        delete fakeCustomer;
        delete fakeOrder;
        delete fakeVolunteer;
        fakeCustomer = nullptr;
        fakeOrder = nullptr;
        fakeVolunteer = nullptr;
        }
        
        const bool WareHouse::getIsOpen() const{
            return isOpen;
        }

        void WareHouse::start(){
            open();
            cout << "WareHouse is open!" << endl;
            while (getIsOpen()){
                string userInput, objType;
                cout << "Enter an action: ";
                getline(std::cin, userInput);
                istringstream iss(userInput);
                iss >> objType;
               if(objType=="step"){
                    int numOfSteps;
                    iss >> numOfSteps;
                    SimulateStep action = SimulateStep(numOfSteps);
                    action.act(*this);
                }
                else if(objType == "orderStatus"){
                    int id;
                    iss>>id;
                    PrintOrderStatus action = PrintOrderStatus(id);
                    action.act(*this);
                }
                else if(objType == "order"){
                    int orderId;
                    iss>>orderId;
                    AddOrder action = AddOrder(orderId);
                    action.act(*this);
                }
                
                else if(objType == "customer"){
                    string name, type;
                    int distance, maxOrders;
                    iss>>name>>type>>distance>>maxOrders;
                    AddCustomer action = AddCustomer(name, type, distance, maxOrders);
                    action.act(*this);
                }
                else if(objType == "customerStatus"){
                    int id;
                    iss>>id;
                    PrintCustomerStatus action = PrintCustomerStatus(id);
                    action.act(*this);
                }
                else if(objType == "volunteerStatus"){
                    int id;
                    iss>>id;
                    PrintVolunteerStatus action = PrintVolunteerStatus(id);
                    action.act(*this);
                }
                else if(objType == "log"){
                    PrintActionsLog action = PrintActionsLog();
                    action.act(*this);
                }
                 else if(objType == "restore"){
                    RestoreWareHouse action = RestoreWareHouse();
                    action.act(*this);
                }
                 else if(objType == "backup"){
                    BackupWareHouse action = BackupWareHouse();
                    action.act(*this);
                }
                else if(objType == "close"){
                    Close action = Close();
                    action.act(*this);
                }
                else {cout<<"invalid input"<<endl;}
            }
        }
        
        
        const vector<BaseAction*>& WareHouse::getActions() const{
            return actionsLog;
        }

        void WareHouse::addOrder(Order* order){
            pendingOrders.push_back(order);
            inscreaseOrderCounter();
        }

        void WareHouse::addAction(BaseAction* action){
            actionsLog.push_back(action);
        } //add action to actionsLog 


        Customer & WareHouse::getCustomer(int customerId) const{
              for (Customer *c: customers){
                if (c->getId() == customerId ){
                    return *c;
                }
              }
              return *fakeCustomer;
        }

        Volunteer & WareHouse::getVolunteer(int volunteerId) const{
            for (Volunteer *v: volunteers){
                if(v->getId() == volunteerId){
                    return *v;
                }
              }
            return *fakeVolunteer;
        } 

        Order & WareHouse::getOrder(int orderId) const {
            for (Order *order: pendingOrders){
                if (order->getId() == orderId){
                    return *order;
                }
              }
             for (Order *order: inProcessOrders){
                if (order->getId() == orderId){
                    return *order;
                }
              }
             for (Order *order: completedOrders){
                if (order->getId() == orderId){
                    return *order;
                }
              }
            return *fakeOrder; 
        }
        

        void WareHouse::close(){
            isOpen = false;
        }

        void WareHouse::open(){
            isOpen = true;
        }

        void WareHouse::increaseCustomerCounter(){
            customerCounter++;
        } //increases by 1 
        void WareHouse::increaseVolunteerCounter(){
            volunteerCounter++;
        } //increases by 1 
        void WareHouse::inscreaseOrderCounter(){
            OrderCounter++;
        } //increase by 1 
        const int WareHouse::getCustomerCounter() const{
            return customerCounter;
        }
        const int WareHouse::getVolunteerCounter() const{
            return volunteerCounter;
        }
        const int WareHouse::getOrderCounter() const{
            return OrderCounter;
        }

        void WareHouse::insertCustomer(Customer * customer){
            customers.push_back(customer);
            increaseCustomerCounter();
        } // adds to customers vector. need to increase cutomerCounter by1.

        void WareHouse::addVolunteer(Volunteer * volunteer){
            volunteers.push_back(volunteer);
            increaseVolunteerCounter();
        } //adds to volunteers vector. need to increase volunteerCounter by1.
        //For closing the Warehouse:
        const vector<Order*> &WareHouse::getPendingOrders() const{
            return pendingOrders;
        }
        const vector<Order*> &WareHouse::getProccessOrders() const{
            return inProcessOrders;
        }
        const vector<Order*> &WareHouse::getCompletedOrders() const{
            return completedOrders;
        }
        const vector<Customer*> &WareHouse::getCustomers() const{
            return customers;
        }
        const vector<Volunteer*> &WareHouse::getVolunteers() const{
            return volunteers;
        }

        void WareHouse::addToPendingOrders(Order *order){
            pendingOrders.push_back(order);
        }

        void WareHouse::addToProcessOrders(Order *order){
            inProcessOrders.push_back(order);
        }

        void WareHouse::addToCompletedOrders(Order *order){
            completedOrders.push_back(order);
        }

        void WareHouse::deleteFromPendingOrders(int orderId){
            auto iter = pendingOrders.begin();
            while(iter != pendingOrders.end()){
                if((*iter)->getId() == orderId){
                    iter=pendingOrders.erase(iter);
                }
                else{
                    iter++;
                }
            }
        }

        void WareHouse::deleteFromProcessOrders(int orderId){
            auto iter = inProcessOrders.begin();
            while(iter != inProcessOrders.end()){
                if((*iter)->getId() == orderId){
                    iter=inProcessOrders.erase(iter);
                }
                else{
                    iter++;
                }
            }
        }

        void WareHouse::deleteFromCompletedOrders(int orderId){
            auto iter = completedOrders.begin();
            while(iter != completedOrders.end()){
                if((*iter)->getId() == orderId){
                    iter=completedOrders.erase(iter);
                }
                else{
                    iter++;
                }
            }
        }

        void WareHouse::deleteVolunteer(Volunteer *volunteer){
            auto iter = volunteers.begin();
            while((*iter)->getId()!=volunteer->getId()){
                iter++;
            }
            iter=volunteers.erase(iter);
        }

         void WareHouse::step(){
            for (size_t i=0; i<volunteers.size(); i++){
                if(volunteers[i]->isBusy()){
                    volunteers[i]->step();
                    if(volunteers[i]->isBusy()==false){
                        Order &order = getOrder(volunteers[i]->getCompletedOrderId());
                        deleteFromProcessOrders(order.getId());
                        if(volunteers[i] -> map()==0) {addToPendingOrders(&order);}
                        if(volunteers[i] -> map()==1) {
                            order.setStatus(OrderStatus::COMPLETED);
                            addToCompletedOrders(&order);
                        }
                        if(volunteers[i]->hasOrdersLeft()==false){
                            delete volunteers[i];
                            volunteers.erase(volunteers.begin()+i);
                            i--;
                        }
                    }
                }
            }
         }
                       

