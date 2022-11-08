#define PORT 8888

#define TRUE 1
#define FALSE 0

#define FAIL_INIT 101;
#define FAIL_SHUTDOWN 102;

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
class Client 
{
public:
    int init();
    int testSendRequest(char* s);

private:
    int sock = 0, valread, client_fd;
    struct sockaddr_in address;
    char buffer[2048 + 1] = {};
};