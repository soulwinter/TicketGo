#include "Task.h"

Task::Task(int sd, char content[]) : sd_(sd)
{
    strcpy(content_, content);
}


int Task::decode()
{
    // TODO: make the arguments right
    char delim[] = " ";  
    char *p;  
    char *token = strtok(content_, delim);  
    operate_number_ = atoi(token);

    while((p = strtok(NULL, delim)))   
    {
        operate_arguments_.push_back(atoi(p));
    } 
    
    return operate_number_;
}

int Task::getRequestType()
{
    return operate_number_;
}

vector<int> Task::getRequestArguments()
{
    return operate_arguments_;
}

int Task::getSd()
{
    return sd_;
}

bool Task::doTask(Train& train)
{
    // first decode the content
    if(decode() != -1)
    {
        switch (operate_number_)
        {
        case 1:
            // 1 means buy tickets
            return train.buyTicket(operate_arguments_[0], operate_arguments_[1]);
            break;
        
        default:
            break;
        }
    } else {
        // return -1 means failed, return false
        return false;
    }
}