#include "../include/Order.h"
#include <iostream>
#include <string> 
using namespace std; 

        std::string Order::OrderStatusToString(OrderStatus value) const{
            switch(value) {
                case OrderStatus::PENDING: return "Pending";
                case OrderStatus::COLLECTING: return "Collecting";
                case OrderStatus::DELIVERING: return "Delivering";
                case OrderStatus::COMPLETED: return "Completed";
            }
            return "";

        }

        Order::Order(int id, int customerId, int distance): id(id), customerId(customerId), distance(distance), 
        status(OrderStatus::PENDING), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER) {};

        int Order::getId() const{
            return id;
        }
        int Order::getCustomerId() const{
            return customerId;
        }
        void Order::setStatus(OrderStatus status){
            this->status=status;
        }
        void Order::setCollectorId(int collectorId){
            this->collectorId=collectorId;
        }
        void Order::setDriverId(int driverId){
            this->driverId=driverId;
        }
        int Order::getCollectorId() const{
            return collectorId;
        }
        int Order::getDriverId() const{
            return driverId;
        }
        OrderStatus Order::getStatus() const{
            return status;
        }

        int Order::getDistance() const{
            return distance;
        }

        Order * Order::clone(){
            return new Order(*this);
        }

        const string Order::toString() const{
            return "Order ID: " + to_string(id) + ", Customer ID: " + to_string(customerId) +
           ", Distance: " + to_string(distance) +
           ", Status: " + OrderStatusToString(status) +
           ", Collector ID: " + to_string(collectorId) +
           ", Driver ID: " + to_string(driverId);
        }