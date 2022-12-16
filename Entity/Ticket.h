#pragma once
#include <vector>
#include "Station.h"
using std::vector;
class Ticket
{
public:
    Ticket(int user_ID_, int train_ID, int from_station, int to_station);
    static int ticket_quantity_;
private:
    int user_ID_;
    int ticket_ID_;
    int price_;
    int train_ID_;
    int from_station_;
    int to_station_;
    bool is_refund_ = false;
};
