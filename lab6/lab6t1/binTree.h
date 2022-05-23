#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include <vector>
using std::vector;
using std::pair;
template <typename KeyType, typename ValueType>
class Map {
    private:
        struct node {
            pair<KeyType, ValueType> value_;
            node* left_;
            node* right_;

            node* next_;
            node* prev_;
            node() {
                next_ = prev_ = left_ = right_ = nullptr;
            }
            node(pair<KeyType, ValueType> value) {
                value_ = value;
                next_ = prev_ = left_ = right_ = nullptr;
            }
        };
        bool check = 1;
        vector < pair < KeyType, pair < KeyType, KeyType > > > buf;
        node* root_;
        size_t size_;

        node* find_min_node(node* current_node) {
            return current_node -> left_ ? find_min_node(current_node -> left_) : current_node;
        }
        node* find_max_node(node* current_node) {
            return current_node -> right_ ? find_max_node(current_node -> right_) : current_node;
        }

        node* erase_(node* current_node, KeyType key, bool& flag) {
            if (!current_node) {
                return 0;
            }
            if (key < current_node -> value_.first) {
                current_node -> left_ = erase_(current_node -> left_, key, flag);
            }
            else if (key < current_node -> value_.first) {
                current_node -> right_ = erase_(current_node -> right_, key, flag);
            }
            else {
                flag = true;
                node* left = current_node -> left_;
                node* right = current_node -> right_;
                node* prev = current_node -> prev_;
                node* next = current_node -> next_;
                if (prev != nullptr) {
                    prev -> next_ = next;
                }
                if (next != nullptr) {
                    next -> prev_ = prev;
                }
                delete current_node;
                if (!right) {
                    return left;
                }
                node* min_node = find_min_node(right);
                min_node -> left_ = left;
                return right;
            }
            return current_node;
        }

        node* insert_(node* current_node, pair<KeyType, ValueType> value) {
            if (!current_node) {
                size_++;
                return new node(value);
            }
            if (value.first < current_node -> value_.first) {
                bool flag = current_node -> left_ == nullptr;
                current_node -> left_ = insert_(current_node -> left_, value);
                if (flag != (current_node -> left_ == nullptr) ) {
                    node* prev = current_node -> prev_;
                    if (prev != nullptr) {
                        current_node -> prev_ = current_node -> left_;
                        current_node -> left_ -> next_ = current_node;
                        current_node -> left_ -> prev_ = prev;
                        prev -> next_ = current_node -> left_;
                    }
                    else {
                        current_node -> prev_ = current_node -> left_;
                        current_node -> left_ -> next_ = current_node;
                    }
                }
            }
            else if (value.first > current_node -> value_.first) {
                bool flag = current_node -> right_ == nullptr;
                current_node -> right_ = insert_(current_node -> right_, value);
                if (flag != (current_node -> right_ == nullptr) ) {
                    node* next = current_node -> next_;
                    if (next != nullptr) {
                        current_node -> next_ = current_node -> right_;
                        current_node -> right_ -> prev_ = current_node;
                        current_node -> right_ -> next_ = next;
                        next -> prev_ = current_node -> right_;
                    }
                    else {
                        current_node -> next_ = current_node -> right_;
                        current_node -> right_ -> prev_ = current_node;
                    }
                }
            }
            else {
                current_node -> value_ = value;
            }
            return current_node;
        }

        node* find_(node* current_node, KeyType key) {
            if (!current_node) {
                return nullptr;
            }
            node* necessary_node;
            if (key < current_node -> value_.first) {
                necessary_node = find_(current_node -> left_, key);
            }
            else if (key > current_node -> value_.first) {
                necessary_node = find_(current_node -> right_, key);
            }
            else {
                necessary_node = current_node;
            }
            return necessary_node;
        }

        node* find_larger_(node* current_node, KeyType key) {
            if (!current_node) {
                return nullptr;
            }
            node* necessary_node;
            if (key >= current_node -> value_.first) {
                necessary_node = find_larger_(current_node -> right_, key);
            }
            else {
                necessary_node = find_larger_(current_node -> left_, key);
                if (necessary_node == nullptr || necessary_node -> value_.first <= key) {
                    necessary_node = current_node;
                }
            }
            return necessary_node;
        }

        node* find_less_(node* current_node, KeyType key) {
            if (!current_node) {
                return nullptr;
            }
            node* necessary_node;
            if (key <= current_node -> value_.first) {
                necessary_node = find_less_(current_node -> left_, key);
            }
            else {
                necessary_node = find_less_(current_node -> right_, key);
                if (necessary_node == nullptr || necessary_node -> value_.first >= key) {
                    necessary_node = current_node;
                }
            }

            return necessary_node;
        }

        void clear_(node* current_node) {
            if (current_node == nullptr) {
                return;
            }
            clear_(current_node -> left_);
            clear_(current_node -> right_);

            delete current_node;
        }

    public:
        class MapIterator : std::iterator<std::bidirectional_iterator_tag, std::pair<KeyType, ValueType>> {
            private:
                node *object;
            public:
                MapIterator() {
                    object = nullptr;
                }
                MapIterator(node *value) {
                    object = value;
                }
                pair<KeyType, ValueType>& operator*() {
                    return object -> value_;
                }
                pair<KeyType, ValueType> operator*() const{
                    return object -> value_;
                }
                MapIterator& operator--() {
                    object = object -> prev_;
                    return *this;
                }
                MapIterator& operator--(int) {
                    auto answer = this;
                    object = object -> prev_;
                    return *answer;
                }
                MapIterator& operator++() {
                    object = object -> next_;
                    return *this;
                }
                MapIterator& operator++(int) {
                    auto answer = this;
                    object = object -> next_;
                    return *answer;
                }
                bool operator==(const MapIterator& other) const {
                    return this -> object == other.object;
                }
                bool operator!=(const MapIterator& other) const {
                    return this -> object != other.object;
                }
        };
        void clrBuf(){
            buf.clear();
            check = 1;
        }
        std::vector < std::pair < KeyType, std::pair < KeyType, KeyType > > > getBuf(){
            return buf;
        }
        MapIterator begin() {
            return MapIterator(find_min_node(root_ -> left_));
        }
        MapIterator end() {
            return MapIterator(root_);
        }

        Map() {
           root_ = new node();
           size_ = 0;
        }
        ~Map() {
            clear_(root_);
        }
        void erase(KeyType key) {
            bool flag = false;
            root_ -> left_ = erase_(root_ -> left_, key, flag);
            if (flag == false) {
                std::cout << "No such key\n";
            }
            else {
                size_--;
            }
            if (size_ != 0) {
                node* max_node = find_max_node(root_ -> left_);
                max_node -> next_ = root_;
                root_ -> prev_ = max_node;
            }
        }
        void insert(std::pair<KeyType, ValueType> value) {
            root_ -> left_ = insert_(root_ -> left_, value);
            node* max_node = find_max_node(root_ -> left_);
            max_node -> next_ = root_;
            root_ -> prev_ = max_node;
        }
        void ob1(node* v = nullptr){
            if(check){
                check = 0;
                v = root_;
            }
            //std::cout << v->value_.<< std::endl;
            if (v != nullptr){
                if (root_ != v){
                    KeyType l, r;
                    if (v->left_ != nullptr){
                        l = v->left_->value_.first;
                    }
                    if (v->right_ != nullptr){
                        r = v->right_->value_.first;
                    }
                    buf.push_back({v->value_.first, {l, r}});
                }
                ob1(v->left_);
                ob1(v->right_);
            }
        }
        void ob2(node* v = nullptr){
            if(check){
                check = 0;
                v = root_;
            }
            if (v != nullptr){
                ob2(v->left_);
                ob2(v->right_);
                if (root_ != v){
                    KeyType l, r;
                    if (v->left_ != nullptr){
                        l = v->left_->value_.first;
                    }
                    if (v->right_ != nullptr){
                        r = v->right_->value_.first;
                    }
                    buf.push_back({v->value_.first, {l, r}});
                }
            }
        }
        void ob3(node* v = nullptr){
            if(check){
                check = 0;
                v = root_;
            }
            if (v != nullptr){
                ob2(v->left_);
                if (root_ != v){
                    KeyType l, r;
                    if (v->left_ != nullptr){
                        l = v->left_->value_.first;
                    }
                    if (v->right_ != nullptr){
                        r = v->right_->value_.first;
                    }
                    buf.push_back({v->value_.first, {l, r}});
                }
                ob2(v->right_);
            }
        }
        bool find(KeyType key) {
            node* value = find_(root_ -> left_, key);
            return value == nullptr ? false : true;
        }
        ValueType& operator[](KeyType key) {
            node* value = find_(root_ -> left_, key);
            if (value == nullptr) {
                std::cout << "ABad key" << std::endl;
            }
            else {
                return value -> value_.second;
            }
        }

        KeyType& find_larger(KeyType key) {
            node* value = find_larger_(root_ -> left_, key);
            if (value == nullptr || value -> value_.first <= key ) {
                std::cout << "BBad key" << std::endl;
            }
            else {
                return value -> value_.first;
            }
        }

        KeyType& find_less(KeyType key) {
            node* value = find_less_(root_ -> left_, key);
            if (value == nullptr || value -> value_.first >= key ) {
                std::cout << "CBad key\n" << std::endl;
            }
            else {
                return value -> value_.first;
            }
        }

        int size() {
            return size_;
        }
        bool empty() {
            return size_ == 0 ? true : false;
        }
        void clear() {
            clear_(root_ -> left_);
            root_ -> left_ = nullptr;
            size_ = 0;
        }
};
#endif // BINTREE_H
