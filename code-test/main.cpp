#include "Solution.hpp"

int main(int argc, char const *argv[])
{
    MyLinkedList* obj = new MyLinkedList();
    
    // int param_1 = obj->get(index);
    obj->addAtHead(7);
    obj->addAtHead(2);
    obj->addAtHead(1);
    obj->addAtIndex(3,0);
    // obj->addAtTail(val);
    // obj->addAtIndex(index,val);
    // obj->deleteAtIndex(index);
    return 0;
}
