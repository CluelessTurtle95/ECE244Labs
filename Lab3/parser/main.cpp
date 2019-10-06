//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

class Parser
{
    static stringstream lineStream;
    static string name,type;
    static int locx,locy,sizex,sizey,angle;
public:
    static void setStream(stringstream & lStream);
    static void maxShapes();
    static void create();
    static void move();
    static void rotate();
    static void draw();
    static void del();
};

int main() {

    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        Parser::setStream(lineStream);
        
        if(command == "maxShapes")
        {
            Parser::maxShapes();
        }
        else if( command == "create")
        {
            Parser::create();
        }
        else if( command == "move")
        {
            Parser::move();
        }
        else if( command == "rotate")
        {
            Parser::rotate();
        }
        else if( command == "draw")
        {
            Parser::draw();
        }
        else if( command == "delete")
        {
            Parser::del();
        }
        else
        {
            cout << "invalid command" << endl;
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
    }  // End input loop until EOF.
    
    return 0;
}

stringstream Parser::lineStream;
string Parser::name, Parser::type ;
int Parser::locx,Parser::locy,Parser::sizex,Parser::sizey, Parser::angle;

void Parser::setStream(stringstream & lStream)
{   
    locx = 0;
    locy = 0;
    sizex = 0;
    sizey = 0;
    angle = 0;
    name = "";
    type = "";
    lineStream << lStream.rdbuf();
}

void Parser::maxShapes()
{
    int temp;
    lineStream >> temp;
    //if (temp < 0 || lineStream.fail())
    //{
    //    cout << "invalid argument" << endl;
    //}
    //else
    {
        max_shapes = temp;
        cout << "New database:  max shapes is " << max_shapes << endl;
    }
    lineStream.clear();
    lineStream.str("");
}

void Parser::create()
{
    bool invArg = false;
    bool toofew = false;
    lineStream >> name >> type >> locx >> locy >> sizex >> sizey;
    if (lineStream.fail())
    {
        if(lineStream.eof())
        {
            toofew = true;
        }
        else
        {
            invArg = true;
        }
        //cout << "im here";
    }
    if (name == "ellipse" || name == "rectangle" || name == "triangle" || name == "maxShapes"
            || name == "create" || name == "move" || name == "rotate" || name == "draw" || name == "delete")
    {
        cout << "invalid shape name" << endl;
    }
    else if(type != "ellipse" & type != "rectangle" & type != "triangle")
    {
        cout << "invalid shape type" << endl;
    }
    else if(invArg)
    {
        cout << "invalid argument" << endl;
    }
    else if(toofew)
    {
        cout << "too few arguments" << endl;
    }
    else if (locx < 0 || locy < 0 || sizex < 0 || sizey < 0)
    {
        cout << "invalid value" << endl;
    }
    else
    {
        cout << "Created " << name << ": " << type << " " << locx << " " << locy << " " << sizex << " " << sizey << endl;
    }
    lineStream.clear();
    lineStream.str("");
}

void Parser::move()
{
    lineStream >> name >> locx >> locy;
    if (name == "ellipse" || name == "rectangle" || name == "triangle" || name == "maxShapes"
            || name == "create" || name == "move" || name == "rotate" || name == "draw" || name == "delete")
    {
        cout << "invalid shape name" << endl;
    }
    else if (locx < 0 || locy < 0)
        cout << "invalid value" << endl;
    cout << "Moved " << name << " to " << locx << " " << locy << endl;
    lineStream.str("");
}

void Parser::rotate()
{
    lineStream >> name >> angle;
    if (name == "ellipse" || name == "rectangle" || name == "triangle" || name == "maxShapes"
            || name == "create" || name == "move" || name == "rotate" || name == "draw" || name == "delete")
    {
        cout << "invalid shape name" << endl;
    }
    else if (angle < 0 || angle > 360)
    {
        cout << "invalid value" << endl;
    }
    else
    {
        cout << "Rotated " << name << " by " << angle << " degrees" << endl;
    }
    lineStream.str("");
}

void Parser::draw()
{
    lineStream >> name;
    if (name == "ellipse" || name == "rectangle" || name == "triangle" || name == "maxShapes"
            || name == "create" || name == "move" || name == "rotate" || name == "draw" || name == "delete")
    {
        cout << "invalid shape name" << endl;
    }
    if (name == "all")
    {
        cout << "Drew all shape" << endl;
    }
    else
    {
        cout << "Drew name: type loc loc size size" << endl;
    }
    lineStream.str("");
}

void Parser::del()
{
    lineStream >> name;
    if (name == "ellipse" || name == "rectangle" || name == "triangle" || name == "maxShapes"
            || name == "create" || name == "move" || name == "rotate" || name == "draw" || name == "delete")
    {
        cout << "invalid shape name" << endl;
    }
    if (name == "all")
    {
        cout << "Deleted: all shapes" << endl;
    }
    else
    {
        cout << "Deleted: name: type loc loc size size" << endl;
    }
}