#include "Task.h"
extern vector<Station> all_stations;

Task::Task(int sd, char content[], vector<Ticket>& tickets) : sd_(sd), tickets_(tickets)
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

int Task::getSd()
{
    return sd_;
}

Message Task::doTask(vector<Train>& trains)
{
    string send_message = "";
    char to_char_send_message[MAX_BUFFER];
    Message to_send_message;
    // first decode the content
    if(decode() != -1)
    {
        switch (operate_number_)
        {
        // 1 [a] [b] [c] [d]: buy tickets train[a], from b(relative) to c(relative), d=1 buy/d=0 check
        case 1:
            send_message += "----------------------------------------\n";
            send_message += "您选择的车票当前剩余：";
            send_message += to_string(trains[operate_arguments_[0]].getTicketNumber(operate_arguments_[1], operate_arguments_[2]));
            send_message += "\n";
            send_message += "----------------------------------------\n";
            // Check remaining tickets
            if (operate_arguments_[3] == 0)
            {
                strcpy(to_send_message.message, send_message.c_str());
                to_send_message.code = 1;
                return to_send_message;
            }
            if (trains[operate_arguments_[0]].buyTicket(operate_arguments_[1], operate_arguments_[2]))
            {
                // create a new ticket
                Ticket newTicket(sd_, trains[operate_arguments_[0]].getTrainID(), 
                    trains[operate_arguments_[0]].getAbsoluteStationID(operate_arguments_[1]), 
                    trains[operate_arguments_[0]].getAbsoluteStationID(operate_arguments_[2]));

                // save the relative stations
                newTicket.setRelativeStation(operate_arguments_[1], operate_arguments_[2]);

                tickets_.push_back(newTicket);
                send_message += "预定成功！您的订单如下：\n";
                send_message += "----------------------------------------\n";
                send_message += "订单号：";
                send_message += to_string(newTicket.getTicketID());
                send_message += "\n";
                send_message += "车次：";
                send_message += to_string(newTicket.getTrainID());
                send_message += "\n";
                send_message += "站点：";
                send_message += newTicket.getFromStationName();
                send_message += " ---> ";
                send_message += newTicket.getToStationName();
                send_message += "\n";
                send_message += "售价： ¥";
                send_message += to_string(newTicket.getPrice());
                send_message += "\n----------------------------------------";

                strcpy(to_send_message.message, send_message.c_str());
                to_send_message.code = 1;
                return to_send_message;
            } else {
                Message to_send_message{-1, "操作失败，请检查您的输入，并重试。"};
                return to_send_message;
            }
            break;

        // 2: show all trains
        case 2:
            for (int i = 0; i < trains.size(); i++)
            {
                
                send_message += "[";
                send_message += to_string(i);
                send_message += "] ";
                // get every station's name
                for (int j = 0; j < trains[i].getStationNumber(); j++)
                {
                    send_message += "(";
                    send_message += to_string(j);
                    send_message += ")";
                    send_message += all_stations[trains[i].getAbsoluteStationID(j)].getName();
                    if (j!=trains[i].getStationNumber()-1)
                        send_message += " -> ";
                }
                
                send_message += "\n----------------------------------------\n";
            }
            
            strcpy(to_send_message.message, send_message.c_str());
            to_send_message.code = 1;
            return to_send_message;
            break;

        // 3 [fd] for check ticket orders
        case 3:
            send_message += "----------------------------------------\n";
            for (int i = 0; i < tickets_.size(); i++)
            {
                if (tickets_[i].getUserID() == sd_)
                {
                    send_message += "[";
                    send_message += to_string(tickets_[i].getTicketID());
                    send_message += "]  ";
                    send_message += "车次：";
                    send_message += to_string(tickets_[i].getTrainID());
                    send_message += ",  ";
                    send_message += "站点：";
                    send_message += tickets_[i].getFromStationName();
                    send_message += " ---> ";
                    send_message += tickets_[i].getToStationName();
                    send_message += ",  ";
                    send_message += "售价： ¥";
                    send_message += to_string(tickets_[i].getPrice());
                    send_message += ",  ";
                    send_message += "是否退票： ";
                    send_message += tickets_[i].getIsRefund() ? "是" : "否";
                    send_message += "\n";
                }
                
            }
            if (tickets_.size() == 0 || send_message.empty())
            {
                send_message += "您当前没有订单！";
            }
            strcpy(to_send_message.message, send_message.c_str());
            to_send_message.code = 1;
            return to_send_message;
            break;

        // 4 [a] [fd] refund a ticket order
        case 4:
            // first make sure the [a] exists, is currently user's and hasn't been refunded 
            if (tickets_.size() > operate_arguments_[0] 
                && !tickets_[operate_arguments_[0]].getIsRefund() 
                && tickets_[operate_arguments_[0]].getUserID() == sd_)
            {
                // make it refunded
                tickets_[operate_arguments_[0]].setRefunded();

            
                // make the tickets back
                if (tickets_[operate_arguments_[0]].getRelativeFrom() != 0 || tickets_[operate_arguments_[0]].getRelativeTo() != 0)
                {
                    trains[tickets_[operate_arguments_[0]].getTrainID()].refundTicket(tickets_[operate_arguments_[0]].getRelativeFrom(), tickets_[operate_arguments_[0]].getRelativeTo());
                    send_message += "退票成功！退还金额：¥";
                    send_message += to_string(tickets_[operate_arguments_[0]].getPrice());
                    strcpy(to_send_message.message, send_message.c_str());
                    to_send_message.code = 1;
                    return to_send_message;
                } else {
                    Message to_send_message{-1, "很抱歉，该票无法退换。"};
                    return to_send_message;
                }

            } else {
                send_message += "发生错误。该票已退换或您的输入有误，请重试。";
                strcpy(to_send_message.message, send_message.c_str());
                to_send_message.code = 1;
                return to_send_message;
            }



        // 5: check profit
        case 5:
            send_message += "----------------------------------------\n";
            send_message += "总收益：¥";
            send_message += to_string(Ticket::total_income_);
            send_message += "\n";
            for (int i = 0; i < tickets_.size(); i++)
            {
                send_message += "[";
                send_message += to_string(tickets_[i].getTicketID());
                send_message += "]  ";
                send_message += "车次：";
                send_message += to_string(tickets_[i].getTrainID());
                send_message += ",  ";
                send_message += "站点：";
                send_message += tickets_[i].getFromStationName();
                send_message += " ---> ";
                send_message += tickets_[i].getToStationName();
                send_message += ",  ";
                send_message += "售价： ¥";
                send_message += to_string(tickets_[i].getPrice());
                send_message += ",  ";
                send_message += "是否退票： ";
                send_message += tickets_[i].getIsRefund() ? "是" : "否";
                send_message += "\n";      
            }
            if (tickets_.size() == 0 || send_message.empty())
            {
                send_message += "当前没有订单！";
            }
            strcpy(to_send_message.message, send_message.c_str());
            to_send_message.code = 1;
            return to_send_message;
            break;

        default:
            break;
        }
    } else {
        // return -1 means failed, return false
        Message to_send_message{-1, "操作失败，请检查您的输入，并重试。"};
        return to_send_message;
    }
}
