#ifndef DARRAY_H
#define DARRAY_H
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <cmath>
template < class T > class vector {
private:
    T *arr;
    int64_t arrSize;
    int64_t arrcapacity;
    int64_t memSt;
public:
    void erase(int pos);
    vector();
    vector(int64_t size);
    vector(int64_t size, const T& value);
    int64_t capacity();
    int64_t size() ;
    T& operator[](int64_t index);
    vector<T>& operator=(const vector<T>&);
    T& front();
    T& back();
    void push_back(const T& value);
    void pop_back();
    void clear();
    template < class ... Args > void emplace_back(Args && ... args);
    void addmem(int64_t capacity);
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<T*> reverse_iterator;
    template < class ... Args > iterator emplace(const_iterator, Args && ... args);
    iterator end();
    iterator begin();
    const_iterator cend();
    const_iterator cbegin();
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
    arrcapacity = 0;
    memSt = 0;
}
template<class T> vector<T>::vector(int64_t size) {
    arrSize = size;
    arr = new T[size];
    arrcapacity = size;
    memSt = 0;
}
template<class T> vector<T>::vector(int64_t size, const T& value) {
    arrSize = size;
    arr = new T[size];
    arrcapacity = size;
    memSt = 0;
    for (int64_t i = 0; i < size; ++i) {
        arr[i] = value;
    }
}
template<class T> vector<T>& vector<T>::operator = (const vector<T>& ne) {
    delete[] arr;
    arr = ne.arr;
    arrcapacity = ne.arrcapacity;
    memSt = ne.memSt;
    arr = new T[arrSize];
    for (int64_t i = 0; i < arrSize; i++) {
        arr[i] = ne.arr[i];
    }
    return *this;
}
template<class T> T& vector<T>::operator[](int64_t index) {
    return arr[index];
}
template<class T> int64_t vector<T>::size(){
    return arrSize;
}
template<class T> int64_t vector<T>::capacity() {
    return arrcapacity;
}
template<class T> typename vector<T>::iterator vector<T>::begin() {
    return arr;
}
template<class T> typename vector<T>::iterator vector<T>::end() {
    return arr + size();
}
template<class T> typename vector<T>::const_iterator vector<T>::cbegin() {
    return arr;
}
template<class T> typename vector<T>::const_iterator vector<T>::cend() {
    return arr + size();
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
    arrcapacity = 0;
    memSt = 0;
    arr = new T[0];
}
template<class T> void vector<T>::addmem(int64_t capacity) {
    if (arr == NULL) {
        arrSize = 0;
        arrcapacity = 0;
        memSt = 0;
    }
    T* nArr = new T[capacity];
    int64_t nSize = std::min(arrSize, capacity);
    for (int64_t i = 0; i < nSize; i++) {
        nArr[i] = arr[i];
    }
    arrcapacity = capacity;
    delete[] arr;
    arr = nArr;
}
template<class T> void vector<T>::erase(int pos){
    if (arr == NULL){
        return;
    }
    if (arrSize == 1){
        clear();
        return;
    }
    T* nArr = new T[arrSize - 1];
    int64_t l = 0;
    for (int64_t i = 0; i < arrSize; i++){
        if (i == pos){
            continue;
        }
        nArr[l] = arr[i];
        l++;
    }
    arrSize--;
    delete[] arr;
    arr = nArr;
}
template<class T> void vector<T>::push_back(const T& value)
{
    if (arrSize >= arrcapacity) {

        addmem(1LL << memSt);
        memSt++;
    }
    arr[arrSize++] = value;
}
template < class T> void vector<T>::resize(int64_t capacity) {
    if (arr == NULL) {
        arrSize = 0;
        arrcapacity = 0;
    }
    T* nArr = new T[capacity];
    int64_t nSize = std::max(arrSize, capacity);
    for (int64_t i = 0; i < nSize; i++) {
        nArr[i] = 0;
    }
    arrcapacity = capacity;
    delete[] arr;
    arr = nArr;
    arrSize = capacity;
    memSt = log2(capacity) + 1;
    arrcapacity = capacity;
}
template < class T> void vector<T>::resize(int64_t capacity, int64_t value) {
    if (arr == NULL) {
        arrSize = 0;
        arrcapacity = 0;
    }
    T* nArr = new T[capacity];
    int64_t nSize = std::max(arrSize, capacity);
    for (int64_t i = 0; i < nSize; i++) {
        nArr[i] = value;
    }
    arrcapacity = capacity;
    delete[] arr;
    arr = nArr;
    arrSize = capacity;
    memSt = log2(capacity) + 1;
    arrcapacity = capacity;
}
template < class T> int64_t vector<T>::max_size() {
    return (1LL << 62) - 1;
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
    T* nArr = new T[arrcapacity];
    for (int64_t i = 0; i < arrcapacity; i++) {
        nArr[i] = arr[i];
    }
    //arrcapacity = capacity;
    delete[] arr;
    arr = nArr;
}
template < class T>
template < class ... Args >
void vector<T>::emplace_back(Args&& ... args) {
    if (arrSize <= arrcapacity) {
        addmem(1LL << memSt);
        memSt++;
    }
    arr[arrSize] = std::move(T(std::forward<Args>(args) ...));
    arrSize++;
}
/*template < class T >
template < class ... Args >
void vector <T>::emplace_back(Args&&...args) {
    if (arrSize <= arrcapacity) {
        addmem(log2(arrcapacity) + 1);

    }
    arr[arrSize] = std::move(T(std::forward<Args>(args) ...));
    arrSize++;
}*/
/*
template < class T >
template < class ... Args >
void vector < T >::emplace_back(Args&& ... args) {
    if (arrSize <= arrcapacity) {
        addmem(1LL << memSt);
        memSt++;
    }
    arr[arrSize] = std::move(T(std::forward<Args>(args)...));
    arrSize++;
}
*/
template < class T>
template < class ... Args >
typename vector<T>::iterator vector<T>::emplace(typename vector<T>::const_iterator it, Args && ... args) {
    iterator it2 = &arr[it - arr];
    if (arrSize == arrcapacity){
        addmem(1LL << memSt);
        memSt++;
    }
    memmove(it2 + 1, it2, (arrSize - (it - arr)) * sizeof(T));
    (*it2) = std::move(T(std::forward<Args>(args)...));
    arrSize++;
    return it2;
}
template < class T>
void vector<T>::shrink_to_fit() {
    arrcapacity = arrSize;
    memSt = log2(arrcapacity);
    addmem(arrcapacity);
}
#endif // DARRAY_H
