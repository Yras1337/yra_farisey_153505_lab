#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <cmath>

template < class T > class vector {
private:
    int64_t arrSize;
    int64_t arrCap;
    int64_t memStep;
    T* arr;
    void addmem(int64_t capacity);
public:
    vector();
    vector(int64_t size);
    vector(int64_t size, const T& value);
    T& operator[](int64_t index);
    vector<T>& operator=(const vector<T>&);
    int64_t capacity();
    int64_t size();
    T& front();
    T& back();
    void push_back(const T& value);
    void pop_back();
    void clear();
    template < class ... Args > void emplace_back(Args && ... args);
    iterator end();
    iterator begin();
    reverse_iterator rend();
    reverse_iterator rbegin();
    const_iterator cend();
    const_iterator cbegin();
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<T*> reverse_iterator;
    template < class ... Args > iterator emplace(const_iterator, Args && ... args);
    const reverse_iterator crend();
    const reverse_iterator crbegin();
    void resize(int64_t capacity);
    void resize(int64_t capacity, int64_t value);
    int64_t max_size();
    bool empty();
    void reverse();
    T* data();
    void insert(vector<T>::iterator, const T& value);
    const T* data() const;
    void shrink_to_fit();
};
template<class T> vector<T>::vector() {
    arrSize = 0;
    arr = 0;
    arrCap = 0;
    memStep = 0;
}
template<class T> vector<T>::vector(int64_t size) {
    arrSize = size;
    arr = new T[size];
    arrCap = size;
    memStep = 0;
}
template<class T> vector<T>::vector(int64_t size, const T& value) {
    arrSize = size;
    arr = new T[size];
    arrCap = size;
    memStep = 0;
    for (int64_t i = 0; i < size; ++i) {
        arr[i] = value;
    }
}
template<class T> vector<T>& vector<T>::operator = (const vector<T>& ne) {
    delete[] arr;

    arr = ne.arr;
    arrCap = ne.arrCap;
    memStep = ne.memStep;
    arr = new T[arrSize];
    for (int64_t i = 0; i < arrSize; i++) {
        arr[i] = ne.arr[i];
    }
    return *this;
}
template<class T> T& vector<T>::operator[](int64_t index) {
    return arr[index];
}
template<class T> int64_t vector<T>::size() {
    return arrSize;
}
template<class T> int64_t vector<T>::capacity() {
    return arrCap;
}
template<class T> typename vector<T>::iterator vector<T>::begin() {
    return arr;
}
template<class T> typename vector<T>::reverse_iterator vector<T>::rbegin() {
    std::reverse_iterator < T* > it(arr + size());
    return it;
}
template<class T> typename vector<T>::iterator vector<T>::end() {
    return arr + size();
}
template<class T> typename vector<T>::reverse_iterator vector<T>::rend() {
    std::reverse_iterator < T* > it(begin());
    return it;
}
template<class T> typename vector<T>::const_iterator vector<T>::cbegin() {
    return arr;
}
template<class T> const typename vector<T>::reverse_iterator vector<T>::crbegin() {
    reverse_iterator it(arr + size());
    return it;
}
template<class T> typename vector<T>::const_iterator vector<T>::cend() {
    return arr + size();
}
template<class T> const typename vector<T>::reverse_iterator vector<T>::crend() {
    reverse_iterator it(arr);
    return it;
}
template<class T> T& vector<T>::front() {
    return arr[0];
}
template<class T> T& vector<T>::back() {
    return arr[size() - 1];
}
template<class T> void vector<T>::pop_back() {
    arrSize--;
}
template<class T> void vector<T>::clear() {
    if (arr != NULL) {
        ZeroMemory(arr, arrSize);
    }
    arrSize = 0;
    memStep = 0;
    arrCap = 0;
    arr = nullptr;
}
template<class T> void vector<T>::addmem(int64_t capacity) {
    if (arr == NULL) {
        arrSize = 0;
        arrCap = 0;
        memStep = 0;
    }
    T* nArr = new T[capacity];
    int64_t nSize = std::min(arrSize, capacity);
    for (int64_t i = 0; i < nSize; i++) {
        nArr[i] = arr[i];
    }
    arrCap = capacity;
    delete[] arr;
    arr = nArr;
}
template<class T> void vector<T>::push_back(const T& value)
{
    if (arrSize >= arrCap) {
        addmem(1LL << memStep);
        memStep++;
    }
    arr[arrSize++] = value;
}
template < class T> void vector<T>::resize(int64_t capacity) {
    if (arr == NULL) {
        arrSize = 0;
        arrCap = 0;
    }
    T* nArr = new T[capacity];
    int64_t nSize = std::max(arrSize, capacity);
    for (int64_t i = 0; i < nSize; i++) {
        nArr[i] = 0;
    }
    arrCap = capacity;
    delete[] arr;
    arr = nArr;
    arrSize = capacity;
    memStep = log2(capacity) + 1;
    arrCap = capacity;
}
template < class T> void vector<T>::resize(int64_t capacity, int64_t value) {
    if (arr == NULL) {
        arrSize = 0;
        arrCap = 0;
    }
    T* nArr = new T[capacity];
    int64_t nSize = std::max(arrSize, capacity);
    for (int64_t i = 0; i < nSize; i++) {
        nArr[i] = value;
    }
    arrCap = capacity;
    delete[] arr;
    arr = nArr;
    arrSize = capacity;
    memStep = log2(capacity) + 1;
    arrCap = capacity;
}
template < class T> int64_t vector<T>::max_size() {
    return (1LL << 63) - 1;
}
template < class T> bool vector<T>::empty() {
    return (size() == 0);
}
template < class T> void vector<T>::reverse() {
    for (int64_t i = arrSize - 1; i >= arrSize / 2; i--) {
        std::swap(arr[i], arr[arrSize - 1 - i]);
    }
}
template < class T> T* vector<T>::data() {
    return arr;
}
template < class T> const T* vector<T>::data() const {
    return arr;
}
template < class T> void vector<T>::insert(vector<T>::iterator pos, const T& value) {
    T* nArr = new T[arrCap];
    for (int64_t i = 0; i < arrCap; i++) {
        nArr[i] = arr[i];
    }
    delete[] arr;
    arr = nArr;
}
template < class T>
template < class ... Args >
void vector<T>::emplace_back(Args&& ... args) {
    if (arrSize <= arrCap) {
        addmem(1LL << memStep);
        memStep++;
    }
    arr[arrSize] = std::move(T(std::forward<Args>(args) ...));
    arrSize++;
}
template < class T>
template < class ... Args >
typename vector<T>::iterator vector<T>::emplace(typename vector<T>::const_iterator it, Args && ... args) {
    iterator it2 = &arr[it - arr];
    if (arrSize == capacity) {
        addmem(1LL << memStep);
        memStep++;
    }
    memmove(it2 + 1, it2, (arrSize - (it - arr)) * sizeof(T));
    (*it2) = std::move(T(std::forward<Args>(args)...));
    arrSize++;
    return it2;
}
template < class T>
void vector<T>::shrink_to_fit() {
    arrCap = arrSize;
    memStep = log2(arrCap);
    addmem(arrCap);
}
