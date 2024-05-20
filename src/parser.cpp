#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include "../include/WareHouse.h"
using namespace std;

void WareHouse::parse(const string &configFilePath){
    ifstream inputFile;
    inputFile.open(configFilePath);
    string line, objType, name, type;
    int i1, i2, i3;

    while(getline(inputFile, line)){
        std::istringstream iss(line);
        iss >> objType;
        if(objType=="customer"){
            iss >> name >> type >> i1 >> i2;
            if(type == "soldier"){
                Customer *c = new SoldierCustomer(getCustomerCounter(), name, i1, i2);
                insertCustomer(c);
            }
            else{
                Customer *c = new CivilianCustomer(getCustomerCounter(), name, i1, i2);
                insertCustomer(c);
            }
        }
        else if(objType=="volunteer"){
            iss >> name >> type >> i1;
            if(type=="collector"){
                    CollectorVolunteer *v = new CollectorVolunteer(
                    getVolunteerCounter(), name, i1);
                    addVolunteer(v);
            }
            else if(type=="limited_collector"){
               iss >> i2;
               LimitedCollectorVolunteer *v = new LimitedCollectorVolunteer(
               getVolunteerCounter(), name, i1, i2);
               addVolunteer(v);
            }
            else if(type=="driver"){
                iss >> i2;
                DriverVolunteer *v = new DriverVolunteer
                (getVolunteerCounter(), name, i1, i2);
                addVolunteer(v);
            }
            else{
                iss >> i2;
                iss >> i3;
                LimitedDriverVolunteer *v = new LimitedDriverVolunteer
                (getVolunteerCounter(), name, i1, i2, i3);
                addVolunteer(v);
                }
            }
            objType="";
        }
    inputFile.close();
}




