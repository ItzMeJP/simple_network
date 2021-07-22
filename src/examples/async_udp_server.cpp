/**\file
 * \brief
 * UDP asynchronous server example
 * @version 22.07.2021
 * @author João Pedro Carvalho de Souza
 */

#include "udp_interface.h"
#include <iostream>

int main(){
    std::string prev_timestamp;
    udp_interface::UDPServer server(udp_interface::IPv4,"192.168.1.70",3303);
    for (;;) {
        server.spinPoll(); //non-blocking update
        if( !(server.getLastReceivedDataTimestamp() == prev_timestamp)) {
            std::cout << "Received from " << server.getLastClientAddress() << " at ["
                      << server.getLastReceivedDataTimestamp() << "] " << "The following message: \n"
                      << server.getLastReceivedData() << std::endl;
            prev_timestamp = server.getLastReceivedDataTimestamp();
        }
        sleep(1);
    }
}

