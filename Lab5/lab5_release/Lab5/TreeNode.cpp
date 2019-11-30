/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TreeNode.h"

TreeNode::TreeNode(DBentry* _entryPtr) {
    entryPtr = _entryPtr;
    left = nullptr;
    right = nullptr;
}

DBentry* TreeNode::getEntry() const {
    return entryPtr;
}

TreeNode* TreeNode::getLeft() const {
    return left;
}

TreeNode* TreeNode::getRight() const {
    return right;
}

void TreeNode::setLeft(TreeNode* newLeft) {
    left = newLeft;
}

void TreeNode::setRight(TreeNode* newRight) {
    right = newRight;
}

TreeNode::~TreeNode() {
    delete entryPtr;
}