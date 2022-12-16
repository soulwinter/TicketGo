#include "Ticket.h"
extern vector<Station> all_stations;

Ticket::Ticket(int user_ID, int train_ID, int from_station, int to_station) : 
user_ID_(user_ID), 
train_ID_(train_ID), 
from_station_(from_station),
to_station_(to_station)
{
    // TODO: 有问题，应该使用 Station 的类
    price_ = all_stations[from_station].getDistanceBetween(all_stations[to_station]);
    ticket_ID_ = ticket_quantity_;
    ticket_quantity_++;
}