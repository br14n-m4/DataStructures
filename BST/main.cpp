#include <iostream>
#include "_bst.h"

int main() {
    bstree<int> A;
    int a[] {10, 9, 12, 8, 11, 13};

    for (int i: a)
        A.insert(i);
    A.print_inorder();
    std::cout << "root: " <<A.root->info;
    std::cout << "\n" <<A.leaftcount() <<"\n";


    return 0;
}
