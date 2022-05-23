#ifndef PAIR_H
#define PAIR_H
#include <iostream>
template<class KeyType, class ValueType>
struct pair
{
    constexpr pair() noexcept = default;
    ~pair() noexcept = default;
    constexpr pair(KeyType key, ValueType value) noexcept
        : first(std::move(key))
        , second(std::move(value))
    {
    }
    template<class T1, class T2>
    constexpr pair(T1&& key, T2&& value) noexcept
        : first(std::forward<T1>(key))
        , second(std::forward<T2>(value))
    {}
    constexpr pair(const pair& pair) noexcept
        : first(pair.first)
        , second(pair.second)
    {}

    constexpr pair& operator = (const pair& pair) noexcept
    {
        first = pair.first;
        second = pair.second;
        return *this;
    }
    constexpr pair& operator = (pair&& pair) noexcept
    {
        first = std::move(pair.first);
        second = std::move(pair.second);
        return *this;
    }
    constexpr pair(pair&& pair) noexcept
        : first(std::forward<KeyType>(pair.first))
        , second(std::forward<ValueType>(pair.second))
    {
    }
    KeyType first;
    ValueType second;
};
#endif // PAIR_H
