#pragma once
#include <concepts>

template <int N, std::integral T = int>
struct fibonacci {

    static constexpr int value=fibonacci<N-1,int>::value+fibonacci<N-2,int>::value;
};


template <>
struct fibonacci<1>{
    static constexpr int value = 1;

};

template <>
struct fibonacci<0>{

    static constexpr int value = 0;

};

