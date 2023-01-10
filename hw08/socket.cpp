#include "socket.h"


namespace net{



    bool is_listening(int fd){

        int opt;
        int len = sizeof(int); 

        auto result = getsockopt(fd, SOL_SOCKET, SO_ACCEPTCONN, (char *)&opt, (socklen_t *)&len);
        
        if(!result){

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
        address.sin_addr.s_addr = htonl(INADDR_ANY);
        address.sin_port = htons(port);
        int opt = 1;       

        if (setsockopt(fd(), SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        throw std::runtime_error{"Setting socket failed"};
    } 
        if(bind(fd(), (struct sockaddr*)&address,sizeof(address))< 0) {
        throw std::runtime_error{"Binding failed"};
    }

    if(::listen(fd(),5)<0){

        throw std::runtime_error{"Listening failed"};

    }

    


}


    Connection Socket::accept() const{




        if(is_listening(fd())){

            auto result = ::accept(fd(),NULL,0);

            if(result<0){

                throw std::runtime_error{"Listening not happening"};

            }

            FileDescriptor f{std::move(result)};
            Connection c{std::move(f)};
            return c;

        }

        
        throw std::runtime_error{"Listening not happening"};
        
        

    }

    Connection Socket::connect(std::string destination,uint16_t port){



        struct sockaddr_in address;
        address.sin_port = htons(port);
        address.sin_family = AF_INET;
        // address.sin_addr.s_addr = inet_addr(destination.c_str());

        if(inet_pton(AF_INET,destination.c_str(),&address.sin_addr)<=0){

            throw std::runtime_error{"Invalid Address"};
        }


       if (::connect(fd(),reinterpret_cast<const sockaddr *>(&address),sizeof(address))<0){
          throw std::runtime_error{"Connection failed"};

       };
        Connection c{std::move(fd_)};

        return c;

    }

    Connection Socket::connect(uint16_t port){
        
        
        return connect("127.0.0.1",port);




    }

    int Socket::fd() const{
        return fd_.unwrap();
    }

}