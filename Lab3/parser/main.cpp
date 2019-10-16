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
bool checkValidCommand(string command);
bool checkValidName(string name);
shape* searchShape(string name);
int searchShapeIndex(string name);
bool checkValidType(string type);
bool checkValidValue(int value);
void maxShapes(stringstream& lineStream);
void create(stringstream& lineStream);
void move(stringstream& lineStream);
void rotate(stringstream& lineStream);
bool checkForAll(string allCheck);
void draw(stringstream& lineStream);
void deleteShape(stringstream& lineStream);
bool checkIfEmpty(stringstream& lineStream);
//void cleanStreamForSpaces(stringstream& lineStream);

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
        
        //first we check if the command entered is valid
        if (checkValidCommand(command)){
            //after checking the command validity we call the corresponding
            //function responsible for the desired action
            if (command==keyWordsList[1]){
                maxShapes(lineStream);
            }
            if (command==keyWordsList[2]){
                create(lineStream);
            }
            if (command==keyWordsList[3]){
                move(lineStream);
            }
            if (command==keyWordsList[4]){
                rotate(lineStream);
            }
            if (command==keyWordsList[5]){
                draw(lineStream);
            }
            if (command==keyWordsList[6]){
                deleteShape(lineStream);
            }
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
    }  // End input loop until EOF.
    
    return 0;
}

//function charged with checking the validity of the inputted command
bool checkValidCommand(string command){
    for (int i=1;i<7;i++){
        if (command==keyWordsList[i]){
            return true;
        }
    }
    cout<<"Error: invalid command"<<endl;
    return false;
}

//function charged with identifying validity of the name of a shape
bool checkValidName(string name){
    for (int i=0;i<7;i++){
        if (name==keyWordsList[i]){
            cout<<"Error: invalid shape name"<<endl;
            return false;
        }
    }
    for (int j=0;j<3;j++){
        if (name==shapeTypesList[j]){
            cout<<"Error: invalid shape name"<<endl;
            return false;
        }
    }
    for (int k=0;k<shapeCount;k++){
        if (shapesArray[k]->getName()==name){
            cout<<"Error: shape name exists"<<endl;
            return false;
        }
    }
    return true;
}

//function searching for the address of a particular created shape
shape* searchShape(string name){
    for (int k=0;k<shapeCount;k++){
        if (shapesArray[k]->getName()==name){
            return shapesArray[k];
        }
    }
    cout<<"Error: shape "<<name<<" not found"<<endl;
    return NULL;
}

//function searching for the index of a particular created shape in the array
int searchShapeIndex(string name){
    for (int k=0;k<shapeCount;k++){
        if (shapesArray[k]->getName()==name){
            return k;
        }
    }
    return -1;
}

//function charged with checking if the type is correct
bool checkValidType(string type){
    for (int j=0;j<3;j++){
        if (type==shapeTypesList[j]){
            return true;
        }
    }
    cout<<"Error: invalid shape type"<<endl;
    return false;
}

//function charged with checking if a value is acceptable
bool checkValidValue(int value){
    if (value<0){
        cout<<"Error: invalid value"<<endl;
        return false;
    }
    return true;
}

//function setting the size of the array
void maxShapes(stringstream& lineStream){
    int value;
    
    if (lineStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return;
    }
    
    lineStream>>value;
    
    if (checkValidValue(value)){
//        cleanStreamForSpaces(lineStream);
        if(!checkIfEmpty(lineStream)){
            cout<<"Error: too many arguments"<<endl;
            return;
        }
        
        cout<<"New database: max shapes is "<<value<<endl;
        max_shapes=value;
        shapesArray = new shape*[max_shapes];
    } 
}

//void cleanStreamForSpaces(stringstream& lineStream)
//{
//    char dummy;
//    while (lineStream.peek() == ' '){
//        lineStream >> dummy;
//    }
//   
////    if (!lineStream.eof()){
////        return false;
////    }
////    return true;
//}

//function charged with checking if string is empty
bool checkIfEmpty(stringstream& lineStream){
    string dummy;
    lineStream>>dummy;
    
    if (dummy.empty()){
        return true;
    }else{
        return false;
    }
}

//function charged with creating a new shape and updating the array
void create(stringstream& lineStream){
    string name;
    string type;
    int locx,locy,sizex,sizey;
    
    //checking if array is full
    if(shapeCount==max_shapes){
        cout<<"Error: shape array full"<<endl; 
        return;
    }
    
    if (lineStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return;
    }
    
    lineStream>>name;
    
    //checking for valid name
    if (checkValidName(name)){
        if (lineStream.eof()){
            cout<<"Error: too few arguments"<<endl;
            return;
        }
        
        lineStream>>type;
        
        //checking for valid type
        if (checkValidType(type)){
            if (lineStream.eof()){
                cout<<"Error: too few arguments"<<endl;
                return;
            }
            
            lineStream>>locx;
            
            if (!checkValidValue(locx)){
                return;
            }
            
            if (lineStream.eof()){
                cout<<"Error: too few arguments"<<endl;
                return;
            }
            
            if (lineStream.fail()){
                cout<<"Error: invalid argument"<<endl;
                return;
            }
            
            lineStream>>locy;
            
            if (!checkValidValue(locy)){
                return;
            }
            
            if (lineStream.eof()){
                cout<<"Error: too few arguments"<<endl;
                return;
            }
            
            if (lineStream.fail()){
                cout<<"Error: invalid argument"<<endl;
                return;
            }
            
            lineStream>>sizex;
            
            if (!checkValidValue(sizex)){
                return;
            }
            
            if (lineStream.eof()){
                cout<<"Error: too few arguments"<<endl;
                return;
            }
            
            if (lineStream.fail()){
                cout<<"Error: invalid argument"<<endl;
                return;
            }   
                
            lineStream>>sizey;
           //bug with 1 1 1" "
            if (!checkValidValue(sizey)){
                return;
            }
            
            if (lineStream.fail()){
                cout<<"Error: invalid argument"<<endl;
                return;
            }
//            cleanStreamForSpaces(lineStream);
            if (!checkIfEmpty(lineStream)){
                cout<<"Error: too many arguments"<<endl;
                return;
            }
            
            cout<<"Created "<<name<<": "<<type<<" "<<locx<<" "<<locy<<" "
                <<sizex<<" "<<sizey<<endl;
            shapesArray[shapeCount]=new shape(name,type,locx,locy,sizex,sizey);
            shapeCount++;
        }
    }
}

//function charged with moving an existing shape to a new position
void move(stringstream& lineStream){
    string name;
    int locx,locy;
    
    if (lineStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return;
    }
    
    lineStream>>name;
    
    shape* currentShape=searchShape(name);
    
    if (currentShape==NULL){
        return;
    }
    
    if (lineStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return;
    }
    
    lineStream>>locx;
    
    if (!checkValidValue(locx)){
        return;
    }
    
    if (lineStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return;
    }
    
    if (lineStream.fail()){
        cout<<"Error: invalid argument"<<endl;
        return;
    }
    
    lineStream>>locy;
    
    if (!checkValidValue(locy)){
        return;
    }
    
//    if (lineStream.eof()){
//        cout<<"Error: too few arguments"<<endl;
//        return;
//    }
    if (lineStream.fail()){
        cout<<"Error: invalid argument"<<endl;
        return;
    }
//    cleanStreamForSpaces(lineStream);
    if (!checkIfEmpty(lineStream)){
        cout<<"Error: too many arguments"<<endl;
        return;
    }
    
    currentShape->setXlocation(locx);
    currentShape->setYlocation(locy);
    cout<<"Moved "<<name<<" to "<<locx<<" "<<locy<<endl;
}

//function charged with rotating an existing shape
void rotate(stringstream& lineStream){
    string name;
    int angle;
    
    if (lineStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return;
    }
    
    lineStream>>name;
    shape* currentShape=searchShape(name);
    
    if (currentShape==NULL){
        return;
    }
    
    if (lineStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return;
    }
    
    lineStream>>angle;
    
//    if (lineStream.eof()){
//        cout<<"Error: too few arguments"<<endl;
//        return;
//    }
    if (lineStream.fail()){
        cout<<"Error: invalid argument"<<endl;
        return;
    }
    
    if (angle<=0||angle>=360){
        cout<<"Error: invalid value"<<endl;
        return;
    }
//    cleanStreamForSpaces(lineStream);
    
    if (!checkIfEmpty(lineStream)){
        cout<<"Error: too many arguments"<<endl;
        return;
    }
    
    currentShape->setRotate(angle);
    cout<<"Rotated "<<name<<" by "<<angle<<" degrees"<<endl;
}

//function charged with check for the word all in the command
bool checkForAll(string allCheck){
    if (allCheck==keyWordsList[0]){
        return true;
    }
    return false;
}

//function charged with drawing either a shape or all of them
void draw(stringstream& lineStream){
    
    if (lineStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return;
    }
    
    string nextArgument;
    lineStream>>nextArgument;
    
    if (checkForAll(nextArgument)){
//        cleanStreamForSpaces(lineStream);
        if (!checkIfEmpty(lineStream)){
            cout<<"Error: too many arguments"<<endl;
            return;
        }
    
        cout<<"Drew all shapes"<<endl;
        
        for (int i=0;i<shapeCount;i++){
            shapesArray[i]->draw();
        }
    }else{
        string name;
        name=nextArgument;
        shape* currentShape=searchShape(name);
        
        if (currentShape==NULL){
            return;
        }
//        cleanStreamForSpaces(lineStream);
        if (!checkIfEmpty(lineStream)){
            cout<<"Error: too many arguments"<<endl;
            return;
        }
        
        cout<<"Drew "<<name<<endl;
        currentShape->draw();
    }
}

//function charged with deleting either a particular shape or all of them
//and updating the array
//error if create after deleting same 
void deleteShape(stringstream& lineStream){
    if (lineStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return;
    }
    string nextArgument;
    lineStream>>nextArgument;
    if (checkForAll(nextArgument)){
//        cleanStreamForSpaces(lineStream);
        if (!checkIfEmpty(lineStream)){
            cout<<"Error: too many arguments"<<endl;
            return;
        }
        for (int i=0;i<shapeCount;i++){
            delete shapesArray[i];
            shapesArray[i]=NULL;
        }
        shapeCount=0;
        cout<<"Deleted: all shapes"<<endl;
    }else{
        string name;
        name=nextArgument;
        shape* currentShape=searchShape(name);
        int index=searchShapeIndex(name);
        if (currentShape==NULL){
            return;
        }
        if (index==-1){
            return;
        }
//        cleanStreamForSpaces(lineStream);
        if (!checkIfEmpty(lineStream)){
            cout<<"Error: too many arguments"<<endl;
            return;
        }
        delete shapesArray[index];
        shapesArray[index]=NULL;
        delete currentShape;
        currentShape=NULL;
        cout<<"Deleted shape "<<name<<endl;
    }
}