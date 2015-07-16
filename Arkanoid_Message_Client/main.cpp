#include <cstdlib>
#include <iostream>
#include <string>
#include "udp_client.h"

int main(int argc, char* argv[])
{
    try
    {
        
        std::string host = "127.0.0.1";
        std::string port = "7200";
        
        boost::asio::io_service io_service;
        
        
        //Nos conectamos al servicio. Los parámetros son del host al cual vamos a bindear
        udp::resolver resolver(io_service);
        udp_client c(io_service, host, port);
        
        
        //Separamos el thread, esto para poder escribir con cin, pero en el caso del juego es para que pueda seguir ejecutándose en su propio demonio. Con el método write de TCPClient podemos escribir sin problemas dentro del hilo principal
        std::thread t([&io_service](){ io_service.run(); });
        std::string msg;
        
        //Construimos el mensaje

        
        std::cout<<"Escribe algo: ";
        std::cin>>msg;
        c.send(msg);
        
        //Se queda recibiendo del servidor
        while(1)
        {
           
            std::cout<<"Trying to receive: "<<std::endl;
            std::cout<<c.receive()<<std::endl;

        }
        
        
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}