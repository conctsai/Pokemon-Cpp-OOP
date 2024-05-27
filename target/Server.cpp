#include "Platform/Platform.hpp"
#include <boost/asio.hpp>

int main()
{
    boost::asio::io_service io_service;
    boost::asio::ip::udp::socket socket(io_service);
    socket.open(boost::asio::ip::udp::v4());
    boost::asio::ip::udp::endpoint remote_endpoint(boost::asio::ip::address::from_string("172.30.96.1"), 8080);
    boost::system::error_code error;
    socket.send_to(boost::asio::buffer("Hello World!\n"), remote_endpoint, 0, error);
}