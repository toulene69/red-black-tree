//
//  RBTree.cpp
//  RedBlackTree
//
//  Created by Apoorv on 02/08/17.
//  Copyright © 2017 presonal. All rights reserved.
//

#include "RBTree.hpp"

void right_rotate(Node **,Node *);
void left_rotate(Node **,Node *);

Node leaf = {NIL,NIL,0,0,BLACK};

Node *get_new_node(int data)
{
    Node *node = (Node*) malloc(sizeof(Node));
    if (node) {
        node->data = data;
        node->lchild = NIL;
        node->rchild = NIL;
        node->color = RED;
        node->parent = NIL;
    }
    return node;
}
void insert_fixup(Node **root,Node *node)
{
    Node *cur = node;
    while (cur != *root && cur->parent->color == RED) {
        
        // case 1 : if sibling of parent cur is also red
        Node *parent = cur->parent;
        Node *grandParent = parent->parent;
        if (grandParent) {
            if ((parent == grandParent->lchild && grandParent->rchild->color == RED) || (parent == grandParent->rchild && grandParent->lchild->color == RED)) {
                parent->color = BLACK;
                grandParent->lchild->color = BLACK;
                grandParent->rchild->color = BLACK;
                grandParent->color = RED;
                cur = grandParent;
            }
            else if (parent == grandParent->lchild && cur == parent->lchild) {
                right_rotate(root,grandParent);
                parent->color = BLACK;
                grandParent->color = RED;
                cur = parent;
            }
            else if (parent == grandParent->rchild && cur == parent->rchild) {
                left_rotate(root,grandParent);
                parent->color = BLACK;
                grandParent->color = RED;
                cur = parent;
            }
            else if (parent == grandParent->lchild && cur == parent->rchild) {
                left_rotate(root, parent);
                right_rotate(root, grandParent);
                cur->color = BLACK;
                parent->color = RED;
                grandParent->color = RED;
            }
            else if (parent == grandParent->rchild && cur == parent->lchild) {
                right_rotate(root, parent);
                left_rotate(root, grandParent);
                cur->color = BLACK;
                parent->color = RED;
                grandParent->color = RED;
            }
        }
        
    }
    (*root)->color = BLACK;
}

Node *insert_node(Node **root, int data)
{
    Node *newNode = get_new_node(data);
    Node *curr = *root;
    Node *parent = 0;
    while (curr!=NIL) {
        parent = curr;
        if (curr->data == data) {
            return curr;
        }
        else if (curr->data > data) {
            curr = curr->lchild;
        }
        else {
            curr = curr->rchild;
        }
    }
    
    if (parent) {
        if (parent->data > data) {
            parent->lchild = newNode;
        }
        else {
            parent->rchild = newNode;
        }
        newNode->parent = parent;
    }
    else {
        *root = newNode;
    }
    
    insert_fixup(root,newNode);
    
    return newNode;
}

void delete_fixup(Node **root, Node *node)
{
    Node *x = node;
    while (x!= *root && x->color == BLACK) {
        Node *parent = x->parent;
        Node *sibling;
        if (x == parent->lchild) { // x is the left child
            sibling = parent->rchild;
            if (sibling->color == BLACK) { // sibling of x is black
                if (sibling->lchild->color == BLACK && sibling->rchild->color == BLACK) { // is both childs of sibling is black
                    sibling->color = RED;
                    x = x->parent;
                }
                else {
                    if (sibling->rchild->color == BLACK) { // right child of sibling is black
                        sibling->lchild->color = BLACK;
                        sibling->color = RED;
                        right_rotate(root, sibling);
                        sibling = x->parent->rchild;
                    }
                    // right child of sibling is red and right child is black
                    sibling->color = x->parent->color;
                    sibling->rchild->color = BLACK;
                    x->parent->color = BLACK;
                    left_rotate(root, x->parent);
                    x = *root;
                }
            }
            else { // sibling of x is red
                sibling->color = BLACK;
                x->parent->color = RED;
                left_rotate(root, x->parent);
                sibling = x->parent->rchild;
            }
        }
        else { // x is the right child (symmetric to above
            sibling = parent->lchild;
            if (sibling->color == BLACK) { // sibling of x is black
                if (sibling->lchild->color == BLACK && sibling->rchild->color == BLACK) {
                    sibling->color = RED;
                    x = x->parent;
                }
                else {
                    if (sibling->lchild->color == BLACK) { // sibling lchild is black
                        sibling->rchild->color = BLACK;
                        sibling->color = RED;
                        left_rotate(root, sibling);
                        sibling = x->parent->lchild;
                    }
                    //sibling lchild is red
                    sibling->color = x->parent->color;
                    sibling->lchild->color = BLACK;
                    right_rotate(root, x->parent);
                    x = *root;
                }
            }
            else { // sibling of x is red
                sibling->color = BLACK;
                x->parent->color = RED;
                right_rotate(root, x->parent);
                sibling = x->parent->lchild;
            }
        }
    }
    (*root)->color = BLACK;
    leaf.parent = NULL;
}

void delete_node(Node **root, int data)
{
    Node *y,*x;
    Node *z = search_item(*root, data);
    if (z==NIL) {
        return;
    }
    // if z has a childs as leafs
    if (z->lchild == NIL || z->rchild == NIL) {
        y = z;
    }
    else { // find successor
        y = z->rchild;
        while (y->lchild != NIL) {
            y = y->lchild;
        }
    }
    
    if (y->lchild!=NIL) {
        x = y->lchild;
    }
    else {
        x = y->rchild;
    }
    
    x->parent = y->parent;
    
    
    if (y->parent!=NIL) {
        if (y == y->parent->lchild) {
            y->parent->lchild = x;
        }
        else {
            y->parent->rchild = x;
        }
    }
    else { // y is root
        *root = x;
    }
    z->data = y->data;
    if (y->color == BLACK) {
        delete_fixup(root, x);
    }
    
    free(y);
}

Node * search_item(Node *root,int data)
{
    if(root== NIL)
    {
        return NIL;
    }
    if (root->data == data) {
        return root;
    }
    if (root->data > data) {
        return search_item(root->lchild, data);
    }
    else
    {
        return search_item(root->rchild, data);
    }
}
void right_rotate(Node **root,Node *x)
{
    Node *y = x->lchild;
    //fix x->lchild
    x->lchild = y->rchild;
    if (y->rchild!=NIL) {
        y->rchild->parent = x;
    }
    //fix y->parent
    if (y!=NIL) {
        y->parent = x->parent;
    }
    // fix child of parent of x
    if (x->parent!=NIL) {
        if (x == x->parent->rchild) {
            x->parent->rchild = y;
        }
        else {
            x->parent->lchild = y;
        }
    }
    else {
        *root = y;
    }
    //link x and y
    y->rchild = x;
    if (x!=NIL) {
        x->parent = y;
    }
}

void left_rotate(Node **root, Node *x)
{
    Node *y = x->rchild;
    // fix x->rchild
    x->rchild = y->lchild;
    if (y->lchild != NIL) {
        y->lchild->parent = x;
    }
    // fix y->parent
    if (y!=NIL) {
        y->parent = x->parent;
    }
    // fix child of x->parent
    if (x->parent!=NIL) {
        if (x== x->parent->rchild) {
            x->parent->rchild = y;
        }
        else
        {
            x->parent->lchild = y;
        }
    }
    else
    {
        *root = y;
    }
    //link x and y
    y->lchild = x;
    if (x!=NIL) {
        x->parent = y;
    }
}


int black_height_rb_tree(Node *node)
{
    if (node == NIL) {
        return 1;
    }
    else
    {
        int lheight = black_height_rb_tree(node->lchild);
        int rheight = black_height_rb_tree(node->rchild);
        if (lheight<0 || rheight <0) {
            return -1;
        }
        if (lheight!=rheight) {
            printf("Left height != Right height %d %d\n",lheight ,rheight);
            return -1;
        }
        if (node->color == RED) {
            return lheight;
        }
        else {
            return lheight+1;
        }
    }
}







