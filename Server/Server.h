#define PORT 8888

#define TRUE 1
#define FALSE 0

#define FAIL_INIT 101;
#define FAIL_SHUTDOWN 102;


#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

class Server
{
public:
    Server();
    int init();
    int run();

private:
    int opt = TRUE;
    int master_socket , addrlen , new_socket , client_socket[30] ,
		max_clients = 30 , activity, i , valread , sd;
	int max_sd;
	struct sockaddr_in address;

    // data buffer
    char buffer[2048 + 1];

    fd_set readfds;


};