//
//  tcp_connection.h
//  Poco_Server
//
//  Created by Daniel Franco on 7/13/15.
//  Copyright (c) 2015 Daniel. All rights reserved.
//

#ifndef __Poco_Server__tcp_connection__
#define __Poco_Server__tcp_connection__

#include <stdio.h>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#endif /* defined(__Poco_Server__tcp_connection__) */

using boost::asio::ip::tcp;

//Usamos el template para poder utilizar un apuntador compartido

class tcp_connection:public boost::enable_shared_from_this<tcp_connection>{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;
    static pointer create(boost::asio::io_service &io_service);
    tcp::socket & socket();
    void start();

private:
    //Constructor privado
    tcp_connection(boost::asio::io_service &io_service): socket_(io_service){}
    void handle_write(const boost::system::error_code& /*error*/,size_t /*bytes_transferred*/){}
    tcp::socket socket_;
    std::string message_;
    
};