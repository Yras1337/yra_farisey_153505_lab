#ifndef MSHARED_PTR_H
#define MSHARED_PTR_H
#include "mWeak_ptr.h"
using namespace std;
template <class T>
class mShared_ptr{
public:
    mShared_ptr() noexcept = default;

    explicit mShared_ptr(T* data)
        : data_(data) {
        if (data_) {
            cblock_ = new cblock();
        }
    }

    mShared_ptr(const mShared_ptr& sp) noexcept
        : data_(sp.data_)
        , cblock_(sp.cblock_) {
        if (cblock_) {
            ++cblock_->shared_count;
        }
    }

    template <class D>
    mShared_ptr(const mShared_ptr<D>& sp) noexcept
        : data_(sp.data_)
        , cblock_(sp.cblock_) {
        if (cblock_) {
            ++cblock_->shared_count;
        }
    }

    explicit mShared_ptr(const mWeak_ptr<T>& wp) noexcept
        : data_(wp.data_)
        , cblock_(wp.cblock_) {
        if (cblock_) {
            ++cblock_->shared_count;
        }
    }

    mShared_ptr(mShared_ptr&& sp) noexcept {
        swap(sp);
        sp.reset();
    }

    ~mShared_ptr() {
        dec_shared_count();
    }

    mShared_ptr& operator=(const mShared_ptr& sp) noexcept {
        mShared_ptr tmp(sp);
        swap(tmp);
        return *this;
    }

    mShared_ptr& operator=(mShared_ptr&& sp) noexcept {
        swap(sp);
        sp.reset();
        return *this;
    }

    T* get() const noexcept {
        return data_;
    }

    T* operator->() const noexcept {
        return data_;
    }

    T& operator*() const noexcept {
        return *data_;
    }

    explicit operator bool() const noexcept {
        return data_ != nullptr;
    }

    void reset() noexcept {
        dec_shared_count();
        data_ = nullptr;
        cblock_ = nullptr;
    }

    void reset(T *data) {
        dec_shared_count();
        data_ = data;
        cblock_ = new cblock();
    }
    void swap(T* x, T* y){
        T*tmp = x;
        x = y;
        y = tmp;
    }
    void swap(cblock* x, cblock* y){
        cblock*tmp = x;
        x = y;
        y = tmp;
    }
private:
    void swap(mShared_ptr& sp) noexcept {

        swap(data_, sp.data_);
        swap(cblock_, sp.cblock_);
    }

    void dec_shared_count() {
        if (!cblock_) {
            return;
        }

        --cblock_->shared_count;

        if (cblock_->shared_count <= 0) {
            delete data_;
            data_ = nullptr;
            if (cblock_->weak_count <= 0) {
                delete cblock_;
                cblock_ = nullptr;
            }
        }
    }

    T* data_ = nullptr;
    cblock* cblock_ = nullptr;

    template<class Y> friend class mShared_ptr;
    template<class Y> friend class mWeak_ptr;
};

#endif // MSHARED_PTR_H
