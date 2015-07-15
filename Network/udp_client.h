//
//  udp_client.h
//  Arkanoid_Message_Client
//
//  Created by Daniel Franco on 7/15/15.
//  Copyright (c) 2015 Daniel. All rights reserved.
//

#ifndef __Arkanoid_Message_Client__udp_client__
#define __Arkanoid_Message_Client__udp_client__

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <thread>
#include <boost/shared_ptr.hpp>



#endif /* defined(__Arkanoid_Message_Client__udp_client__) */
using boost::asio::ip::udp;

class udp_client{
public:
    udp_client(boost::asio::io_service &io_service, std::string host, std::string port);
    void send(std::string message);
    void close();
    std::string receive();
    
private:
    udp::socket socket;
    udp::endpoint receiver_endpoint;
    udp::endpoint sender_endpoint;
};