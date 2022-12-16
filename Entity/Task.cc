#include "Task.h"

Task::Task(int sd, char content[], vector<Ticket>& tickets) : sd_(sd), tickets_(tickets)
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

Message Task::doTask(Train& train)
{
    // first decode the content
    if(decode() != -1)
    {
        switch (operate_number_)
        {
        case 1:
            // 1 means buy tickets
            if (train.buyTicket(operate_arguments_[0], operate_arguments_[1]))
            {
                // create a new ticket

                tickets_.push_back(Ticket(sd_, train.getTrainID(), train.getAbsoluteStationID(operate_arguments_[0]), train.getAbsoluteStationID(operate_arguments_[1])));
                Message to_send_message{1, "预定成功!"};
                return to_send_message;
            }
            break;
        
        default:
            break;
        }
    } else {
        // return -1 means failed, return false
        Message to_send_message{-1, "操作失败，请重试。"};
        return to_send_message;
    }
}