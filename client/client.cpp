#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 4000
#define HOST "127.0.0.1"

int main() {

    int sock =0, valread, client_fd;
    struct sockaddr_in serv_addr;
    std::string hello = R"({"name": "loona", "age": 20})";
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { // tries creating socket
        printf("\n cant create socket\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    //take string ip addresses and convert to binary
    if (inet_pton(AF_INET, HOST, &serv_addr.sin_addr) <=0) {
        printf("\nInvalid address/address not supported \n");
        return -1;
    }

    if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))<0){
        printf("\nConnection failed \n");
        return -1;
    }

    send(sock, // send and provide socket, data and data length and flags
        hello.c_str(),
        strlen(hello.c_str()), 
        0);
    printf("\nMessage sent\n");
    sleep(1);
    valread = read(sock, buffer, 1024); // pass in socket, buffer and num bytes
    printf("%s\n", buffer);

    close(client_fd);
    return 0;

}
