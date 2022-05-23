#ifndef MSTACK_H
#define MSTACK_H
#include <iostream>
#include "mUnique_ptr.h"
template < class T >
class mStack {
private:
    struct node
    {
        T valdata;
        mUnique_ptr<node> next;
    };
    size_t Size = 0;
    mUnique_ptr < node > topPtr;
    mUnique_ptr < node > *tmp;
public:
    mStack(){
    }
    void push(T value) {
        node *v = new node;
        v->valdata = value;
        v->next = move(topPtr);
        tmp = new mUnique_ptr<node>(v);
        topPtr = move(*tmp);
        Size++;
    }
    void pop() {
        if (!topPtr) {
            return;
        }
        if (Size == 0){
            return;
        }
        if (Size == 1){
            Size--;
            topPtr = mUnique_ptr < node >(nullptr);
            return;
        }
        Size--;
        topPtr = move(topPtr->next);
        return;
    }
    T top() {
        if (Size == 0){
            T n;
            return n;
        }
        return topPtr->valdata;
    }
    bool empty() {
        if (topPtr){
            return 0;
        }
        else{
            return 1;
        }
    }
};

#endif // MSTACK_H
