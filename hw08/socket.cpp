#include "socket.h"


namespace net{



    bool is_listening(int fd){

        socklen_t opt = 1;

        auto result = getsockopt(fd,SOL_SOCKET,SO_ACCEPTCONN,&opt,(socklen_t*)sizeof(opt));

        if (!result){

            
            return true;
        }

        return false;
    }

    Socket::Socket(){

        auto val = ::socket(AF_INET,SOCK_STREAM,0);

        fd_ = std::move(val);

        if(fd()<0){

            throw std::runtime_error{"Socket creation failed"};
        }

    }

    void Socket::listen(uint16_t port) const{


        struct sockaddr_in address;

        
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
        int opt = 1;        
        if(bind(fd(), (struct sockaddr*)&address,sizeof(address))< 0) {
        throw std::runtime_error{"Binding failed"};
    }

    if(::listen(fd(),5)<0){

        throw std::runtime_error{"Listening failed"};

    }


}


    Connection Socket::accept() const{


        if(is_listening(fd())){

            FileDescriptor f{std::move(::accept(fd(),NULL,0))};

            // this->fd_ = std::move(conn);

            Connection c{std::move(f)};

            return c;

        }

        
        throw std::runtime_error{"Listening not happening"};
        
        

    }

    Connection Socket::connect(std::string destination,uint16_t port){



        struct sockaddr_in address;
        address.sin_port = htons(port);
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr(destination.c_str());

        fd_ = std::move(::connect(fd(),reinterpret_cast<const sockaddr *>(&address),sizeof(address)));


        Connection c{std::move(fd_)};


        return c;


        



    }

    Connection Socket::connect(uint16_t port){

        auto it = ::gethostbyname("localhost");
        
        
        return connect(it->h_name,port);




    }

    int Socket::fd() const{
        return fd_.unwrap();
    }

}