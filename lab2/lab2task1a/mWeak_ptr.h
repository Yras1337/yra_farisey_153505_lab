#ifndef MWEAK_PTR_H
#define MWEAK_PTR_H
#include "mShared_ptr.h"
struct cblock {
    int shared_count = 1;
    int weak_count = 0;
};
template <class T>
class mShared_ptr;
template <class T>
class mWeak_ptr{
private:
    void swap(mWeak_ptr& wp) noexcept {
        swap(data_, wp.data_);
        swap(cblock_, wp.cblock_);
    }

    void dec_weak_count() {
        if (!cblock_) {
            return;
        }
        --cblock_->weak_count;
        if (cblock_->shared_count <= 0 && cblock_->weak_count <= 0) {
            delete cblock_;
            cblock_ = nullptr;
        }
    }
    T* data_ = nullptr;
    cblock* cblock_ = nullptr;
    template<class Y> friend class mShared_ptr;
public:
    mWeak_ptr() noexcept = default;
    mWeak_ptr(const mWeak_ptr& wp) noexcept
        : data_(wp.data_)
        , cblock_(wp.cblock_) {
        if (cblock_) {
            ++cblock_->weak_count;
        }
    }
    mWeak_ptr(const mShared_ptr<T>& sp) noexcept
        : data_(sp.data_)
        , cblock_(sp.cblock_) {
        if (cblock_) {
            ++cblock_->weak_count;
        }
    }
    mWeak_ptr(mWeak_ptr&& wp) noexcept {
        swap(wp);
        wp.reset();
    }
    ~mWeak_ptr() {
        dec_weak_count();
    }
    mWeak_ptr& operator=(const mWeak_ptr& wp) noexcept {
        mWeak_ptr tmp(wp);
        swap(tmp);
        return *this;
    }
    mWeak_ptr& operator=(mWeak_ptr&& wp) noexcept {
        swap(wp);
        wp.reset();
        return *this;
    }
    mShared_ptr<T> lock() const {
        return expired() ? mShared_ptr<T>(nullptr) : mShared_ptr<T>(*this);
    }
    bool expired() const noexcept {
        return !cblock_ || cblock_->shared_count <= 0;
    }
    void reset() noexcept {
        dec_weak_count();
        data_ = nullptr;
        cblock_ = nullptr;
    }
};
#endif // MWEAK_PTR_H
