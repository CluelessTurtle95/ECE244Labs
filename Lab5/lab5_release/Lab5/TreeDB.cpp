/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TreeDB.h"
#include<iostream>

using namespace std;

TreeDB::TreeDB() {
    root = nullptr;
    probesCount = 0;
}

bool TreeDB::insert(DBentry* newEntry) {
    TreeNode * newNode = new TreeNode(newEntry);
    if(root == nullptr)
    {
        root = newNode;
        return true;
    }
    else         
        if(insert(newNode, root))
        {
            return true;
        }
        else
        {
            delete newNode;
            return false;
        }
}

bool TreeDB::insert(TreeNode* newNode, TreeNode* parent) {
    if(newNode->getEntry()->getName() < parent->getEntry()->getName())
    {
        if(parent->getLeft() != nullptr)
            return insert(newNode, parent->getLeft());
        else
        {
            parent->setLeft(newNode);
            return true;
        }
    }
    else if(newNode->getEntry()->getName() > parent->getEntry()->getName())
    {
        if(parent->getRight() != nullptr)
            return insert(newNode, parent->getRight());
        else
        {
            parent->setRight(newNode);
            return true;
        }
    }
    else
        return false;
}

DBentry* TreeDB::find(string name) {
    probesCount = 0;
    if(root != nullptr)
        return find(name, root);
    else 
        return nullptr;
}

DBentry* TreeDB::find(string name, TreeNode* parent) {
    probesCount++;
    if(parent == nullptr)
        return nullptr;
    if(name < parent->getEntry()->getName())
    {
        if(parent->getLeft() != nullptr)
            return find(name, parent->getLeft());
        else
        {
            return nullptr;
        }
    }
    else if(name > parent->getEntry()->getName())
    {
        if(parent->getRight() != nullptr)
            return find(name, parent->getRight());
        else
        {
            return nullptr;
        }
    }
    else
        return parent->getEntry();
}

void TreeDB::printProbes() const {
    cout << probesCount << endl;
}

TreeDB::~TreeDB() {
    clear();
}

void TreeDB::clear() {
    if(root == nullptr)
        return;
    clear(root);
    root = nullptr;
}

void TreeDB::clear(TreeNode * parent) {
    if(parent->getLeft() != nullptr)
        clear(parent->getLeft());
    if(parent->getRight() != nullptr)
        clear(parent->getRight());
    delete parent;
}

void TreeDB::countActive() const {
    int z = 0;
    if(root != nullptr)
        countActive(z, root);
    cout <<  z << endl;
}

void TreeDB::countActive(int &num, const TreeNode * parent) const {
    num += parent->getEntry()->getActive();
    if(parent->getLeft() != nullptr)
    {
        countActive(num, parent->getLeft());
    }
    if(parent->getRight() != nullptr)
    {
        countActive(num, parent->getRight());
    }
}

bool TreeDB::remove(string name) {
    if(root != nullptr)
        return remove(name, root, nullptr);
    else 
        return false;
}

bool findAndSet(TreeNode * parent, TreeNode * node, TreeNode * newNode)
{
    if(parent->getLeft() == node)
    {
        parent->setLeft(newNode);
        return true;
    }
    else if(parent->getRight() == node)
    {
        parent->setRight(newNode);
        return true;
    }
    else
        return false;
}

TreeNode * findMax(TreeNode * node, bool removeNode)
{
    if(node->getRight() != nullptr)
    {
        TreeNode * temp = node->getRight();
        if(node->getRight()->getRight() == nullptr)
        {
            // Node is second last
            if(removeNode)
                node->setRight(nullptr);
        }
        return findMax(temp, removeNode);
    }
    else
        return node;
}

bool TreeDB::remove(string name, TreeNode* parent, TreeNode * prev_parent) {
    // If match remove else find
    if(name == parent->getEntry()->getName())
    {
        // remove
        if(parent->getLeft() == nullptr && parent->getRight() == nullptr)
        {
            // Leaf Case
            if(prev_parent != nullptr)
                findAndSet(prev_parent, parent, nullptr);
            else
                root = nullptr;
            delete parent;
            
        }
        else if(parent->getLeft() == nullptr || parent->getRight() == nullptr)
        {
            TreeNode * nextNode = (parent->getLeft() == nullptr) ? parent->getRight() : parent->getLeft() ;
            // Single Node Case
            if(prev_parent != nullptr)
                findAndSet(prev_parent, parent, nextNode);
            else
                root = nextNode;
            delete parent;
        }
        else
        {
            // Double Node Case
            // Find Max Node Left
            TreeNode * maxLeft = findMax(parent->getLeft(), true);
            // Replace
            if(parent->getRight() != maxLeft)
                maxLeft->setRight(parent->getRight());
            else
            {
                maxLeft->setRight(nullptr);
            }
            if(parent->getLeft() != maxLeft)
                maxLeft->setLeft(parent->getLeft());
            else
            {
                maxLeft->setLeft(nullptr);
            }
            
            if(prev_parent != nullptr)
                findAndSet(prev_parent,parent,maxLeft);
            else
                root = maxLeft;
            // Delete
            delete parent;
        }
        //after remove
        return true;
    }
    else
    {
        // find
        if(name < parent->getEntry()->getName())
        {
            if(parent->getLeft() != nullptr)
                return remove(name, parent->getLeft(), parent);
            else
                return false;
        }
        else
        {
            if(parent->getRight() != nullptr)
                return remove(name, parent->getRight(), parent);
            else
                return false;
        }
    }
}

ostream& operator<< (ostream& out, const TreeDB& rhs)
{
    if(rhs.root == nullptr)
    {
        return out;
    }
    TreeDB rightTree = TreeDB();
    rightTree.root = rhs.root->getRight();
    TreeDB leftTree = TreeDB();
    leftTree.root = rhs.root->getLeft();
    
    out << leftTree;
    out << rhs.root << endl;
    out << rightTree;
    
    leftTree.root = nullptr;
    rightTree.root = nullptr;
    return out;
}

ostream& operator<<(ostream& out, TreeNode* rhs)
{
    out << *rhs->getEntry();
    return out;
}