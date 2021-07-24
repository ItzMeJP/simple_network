/**\file
 * \brief
 * TCP client example
 * @version 23.07.2021
 * @author João Pedro Carvalho de Souza
 */


#include <iostream>
#include "tcp_interface.h"

int main(){

    simple_network::tcp_interface::TCPClient client(simple_network::IPv4,"192.168.1.70",3303);
    std::string result;
    if(!client.send_request("Request Test String", result)) {
        std::cout << "Output: " << client.getOutputMSG() << std::endl;
        return -1;
    }

    std::cout << "Output" << client.getOutputMSG() << std::endl;
    std::cout << "Feedback result" << result << std::endl;

    return 0;

}

/*
//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }

        boost::asio::io_context io_context;

        //tcp::resolver resolver(io_context);
        //tcp::resolver::results_type endpoints =
        //        resolver.resolve(argv[1], "daytime");

        tcp::socket socket(io_context);
        socket.connect(boost::asio::ip::tcp::endpoint{boost::asio::ip::make_address("192.168.1.70"), 3303 });
        //boost::asio::connect(socket, endpoints);

        for (;;)
        {
            boost::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof) {
                std::cout << "finalizado" << std::endl;
                break; // Connection closed cleanly by peer.
            }
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            std::cout.write(buf.data(), len);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
 */