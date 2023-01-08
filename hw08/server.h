#pragma once
#include "socket.h"

namespace net {

/**
 * TCP socket server. Listens for your request to deliver you juicy data!
 */
class Server {


    public:
        Server(uint16_t port){};

        Connection accept(){

            FileDescriptor fd;

            Connection c{std::move(fd)};

            return c;
        }

    private:
        Socket s;
};

} // namespace net
