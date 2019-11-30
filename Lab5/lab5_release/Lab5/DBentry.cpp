/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include"DBentry.h"
#include<iostream>

using namespace std;

DBentry::DBentry() {
    name = " ";
    IPaddress = 0;
    active = false;
}

DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active) {
    IPaddress = _IPaddress;
    name = _name;
    active = _active;
}

bool DBentry::getActive() const {
    return active;
}

unsigned int DBentry::getIPaddress() const {
    return IPaddress;
}

string DBentry::getName() const {
    return name;
}

ostream& operator<<(ostream& out, const DBentry& rhs) {
    string temp = rhs.active ? "active" : "inactive";
    out << rhs.name << " : " << rhs.IPaddress  << " : " << temp ;
    return out;
}

void DBentry::setActive(bool _active) {
    active = _active;
}

void DBentry::setIPaddress(unsigned int _IPaddress) {
    IPaddress = _IPaddress;
}

void DBentry::setName(string _name) {
    name = _name;
}

DBentry::~DBentry() {
    
}



