#pragma once

#include <array>

template <typename T, typename U, typename V, typename W> 
struct Quadruple {
public:

    Quadruple(T f, U s, V t, W ff){


        first = f;
        second = s; 
        third = t;
        fourth = ff;
    }

    T get_first() const {

        return first;
    }

    U get_second() const {
        return second;
    }

    V get_third() const{

        return third;
    }

    W get_fourth() const{

        return fourth;
    }

private:
    T first ;
    U second;
    V third; 
    W fourth;
};








template <typename T> 
struct Quadruple<T,T,T,T> {
public:

    Quadruple(T f, T s, T t, T ff){


       members[0] = f;
       members[1] = s;
       members[2] = t;
       members[3] = ff;
    }

    T get_first() const {

        return members[0];
    }

    T get_second() const {
        return members[1];
    }

    T get_third() const{

        return members[2];
    }

    T get_fourth() const{

        return members[3];
    }

    T size() const{

        return members.size();
    }

     std::array<T,4> members;

private:

   
  
};
