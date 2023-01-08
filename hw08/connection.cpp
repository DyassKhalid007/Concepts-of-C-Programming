#include "connection.h"


namespace net{


    ssize_t send(int fd, std::span<const char> data){


        return ::send(fd,reinterpret_cast<const void *>(data.data()),data.size_bytes(),0);
    }

    ssize_t receive(int fd, std::span<char> buf){

        return ::recv(fd,reinterpret_cast<void *>(buf.data()),buf.size_bytes(),0||MSG_WAITALL);
    }


    void Connection::send(std::string_view data) const{

        auto result = net::send(fd(),data);

    }


    void Connection::send(std::istream& data) const{


        // auto result = net::send(fd(),data);
    }


    ssize_t Connection::receive(std::ostream& stream) const{



        // stream<<net::receive(fd(),stream);

        
    }

    ssize_t Connection::receive_all(std::ostream& stream) const{


        std::vector<char> vv;

        stream<<net::receive(fd(),vv);

    }











    




}