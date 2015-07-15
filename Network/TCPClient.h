
//
//  TCPClient.h
//  Poco_Server
//
//  Created by Daniel Franco on 7/13/15.
//  Copyright (c) 2015 Daniel. All rights reserved.
//

#ifndef __Poco_Server__TCPClient__
#define __Poco_Server__TCPClient__

#include <stdio.h>
#include <deque>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include "Message.h"

#endif /* defined(__Poco_Server__TCPClient__) */

typedef std::deque<Message> chat_message_deque;
using boost::asio::ip::tcp;
class TCPClient{
public:
    TCPClient(boost::asio::io_service &io_service,tcp::resolver::iterator endpoint_iterator): io_service_(io_service),socket_(io_service){
        do_connect(endpoint_iterator);
    }
    void write(const Message &msg);
    void close();
private:

    void do_connect(tcp::resolver::iterator endpoint_iterator);
    void do_read_header();
    void do_read_body();
    void do_write();
    
    boost::asio::io_service & io_service_;
    tcp::socket socket_;
    Message read_msg_;
    chat_message_deque write_msgs_;
    
};