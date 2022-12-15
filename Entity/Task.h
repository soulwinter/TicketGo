#define MAX_BUFFER 2048
#include <stdio.h>
#include <stdlib.h>  // atoi
#include <string.h>
#include <vector>

#include "Train.h"

using std::vector;

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

public:
    Task(int sd, char content[]);

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
    bool doTask(Train& train);


};
