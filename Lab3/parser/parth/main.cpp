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

void initShape();
int addToDataBase(string name, string type , int xloc , int yloc , int xsz , int ysz);
int searchDatabase(string name);

class Parser
{
    static stringstream lineStream;
    static string name,type;
    static int locx,locy,sizex,sizey,angle;
    static bool invArg;
    static bool toofew;
    static bool toomany;

    static void checkArgs();
    static void resetArgs();
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
        
        //cout << "Entire Stream : " ;
        //if(!lineStream.eof())
        //    cout << lineStream.rdbuf() << endl;
        //else
        //    cout << endl;
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
            cout << "Error: invalid command" << endl;
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
bool Parser::invArg = false,  Parser::toofew = false, Parser::toomany = false;

void Parser::resetArgs()
{
    invArg = false;
    toofew = false;
    toomany = false;
}

void Parser::checkArgs()
{
    resetArgs();
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
    }
    else if(lineStream.peek() == '.')
    {
        invArg = true;
    }
    {
        string temp;
        lineStream >> temp;
        toomany = !lineStream.fail(); 
    }   
}

void Parser::setStream(stringstream & lStream)
{   
    locx = 0;
    locy = 0;
    sizex = 0;
    sizey = 0;
    angle = 0;
    name = "";
    type = "";
    lineStream.str("");
    resetArgs();
    lineStream << lStream.rdbuf();
    lineStream.clear();
//    cout << "Entire Stream : " ;
//    if(!lineStream.eof())
//        cout << lStream.rdbuf() << endl;
//    else
//        cout << endl;
}

void Parser::maxShapes()
{
    int temp;
    lineStream >> temp;
    {
        max_shapes = temp;
        initShape();
        cout << "New database:  max shapes is " << max_shapes << endl;
    }
    lineStream.clear();
    lineStream.str("");
}

void Parser::create()
{
    //cout << "Entire Stream : " << lineStream.rdbuf() << endl;
    lineStream >> name >> type >> locx >> locy >> sizex >> sizey;
    checkArgs();

    if (name == "ellipse" || name == "rectangle" || name == "triangle" || name == "maxShapes"
            || name == "create" || name == "move" || name == "rotate" || name == "draw" || name == "delete")
    {
        cout << "Error: invalid shape name" << endl;
    }
    else if(name == "")
    {
        //cout << "im here";
        cout << "Error: too few arguments" << endl;
    }
    else if( (type != "ellipse") & (type != "rectangle") & (type != "triangle") )
    {
        if(type == "")
        {
            cout << "Error: too few arguments" << endl;
        }
        else
            cout << "Error: invalid shape type" << endl;
    }
    else if(invArg)
    {
        cout << "Error: invalid argument" << endl;
    }
    else if(toofew)
    {
        cout << "Error: too few arguments" << endl;
    }
    else if(toomany)
    {
        cout << "Error: too many arguments" << endl;
    }
    else if (locx < 0 || locy < 0 || sizex < 0 || sizey < 0)
    {
        cout << "Error: invalid value" << endl;
    }
    else
    {
        if (searchDatabase(name) != -1)
        {
            cout << "Error: shape name exists" << endl;
        }
        else if(addToDataBase(name,type,locx,locy,sizex,sizey) == -1)
        {
            cout << "Error: shape array is full" << endl;
        }
        else
        {
            cout << "Created " << name << ": " << type << " " << locx << " " << locy << " " << sizex << " " << sizey << endl;
        }
    }

    lineStream.clear();
    lineStream.str("");
}

void Parser::move()
{
    lineStream >> name >> locx >> locy;
    checkArgs();

    if (name == "ellipse" || name == "rectangle" || name == "triangle" || name == "maxShapes"
            || name == "create" || name == "move" || name == "rotate" || name == "draw" || name == "delete")
    {
        cout << "Error: invalid shape name" << endl;
    }
    else if(name == "")
    {
        cout << "Error: too few arguments" << endl;
    }
    else if (locx < 0 || locy < 0)
    {
        cout << "Error: invalid value" << endl;
    }
    else
    {
        int tempInt = searchDatabase(name);
        if (tempInt == -1)
        {
            cout << "Error: shape " << name << " not found" << endl;
        }
        else if(invArg)
        {
            cout << "Error: invalid argument" << endl;
        }
        else if(toofew)
        {
            cout << "Error: too few arguments" << endl;
        }
        else if(toomany)
        {
            cout << "Error: too many arguments" << endl;
        }
        else
        {
            shape * temp = shapesArray[tempInt];
            temp->setXlocation(locx);
            temp->setYlocation(locy);
            cout << "Moved " << name << " to " << locx << " " << locy << endl;   
        }
    }
    lineStream.clear();
    lineStream.str("");
}

void Parser::rotate()
{
    lineStream >> name >> angle;
    checkArgs();

    if (name == "ellipse" || name == "rectangle" || name == "triangle" || name == "maxShapes"
            || name == "create" || name == "move" || name == "rotate" || name == "draw" || name == "delete")
    {
        cout << "invalid shape name" << endl;
    }
    else if(name == "")
    {
        cout << "Error: too few arguments" << endl;
    }
    else if (angle < 0 || angle > 360)
    {
        cout << "Error: invalid value" << endl;
    }
    else
    {
        int tempInt = searchDatabase(name);
        if (tempInt == -1)
        {
            cout << "Error: shape " << name << " not found" << endl;
        }
            else if(invArg)
        {
            cout << "Error: invalid argument" << endl;
        }
        else if(toofew)
        {
            cout << "Error: too few arguments" << endl;
        }
        else if(toomany)
        {
            cout << "Error: too many arguments" << endl;
        }
        else
        {
            shape * temp = shapesArray[tempInt];
            temp->setRotate(angle);
            cout << "Rotated " << name << " by " << angle << " degrees" << endl;
        }
    }

    lineStream.clear();
    lineStream.str("");
}

void Parser::draw()
{
    lineStream >> name;
    checkArgs();

    if (name == "ellipse" || name == "rectangle" || name == "triangle" || name == "maxShapes"
            || name == "create" || name == "move" || name == "rotate" || name == "draw" || name == "delete")
    {
        cout << "Error: invalid shape name" << endl;
    }
    else if(name == "")
    {
        cout << "Error: too few arguments" << endl;
    }
    else if (name == "all")
    {
        if(invArg)
        {
            cout << "Error: invalid argument" << endl;
        }
        else if(toofew)
        {
            cout << "Error: too few arguments" << endl;
        }
        else if(toomany)
        {
            cout << "Error: too many arguments" << endl;
        }
        else
        {
            cout << "Drew all shapes" << endl;
            for (int i = 0; i < max_shapes; i++)
            {
                if(shapesArray[i] == nullptr)
                    continue;
                shapesArray[i]->draw();
            }
        }
    }
    else
    {
        int tempInt = searchDatabase(name);
        if (tempInt == -1)
        {
            cout << "Error: shape " << name << " not found" << endl;
        }
        else if(invArg)
        {
            cout << "Error: invalid argument" << endl;
        }
        else if(toofew)
        {
            cout << "Error: too few arguments" << endl;
        }
        else if(toomany)
        {
            cout << "Error: too many arguments" << endl;
        }
        else
        {
            shape * temp = shapesArray[tempInt];
            cout << "Drew " << name << endl;
            temp->draw();
        }
    }

    lineStream.clear();
    lineStream.str("");
}

void Parser::del()
{
    lineStream >> name;
    checkArgs();

    if (name == "ellipse" || name == "rectangle" || name == "triangle" || name == "maxShapes"
            || name == "create" || name == "move" || name == "rotate" || name == "draw" || name == "delete")
    {
        cout << "Error: invalid shape name" << endl;
    }
    else if(name == "")
    {
        cout << "Error: too few arguments" << endl;
    }
    else if (name == "all")
    {
        if(invArg)
        {
            cout << "Error: invalid argument" << endl;
        }
        else if(toofew)
        {
            cout << "Error: too few arguments" << endl;
        }
        else if(toomany)
        {
            cout << "Error: too many arguments" << endl;
        }
        else
        {
            cout << "Deleted: all shapes" << endl;
            for (int i = 0; i < max_shapes; i++)
            {
                if(shapesArray[i] == nullptr)
                    continue;
                delete shapesArray[i];
                shapesArray[i] = nullptr;
            }
        }
    }
    else
    {
        int tempInt = searchDatabase(name);
        if (tempInt == -1)
        {
            cout << "Error: shape " << name << " not found" << endl;
        }
        else if(invArg)
        {
            cout << "Error: invalid argument" << endl;
        }
        else if(toofew)
        {
            cout << "Error: too few arguments" << endl;
        }
        else if(toomany)
        {
            cout << "Error: too many arguments" << endl;
        }
        else
        {
            cout << "Deleted shape " << name << endl;
            delete shapesArray[tempInt];
            shapesArray[tempInt] = nullptr;
        }
    }
    lineStream.clear();
    lineStream.str("");
}

void initShape()
{
    shapesArray = new shape* [max_shapes];
    for (int i = 0; i < max_shapes; i++)
    {
        shapesArray[i] = nullptr;
    }
}

int searchDatabase(string name)
{
    //shapesArray;
    for (int i = 0; i < max_shapes; i++)
    {
        if(shapesArray[i] == nullptr)
            continue;
        if (shapesArray[i]->getName() == name)
        {
            return i;
        }
    }
    return -1;
}

int addToDataBase(string name, string type , int xloc , int yloc , int xsz , int ysz)
{
    shape * temp = new shape(name, type , xloc , yloc , xsz , ysz);
    if (shapeCount < max_shapes)
    {
        shapesArray[shapeCount] = temp;
        shapeCount++;
        return 0;
    }
    return -1;
}