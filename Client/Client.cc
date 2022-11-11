#include "Client.h"

int Client::init()
{
    if ((sock_ = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failed");
		return FAIL_INIT;
    }

    address_.sin_family = AF_INET;
    address_.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &address_.sin_addr) <= 0) 
    {
        perror("Invalid address");
        return FAIL_INIT;
    }

    if ((client_fd_ = connect(sock_, (struct sockaddr*)&address_, sizeof(address_))) < 0) 
    {
        perror("Connection failed");
        return FAIL_INIT;
    }

    return 0;

}

// just send all input string entered by user
int Client::testSendRequest()
{
    
    char toSend[MAX_BUFFER];

    while (true)
    {
        std::cin.getline(toSend, 80);
        send(sock_, toSend, strlen(toSend), 0);
        std::cout << "Send successful. [" << toSend << "]\n";

        valread_ = read(sock_, buffer_, MAX_BUFFER);
        // set the receiving data length
        buffer_[valread_] = '\0';
        printf("Receiced: %s\n", buffer_);

    }
        
    return 0;
}