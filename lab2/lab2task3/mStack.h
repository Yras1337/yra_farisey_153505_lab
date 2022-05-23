#ifndef MSTACK_H
#define MSTACK_H
template < class T >
struct stackNode
{
    T item;
    stackNode<T>* next;
};
template < class T >
class mStack {
private:
    stackNode<T>* topPtr;
    int size = 0;
public:
    mStack() {
        topPtr = nullptr;
    }
    int Size(){
        return size;
    }
    void push(T value) {
        stackNode<T>* temp = new stackNode<T>;
        temp->item = value;
        temp->next = topPtr;
        topPtr = temp;
        size++;
    }
    void pop() {
        if (topPtr == nullptr) {
            return;
        }
        stackNode<T>* temp;
        temp = topPtr;
        topPtr = topPtr->next;
        delete temp;
        size--;
    }
    void clear() {
        stackNode<T>* tmp1, * tmp2;
        tmp1 = topPtr;
        while (tmp1 != nullptr) {
            tmp2 = tmp1;
            tmp1 = tmp1->next;
            delete tmp2;
        }
        topPtr = nullptr;
    }
    T top() {
        return topPtr->item;
    }
    bool empty() {
        return (topPtr == nullptr);
    }
};

#endif // MSTACK_H
