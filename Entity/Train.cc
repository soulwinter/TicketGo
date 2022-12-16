#include "Train.h"
extern vector<Station> all_stations;

Train::Train(int capacity, int station_number, int train_id) : capacity_(capacity), station_number_(station_number), train_id_(train_id)
{
    // Initialize seats to all available
    each_available_seats_.insert(each_available_seats_.begin(), station_number_ - 1, capacity);
    // randomly generate not_passed_stations
    set<int> not_passed_stations;
    while (not_passed_stations.size() < all_stations.size() - station_number)
    {

        int number = rand() % (all_stations.size() + 1);  // generate a random number from 0 to 15
        not_passed_stations.insert(number);
    }
    // Add stations to the train
    printf("Train %d: ", train_id);
    for (int i = 0; i < all_stations.size(); i++)
    {
        if (!not_passed_stations.count(i))
        {
            stations_.push_back(all_stations[i]);
            printf("%s ", all_stations[i].getName());
        }
    }
    printf("\n");
    
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

int Train::getAbsoluteStationID(int id)
{
    return stations_[id].getStationID();
}

int Train::getStationNumber()
{
    return station_number_;
}

int Train::getTrainID()
{
    return train_id_;
}
