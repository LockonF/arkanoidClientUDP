//
//  udp_client.cpp
//  Arkanoid_Message_Client
//
//  Created by Daniel Franco on 7/15/15.
//  Copyright (c) 2015 Daniel. All rights reserved.
//


#include "udp_client.h"

udp_client::udp_client(boost::asio::io_service &io_service, std::string host, std::string port): receiver_endpoint(boost::asio::ip::address::from_string(host.c_str()), std::atoi(port.c_str())), socket(io_service)
{
    socket.open(udp::v4());

}

void udp_client::close()
{
    socket.close();
}

void udp_client::send(std::string message)
{
    boost::shared_ptr<std::string> send_message(new std::string(message));
    socket.send_to(boost::asio::buffer(*send_message), receiver_endpoint);
}

std::string udp_client::receive()
{
    boost::array<char, 5000> recv_buf;
    recv_buf.assign('\0');
    size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
    return std::string(recv_buf.data());
}