#ifndef MSTACK_H
#define MSTACK_H
#include "mShared_ptr.h"
template < class T >
class mStack {
private:
    struct node
    {
        T data;
        mShared_ptr<node> next;
    };
    mShared_ptr < node > topPtr;
public:
    mStack();
    void push(T value) {
        node *v;
        v->data = value;
        v->next = topPtr;
        mShared_ptr < node > tmp;
        tmp.reset(v);
        topPtr.reset(v);

    }
    void pop() {
        if (topPtr) {
            return;
        }
        mShared_ptr<node> tmp = topPtr;
        topPtr = topPtr->next;
        return;
    }
    T top() {
        return topPtr->data;
    }
    bool empty() {
        if (topPtr){
            return 1;
        }
        else{
            return 0;
        }
    }
};

#endif // MSTACK_H
