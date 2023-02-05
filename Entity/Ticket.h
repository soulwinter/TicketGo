#pragma once
#include <vector>
#include "Station.h"
#include <stdio.h>
using std::vector;
class Ticket
{
public:
    Ticket(int user_ID_, int train_ID, int from_station, int to_station);
    static int ticket_quantity_;
    static int total_income_;
    int getUserID();
    int getTicketID();
    int getPrice();
    int getTrainID();
    char* getFromStationName();
    int getFromStation();
    char* getToStationName();
    int getToStation();
    bool getIsRefund();
    void setRefunded();
    void setRelativeStation(int from, int to);
    int getRelativeFrom();
    int getRelativeTo();
private:
    int user_ID_;
    int ticket_ID_;
    int price_;
    int train_ID_;
    int from_station_;
    int to_station_;
    int relative_from_station_id_, relative_to_station_id_;
    bool is_refund_ = false;
};
