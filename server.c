#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>  // POSIX API 
#include<string.h>
#include<netinet/in.h> // internet address structures sockaddr_in


#define PORT 8080
#define BUFFER_SIZE 1024


int main(){
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE] = {0};
    int addrlen = sizeof(address);

    // create socker
    server_fd = socket(AF_INET, SOCK_STREAM, 0); //creates a TCP(stream) socket in the IPv4 address family
    // check if socket creation was successful
    if(server_fd ==0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // set address family, port and IP address
    address.sin_family = AF_INET; // IPv4 address family
    address.sin_addr.s_addr = INADDR_ANY; // bind to any IP address
    address.sin_port = htons(PORT); // convert port number to network byte order
    // bind the socket to the address
    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE); 
    }
    // bind() ties the socket to that IP+port so the kernel knows which port to listen on.
    // listen
    listen(server_fd, 3); // listen for incoming connections, max 3 queued connections
    printf("Listening on port %d...\n", PORT);
    // accept a connection
    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen); //accept() blocks until a client connects.
    if(new_socket < 0){
        perror("accept failed");
        exit(EXIT_FAILURE);
    }    //Returns a brand-new socket descriptor (new_socket) for that one client
    // echo loop
    while(1){
        memset(buffer, 0, BUFFER_SIZE); // clear the buffer
        int bytes  = read(new_socket, buffer, BUFFER_SIZE); // read data from the client
        if(bytes<=0) break;
        // read() returns the number of bytes read, or -1 on error, or 0 if the client has closed the connection
        send(new_socket, buffer, bytes, 0); // echo back the data
        printf("Received and echoed back: %s\n", buffer);
    }
    close(new_socket); // close the client socket
    close(server_fd); // close the server socket
    printf("Server closed.\n");
    return 0;

}