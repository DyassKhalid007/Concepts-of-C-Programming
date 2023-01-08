#pragma once

#include "connection.h"
#include "socket.h"

namespace net {

/**
 * TCP socket client. Can connect to a server given a destination IP address and a port.
 */
class Client {

    public:

    Client(){}
    Connection connect(std::string destination,uint16_t port){

        return;
    }

    Connection connect(uint16_t port){

        return ;
    }

};

} // namespace net
