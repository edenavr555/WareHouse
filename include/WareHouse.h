#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include "../include/Order.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"

class BaseAction;
class Volunteer;


// Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse(const string &configFilePath);
        WareHouse(const WareHouse &other); // copy constructor 
        virtual ~WareHouse(); //destructor 
        const WareHouse& operator=(const WareHouse &other); //copy assignment operator
        WareHouse& operator=(WareHouse &&other); //move assignment operator 
        WareHouse(WareHouse &&other); //move constructor
        void start();
        const vector<BaseAction*> &getActions() const;
        void addOrder(Order* order); 
        void addAction(BaseAction* action); //add action to actionsLog 
        Customer &getCustomer(int customerId) const; //returns nullptr if does'nt exist 
        Volunteer &getVolunteer(int volunteerId) const; //return nullptr if doesnt exist
        Order &getOrder(int orderId) const; //return nullptr if doesnt exist
        void close();
        void open();
        const int getCustomerCounter() const; 
        const int getVolunteerCounter() const;
        const int getOrderCounter() const;
        void insertCustomer(Customer * customer); // adds to customers vector. need to increase cutomerCounter by1.
        void addVolunteer(Volunteer * volunteer); //adds to volunteers vector. need to increase volunteerCounter by1.
        const vector<Order*> &getPendingOrders() const;
        const vector<Order*> &getProccessOrders() const;
        const vector<Order*> &getCompletedOrders() const;
        void parse(const string &configFilePath);
        const vector<Customer*> &getCustomers() const;
        const vector<Volunteer*> &getVolunteers() const;
        const bool getIsOpen() const;
        void addToPendingOrders(Order *order);
        void addToProcessOrders(Order *order);
        void addToCompletedOrders(Order *order);
        void deleteFromPendingOrders(int orderId);
        void deleteFromProcessOrders(int orderId);
        void deleteFromCompletedOrders(int orderId);
        void deleteVolunteer(Volunteer *volunteer);
        void step();


 

    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        int OrderCounter; //For assigning unique Order IDs 
        void increaseCustomerCounter(); //increases by 1 
        void increaseVolunteerCounter(); //increases by 1 
        void inscreaseOrderCounter(); //increase by 1 
        //for returning references that don't exist: 
        CollectorVolunteer* fakeVolunteer; // heap, need to delete at the end
        CivilianCustomer * fakeCustomer; // heap, need to delete at the end
        Order* fakeOrder; // heap, need to delete at the end

};