#include "Client.h"

int Client::init()
{
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failed");
		return FAIL_INIT;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) 
    {
        perror("Invalid address");
        return FAIL_INIT;
    }

    if ((client_fd = connect(sock, (struct sockaddr*)&address, sizeof(address))) < 0) 
    {
        perror("Connection failed");
        return FAIL_INIT;
    }

    return 0;

}

int Client::testSendRequest(char* s)
{
    send(sock, s, strlen(s), 0);
    while (true)
    {
        valread = read(sock, buffer, 2048);
        printf("%s\n", buffer);
    }
    valread = read(sock, buffer, 2048);
    printf("%s\n", buffer);
    return 0;
}