/**\file
 * \brief
 * UDP asynchronous client example
 * @version 22.07.2021
 * @author João Pedro Carvalho de Souza
 */

#include <iostream>
#include "udp_interface.h"

int main(){

    udp_interface::UDPClient client(udp_interface::IPv4,"192.168.1.70",3303);
    if(!client.send("Test String")) {
        std::cout << "Output: " << client.getOutputMSG() << std::endl;
        return -1;
    }

    std::cout << "Output" << client.getOutputMSG() << std::endl;
    return 0;

}