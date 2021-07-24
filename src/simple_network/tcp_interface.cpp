/**\file
 * \brief
 * TCPBasis, TCPClient and TCPServer classes definition
 * @version 23.07.2021
 * @author João Pedro Carvalho de Souza
 */

#include "tcp_interface.h"

namespace simple_network {
    namespace tcp_interface {

        /// TCP base class
        TCPBasis::TCPBasis() {};

        TCPBasis::~TCPBasis() {};


        /// TCP client class
        TCPClient::TCPClient(int _protocol, std::string _ip_address, unsigned short _port) {
            setTarget(_protocol, _ip_address, _port);
        }

        TCPClient::~TCPClient() {
        }

        bool TCPClient::send_request(std::string _request, std::string &_result) {

            std::string ss;
            socket_ = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);

            try {
                socket_->connect( boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string(ip_address_), port_ ));
                for (;;)
                {
                    boost::array<char, 128> buf;
                    boost::system::error_code error;

                    socket_->send(boost::asio::buffer(_request));
                    size_t len = socket_->read_some(boost::asio::buffer(buf), error);

                    if (error == boost::asio::error::eof) {
                        std::cout << "Acabou: "  << _result << std::endl;
                        break; // Connection closed cleanly by peer.
                    }
                    else if (error)
                        throw boost::system::system_error(error); // Some other error.

                    std::cout.write(buf.data(), len);
                    ss += buf.data();
                }
                _result=ss;
                std::cout << _result << std::endl;
            }
            catch (std::exception &e) {
                output_string_ = e.what();
                return false;
            }



            return true;
        }

        // TCP Server class


    }
}
