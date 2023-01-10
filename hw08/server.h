#pragma once
#include "socket.h"

namespace net {

/**
 * TCP socket server. Listens for your request to deliver you juicy data!
 */
class Server {


    public:
        Server(uint16_t port):s(Socket()){


            s.listen(port);
           
        };

        Connection accept(){
            

            return s.accept();
        }

    private:
        Socket s;
};

} // namespace net
