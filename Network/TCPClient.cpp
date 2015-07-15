//
//  TCPClient.cpp
//  Poco_Server
//
//  Created by Daniel Franco on 7/13/15.
//  Copyright (c) 2015 Daniel. All rights reserved.
//

#include "TCPClient.h"

void TCPClient::write(const Message &msg)
{
    //Función Lambda para el handler de lo que va hacer el io_service al postear
    
    io_service_.post([this,msg](){
        bool write_in_progress = !write_msgs_.empty();
        write_msgs_.push_back(msg);
        if(!write_in_progress){
            do_write();
        }
    });
}

void TCPClient::close()
{
    io_service_.post([this]()
                     {
                         socket_.close();
                     });
}


void TCPClient::do_connect(tcp::resolver::iterator endpoint_iterator)
{
    //El conector requiere del socket, el iterador de endpoints y una función de handler. En este caso la función es una función Lambda
    boost::asio::async_connect(socket_, endpoint_iterator, [this](boost::system::error_code ec,tcp::resolver::iterator){
        //Si no hay error. Dinero es Dinero
        if(!ec)
        {
            do_read_header();
        }
    });
}

void TCPClient::do_read_header()
{
    //La lectura asíncrona requiere de el socket, el buffer que parte de los datos y la longitud que va a leer, que en este caso es el header. Además requiere una función que haga de handler
    boost::asio::async_read(socket_,boost::asio::buffer(read_msg_.data(), Message::header_length),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec && read_msg_.decode_header())
            {
                do_read_body();
            }
            else
            {
                socket_.close();
            }
        });
}

void TCPClient::do_read_body(){
    boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.body(),read_msg_.body_length()),[this](boost::system::error_code ec,std::size_t){
        if(!ec){
            //Aquí procesamos el cuerpo del mensaje
            std::cout.write(read_msg_.body(),read_msg_.body_length());
            std::cout<<std::endl;
            do_read_header();
        }
    });
}

void TCPClient::do_write(){
    boost::asio::async_write(socket_,boost::asio::buffer(write_msgs_.front().data(),write_msgs_.front().length()),[this](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                write_msgs_.pop_front();
                if (!write_msgs_.empty())
                {
                    do_write();
                }
            }
            else
            {
                socket_.close();
            }
        });
}