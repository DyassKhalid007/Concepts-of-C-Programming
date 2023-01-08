#pragma once
#include "socket.h"

namespace net {

/**
 * TCP socket server. Listens for your request to deliver you juicy data!
 */
class Server {


    public:
        Server(uint16_t port);

    private:
        Socket s;
};

} // namespace net
