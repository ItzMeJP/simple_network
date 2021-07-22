/*
#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string() {
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class udp_server {
public:
    udp_server(boost::asio::io_service &io_service)
            : socket_(io_service, {boost::asio::ip::make_address("192.168.1.70"), 3303}) {
        start_receive();
    }

    std::string getMsg(){
        //std::string ss(buffer);
        //std::string ss(recv_buffer_.begin(),recv_buffer_.end());
        return current_msg_;
    }

private:
    void start_receive() {
        socket_.async_receive_from(
                //boost::asio::buffer(recv_buffer_), remote_endpoint_,
                boost::asio::null_buffers(), remote_endpoint_,
                boost::bind(&udp_server::handle_receive, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));

    }

    void handle_receive(const boost::system::error_code &error,
                        std::size_t ) {
        if (!error || error == boost::asio::error::message_size) {
            boost::shared_ptr<std::string> message(
                    new std::string(make_daytime_string()));

            // Prepare buffer
            unsigned int available = socket_.available();
            buffer = new char[available];

            boost::asio::ip::udp::endpoint senderEndpoint;
            boost::system::error_code ec;
            unsigned int packetSize = socket_.receive_from(boost::asio::buffer(buffer, available), senderEndpoint, 0, ec);
            std::string ss(buffer,buffer+packetSize*sizeof(char));
            current_msg_ = ss;
            std::cout << "Msg updated "<< available << " | " << packetSize << " : " << ss << std::endl;


            socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
                                  boost::bind(&udp_server::handle_send, this, message,
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));

            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string> ,
                     const boost::system::error_code & ,
                     std::size_t ) {
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1> recv_buffer_;
    char* buffer;
    std::string current_msg_;
};

int main() {
    boost::asio::io_service io_service;
    udp_server server(io_service);


    for (;;) {

        try {
            //io_service.run(); // blocking forever and update each new msg received
            io_service.run_one(); // blocking once but guarantee a new msg
            //io_service.poll(); // non blocking
        }
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        //io_service.poll();

        //io_service.run_one();
        std::cout << server.getMsg() << std::endl;

        sleep(1);
    }
    return 0;
}
*/
