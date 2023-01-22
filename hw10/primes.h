#pragma once

#include <cmath>
template <typename T>
constexpr T gcd(const T&a){
    return a;
}

template <typename T>
constexpr T gcd(const T& a, const T&b){

    if(b!=0){

        return gcd(b,a%b);
    }else{

        return a;
    }
}

template<typename Head, typename ... Tail>
constexpr Head gcd(const Head & head,const Tail & ... tail){

    return gcd(head,gcd(tail...));
}


template<typename ...Args>
constexpr unsigned multiply(const Args & ...head){

    return (head * ...);
}


template<typename T>
constexpr T multiply(const T &a, const T&b){

    return a*b;
}


template <typename T>
constexpr T mcm(const T& a, const T&b){

    return multiply(a,b)/gcd(a,b);
}


template<typename Head, typename ... Tail>
constexpr Head mcm(const Head & head,const Tail & ... tail){

    return mcm(head,mcm(tail...));
}

template<unsigned B,unsigned E,unsigned M>
struct Power{
    static constexpr int value = ((B%M)*(Power<B,E-1,M>::value)%M)%M;
};
template <unsigned B,unsigned M>

struct Power<B,0,M>{

    static constexpr int value = 1%M;
};







