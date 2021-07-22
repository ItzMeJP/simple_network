/**\file
 * \brief
 * UDPBasis, UDPClient and UDPServer classes declarations
 * @version 22.07.2021
 * @author João Pedro Carvalho de Souza
 */

#ifndef SIMPLE_NETWORK_UDP_INTERFACE_H
#define SIMPLE_NETWORK_UDP_INTERFACE_H

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>

namespace udp_interface {

    enum IPVersion {
        IPv4,
        IPv6,
    };

/// *******************************************************************************************************************
/// <summary>
/// UDP common class interface
/// </summary>
    class UDPBasis {
    public:
/// <summary>
/// Constructor
/// </summary>
        UDPBasis();

/// <summary>
/// Destructor
/// </summary>
        ~UDPBasis();

/// <summary>
/// Set UDP target properties
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
        boost::asio::io_service io_service_;
        std::shared_ptr<boost::asio::ip::udp::socket> socket_;

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
/// *******************************************************************************************************************

/// *******************************************************************************************************************
/// <summary>
/// UDP server class
/// </summary>
    class UDPServer : public UDPBasis {
    public:

/// <summary>
/// Contructor. The params define the UDP server.
/// </summary>
/// <param name="_protocol"> IP protocol version. IPv4 or IPv6 path.</param>
/// <param name="_ip_address"> IP address.</param>
/// <param name="_port"> IP port.</param>
        UDPServer(int _protocol, std::string ip_address, unsigned short _port);

/// <summary>
/// Destructor.
/// </summary>
        ~UDPServer();

/// <summary>
/// Get the last received UDP message
/// </summary>
/// <returns> The UDP message.</returns>
        std::string getLastReceivedData();

/// <summary>
/// Get the last client IP address that send a message to the server.
/// </summary>
/// <returns> The client IP.</returns>
        std::string getLastClientAddress();

/// <summary>
/// Get the last received UDP message timestamp.
/// </summary>
/// <returns> The UDP message timestamp.</returns>
        std::string getLastReceivedDataTimestamp();

/// <summary>
/// Single blocking spin. When called, the API will block the program executing until receive a valid message in UDP socket.
/// </summary>
        void spinOnce();

/// <summary>
/// Non-blocking spin. When called, the API will update the socket verification and it will continue the program even though none message is received.
/// </summary>
        void spinPoll();

/// <summary>
/// Blocking spin. When called, the API will update the socket verification forever, blocking the program.
/// </summary>
        void spinForever();

    private:

        boost::asio::ip::udp::udp::endpoint current_client_info_;
        std::string current_msg_,
                current_msg_timestamp_;

/// <summary>
///Start the server.
/// </summary>
        void startReceive();

/// <summary>
/// Asynchronous receiver message handler
/// </summary>
/// <param name="_error"> Error message.</param>
/// <param name="_size"> UDP package message size.</param>
        void receiveHandler(const boost::system::error_code &_error, std::size_t _size);

/// <summary>
/// Generate a timestamp
/// </summary>
        void generateTimestamp();

    };
/// *******************************************************************************************************************

/// *******************************************************************************************************************
/// <summary>
/// UDP cleint class
/// </summary>
    class UDPClient : public UDPBasis {
    public:
/// <summary>
/// Contructor. The params define the UDP server.
/// </summary>
/// <param name="_protocol"> IP protocol version. IPv4 or IPv6 path.</param>
/// <param name="_ip_address"> Server IP address.</param>
/// <param name="_port"> Server IP port.</param>
        UDPClient(int _protocol, std::string ip_address, unsigned short _port);

/// <summary>
/// Destructor. The params define the UDP server.
/// </summary>
        ~UDPClient();

/// <summary>
/// Send an UDP message to the server.
/// </summary>
/// <param name="_protocol"> UDP message to sent.</param>
        bool send(std::string _data);

    private:

    };

}
#endif //SIMPLE_NETWORK_UDP_INTERFACE_H
