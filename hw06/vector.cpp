#include "vector.h"

#include <iterator>



namespace linalg {
auto operator<<(std::ostream& ostr, const Vector& x) -> std::ostream& {
    ostr << "[ ";
    std::copy(x.begin(), x.end(), std::ostream_iterator<float>(ostr, " "));
    ostr << "]";
    return ostr;
}
}

/*
 * Please Implement all functions from the header file here!#
 * Have fun! :-) And don't forget maybe you can use standard algorithms ;-)
 */

namespace linalg{

    Vector::Vector(std::size_t n){
        data_.resize(n);
         
    }

    Vector::Vector(std::size_t n, float val){
        data_.resize(n,val);
    }

    Vector::Vector(std::initializer_list<float> list): data_(list){}


    auto Vector::operator=(float val) -> Vector &{

        assign(val);
        return *this; 
    }

    auto Vector::assign(float val) -> void{

        std::for_each(data_.begin(),data_.end(),
        [&val](float &n){n = val;}
        );
    }

    auto Vector::assign(Vector v) -> void{


        data_ = v.data_; 

    }

    auto Vector::size() const -> std::size_t{

        return data_.size();
    }

    auto Vector::begin() -> iterator{

        return data_.begin();
    }

    auto Vector::end() -> iterator{

        return data_.end();
    }

    auto Vector::begin() const -> const_iterator{
        return data_.begin();
    }

    auto Vector::end() const -> const_iterator{

        return data_.end();
    }

    auto Vector::cbegin() const -> const_iterator{

        return begin();
    }

    auto Vector::cend() const -> const_iterator{

        return end();
    }



    auto Vector::operator[](int idx) -> float &{

        int index{0};
        int cur_size = size();
        if (idx<0){
            index = cur_size + idx;
        }else{
            index = idx;
        }

        

            if (index<0||index>=cur_size){
                throw (std::out_of_range{"Out of range"});
            }

            return data_.at(index);
    }

    auto Vector::operator[](int idx) const -> const float &{


        // return (*this)[idx];

        int index{0};
        int cur_size = size();
        if (idx<0){
            index = cur_size + idx;
        }else{
            index = idx;
        }

        

            if (index<0||index>=cur_size){
                throw (std::out_of_range{"Out of range"});
            }

            return data_.at(index);
    

        
    }

    auto Vector::coeff(int idx) -> float &{


        int cur_size = size();

        if(idx>=cur_size||idx<0){
            throw (std::out_of_range{"Out of range"});
        }

        return (*this)[idx];

    // return (*this)[idx];
    }

    auto Vector::coeff(int idx) const -> const float &{

        int cur_size = size();

        if(idx>=cur_size||idx<0){
            throw (std::out_of_range{"Out of range"});
        }

        return (*this)[idx];
    }

    auto Vector::operator+=(float val) -> Vector &{


        action(val,std::plus<>{});

        return *this;
    }

    auto Vector::operator-=(float val) -> Vector &{

        action(val,std::minus<>{});
        return *this;
    }

    auto Vector::operator*=(float val) -> Vector &{

        action(val,std::multiplies<>{});
        return *this;
    }

    auto Vector::operator/=(float val) -> Vector &{

        action(val,std::divides<>{});
        return *this;
    }

    auto Vector::operator+=(const Vector &y) -> Vector &{

        if(y.size()!=size()){
            throw (std::invalid_argument{"Diff sizes"});
        }


        for(auto i=0;i<size();i++){

            data_.at(i) = data_.at(i) + y[i];
        }


    return *this;
         

        // action(y,std::plus<const std::vector<float>>{});
    }

    auto Vector::operator-=(const Vector &y) -> Vector &{

        // action(y,std::minus<const std::vector<float>>{});

        if(y.size()!=size()){
            throw (std::invalid_argument{"Diff sizes"});
        }

                for(auto i=0;i<size();i++){

            data_.at(i) = data_.at(i) - y[i];
        }

        return *this;
    }

    auto min(const Vector &x) -> float{


        check_size(x);

        return *(std::min_element(x.begin(),x.end()));
    }

    auto max(const Vector &x) -> float{

        check_size(x);

        return *(std::max_element(x.begin(),x.end()));
    }

    auto argmin(const Vector &x) -> std::size_t{


        check_size(x);
        auto it = std::min_element(x.begin(),x.end());

        return std::distance(x.begin(),it);
    }

    auto argmax(const Vector &x) -> std::size_t{


        check_size(x);

        

        auto it = std::max_element(x.begin(),x.end());

        return std::distance(x.begin(),it);
    }

    auto non_zeros(const Vector &x) -> std::size_t{

        return x.size() - std::count(x.begin(),x.end(),0);
    }

    auto sum(const Vector &x) -> float{


        auto result{0.0};

        for(auto i=x.begin();i!=x.end();i++){

            result= result + *i;
        }

        return result;


        // return std::accumulate(x.begin(),x.end(),0.0);

    }

    auto prod(const Vector &x) -> float{


        return std::accumulate(x.begin(),x.end(),1,std::multiplies<float>{});
    }


    auto Vector::operator*=(const Vector &y) -> Vector &{


        if(size()!=y.size()){


            throw (std::invalid_argument{"Invalid argument"});
        }

        for(auto i=0;i<size();i++){

            data_.at(i) = data_.at(i)*y[i];
        }

        return *this; 
    }

    auto dot(const Vector &x, const Vector &y) -> float{


        Vector result;
        result.assign(x);

        result*=y; 


        return sum(result);

    }

    auto norm(const Vector &x) -> float{}

    auto normalize(Vector &x) -> void{}

    auto normalized(const Vector &x) -> Vector{}

    auto floor(const Vector &x) -> Vector{

        Vector result;

        result.assign(x);


        std::for_each(result.begin(),result.end(),[](float&n){

            n = std::floor(n);
        });

        return result;
    }

    auto ceil(const Vector &x) -> Vector{


        Vector result;
        result.assign(x);
        std::for_each(result.begin(),result.end(),[](float&n){

            n = std::ceil(n);
        });

        return result;
    }

    auto operator+(const Vector &x) -> Vector{

        Vector result;

        result.assign(x);


        std::for_each(result.begin(),result.end(),[](float&n){

            n = +n;
        });


        return result;
    }

    auto operator-(const Vector &x) -> Vector{

        Vector result;

        result.assign(x);

         std::for_each(result.begin(),result.end(),[](float&n){

            n = n*(-1);
        });


        return result;

    }

    auto operator+(const Vector &x, const Vector &y) -> Vector{


        Vector result; 

        result.assign(x);

        result+=y;

        return result; 

    }

    auto operator-(const Vector &x, const Vector &y) -> Vector{


        Vector result; 

        result.assign(x);

        result+=-y; 

        return result; 
    }

    auto operator+(const Vector &x, float val) -> Vector{


        Vector result; 
        result.assign(x); 
        result+=val; 
        return result;
    }

    auto operator-(const Vector &x, float val) -> Vector{

        Vector result; 
        result.assign(x);
        result-=val;
        return result;
    }

    auto operator*(const Vector &x, float val) -> Vector{

        Vector result;
        result.assign(x);

        result*=val;

        return result; 
    }

    auto operator/(const Vector &x, float val) -> Vector{

        Vector result;
        result.assign(x);

        result/=val;

        return result;
    }

    auto operator+(float val, const Vector &x) -> Vector{

        Vector result;
        result.assign(x);

        result+=val;

        return result;
    }

    auto operator-(float val, const Vector &x) -> Vector{

        Vector result;
        result.assign(x);

        result = val + (-result);

        return result;


    }

    auto operator*(float val, const Vector &x) -> Vector{

        Vector result;
        result.assign(x);

        result*=val;

        return result;


    }



void check_size(const Vector& x) {

  if(!x.size()){

            throw (std::invalid_argument{"Invalid argument"});
  }
}




























}