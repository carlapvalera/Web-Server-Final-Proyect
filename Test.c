//Testing del server 

#include <stdio.h>
#include<string.h>
#include <unistd.h> 
#include"Server.h"

void launch( struct Server *server){
    //Crear el buffer
    char buffer[1024];
    char *hello ="HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
     
    //Longitud de la direccion
    int address_len=sizeof(server->address);
   
    while(1)
    { 
    printf(" Esperando conexion \n"); 
    int new_socket;
    new_socket=accept(server->socket,
    (struct sockaddr*)&server->address,
    (socklen_t*)&address_len);

    //Leer el mensaje del cliente
    int valread=read(new_socket,buffer,1024);
    printf("%s\n",buffer);
    //Enviar el mensaje al cliente
    write(new_socket,hello,strlen(hello));
   
   //Cerrar conexion
    close(new_socket);
    }
}

int main()
{
    struct Server server =server_constructor(AF_INET,SOCK_STREAM,
    0,INADDR_ANY,80,10,launch);
    server.launch(&server);
}
