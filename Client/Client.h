#pragma once
#define PORT 8888

#define MAX_BUFFER 2048

#define TRUE 1
#define FALSE 0

#define FAIL_INIT 101;
#define FAIL_SHUTDOWN 102;

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
class Client 
{
public:
    // Initialize for the client
    int init();

    // Test for connction, sending a message to server
    int testSendRequest();

private:
    int sock_ = 0, valread_, client_fd_;
    struct sockaddr_in address_;
    char buffer_[MAX_BUFFER + 1] = {};
};