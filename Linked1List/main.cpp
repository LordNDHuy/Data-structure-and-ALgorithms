#include <iostream>
#include "Linked1List.h"
using namespace std;

int main(){
    L1List<int> * test = new L1List<int>();
    int no[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    for(int i = 0; i< 15; i++){
        test->insertHead(no[i]);
    }
    
    for(int i = 0;i< 15;i++){
        std::cout << test->at(i)<< " ";
    }
        std::cout <<(*test)[0];

    L1List<int> * clone = new L1List<int>();
    test->clone(clone);
    clone->reverse();
    return 0;
}
