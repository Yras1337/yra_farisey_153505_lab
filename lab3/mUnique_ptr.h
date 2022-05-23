#ifndef MUNIQUE_PTR_H
#define MUNIQUE_PTR_H
#include <iostream>
using namespace std;
template <class T>
class mUnique_ptr {
public:
    mUnique_ptr() noexcept = default;

    explicit mUnique_ptr(T* data)
        : data_(data) {
    }

    mUnique_ptr(const mUnique_ptr& up) = delete;

    mUnique_ptr(mUnique_ptr&& up) noexcept
        : data_(up.data_){
        up.data_ = nullptr;
    }

    ~mUnique_ptr() {
        delete data_;
        data_ = nullptr;
    }

    mUnique_ptr& operator=(const mUnique_ptr& up) = delete;

    mUnique_ptr& operator=(mUnique_ptr&& up) noexcept {
        reset(up.data_);
        up.data_ = nullptr;
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

    T* release() noexcept {
        T* tmp = data_;
        data_ = nullptr;
        return tmp;
    }

    void reset(T* data = nullptr) noexcept {
        data_ = data;
    }

private:
    T* data_ = nullptr;
};
#endif // MUNIQUE_PTR_H
