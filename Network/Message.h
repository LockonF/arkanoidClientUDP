//
//  Message.h
//  Arkanoid
//
//  Created by Daniel Franco on 7/13/15.
//  Copyright (c) 2015 Daniel. All rights reserved.
//

#ifndef __Arkanoid__Message__
#define __Arkanoid__Message__

#include <cstdio>
#include <cstdlib>
#include <string>

#endif /* defined(__Arkanoid__Message__) */


//Clase base para enviar mensajes por TCP
class Message{
public:
    Message();
    enum {header_length = 4};
    enum {max_body_length = 3000};
    const char * data() const;
    char * data();
    std::size_t length() const;
    const char * body() const;
    char * body();
    std::size_t body_length() const;
    void body_length(std::size_t new_length);
    bool decode_header();
    void encode_header();
    

private:
    char data_[header_length+max_body_length];
    std::size_t body_length_;
    
};