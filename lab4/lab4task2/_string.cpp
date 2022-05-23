#ifndef _STRING_CPP
#define _STRING_CPP
#include <iostream>
void* Memcpy(void* s1, const void* s2, size_t n) {
    char* p = (char*)s1;
    char* q = (char*)s2;
    while (n--) {
        *p++ = *q++;
    }
    return s1;
}
void* Memmove(void* s1, const void* s2, size_t n) {
    void* ret = s1;
    if (s1 <= s2 || (char*)s1 >= ((char*)s2 + n)){
        while (n--){
            *(char*)s1 = *(char*)s2;
            s1 = (char*)s1 + 1;
            s2 = (char*)s2 + 1;
        }
    }
    else{
        s1 = (char*)s1 + n - 1;
        s2 = (char*)s2 + n - 1;
        while (n--){
            *(char*)s1 = *(char*)s2;
            s1 = (char*)s1 - 1;
            s2 = (char*)s2 - 1;
        }
    }
    return(ret);
}

char* Strcpy(char* s1, const char* s2) {
    char* ret = s1;
    if (s1 != NULL && s2 != NULL) {
        while (1) {
            *s1++ = *s2++;
            if (*s2 == '\0') {
                *s1++ = *s2++;
                break;
            }
        }
    }
    return ret;
}
char* Strncpy(char* s1, const char* s2, size_t n) {
    char* ret = s1;
    while (n--) {
        *s1++ = *s2++;
    }
    return ret;
}
char* Strcat(char* s1, const char* s2) {
    char* ret = s1;
    while (*s1) {
        s1++;
    }
    while (1) {
        *s1++ = *s2++;
        if (*s2 == '\0') {
            *s1++ = *s2++;
            break;
        }
    }
    return ret;
}
char* Strncat(char* s1, const char* s2, size_t n) {
    char* ret = s1;
    while (*s1) {
        s1++;
    }
    while (n--) {
        *s1++ = *s2++;
    }
    *s1 = '\0';
    return ret;
}
int Memcmp(const void* s1, const void* s2, size_t n) {
    char* p = (char*)s1;
    char* q = (char*)s2;
    while (n--) {
        if (*p > *q) {
            return 1;
        }
        else if (*p < *q) {
            return -1;
        }
        p++;
        q++;
    }
    return 0;
}
int Strcmp(const char* s1, const char* s2) {
    const char* p = (const char*)s1;
    const char* q = (const char*)s2;
    while (*p || *q) {
        if (*p > *q) {
            return -1;
        }
        else if (*p < *q) {
            return 1;
        }
        p++;
        q++;
    }
    return 0;
}


int Strncmp(const char* s1, const char* s2, size_t n) {
    const char* p = (const char*)s1;
    const char* q = (const char*)s2;
    while (n--) {
        if (*p > *q) {
            return -1;
        }
        else if (*p < *q) {
            return 1;
        }
        p++;
        q++;
    }
    return 0;
}
void* Memset(void* s, int c, size_t n) {
    char* ret = (char*)s;
    while (n--) {
        *ret++ = (char)c;
    }
    return s;
}
size_t Strlen(const char* s) {
    size_t result = 0;
    while (*s++)   {
        ++result;
    }
    return result;
}
class _string {
private:
    char* str;
    int len;
    int cap;
public:
    _string() :len(0), str(0), cap(0) {}
    _string(const char* s) :len(Strlen(s)) {
        cap = len;
        str = new char[cap + 1];
        Strcpy(str, s);
    }
    _string(const _string& t) :len(Strlen(t.str)) {
        cap = len;
        str = new char[cap + 1];
        Strcpy(str, t.str);
    }
    ~_string() {
        str = nullptr;
        len = 0;
        cap = 0;
        delete[] str;
    }
    size_t size() const noexcept;
    size_t length() const noexcept;
    size_t max_size() const noexcept;
    size_t capacity() const noexcept;

    void shrink_to_fit();
    void clear() noexcept;
    bool empty() const noexcept;

    char& operator[] (size_t pos);
    const char& operator[] (size_t pos) const;

    friend std::ostream& operator<<(std::ostream& os, const _string& str);
    friend std::istream& operator>>(std::istream& is, _string& str);

    _string& operator= (const _string& str);
    _string& operator= (const char* s);
    _string& operator= (char c);

    _string& operator+= (const _string& str);
    _string& operator+= (const char* str);
    _string& operator+= (char c);

    _string operator+ (const _string& t);
    _string operator+ (const char* t);

    friend _string operator+ (const char* str, const _string& t);
    friend _string operator+ (char str, const _string& t);
    friend _string operator+ (const _string& t, char str);


    char& at(size_t pos);
    const char& at(size_t pos) const;

    char& back();
    const char& back() const;

    char& front();
    const char& front() const;

    void resize(size_t n);
    void resize(size_t n, char c);
    void reserve(size_t n = 0);

    void push_back(char c);


    _string& append(const _string& str);
    _string& append(const _string& t, size_t subpos, size_t sublen);
    _string& append(const char* s);
    _string& append(const char* s, size_t n);

    _string& assign(const _string& str);
    _string& assign(const _string& str, size_t subpos, size_t sublen);
    _string& assign(const char* s);
    _string& assign(const char* s, size_t n);

    _string& insert(size_t pos, const _string& str);
    _string& insert(size_t pos, const char* s, size_t n);
    _string& insert(size_t pos, const _string& str, size_t subpos, size_t sublen);

    _string& erase(size_t pos, size_t len);

    _string& replace(size_t pos, size_t len, const _string& str);
    _string& replace(size_t pos, size_t len, const _string& str,size_t subpos, size_t sublen);
    _string& replace(size_t pos, size_t len, const char* s, size_t n);

    void swap(_string& str);

    const char* c_str() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const _string& str)
{
    if (str.str) {
        os << str.str;
    }
    return os;
}


std::istream& operator>>(std::istream& is, _string& str)
{
    char buf[1024];
    is >> buf;
    str = buf;
    return is;

}
size_t _string::size() const noexcept {
    return len;
}

size_t _string::length() const noexcept {
    return len;
}

size_t _string::max_size() const noexcept {
    return UINT_MAX;
}

void _string::resize(size_t n) {
    if (n > cap) {
        cap = n;
        reserve(cap);
        for (int i = len; i < cap; i++) {
            str[i] = '\0';
        }
    }
    else if (n < cap) {
        cap = n;
        char* new_str = new char[cap - 1];
        for (int i = 0; i < cap; i++) {
            new_str[i] = str[i];
        }
        str = nullptr;
        delete[] str;
        str = new_str;
        len = cap;
        str[len] = '\0';
    }

}
void _string::resize(size_t n, char c) {

    if (n > cap) {
        cap = n;
        reserve(cap);
        for (int i = len; i < cap; i++) {
            str[i] = c;
            len++;
        }
        str[len] = '\0';
    }
    else if (n < cap) {
        cap = n;
        char* new_str = new char[cap - 1];
        for (int i = 0; i < cap; i++) {
            new_str[i] = str[i];
        }
        str = nullptr;
        delete[] str;
        str = new_str;
        len = cap;
        str[len] = '\0';
    }
}
void _string::reserve(size_t n) {
    if (n > cap) {
        char* new_a = new char[n + 1];
        Strcpy(new_a, str);
        delete[] str;
        str = new_a;
        cap = n;
    }
}
size_t _string::capacity() const noexcept {
    return cap;
}
void _string::clear() noexcept {
    str = 0;
    len = 0;
}
bool _string::empty() const noexcept {
    return str == 0 || str[0] == '\0';
}
void _string::shrink_to_fit() {
    char* newMas = new char[len];
    for (int i = 0; i < len; i++) {
        newMas[i] = str[i];
    }
    str = nullptr;
    delete[] str;
    str = newMas;
    cap = len;
}
char& _string::operator[] (size_t pos) {
    return str[pos];
}
const char& _string::operator[] (size_t pos) const {
    return str[pos];
}
_string& _string::operator= (const _string& t) {
    if (this != &t) {
        str = new char[Strlen(t.str) + 1];
        Strcpy(str, t.str);
        len = Strlen(t.str);
        cap = t.cap;
    }
    return *this;
}
_string& _string::operator= (const char* s) {
    str = new char[Strlen(s) + 1];
    Strcpy(str, s);
    len = Strlen(s);
    cap = Strlen(s);
    return *this;
}
_string& _string::operator= (char c) {
    char* mas = new char[0];
    mas[0] = c;
    str = nullptr;
    delete[] str;
    str = mas;
    len = 1;
    cap = 1;
    str[len] = '\0';
    return *this;
}
char& _string::at(size_t pos) {
    if (pos >= len) throw std::out_of_range("Invalid index");
    return str[pos];
}
const char& _string::at(size_t pos) const {
    if (pos >= len) throw std::out_of_range("Invalid index");
    return str[pos];
}
char& _string::back() {
    if (!len) throw std::out_of_range("Invalid index");
    int s = len - 1;
    char* per = str;
    while (s--) {
        *per++;
    }
    return *per;
}
const char& _string::back() const {
    if (!len) throw std::out_of_range("Invalid index");
    int s = len - 1;
    char* per = str;
    while (s--) {
        *per++;
    }
    return *per;
}
char& _string::front() {
    if (!len) throw std::out_of_range("Invalid index");
    return str[0];
}
const char& _string::front() const {
    if (!len) throw std::out_of_range("Invalid index");
    return str[0];
}
_string& _string::operator+= (const _string& t) {
    int newLength = len + t.len;
    int newcap = cap + t.cap;
    char* newStr = new char[newcap + 1];
    Strcpy(newStr, str);
    Strcat(newStr, t.str);
    delete[] str;
    str = newStr;
    len = newLength;
    cap = newcap;
    return *this;
}
_string& _string::operator+=(const char* t) {
    int len1 = Strlen(t);
    int newLength = len + len1;
    int newcap = Strlen(t) + cap;
    char* newStr = new char[newLength + 1];
    Strcpy(newStr, str);
    Strcat(newStr, t);
    str = nullptr;
    delete[] str;
    str = newStr;
    len = newLength;
    cap = newcap;
    return *this;
}
_string& _string::operator+= (char c) {
    int len1 = 1;
    int newLength = len + len1;
    int newcap = 1 + cap;
    char* newStr = new char[newLength + 1];
    for (int i = 0; i < newLength; i++) {
        if (str[i] == '\0') {
            break;
        }
        newStr[i] = str[i];
    }
    newStr[newLength - 1] = c;
    newStr[newLength] = '\0';
    str = nullptr;
    delete[] str;
    str = newStr;
    len = newLength;
    cap = newcap;
    return *this;
}
_string _string::operator+ (const _string& t) {
    _string res;
    res.str = new char[Strlen(str) + Strlen(t.str) + 1];
    Strcpy(res.str, str);
    Strcat(res.str, t.str);
    return res;
}
_string _string::operator+ (const char* t) {
    _string res;
    res.str = new char[Strlen(str) + Strlen(t) + 1];
    Strcpy(res.str, str);
    Strcat(res.str, t);
    return res;
}
_string operator+ (const char* str, const _string& t) {
    _string res;
    res.str = new char[Strlen(str) + Strlen(t.str) + 1];
    Strcpy(res.str, str);
    Strcat(res.str, t.str);
    return res;
}
_string operator+ (char str, const _string& t) {
    _string res;
    res.str = new char[Strlen(t.str) + 2];
    res.str[0] = str;
    res.str[1] = '\0';
    Strcat(res.str, t.str);
    return res;
}
_string operator+ (const _string& t, char str) {
    _string res;
    res.str = new char[Strlen(t.str) + 2];
    for (int i = 0; i < Strlen(t.str); i++) {
        if (t.str[i] == '\0') {
            break;
        }
        res.str[i] = t.str[i];
    }
    res.str[Strlen(t.str)] = str;
    res.str[Strlen(t.str) + 1] = '\0';
    return res;
}
_string& _string::append(const _string& t) {
    if (len + Strlen(t.str) > cap)
        reserve(cap + t.cap);
    Strcpy(str + len, t.str);
    len += Strlen(t.str);
    return *this;
}
_string& _string::append(const _string& t, size_t subpos, size_t sublen) {
    if (len + sublen > cap)
        reserve(cap + sublen);
    char* newmas = new char[sublen];
    int j = 0;
    for (int i = subpos; i < subpos + sublen; i++) {
        newmas[j++] = t.str[i];
    }
    Strcpy(str + len, newmas);
    len += sublen;
    str[len] = '\0';
    return *this;
}
_string& _string::append(const char* t) {
    if (len + Strlen(t) > cap)
        reserve(cap + Strlen(t));
    Strcpy(str + len, t);
    len += Strlen(t);
    return *this;
}
_string& _string::append(const char* t, size_t n) {
    if (len + n > cap)
        reserve(cap + n);
    char* newmas = new char[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        newmas[j++] = t[i];
    }
    Strcpy(str + len, newmas);
    len += n;
    str[len] = '\0';
    return *this;
}
void _string::push_back(char c) {
    if (len + 1 > cap)
        reserve(cap + 1);
    str[len] = c;
    str[cap] = '\0';
    len += 1;
}
_string& _string::assign(const _string& t) {
    char* mas = new char[Strlen(t.str)];
    for (int i = 0; i < Strlen(t.str); i++) {
        mas[i] = t.str[i];
    }
    delete[] str;
    str = mas;
    len = Strlen(t.str);
    cap = t.capacity();
    str[len] = '\0';
    return *this;
}
_string& _string::assign(const _string& t, size_t subpos, size_t sublen) {
    if (len + sublen > cap)
        reserve(cap + sublen);
    char* newmas = new char[sublen];
    int j = 0;
    for (int i = subpos; i < subpos + sublen; i++) {
        newmas[j++] = t.str[i];
    }
    Strcpy(str, newmas);
    len += sublen;
    str[len] = '\0';
    return *this;
}
_string& _string::assign(const char* t) {
    if (len + Strlen(t) > cap)
        reserve(cap + Strlen(t));
    Strcpy(str, t);
    len += Strlen(t);
    return *this;
}
_string& _string::assign(const char* t, size_t n) {
    if (len + n > cap)
        reserve(cap + n);
    char* newmas = new char[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        newmas[j++] = t[i];
    }
    Strcpy(str, newmas);
    len += n;
    str[len] = '\0';
    return *this;
}
_string& _string::insert(size_t pos, const _string& t) {
    if (len == cap)
        reserve(cap * 2);
    _string s(*this);
    int len1 = Strlen(t.str);
    char* arr = s.str + pos;
    Strcpy(str + pos, t.str);
    Strcpy(str + pos + len1, arr);
    len += len1;
    return *this;
}
_string& _string::insert(size_t pos, const char* t, size_t n) {
    if (len == cap)
        reserve(cap * 2);
    _string s(*this);
    int len1 = n;
    char* arr = s.str + pos;
    Strcpy(str + pos, t);
    Strcpy(str + pos + len1, arr);
    len += len1;
    return *this;
}
_string& _string::insert(size_t pos, const _string& t, size_t subpos, size_t sublen) {
    if (len == cap)
        reserve(cap * 2);
    char* newmas = new char[sublen];
    int j = 0;
    for (int i = subpos; i < subpos + sublen; i++) {
        newmas[j++] = t.str[i];
    }
    _string s(*this);
    int len1 = sublen;
    char* arr = s.str + pos;
    Strcpy(str + pos, newmas);
    Strcpy(str + pos + len1, arr);
    len += len1;
    return *this;
}
_string& _string::erase(size_t pos, size_t len1) {
    if (pos > len) throw std::out_of_range("Invalid index");
    if (pos + len1 >= len){
        len = pos;
        str[pos] = '\0';
    }
    else{
        char* arr = str + pos;
        char* s = arr + len1;
        Strcpy(str + pos, s);
        len -= len1;
    }
    return *this;
}
_string& _string::replace(size_t pos, size_t lens, const _string& t) {
    if (len == cap)
        reserve(cap * 2);
    _string s(*this);
    s.erase(pos, lens);
    int len1 = Strlen(t.str);
    char* arr = s.str + pos;
    Strcpy(str + pos, t.str);
    Strcpy(str + pos + len1, arr);
    return *this;
}
_string& _string::replace(size_t pos, size_t lens, const _string& t, size_t subpos, size_t sublen) {
    if (len == cap)
        reserve(cap * 2);
    char* newmas = new char[sublen];
    int j = 0;
    for (int i = subpos; i < subpos + sublen; i++) {
        newmas[j++] = t.str[i];
    }
    _string s(*this);
    s.erase(pos, lens);
    int len1 = sublen;
    char* arr = s.str + pos;
    Strcpy(str + pos, newmas);
    Strcpy(str + pos + len1, arr);
    len += 1;
    return *this;
}
_string& _string::replace(size_t pos, size_t lens, const char* t, size_t n) {
    if (len == cap)
        reserve(cap * 2);
    _string s(*this);
    s.erase(pos, lens);
    int len1 = n;
    char* arr = s.str + pos;
    Strcpy(str + pos, t);
    Strcpy(str + pos + len1, arr);
    return *this;
}
void _string::swap(_string& t) {
    char* temp = t.str;
    t.str = str;
    str = temp;
    int tem = len;
    len = t.len;
    t.len = tem;
    int te = cap;
    cap = t.cap;
    t.cap = te;
}
const char* _string::c_str() const noexcept {
    return str;
}
#endif // _STRING_CPP
