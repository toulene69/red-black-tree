//
//  RBTree.hpp
//  RedBlackTree
//
//  Created by Apoorv on 02/08/17.
//  Copyright © 2017 presonal. All rights reserved.
//

#ifndef RBTree_hpp
#define RBTree_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
#define NIL &leaf

typedef enum {RED=0,BLACK=1} COLOR;

typedef struct Node_
{
    struct Node_ *lchild;
    struct Node_ *rchild;
    struct Node_ *parent;
    int data;
    COLOR color;
}Node;

typedef struct {
    Node *root;
} RBTree;

extern Node leaf; 

Node *insert_node(Node **root, int data);

void delete_node(Node **root, int data);

int black_height_rb_tree(Node *);

Node * search_item(Node *root,int data);

#endif /* RBTree_hpp */
