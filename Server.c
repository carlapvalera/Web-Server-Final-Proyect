#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Server.h"


//Implementacion de la estructura Server
struct Server server_constructor(int domain, int service, int protocol,unsigned long interface,
                                int port, int backlog, void (*launch)(struct Server *server)) {
    struct Server server;
    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface;
    server.port = port;
    server.backlog = backlog;
    server.launch = launch;
    
    server.address.sin_family=domain;
    server.address.sin_port=htons(port);
    //Esta opcion envia directamente a la direccion ip del servidor  127.0.0.1
    //server.address.sin_addr.s_addr=htonl(interface);
    //Aca se deja seleccionar manualmente que direccion se quiere
     server.address.sin_addr.s_addr = inet_addr("127.0.0.1");  // Dirección IP del servidor
    //Crear el socket
    server.socket=socket(domain,service,protocol);
    if(server.socket==0){
        perror("failed to connect socket ...");
        exit(1);
    }

    //Asignar el socket a la direccion ip y al puerto
   if(( bind(server.socket,(struct sockaddr*)&server.address,sizeof(server.address)))<0)
   {
         perror("failed to bind socket ...");
         exit(1);
   }

   //Esperar a que se conocecte el cliente
   if((listen(server.socket,server.backlog))<0)
   {
            perror("failed to listen socket ...");
            exit(1);
   }
   
   server.launch = launch;


    return server;
}
