#pragma once

#include "connection.h"
#include "socket.h"

namespace net {

/**
 * TCP socket client. Can connect to a server given a destination IP address and a port.
 */
class Client {

    private:

        Socket s;

    public:

    Client():s(Socket()){}
    Connection connect(std::string destination,uint16_t port){

        return s.connect(destination,port);
    }

    Connection connect(uint16_t port){

        return s.connect(port);

        
    }

};

} // namespace net
