#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class tcp_connection
        : public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_context& io_context)
    {
        return pointer(new tcp_connection(io_context));
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
        message_ = make_daytime_string();


        socket_.async_read_some(boost::asio::buffer(request_msg_, 1024),
                boost::bind(&tcp_connection::handle_read,
                            shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));

        std::cout << "foo: " << request_msg_ << std::endl;

        std::cout << "Request received: " << request_msg_ << std::endl;
        std::cout << "Sending feedback message" << std::endl;


        socket_.async_write_some(
                boost::asio::buffer(message_),
                boost::bind(&tcp_connection::handle_write,
                            shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }

private:
    char request_msg_ [1024];

    tcp_connection(boost::asio::io_context& io_context)
            : socket_(io_context)
    {
    }

    // corre depois que escreveu
    void handle_write(const boost::system::error_code& _error_code,
                      size_t _size)
    {
        if (!_error_code) {
            message_ += " !!!!!!!! ";
        } else {
            std::cerr << "error: " << _error_code.message() << std::endl;
            socket_.close();
        }
    }

    // corre depois que leu
    void handle_read(const boost::system::error_code& _error_code,
                      size_t _size)
    {
    }

    tcp::socket socket_;
    std::string message_;
};

class tcp_server
{
public:
    tcp_server(boost::asio::io_context& io_context)
            : io_context_(io_context),
              acceptor_(io_context, boost::asio::ip::tcp::endpoint{boost::asio::ip::make_address("192.168.1.70"), 3303 })
    {
        start_accept();
    }

private:
    void start_accept()
    {
        tcp_connection::pointer new_connection =
                tcp_connection::create(io_context_);

        acceptor_.async_accept(new_connection->socket(),
                               boost::bind(&tcp_server::handle_accept, this, new_connection,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(tcp_connection::pointer new_connection,
                       const boost::system::error_code& error)
    {
        if (!error)
        {
            new_connection->start();
        }

        start_accept();
    }

    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
};

int main()
{
    for(;;){
    try
    {
        boost::asio::io_context io_context;
        tcp_server server(io_context);
        io_context.run_one();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    }

    return 0;
}