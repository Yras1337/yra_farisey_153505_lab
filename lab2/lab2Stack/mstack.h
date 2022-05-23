#ifndef MSTACK_H
#define MSTACK_H
#include <iostream>
using namespace std;
template < class T > class mStack
{
public:
    T top();
    bool empty();
    int size();
    void push(T value);
    void pop();
private:
    T* value;
    mStack* tek = nullptr, * prev = nullptr;
    int size_s = 0;
};
#endif // MSTACK_H
