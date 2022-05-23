#ifndef LIST_H
#define LIST_H
#include <iostream>
#include "queue.h"
template < class T >
class list : public mQueue<T>{
public:
    std::string get_string(){
        std::string tmp;
        for (int i = 0; i < this->size(); i++){
            tmp += this->getItem(i);
        }
        return tmp;
    }
};

#endif // LIST_H
