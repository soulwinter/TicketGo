#pragma once
#define MAX_BUFFER 2048
#include <stdio.h>
#include <stdlib.h>  // atoi
#include <string.h>
#include <vector>

#include "Train.h"
#include "Ticket.h"

using std::vector;

struct Message {
    int code;
    char message[MAX_BUFFER];
};

class Task
{
private:
    int sd_;
    /*
    content protocol:
    [a] [b] [c] [d] [e] [f] [g]
    [a]:
        1. Buy Tickets from [b] to [c]
    */
    char content_[MAX_BUFFER];


    int operate_number_ = -1;
    vector<int> operate_arguments_;
    vector<Ticket>& tickets_;

public:
    Task(int sd, char content[], vector<Ticket>& tickets);

    // Decode the content from the char[]
    // ret: [1]Buy tickets
    int decode();

    // return operate_number_
    // ret: [1]Buy tickets
    int getRequestType();

    //return operate_arguments_
    vector<int> getRequestArguments();

    // return sd
    int getSd();

    // do the task for 
    Message doTask(Train& train);


};

