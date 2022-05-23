#ifndef PTRS_H
#define PTRS_H
template <class T>
class mUnique_ptr{
    T *ptr = nullptr;
    void clr(){
        if(ptr != nullptr){
            delete ptr;
        }
    }
public:
    mUnique_ptr():ptr(nullptr){}
    mUnique_ptr(T* ptr) : ptr(ptr){}
    mUnique_ptr(const mUnique_ptr &obj) = delete;
    mUnique_ptr&operator = (const mUnique_ptr &obj) = delete;
    mUnique_ptr(mUnique_ptr && obj){
        this->ptr = obj.ptr;
        obj.ptr = nullptr;
    }
    T* operator->(){
        return this->ptr;
    }
    T& operator*(){
        return this->ptr;
    }
    ~mUnique_ptr(){
        clr();
    }
};


#endif // PTRS_H
