#include "contact_list.h"

#include <algorithm>
#include <numeric>
#include <sstream>


// using namespace contact_list;

// TODO create implementation here!

/*

references used:

https://en.cppreference.com/w/cpp/algorithm/find
https://en.cppreference.com/w/cpp/algorithm/sort
https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
https://stackoverflow.com/questions/26903602/an-enclosing-function-local-variable-cannot-be-referenced-in-a-lambda-body-unles
https://en.cppreference.com/w/cpp/container/vector/erase






*/

namespace contact_list{



bool add(storage& contacts, std::string_view name, number_t number){

    //conversion into string from string_view
    
    auto &map{contacts.map};
    std::string converted_name{name};

    if(get_length(converted_name)&&!is_exists(contacts,converted_name)){

        map.push_back(std::make_pair(converted_name,number));

        return true;
    }

    

    return false;
    





    return true;
}

size_t size(const storage& contacts){

    return contacts.map.size();
}

number_t get_number_by_name(storage& contacts, std::string_view name){


    auto &map = contacts.map;
    auto helper{[&](const std::pair<std::string,number_t>&ele){

        return name==ele.first;
    }};

    auto finder{std::find_if(std::begin(map),std::end(map),helper)};

   
   if (finder!=std::end(map)){
    return finder->second;
   }
    return -1;

    return 0;
}

std::string to_string(const storage& contacts){

    auto map = contacts.map;

    std::string result{""};

    std::string first_name{""};
    std::string phone_number{""};



    for (auto i = std::begin(map); i !=std::end(map); i++)
    {
        /* code */

        first_name = i->first;
        phone_number = std::to_string(i->second);

        if(i!=std::end(map)-1){
            result+=first_name+" - "+phone_number+"\n";
        }else{

            result+=first_name+" - "+phone_number;

        }

    }
    

    return result;

}


bool remove(storage& contacts, std::string_view name){


    auto &map = contacts.map;
    auto helper{[&](const std::pair<std::string,number_t>&ele){

        return name.compare(ele.first)==0;
    }};

    auto finder{std::find_if(std::begin(map),std::end(map),helper)};


   if (finder!=std::end(map)){

    map.erase(finder);
    return true; 
   }
    return false;





    return false;

}

void sort(storage& contacts){

    auto &map = contacts.map;

    auto helper{
        [](std::pair<std::string,number_t> a, std::pair<std::string,number_t> b){
            return a.first<b.first;
        }
    };
    
    std::sort(std::begin(map), std::end(map),helper);

}

std::string get_name_by_number(storage& contacts, number_t number){


    auto &map = contacts.map;
    auto helper{[&](const std::pair<std::string,number_t>&ele){

        return number==ele.second;
    }};

    auto finder{std::find_if(std::begin(map),std::end(map),helper)};

   
   if (finder!=std::end(map)){
    return finder->first;
   }
    return "";

}


number_t get_length(std::string name){
    
    return name.length();
}


bool is_exists(const storage&contacts,std::string name){


    auto &map = contacts.map;


    auto helper{[&](const std::pair<std::string,number_t>&ele){

        return name.compare(ele.first)==0;
    }};
    auto finder{std::find_if(std::begin(map),std::end(map),helper)};

   
   if (finder!=std::end(map)){
    return true;
   }
    return false;
    

}

auto find_iterator(const storage&contacts,std::string name){

    auto &map = contacts.map;


    auto helper{[&](const std::pair<std::string,number_t>&ele){

        return name.compare(ele.first)==0;
    }};
    auto finder{std::find_if(std::begin(map),std::end(map),helper)};

    return finder;

}

}