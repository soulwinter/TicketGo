#pragma once
#define PORT 8888


#define MAX_BUFFER 2048
#define TASK_DEALER_NUMBER 5

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

#include <thread>
#include <iostream> // std::cout
#include <deque>    // std::deque
#include <chrono>   // std::chrono
#include <mutex>    // std::mutex
#include <condition_variable>
#include <queue>
#include <string>


#include "../Entity/Task.h"
#include "../Entity/Train.h"
#include "../Entity/Ticket.h"


using std::queue;

class Server
{
public:
    Server();
   
    int initServer();

    int run();
    // put requests from clients to the task-dealing queue
    int addTaskToQueue(int sd, char content[]);
    void dealTask(int i);

    // task-dealing function
    

private:
    int opt_ = TRUE;
    int master_socket_ , addrlen_ , new_socket_ , client_socket_[30] ,
		max_clients_ = 30 , activity_, i , valread_ , sd_;
	int max_sd;
	struct sockaddr_in address_;

    // data buffer
    char buffer_[MAX_BUFFER + 1];

    fd_set readfds_;


    // task queue for dealing requests from clients
    queue<Task> task_queue_;
    // mutex for task_queue_
    std::mutex task_mutex_;
    // create n task_dealer threads
    std::thread task_dealer_[TASK_DEALER_NUMBER];
    // cond for mutex
    std::condition_variable task_cond_;


    
    
    vector<Train> trains_;
    vector<Ticket> tickets_;
    

};