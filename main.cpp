#include <iostream>


#include "tree_splay.h"
#include "node_tree.h"
#include "test_tree.h"


int main(){
    srand(time(NULL));

    TreeSplay<int, int> t;
    t.insert(2,2);
    std::cout<<"1)\t -------\n";
    t.writeOut();
    t.insert(4,4);
    std::cout<<"2)\t -------\n";
    t.writeOut();
    t.insert(0,0);
    std::cout<<"3)\t -------\n";
    t.writeOut();
    t.insert(3,3);
    std::cout<<"4)\t -------\n";
    t.writeOut();
    t.insert(5,5);
    t.insert(6,6);
    t.insert(-1,-1);

    t.writeOut();
    t.search(4);
    t.writeOut();
    return 0;
}