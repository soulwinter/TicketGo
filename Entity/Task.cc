#include "Task.h"

Task::Task(int sd, char content[]) : sd_(sd)
{
    strcpy(content_, content);
}


int Task::decode()
{

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
