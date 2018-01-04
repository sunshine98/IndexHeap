#include <iostream>
#include "indexheap.h"
using namespace std;
int main() {
int arr[5]={5,7,3,2,6};
    indexheap heap(5);
    for(int i=0;i<5;i++)
    {
        heap.insert(i,arr[i]);
    }
heap.test();

    return 0;
}