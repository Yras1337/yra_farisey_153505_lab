#ifndef MLIST_H
#define MLIST_H
#include <iostream>
#include <mShared_ptr.h>
#include <mWeak_ptr.h>
template<class T>
class mList{
public:
    mList():Head(nullptr),Tail(nullptr){};
    ~mList(){
        clear();
    }
    void add(T addItem){
        count++;
        listNode *f = new listNode;
        f->item = addItem;
        mShared_ptr < listNode > tmp = mShared_ptr<listNode>(f);

        if (Head.get() != nullptr){
            f->Prev = mShared_ptr<listNode>(Tail);
            Tail->Next = tmp;
            Tail = tmp;
        }
        else{
            f->Prev = mShared_ptr<listNode>(nullptr);
            Head = tmp;
            Tail = tmp;
        }
    }
    T getItem(int pos){
        mShared_ptr < listNode > tmp = Head;
        int id = 0;
        while(tmp.get() != nullptr){
            if (id == pos){
                return tmp->item;
            }
            id++;
            tmp = tmp->Next;
        }
        return item;
    }
    void delItem(int pos){
        mShared_ptr < listNode > tmp = Head;
        int id = 0;
        while (tmp.get() != nullptr){
            if (id == pos){
                break;
            }
            id++;
            tmp = tmp->Next;
        }
        if (tmp.get() == nullptr){
            return;
        }
        mShared_ptr < listNode > tmpPrev = tmp->Prev, tmpNext = tmp->Next;
        if (tmpPrev.get() != nullptr && count != 1){
            tmpPrev->Next = tmpNext;
        }
        if (tmpNext.get() != nullptr && count != 1){
            tmpNext->Prev = tmpPrev;
        }
        if (pos == 0){
            Head = tmpNext;
        }
        if (pos == count - 1){
             Tail = tmpPrev;
        }
        count--;
    }
    void clear(){
        while(Head){
            Tail = Head->Next;
            Head = Tail;
        }
    }
    unsigned int size(){
        return (count);
    }
private:
    struct listNode{
        T item;
        mShared_ptr < listNode > Next, Prev;
    };
    unsigned int count = 0;
    T item;
    mShared_ptr < listNode > Head, Tail;
};
#endif // MLIST_H
