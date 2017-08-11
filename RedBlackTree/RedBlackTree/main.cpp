//
//  main.cpp
//  RedBlackTree
//
//  Created by Apoorv on 02/08/17.
//  Copyright © 2017 presonal. All rights reserved.
//

#include <iostream>
#include "RBTree.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Node *root = NIL;
    insert_node(&root, 100);
    cout<<black_height_rb_tree(root)<<endl;
    insert_node(&root, 90);
    cout<<black_height_rb_tree(root)<<endl;
    insert_node(&root, 80);
    cout<<black_height_rb_tree(root)<<endl;
    insert_node(&root, 70);
    cout<<black_height_rb_tree(root)<<endl;
    insert_node(&root, 60);
    cout<<black_height_rb_tree(root)<<endl;
    insert_node(&root, 50);
    cout<<black_height_rb_tree(root)<<endl;
    insert_node(&root, 40);
    cout<<black_height_rb_tree(root)<<endl;
    insert_node(&root, 30);
    cout<<black_height_rb_tree(root)<<endl;
    insert_node(&root, 20);
    cout<<black_height_rb_tree(root)<<endl;
    insert_node(&root, 10);
    cout<<black_height_rb_tree(root)<<endl;
    delete_node(&root, 50);
    cout<<black_height_rb_tree(root)<<endl;
    return 0;
}
