#include "Train.h"

Train::Train(int capacity, int station_number) : capacity_(capacity), station_number_(station_number)
{
    // Initialize seats to all available
    each_available_seats_.insert(each_available_seats_.begin(), station_number_ - 1, capacity);
}

bool Train::buyTicket(int from_station, int to_station)
{
    if (isEnoughTickets(from_station, to_station))
    {
        for (int i = from_station; i < to_station; i++)
        {
            each_available_seats_[i]--;
        }
        return true;
    } else {
        return false;
    }
    return false;
}

bool Train::isEnoughTickets(int from_station, int to_station)
{
    
    if (to_station <= from_station || to_station >= station_number_|| from_station >= station_number_)
    {
        return false;
    }

    for (int i = from_station; i < to_station; i++)
    {
        if (each_available_seats_[i] <= 0)
        {
            return false;
        }
    }

    return true;

}

int Train::getTicketNumber(int from_station, int to_station)
{

    if (to_station <= from_station || to_station >= station_number_ || from_station >= station_number_)
    {
        return 0;
    }

    int min_ticket_number = capacity_ + 1;

    for (int i = from_station; i < to_station; i++)
    {
        if (each_available_seats_[i] <= 0)
        {
            return 0;
        } else {
            // get the mininum ticket number which is the number from A to B
            if (min_ticket_number > each_available_seats_[i])
            {
                min_ticket_number = each_available_seats_[i];
            }
        }
    }

    return min_ticket_number;
}