#include "mstack.h"
template < class T > T mStack<T>::top() {
    if (size_s == 0) {
        cout << "invalid operation" << endl;
        return 0;
    }
    return tek->value;
}
template < class T > bool mStack<T>::empty() {
    if (size_s) {
        return true;
    }
    else {
        return false;
    }
}
template < class T > int mStack<T>::size() {
    return size_s;
}
template < class T > void mStack<T>::push(T value) {
    mStack* temp = new mStack;
    temp->value = value;
    temp->prev = tek->tek;
    temp->tek = *temp;
    size_s++;
}
template < class T > void mStack<T>::pop() {

}
