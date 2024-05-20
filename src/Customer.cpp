
#include "../include/Customer.h"  
using std::string;
#include <string>

        Customer::Customer(int id, const string &name, int locationDistance, int maxOrders):
        id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders),
        ordersId(){}


        const string& Customer::getName() const{
            return name;
        }
        
        int Customer::getId() const{
            return id;
        }

        int Customer::getCustomerDistance() const{
            return locationDistance;
        }

        int Customer::getMaxOrders() const{
            return maxOrders;

        } //Returns maxOrders

        int Customer::getNumOrders() const{
            return ordersId.size();
        } //Returns num of orders the customer has made so far

        bool Customer::canMakeOrder() const{
            return ordersId.size()<(static_cast<std::vector<int>::size_type>(maxOrders));
            } //Returns true if the customer didn't reach max orders

        const vector<int>& Customer::getOrdersIds() const{
            return const_cast<vector<int>&>(ordersId);
        }

        int Customer::addOrder(int orderId){
            if(canMakeOrder()){
                ordersId.push_back(orderId);
                return orderId;
            }
            else{
                return -1;
            }
        } //return OrderId if order was added successfully, -1 otherwise

         SoldierCustomer::SoldierCustomer(int id, const string &name, int locationDistance, int maxOrders):
         Customer(id, name, locationDistance, maxOrders) {};


        SoldierCustomer * SoldierCustomer::clone() const {
            return new SoldierCustomer(*this);
        }

        string SoldierCustomer::toString() const{
            return "customer soldier "+getName()+", locationDistance: "+
            std::to_string(getCustomerDistance())+", maxOrders: "+std::to_string(getMaxOrders());
        }

        CivilianCustomer::CivilianCustomer(int id, const string &name, int locationDistance, int maxOrders):
        Customer(id, name, locationDistance, maxOrders){};

        CivilianCustomer * CivilianCustomer::clone() const {
            return new CivilianCustomer(*this);
        }

        string CivilianCustomer::toString() const{
            return "customer civilian "+getName()+", locationDistance: "+
            std::to_string(getCustomerDistance())+", maxOrders: "+
            std::to_string(getMaxOrders());
        }

        



        

