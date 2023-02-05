#include "Ticket.h"
extern vector<Station> all_stations;

Ticket::Ticket(int user_ID, int train_ID, int from_station, int to_station) : user_ID_(user_ID), train_ID_(train_ID), from_station_(from_station),to_station_(to_station)
{
    // the price is the half the distance between two stations
    price_ = all_stations[from_station].getDistanceBetween(all_stations[to_station]) / 2;
    ticket_ID_ = ticket_quantity_;
    ticket_quantity_++;
    total_income_ += price_;
}

int Ticket::getUserID()
{
    return user_ID_;
}

int Ticket::getTicketID()
{
    return ticket_ID_;
}

int Ticket::getPrice()
{
    return price_;
}

int Ticket::getTrainID()
{
    return train_ID_;
}
int Ticket::getFromStation()
{
    return from_station_;
}
char* Ticket::getFromStationName()
{
    return all_stations[from_station_].getName();
}
int Ticket::getToStation()
{
    return to_station_;
}
char* Ticket::getToStationName()
{
    return all_stations[to_station_].getName();
}
bool Ticket::getIsRefund()
{
    return is_refund_;
}

void Ticket::setRefunded()
{
    is_refund_ = true;
    total_income_ -= price_;
}

void Ticket::setRelativeStation(int from, int to)
{
    relative_from_station_id_ = from;
    relative_to_station_id_ = to;
}

int Ticket::getRelativeFrom()
{
    return relative_from_station_id_;
}
int Ticket::getRelativeTo()
{
    return relative_to_station_id_;
}