#include <iostream>
#include "AVLTree.h"
class LargerThan {
public:
    int operator()(int a, int b) {
        if(a>b) return 1;
        if(a<b) return -1;
        return 0;
    }
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    LargerThan l;
    AVLTree<int,int,LargerThan> tree(l);

    tree.insert(6,6);
    tree.insert(22,22);
    tree.insert(10,10);
    tree.insert(7,7);
    tree.insert(20,20);
    tree.insert(17,17);
    tree.insert(15,15);
    tree.insert(8,8);
    tree.insert(11,11);
    tree.insert(5,5);
    tree.insert(13,13);
    tree.insert(10,10);
    tree.insert(19,19);
    tree.insert(1,1);
    tree.insert(2,2);
    tree.insert(18,18);
    //InsertResult result=tree.insert(18,18);
    tree.remove(20);
    tree.remove(7);
    tree.remove(15);
    tree.printInOrder();
    tree.printPreOrder();
    return 0;
}