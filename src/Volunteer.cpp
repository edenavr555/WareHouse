#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <string> 
using namespace std; 

//Volunteer map: Collector=0, Driver=1

Volunteer::Volunteer(int id, const string &name):  completedOrderId(NO_ORDER), activeOrderId(NO_ORDER), id(id), name(name){};


int Volunteer:: getId() const {
    return id;
}

const string &  Volunteer:: getName() const {
    return name;
}

 int Volunteer:: getActiveOrderId() const {
    return activeOrderId;
}

int Volunteer:: getCompletedOrderId() const{
    return completedOrderId;
}

bool Volunteer:: isBusy() const{
    return (activeOrderId != NO_ORDER);
}

void Volunteer::clear() {
    completedOrderId = NO_ORDER;
}

CollectorVolunteer::CollectorVolunteer
(int id, const string &name, int coolDown): Volunteer(id,name), coolDown(coolDown), timeLeft(0){};


CollectorVolunteer * CollectorVolunteer:: clone() const { 
    return new CollectorVolunteer(*this);
}
    
int CollectorVolunteer:: getCoolDown() const {
    return coolDown;
}

int CollectorVolunteer:: getTimeLeft() const {
    return timeLeft;
}

bool CollectorVolunteer:: decreaseCoolDown() {
    if(!isBusy()){
        return false;
    }
    timeLeft --;
    return (timeLeft==0);
}

bool  CollectorVolunteer:: hasOrdersLeft() const {
    return true;
}

bool CollectorVolunteer:: canTakeOrder(const Order &order) const  {
    return hasOrdersLeft() && (!isBusy());
}

void CollectorVolunteer:: acceptOrder(const Order &order) {
    if(canTakeOrder(order)){
        timeLeft = coolDown;
        activeOrderId = order.getId();
    }
}

void CollectorVolunteer:: setTimeLeft(int newTime) {
    timeLeft = newTime;
}

string CollectorVolunteer::toString() const {
    return "Collector Volunteer: ID=" + to_string(getId()) + ", Name=" + getName() + ", Cool Down=" + to_string(coolDown) +
           ", Time Left=" + to_string(timeLeft);
}

string CollectorVolunteer::getDetails() const{
    if(isBusy()){
        return "VolenteerID: "+to_string(getId())+"\n"+"isBusy: True\nOrderId: "+to_string(getActiveOrderId())
        +"\ntimeLeft: "+to_string(getTimeLeft())+"\nordersLeft: noLimit";
    } 
    else{
         return "VolenteerID: "+to_string(getId())+"\nisBusy: fasle\nOrderId: None\ntimeLeft: None\nordersLeft: noLimit";
    }
}

const int CollectorVolunteer::map() const {
    return 0;
}
    

void CollectorVolunteer::step(){
    if(decreaseCoolDown()){
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;}
    }
    
LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string &name, int coolDown,int maxOrders): CollectorVolunteer(id,name,coolDown), maxOrders(maxOrders), ordersLeft(maxOrders){};


LimitedCollectorVolunteer * LimitedCollectorVolunteer:: clone() const  {
    return new LimitedCollectorVolunteer(*this);
}

bool LimitedCollectorVolunteer:: hasOrdersLeft() const  {
    return (ordersLeft!=0);
}

bool LimitedCollectorVolunteer:: canTakeOrder(const Order &order) const {
     return hasOrdersLeft() && !isBusy();
}

void LimitedCollectorVolunteer:: acceptOrder(const Order &order) {
    CollectorVolunteer:: acceptOrder(order);
    ordersLeft --;
}

int LimitedCollectorVolunteer:: getMaxOrders() const{
    return maxOrders;
}

int LimitedCollectorVolunteer :: getNumOrdersLeft() const{
    return ordersLeft;
}

string LimitedCollectorVolunteer::toString() const {
    return "Limited Collector Volunteer: ID=" + to_string(getId()) + ", Name=" + getName() + ", Cool Down=" + to_string(getCoolDown()) +
           ", Max Orders=" + to_string(getMaxOrders()) + ", Orders Left=" + to_string(getNumOrdersLeft());
}

string LimitedCollectorVolunteer::getDetails() const{
     if(isBusy()){
        return "VolenteerID: "+to_string(getId())+"\n"+"isBusy: True\nOrderId: "+to_string(getActiveOrderId())
        +"\ntimeLeft: "+to_string(getTimeLeft())+"\nordersLeft: "+to_string(getNumOrdersLeft());
    } 
    else{
         return "VolenteerID: "+to_string(getId())+"\nisBusy: Fasle\nOrderId: None\ntimeLeft: None\nordersLeft: "+
         to_string(getNumOrdersLeft());
    }
}



 DriverVolunteer:: DriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep): Volunteer(id,name), maxDistance(maxDistance), distancePerStep(distancePerStep), distanceLeft(maxDistance){};


 DriverVolunteer * DriverVolunteer:: clone() const {
    return new DriverVolunteer(*this);
}
 
int DriverVolunteer:: getDistanceLeft() const {
    return distanceLeft;
}

 int DriverVolunteer:: getMaxDistance() const{
    return maxDistance;
 }

int DriverVolunteer:: getDistancePerStep() const{
    return distancePerStep;
}

bool DriverVolunteer:: decreaseDistanceLeft(){
    if(isBusy()){distanceLeft = distanceLeft - distancePerStep;}
    if(distanceLeft<=0){distanceLeft=0;}
    return distanceLeft == 0;
}

bool DriverVolunteer:: hasOrdersLeft() const {
    return true;
}


void DriverVolunteer:: acceptOrder(const Order &order) {
    if(canTakeOrder(order)){
        distanceLeft = order.getDistance();
        activeOrderId = order.getId();
    }
}

void DriverVolunteer:: setDistanceLeft(int newDistance) {
    distanceLeft = newDistance;
}

void DriverVolunteer::step(){
    if(decreaseDistanceLeft()){ 
        completedOrderId=activeOrderId;
        activeOrderId = NO_ORDER;
    }
}

string DriverVolunteer::toString() const {
    return "Driver Volunteer: ID=" + to_string(getId()) + ", Name=" + getName() + ", Max Distance=" + to_string(getMaxDistance()) +
           ", Distance Per Step=" + to_string(getDistancePerStep()) + ", Distance Left=" + to_string(getDistanceLeft());
}

bool DriverVolunteer:: canTakeOrder(const Order &order) const {
    return ((isBusy()==false) && (hasOrdersLeft()) && (order.getDistance()<=getMaxDistance()));
}


string DriverVolunteer::getDetails() const {
      if(isBusy()){
        return "VolenteerID: "+to_string(getId())+"\n"+"isBusy: True\nOrderId: "+to_string(getActiveOrderId())
        +"\ndistanceLeft: "+to_string(getDistanceLeft())+"\nordersLeft: noLimit";
    } 
    else{
         return "VolenteerID: "+to_string(getId())+"\nisBusy: Fasle\nOrderId: None\ndistanceLeft: None\nordersLeft: noLimit";
    }
}

const int DriverVolunteer::map() const{
    return 1;
}
    


LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep,int maxOrders): DriverVolunteer(id,name,maxDistance,distancePerStep), maxOrders(maxOrders), ordersLeft(maxOrders){};


LimitedDriverVolunteer* LimitedDriverVolunteer:: clone() const {
    return new LimitedDriverVolunteer(*this);
}

int LimitedDriverVolunteer:: getMaxOrders() const{
    return maxOrders;
}

 int LimitedDriverVolunteer:: getNumOrdersLeft() const{
    return ordersLeft;
 }

bool LimitedDriverVolunteer:: hasOrdersLeft() const {
    return (getNumOrdersLeft());
}

 bool LimitedDriverVolunteer:: canTakeOrder(const Order &order) const {
    return (!isBusy()) && (hasOrdersLeft()) && (order.getDistance()<=getMaxDistance());
 }

void LimitedDriverVolunteer:: acceptOrder(const Order &order) {
    DriverVolunteer:: acceptOrder(order);
    ordersLeft--;
    }

string LimitedDriverVolunteer::toString() const {
    return "Limited Driver Volunteer: ID=" + to_string(getId()) + ", Name=" + getName() + ", Max Distance=" + to_string(getMaxDistance()) +
           ", Distance Per Step=" + to_string(getDistancePerStep()) + ", Max Orders=" + to_string(getMaxOrders()) +
           ", Orders Left=" + to_string(getNumOrdersLeft());
}

string LimitedDriverVolunteer::getDetails() const {
      if(isBusy()){
        return "VolenteerID: "+to_string(getId())+"\n"+"isBusy: True\nOrderId: "+to_string(getActiveOrderId())
        +"\ndistanceLeft: "+to_string(getDistanceLeft())+"\nordersLeft: "+to_string(getNumOrdersLeft());
    } 
    else{
         return "VolenteerID: "+to_string(getId())+"\nisBusy: Fasle\nOrderId: None\ndistanceLeft: None \nordersLeft: "
         +to_string(getNumOrdersLeft());
    }

}
