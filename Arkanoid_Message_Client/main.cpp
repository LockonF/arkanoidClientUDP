#include <cstdlib>
#include <iostream>
#include <string>
#include "TCPClient.h"

int main(int argc, char* argv[])
{
    try
    {
        
        std::string host = "127.0.0.1";
        std::string port = "7000";
        
        boost::asio::io_service io_service;
        
        
        //Nos conectamos al servicio, si no funciona, usar una cadena directamente.
        tcp::resolver resolver(io_service);
        auto endpoint_iterator = resolver.resolve({ host.c_str(), port.c_str() });
        TCPClient c(io_service, endpoint_iterator);
        
        
        //Separamos el thread, esto para poder escribir con cin, pero en el caso del juego es para que pueda seguir ejecutándose en su propio demonio. Con el método write de TCPClient podemos escribir sin problemas dentro del hilo principal
        std::thread t([&io_service](){ io_service.run(); });
        
        
        //Construimos el mensaje
        char line[Message::max_body_length + 1];
        while (std::cin.getline(line, Message::max_body_length + 1))
        {
            Message msg;
            msg.body_length(std::strlen(line));
            std::memcpy(msg.body(), line, msg.body_length());
            msg.encode_header();
            c.write(msg);
        }
        
        c.close();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}