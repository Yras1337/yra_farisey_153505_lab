#ifndef HASHMAP_H
#define HASHMAP_H
#include <algorithm>
#include <functional>
#include <list>
#include <iostream>
template <typename KeyType, typename ValueType, typename Hasher = std::hash<KeyType>>
class MyHashMap {
    private:
        struct Data
        {
            std::list<std::pair<const KeyType, ValueType >> chain;
        };
        Hasher hash_;
        Data* Datas_;
        size_t size_;
        size_t capacity;
        size_t usedData;

        void rehash() {
            size_t new_capacity = capacity * 2;
            Data* new_Datas_ = new Data[new_capacity];
            size_t new_usedData = 0;

            for (size_t i = 0; i < capacity; i++) {
                for (auto x : Datas_[i].chain) {
                    KeyType key = x.first;
                    ValueType value = x.second;
                    auto hash = static_cast<size_t>(hash_(key)) % new_capacity;
                    new_Datas_[hash].chain.push_back(std::make_pair(key, value));
                    if (new_Datas_[hash].chain.size() == 1) {
                        new_usedData++;
                    }
                }
            }

            delete[] Datas_;
            Datas_ = new_Datas_;
            capacity = new_capacity;
            usedData = new_usedData;
        }
    public:
        MyHashMap(size_t size = 7) : hash_() {
            Datas_ = new Data[size];
            capacity = size;
            size_ = 0;
            usedData = 0;
        }
        ~MyHashMap() {
            clear();
            delete[] Datas_;
        }
        void clear() {
            for (size_t i = 0; i < capacity; i++) {
                Datas_[i].chain.clear();
            }
            Datas_ = new Data[7];
            size_ = 0;
            capacity = 7;
            usedData = 0;
        }
        bool contains(KeyType key) {
            auto hash = static_cast<size_t>(hash_(key)) % capacity;

            for (auto x : Datas_[hash].chain) {
                if (x.first == key) return true;
            }

            return false;
        }
        size_t size() {
            return size_;
        }
        void erase(KeyType key) {
            auto hash = static_cast<size_t>(hash_(key)) % capacity;

            if (contains(key)) {
                for (auto x : Datas_[hash].chain) {
                    if (x.first == key) {
                        Datas_[hash].chain.remove(x);
                        break;
                    }
                }

                size_--;
                if (Datas_[hash].chain.size() == 1) {
                    usedData--;
                }
            }
        }
        ValueType operator[](KeyType key) const {
            auto hash = static_cast<size_t>(hash_(key)) % capacity;

            if (contains(key)) {
                for (auto x : Datas_[hash].chain) {
                    if (x.first == key) {
                        return x.second;
                    }
                }
            }

            return ValueType();
        }
        void insert(KeyType key, ValueType value) {
            auto hash = static_cast<size_t>(hash_(key)) % capacity;

            if (contains(key)) {
                erase(key);
            }

            Datas_[hash].chain.push_back(std::make_pair(key, value));
            size_++;
            if (Datas_[hash].chain.size() == 1) {
                usedData++;
            }
            if (capacity * 0.6 < usedData) {
                rehash();
            }
        }
        ValueType& operator[](KeyType key) {
            auto hash = static_cast<size_t>(hash_(key)) % capacity;

            if (!contains(key)) {
                insert(key, ValueType());
            }

            for (auto x : Datas_[hash].chain) {
                if (x.first == key) {
                    auto it = std::find(Datas_[hash].chain.begin(), Datas_[hash].chain.end(), x);
                    return it -> second;
                }
            }
        }
};
#endif // HASHMAP_H
