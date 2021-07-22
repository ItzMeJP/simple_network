/*
#include <boost/asio.hpp>

int main()
{
    try
    {
        boost::asio::io_service io_context;

        boost::asio::ip::udp::socket socket(io_context);
        socket.open(boost::asio::ip::udp::v4());

        socket.send_to(
                boost::asio::buffer("Hello world!"),
                boost::asio::ip::udp::endpoint{boost::asio::ip::make_address("192.168.1.70"), 3303});
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}
 */
