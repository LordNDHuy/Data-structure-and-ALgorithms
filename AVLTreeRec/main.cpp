#include "AVLTree.h"
template <class T>
void print(T &a){
    std::cout << a << "  ";
}
int main(){
    /*AVLTree<int> * test = new AVLTree<int>;
    int no[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    for(int i=0; i< 15;i++){
        test->insert(no[i]);
    }
    test->insert(no[6]);
    test->remove(no[8]);
    test->remove(no[12]);
    test->remove(no[13]);
    test->remove(no[2]);
    test->remove(no[10]);
    /*test->remove(no[7]);
    test->remove(no[4]);
    test->remove(no[5]);
    test->remove(no[3]);
    test->remove(no[2]);
    test->remove(no[1]);
    test->remove(no[8]);
    test->remove(no[9]);
    test->remove(no[13]);*/
    int no[11] = {10,5,8,7,12,1,0,2,8,9,6};
    AVLTree<int> * tree = new AVLTree<int>();
    tree->insert(no[0]);
    tree->insert(no[1]);
    tree->insert(no[2]);
    tree->insert(no[3]);
    tree->insert(no[4]);
    tree->insert(no[5]);
    tree->insert(no[6]);
    tree->insert(no[6]);
    tree->insert(no[7]);
    tree->insert(no[3]);
    tree->insert(no[8]);
    tree->insert(no[9]);
    tree->insert(no[9]);
    tree->insert(no[9]);
    tree->insert(no[9]);
    tree->insert(no[8]);
    tree->insert(no[9]);
    tree->insert(no[9]);
    tree->insert(no[9]);
    tree->insert(no[10]);
    tree->insert(no[10]);
    tree->insert(no[10]);
    tree->insert(no[10]);
    tree->insert(no[10]);

    tree->traverseLNR(&print);
    /*
    tree->remove(no[9]);
    tree->remove(no[9]);
    tree->remove(no[9]);       
    tree->remove(no[9]);
    tree->remove(no[9]);
    tree->remove(no[9]);
    tree->remove(no[9]);
    tree->remove(no[0]);
    tree->remove(no[4]);
    tree->remove(no[10]);
    tree->remove(no[10]);
    tree->remove(no[10]);
    tree->remove(no[10]);
    tree->remove(no[10]);
    tree->remove(no[8]);
    tree->remove(no[8]);
    tree->remove(no[8]);
    tree->remove(no[6]);
    tree->remove(no[6]);
    tree->remove(no[5]);
    tree->remove(no[7]);
    tree->remove(no[1]);
    tree->remove(no[3]);
    tree->remove(no[3]);
    tree->remove(no[8]);*/
    return 0;
}