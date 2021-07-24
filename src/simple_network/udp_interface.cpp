/**\file
 * \brief
 * UDPBasis, UDPClient and UDPServer classes definition
 * @version 22.07.2021
 * @author João Pedro Carvalho de Souza
 */

#include "udp_interface.h"

namespace simple_network {
    namespace udp_interface {

        /// UDP base class
        UDPBasis::UDPBasis() {};

        UDPBasis::~UDPBasis() {}

        /// UDP client class
        UDPClient::UDPClient(int _protocol, std::string _ip_address, unsigned short _port) {
            setTarget(_protocol, _ip_address, _port);
        }

        UDPClient::~UDPClient() {
        }

        bool UDPClient::send(std::string _data) {

            socket_ = std::make_shared<boost::asio::ip::udp::socket>(io_context_);

            try {
                if (protocol_ == simple_network::IPv6)
                    socket_->open(boost::asio::ip::udp::v6());
                else
                    socket_->open(boost::asio::ip::udp::v4());

                socket_->send_to(boost::asio::buffer(_data),
                                 boost::asio::ip::udp::endpoint{boost::asio::ip::make_address(ip_address_), port_});

            }
            catch (std::exception &e) {
                output_string_ = e.what();
                return false;
            }

            output_string_ = "The data was sent to : " + ip_address_ + " | " + std::to_string(port_);
            return true;
        }


        /// UDP server class
        UDPServer::UDPServer(int _protocol, std::string _ip_address, unsigned short _port) {

            setTarget(_protocol, _ip_address, _port);

            socket_ = std::make_shared<boost::asio::ip::udp::socket>(io_context_,
                                                                     boost::asio::ip::udp::endpoint{
                                                                             boost::asio::ip::make_address(ip_address_),
                                                                             port_});
            startReceive();
        }

        UDPServer::~UDPServer() {};

        std::string UDPServer::getLastReceivedData() {
            return current_msg_;
        }

        std::string UDPServer::getLastReceivedDataTimestamp() {
            return current_msg_timestamp_;
        }

        std::string UDPServer::getLastClientAddress() {
            return current_client_info_.address().to_string();
        }

        void UDPServer::generateTimestamp() {
            std::time_t now = std::time(0);
            std::string ss(std::ctime(&now),
                           std::ctime(&now) + sizeof(char) * (strlen(std::ctime(&now)) - 1)); //just to remove a \n
            current_msg_timestamp_ = ss;
        }

        void UDPServer::startReceive() {

            boost::asio::ip::udp::udp::endpoint empty_endpoint;

            socket_->async_receive_from(
                    //boost::asio::buffer(recv_buffer_), remote_endpoint_,
                    boost::asio::null_buffers(), empty_endpoint,
                    boost::bind(&UDPServer::receiveHandler, this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));
        }

        void UDPServer::receiveHandler(const boost::system::error_code &error, std::size_t) {

            if (!error || error == boost::asio::error::message_size) {
                unsigned int available = socket_->available();
                char *buffer = new char[available];
                boost::system::error_code ec;
                unsigned int packetSize = socket_->receive_from(boost::asio::buffer(buffer, available),
                                                                current_client_info_, 0, ec);
                generateTimestamp();
                std::string ss(buffer, buffer + packetSize * sizeof(char));
                current_msg_ = ss;
                startReceive();
            }
        }

        void UDPServer::spinOnce() {
            try {
                io_context_.run_one(); // blocking once but guarantee a new msg
            }
            catch (std::exception &e) {
                output_string_ = e.what();
            }
        }

        void UDPServer::spinPoll() {
            try {
                io_context_.poll(); // blocking once but guarantee a new msg
            }
            catch (std::exception &e) {
                output_string_ = e.what();
            }
        }

        void UDPServer::spinForever() {
            try {
                io_context_.run(); // blocking once but guarantee a new msg
            }
            catch (std::exception &e) {
                output_string_ = e.what();
            }
        }
    }
}