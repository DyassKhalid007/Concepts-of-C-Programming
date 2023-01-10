#include "connection.h"


namespace net{


    ssize_t send(int fd, std::span<const char> data){


        auto result = ::send(fd,reinterpret_cast<const void *>(data.data()),data.size_bytes(),0);

        if(result<0){

            throw std::runtime_error{"Sending data failed"};
        }

        return result;
    }

    ssize_t receive(int fd, std::span<char> buf){

        auto result = ::recv(fd,reinterpret_cast<void *>(buf.data()),buf.size_bytes(),0);

        if(result<0){
            throw std::runtime_error{"Receiving data failed"};
        }

        return result;
    }


    void Connection::send(std::string_view data) const{

        auto result = net::send(fd(),std::span(data.data(),data.size()));

    }


    void Connection::send(std::istream& data) const{

        std::istreambuf_iterator<char> it{data}, end;
        std::string ss{it, end};

        auto result = net::send(fd(),std::span(ss.data(),ss.size()));


        // auto result = net::send(fd(),data);
    }


    ssize_t Connection::receive(std::ostream& stream) const{ 

        std::string s;
        s.resize(128);

        auto result = net::receive(fd(),std::span(s.data(),s.size()));


        s = s.substr(0,result);



        stream<<s;

        return result;

        
    }

    ssize_t Connection::receive_all(std::ostream& stream) const{

        ssize_t result{0};


        while((result = receive(stream))!=0){

        }

        return result;



        // stream<<net::receive(fd(),vv);

    }

    int Connection::fd() const{

        return fd_.unwrap();
    }











    




}