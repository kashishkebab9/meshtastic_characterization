#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Connect to the server
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(5200); // Port number
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP 

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error connecting to server" << std::endl;
        close(clientSocket);
        return 2;
    }

    // Sending data to Server
    const char *message = "Hello from client!";
    send(clientSocket, message, strlen(message), 0);

    // Receive data from the server

    const char* ack = "ACK"; 
    while(true) {
      char buffer[1024] = {0};
      if (recv(clientSocket, buffer, sizeof(buffer), 0) != 0) {;
        std::cout << "Server says: " << buffer << std::endl;
        send(clientSocket, ack, strlen(ack), 0);
      }
    }

    // Close socket
    close(clientSocket); 

    return 0;
}
