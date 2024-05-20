#pragma once
#include <string>
#include <vector>
#include "WareHouse.h"
using std::string;
using std::vector;

enum class ActionStatus{
    COMPLETED, ERROR
};

enum class CustomerType{
    Soldier, Civilian
};


class Customer;

class BaseAction{
    public:
        BaseAction();
        ActionStatus getStatus() const; 
        virtual void act(WareHouse& wareHouse)=0;
        virtual string toString() const=0;
        virtual BaseAction* clone() const=0;
        virtual ~BaseAction() = default;

    protected:
        void complete();
        void error(string errorMsg);
        string getErrorMsg() const;

    private:
        string errorMsg;
        ActionStatus status;
};

class SimulateStep : public BaseAction {

    public:
        SimulateStep(int numOfSteps);
        void act(WareHouse &wareHouse) override;
        std::string toString() const override;
        SimulateStep *clone() const override;
        ~SimulateStep() override = default;
    
    protected: 
        const int getNumOfSteps() const;
        bool assignVolunteer(Order &order, WareHouse &wareHouse);
    
    private:
        const int numOfSteps;
};

class AddOrder : public BaseAction {
    public:
        AddOrder(int id);
        void act(WareHouse &wareHouse) override;
        string toString() const override;
        AddOrder *clone() const override;
        ~AddOrder() override = default;

    protected:
        const int getCustomerId() const;

    private:
        const int customerId;
};


class AddCustomer : public BaseAction {
    public:
        AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders);
        void act(WareHouse &wareHouse) override;
        AddCustomer *clone() const override;
        string toString() const override;
        ~AddCustomer() override = default;

    protected:
        const string getCustomerName() const;
        const CustomerType getCustomerType() const;
        const int getDistance() const;
        const int getMaxOrders() const;
        static const CustomerType getType(const string &type);

    private:
        const string customerName;
        const CustomerType customerType;
        const int distance;
        const int maxOrders;
};



class PrintOrderStatus : public BaseAction {
    public:
        PrintOrderStatus(int id);
        void act(WareHouse &wareHouse) override;
        PrintOrderStatus *clone() const override;
        string toString() const override;
        ~PrintOrderStatus() override = default;

    protected:
        const int getOrderId() const;
    private:
        const int orderId;
};

class PrintCustomerStatus: public BaseAction {
    public:
        PrintCustomerStatus(int customerId);
        void act(WareHouse &wareHouse) override;
        PrintCustomerStatus *clone() const override;
        string toString() const override;
        ~PrintCustomerStatus() override = default;

    protected:
        const int getCustomerId() const;
    private:
        const int customerId;
};


class PrintVolunteerStatus : public BaseAction {
    public:
        PrintVolunteerStatus(int id);
        void act(WareHouse &wareHouse) override;
        PrintVolunteerStatus *clone() const override;
        string toString() const override;
        ~PrintVolunteerStatus() override = default;
    
    protected:
        const int getVolunteerId() const;
    
    private:
        const int volunteerId;
};


class PrintActionsLog : public BaseAction {
    public:
        PrintActionsLog();
        void act(WareHouse &wareHouse) override;
        PrintActionsLog *clone() const override;
        string toString() const override;
        ~PrintActionsLog() override=default;
    private:
};

class Close : public BaseAction {
    public:
        Close();
        void act(WareHouse &wareHouse) override;
        string toString() const override;
        Close *clone() const override;
        ~Close() override =default;
    private:
};

class BackupWareHouse : public BaseAction {
    public:
        BackupWareHouse();
        void act(WareHouse &wareHouse) override;
        BackupWareHouse *clone() const override;
        string toString() const override;
        ~BackupWareHouse() override = default;
    private:
};


class RestoreWareHouse : public BaseAction {
    public:
        RestoreWareHouse();
        void act(WareHouse &wareHouse) override;
        RestoreWareHouse *clone() const override;
        string toString() const override;
        ~RestoreWareHouse() override=default;
    private:
};