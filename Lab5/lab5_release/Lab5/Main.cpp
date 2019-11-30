/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: sindhupa
 *
 * Created on November 25, 2019, 5:35 PM
 */

#include <iostream>
#include<sstream>
#include "TreeDB.h"
#include<string>
using namespace std;

/*
 * 
 */
int main() {
    string line;
    string command;
    TreeDB myDB;
    
    cout << "> ";
    getline(cin, line);
    
    string name;
    unsigned int IPaddress;
    bool status;
    string stat;
    
    while(!cin.eof())
    {
        stringstream linestream(line);
        linestream >> command;
        if(command == "insert")
        {
            linestream >> name >> IPaddress >> stat;
            status = (stat == "active");
            DBentry * newEntry = new DBentry(name, IPaddress, status);
            if(myDB.insert(newEntry))
            {
                cout << "Success" << endl;
            }
            else
                cout << "Error: entry already exists" << endl;
        }
        else if(command == "find")
        {
            linestream >> name;
            DBentry * temp =  myDB.find(name);
            if(temp == nullptr)
                cout << "Error: entry does not exist" << endl;
            else
                cout << *temp << endl;
        }
        else if(command == "remove")
        {
            linestream >> name;
            if(myDB.remove(name))
            {
                cout << "Success" << endl;
            }
            else
            {
                cout << "Error: entry does not exist" << endl;
            }
        }
        else if(command == "printall")
        {
            cout << myDB ;
        }
        else if(command == "printprobes")
        {
            linestream >> name;
            if( myDB.find(name) == nullptr)
            {
                cout << "Error: entry does not exist" << endl;
            }
            else
            {
                myDB.printProbes();
            }
        }
        else if(command == "removeall")
        {
            myDB.clear();
            cout << "Success" << endl;
        }
        else if(command == "countactive")
        {
            myDB.countActive();
        }
        else if(command == "updatestatus")
        {
            linestream >> name >> stat;
            status = (stat == "active");
            DBentry * temp = myDB.find(name);
            if(temp != nullptr)
            {
                temp->setActive(status);
                cout << "Success" << endl;
            }
            else
                cout << "Error: entry does not exist" << endl;
        }
        // Prompt
        cout << "> ";
        getline(cin, line);
    }
    
    return 0;
}

