//
// Created by joaopedro on 23/07/21.
//

#ifndef SIMPLE_NETWORK_TCP_INTERFACE_H
#define SIMPLE_NETWORK_TCP_INTERFACE_H

#include <iostream>
#include <boost/array.hpp>
#include "network_basis.h"

namespace simple_network {
    namespace tcp_interface {

/// *******************************************************************************************************************
/// <summary>
/// TCP common class interface
/// </summary>
        class TCPBasis : public simple_network::NetworkBasis {
        public:
/// <summary>
/// Constructor
/// </summary>
            TCPBasis();

/// <summary>
/// Destructor
/// </summary>
            ~TCPBasis();

        protected:
            std::shared_ptr<boost::asio::ip::tcp::socket> socket_;

        };
/// *******************************************************************************************************************

/// *******************************************************************************************************************
/// <summary>
/// UDP server class
/// </summary>
        class TCPServer : public TCPBasis {
        public:

/// <summary>
/// Contructor. The params define the TCP server.
/// </summary>
/// <param name="_protocol"> IP protocol version. IPv4 or IPv6 path.</param>
/// <param name="_ip_address"> IP address.</param>
/// <param name="_port"> IP port.</param>
            TCPServer(int _protocol, std::string ip_address, unsigned short _port);

/// <summary>
/// Destructor.
/// </summary>
            ~TCPServer();
        };

/// *******************************************************************************************************************

/// *******************************************************************************************************************
/// <summary>
/// UDP client class
/// </summary>
        class TCPClient : public TCPBasis {
        public:
/// <summary>
/// Contructor. The params define the UDP server.
/// </summary>
/// <param name="_protocol"> IP protocol version. IPv4 or IPv6 path.</param>
/// <param name="_ip_address"> Server IP address.</param>
/// <param name="_port"> Server IP port.</param>
            TCPClient(int _protocol, std::string ip_address, unsigned short _port);

/// <summary>
/// Destructor. The params define the UDP server.
/// </summary>
            ~TCPClient();

/// <summary>
/// Send an TCP request message to the server. It is a blocking function until a complete feedback result arrives
/// </summary>
/// <param name="_request"> TCP request message to sent.</param>
/// <param name="_result"> Server feedback.</param>
/// <returns> False if it fails to send, true otherwise.</returns>

            bool send_request(std::string _request, std::string &_result);

        };

    }
}
#endif //SIMPLE_NETWORK_TCP_INTERFACE_H
