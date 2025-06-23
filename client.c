#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h> // for inet_pton
#include<netinet/in.h> // for sockaddr_in

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int sock = 0; //client socket descriptor
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0); // create a TCP socket
    if(sock < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = AF_INET; // IPv4 address family
    serv_addr.sin_port = htons(PORT); // convert port number to network byte order
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); // convert IP address from text to binary form
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); // connect to the server
    // connect() tells the OS I want to establish a TCP connection to that IP:port

    while(1){
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin); // read input from the user
        if(strncmp(buffer, "exit", 4) == 0) { // check for exit command
            printf("Exiting...\n");
            break;  
        }
        send(sock, buffer, strlen(buffer), 0); // send data to the server
        memset(buffer, 0, BUFFER_SIZE); // clear the buffer
        int bytes = read(sock, buffer, BUFFER_SIZE); // read data from the server
        if(bytes <= 0) {
            perror("Server closed connection");
            break; // exit if server closes connection  
        }
        printf("Server: %s", buffer); // print the server's response
        close(sock); // close the socket
        return 0;
        
    }
}