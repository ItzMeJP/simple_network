/**\file
 * \brief
 * NetworkBasis class declaration
 * @version 23.07.2021
 * @author João Pedro Carvalho de Souza
 */

#ifndef SIMPLE_NETWORK_NETWORK_BASIS_H
#define SIMPLE_NETWORK_NETWORK_BASIS_H

#include <boost/asio.hpp>

namespace simple_network {

    enum IPVersion {
        IPv4,
        IPv6,
    };

/// *******************************************************************************************************************
/// <summary>
/// Network common class interface
/// </summary>
    class NetworkBasis {
    public:
/// <summary>
/// Constructor
/// </summary>
        NetworkBasis();

/// <summary>
/// Destructor
/// </summary>
        ~NetworkBasis();

/// <summary>
/// Set target properties
/// </summary>
/// <param name="_protocol"> IP protocol version. IPv4 or IPv6 path.</param>
/// <param name="_ip_address"> IP address.</param>
/// <param name="_port"> IP port.</param>
        void setTarget(int _protocol, std::string _ip_address, unsigned short _port);

/// <summary>
/// Get API output message
/// </summary>
/// <returns> The output message.</returns>
        std::string getOutputMSG();

    protected:
        int protocol_;
        unsigned short port_;
        std::string ip_address_, output_string_;
        //boost::asio::io_service io_service_;
        boost::asio::io_context io_context_;

    private:
/// <summary>
/// Set the IP protocol
/// </summary>
        void setProtocol(int _in);

/// <summary>
/// Set the IP address
/// </summary>
        void setAddress(std::string _in);

/// <summary>
/// Set the IP Port
/// </summary>
        void setPort(unsigned short _in);
    };
}
/// *******************************************************************************************************************

#endif //SIMPLE_NETWORK_NETWORK_BASIS_H
