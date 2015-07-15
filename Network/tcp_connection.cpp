//
//  tcp_connection.cpp
//  Poco_Server
//
//  Created by Daniel Franco on 7/13/15.
//  Copyright (c) 2015 Daniel. All rights reserved.
//

#include "tcp_connection.h"

using boost::asio::ip::tcp;

//Usamos esta función en vez del constructor privado
tcp_connection::pointer tcp_connection::create(boost::asio::io_service& io_service)
{
    return pointer(new tcp_connection(io_service));
}

//Función que nos regresa el socket
tcp::socket & tcp_connection::socket()
{
    return socket_;
}

//Lo que va a hacer el servidor una vez que lo hayamos inicializado, usamos la funcion handle_write en caso de que haya un errror

void tcp_connection::start()
{
    message_ = "hola mundo";
    //Escritura asíncrona
    boost::asio::async_write(socket_, boost::asio::buffer(message_),boost::bind(&tcp_connection::handle_write, shared_from_this(),boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
    
}
