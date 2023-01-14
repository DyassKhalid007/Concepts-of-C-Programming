#pragma once

#include <memory>
#include <ostream>
#include <stdexcept>
#include <utility>

template <typename T>
class Vector {
public:
    Vector() = default;

    /**
     * Creates a vector of size n with values default_val.
     */
    Vector(size_t n, const T& default_val) {

        _size = n;
        _capacity = n;
        _data = std::make_unique<T[]>(_capacity);


        for(auto i=0;i<_size;i++){
            
            _data[i] = default_val;
        }
        
    }



    /**
     * Creates a vector containing the elements in l.
     */
    Vector(std::initializer_list<T> l) {

        _size = 0;
        _capacity = l.size();
        _data = std::make_unique<T[]>(_capacity);

        for(auto it= l.begin();it!=l.end();it++){

            _data[_size++] = *it;
        }


        
    }

    Vector(const Vector& copy) : _size(copy._size), _capacity(copy._capacity) {

        _data = std::make_unique<T[]>(_capacity);

        for(auto i=0;i<_size;i++){

            _data[i] = copy._data[i];
        }
    }

    Vector(Vector&& move) : _size(move._size), _capacity(move._capacity) {


        _data = std::make_unique<T[]>(_capacity);

        for(auto i=0;i<_size;i++){
            _data[i] = std::move(move._data[i]);
        }
    }

    /**
     * Replaces the contents of the vector.
     */
    Vector& operator=(const Vector& copy) {

        _size = copy._size;
        _capacity = copy._capacity;

        _data.reset();

        _data = std::make_unique<T []>(_size);


        for(auto i=0;i<_size;i++){

            _data[i] = copy._data[i];
        }

        return *this;
    }


    /**
     * Replaces the contents of the vector.
     */
    Vector& operator=(Vector&& move) noexcept {

        _capacity = move._capacity;
        _size = move._size;
        _data = std::move(move._data);

        return *this;
    }

    size_t size() const noexcept { return _size; }

    size_t capacity() const noexcept { return _capacity; }

    /**
     * Appends the given element value to the end of the vector.
     */
    void push_back(const T& value) {

        auto current_size = size();
        auto new_size = current_size+1;

        auto new_capacity = calculate_capacity(new_size);

        if(new_capacity!=0){

            resize(new_capacity);
        }

        _data[_size++] = value;
        

    }

    /**
     * Appends the given element value to the end of the vector.
     */
    void push_back(T&& value) {


        auto current_size = size();
        auto new_size = current_size+1;

        auto new_capacity = calculate_capacity(new_size);

        if(new_capacity!=0){

            resize(new_capacity);
        }

        _data[_size++] = std::move(value);



    }

    /**
     * Removes the last element of the vector.
     */
    void pop_back() {

        _size--;
    }

    /**
     * Returns a reference to the element at specified location pos, with bounds checking.
     * If pos is not within the range of the vector, an exception of type std::out_of_range is thrown.
     */
    T& at(const size_t pos) const {


        if(_capacity!=0){
            if(pos>=0&&pos<=_size-1){

                return _data[pos];
            }

        }else{

            throw std::out_of_range{"Out of range"};
        }

        throw std::out_of_range{"Out of range"};
    }

    /**
     * Returns a reference to the element at specified location pos, with bounds checking.
     * If pos is not within the range of the vector, an exception of type std::out_of_range is thrown.
     */
    T& at(const size_t pos) {

        

        return (const_cast<const Vector<T>*>(this))->at(pos); 
    }

    /**
     * Returns a reference to the element at specified location pos.
     * No bounds checking is performed.
     */
    T& operator[](const size_t index) const {

        return _data[index];
    }

    /**
     * Returns a reference to the element at specified location pos.
     * No bounds checking is performed.
     */
    T& operator[](const size_t index) {


        return _data[index];
    }

    friend std::ostream& operator<<(std::ostream& o, Vector<T> v) {
        o << "Size: " << v._size << ", Capacity: " << v._capacity << std::endl;
        for (size_t i = 0; i < v._size; ++i) {
            if (i > 0)
                o << ", ";
            o << v._data[i];
        }
        o << std::endl;
        return o;
    }

    ~Vector() = default;

private:
    // Defines how the `_capacity` is increased.
    size_t growth_factor = 2;
    size_t _size;
    size_t _capacity;

    // Holds vector's data.
    std::unique_ptr<T[]> _data;

    /**
     * Calculates the necessary capacity for new_size.
     * If necessary, double `_capacity` using `growth_factor`.
     */
    size_t calculate_capacity(size_t new_size) {

        if(_capacity==0){

            return new_size;
        }else if(_capacity>=new_size){

            return 0;
        }

        //no resizing necessary
        return _capacity*growth_factor;


    }

    /**
    * Resizes the vector to new_capacity.
    * If the current capacity is less than new_capacity
    * the vector moves all elements to a new array.
    */
    void resize(size_t new_capacity) {


        auto uptr = std::make_unique<T []>(new_capacity);

        for(auto i=0;i<size();i++){

            uptr[i] = std::move(_data[i]);
        }

        _data.reset();

        _data = std::move(uptr);

        _capacity = new_capacity;




    }
};
