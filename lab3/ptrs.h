#ifndef PTRS_H
#define PTRS_H
template <class T>
class mShared_ptr{
    T *ptr = nullptr;
    unsigned int *rCount = nullptr;
    void clr(){
        (*rCount)--;
        if (*rCount == 0){
            if (nullptr != ptr){
                delete ptr;
            }
            delete rCount;
        }
    }
public:
    mShared_ptr():ptr(nullptr), rCount(new (unsigned int)(0)){}
    mShared_ptr(T *ptr):ptr(ptr), rCount(new (unsigned int)(1)){}
    mShared_ptr(const mShared_ptr &obj){
        this->ptr = obj.ptr;
        this->rCount = obj.refCount;
        if (nullptr != obj.ptr){
            (*this->rCount)++;
        }
    }
    mShared_ptr& operator = (const mShared_ptr &obj){
        clr();
        this->ptr = obj->ptr;
        this->rCount = obj.rCount;
        if (nullptr != obj.ptr){
            (*this->rCount)++;
        }
    }
    mShared_ptr& operator = (const mShared_ptr &&obj){
        clr();
        this->ptr = obj->ptr;
        this->rCount = obj.rCount;
        obj.ptr = obj.rCount = nullptr;
    }
    mShared_ptr(const mShared_ptr &&obj){
        this->ptr = obj.ptr;
        this->rCount = obj.refCount;
        obj.ptr = obj.rCount = nullptr;
    }
    unsigned int get_count() const{
        return *rCount;
    }
    T* get() const{
        return this->ptr;
    }
    T* operator->() const{
        return this->ptr;
    }
    T& operator*() const{
        return this->ptr;
    }
    ~mShared_ptr(){
        clr();
    }
};
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
    mUnique_ptr&operator =(const mUnique_ptr &obj) = delete;
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
