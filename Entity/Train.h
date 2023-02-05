#pragma once
#include <vector>
#include <set>
#include <string>
#include <cstdlib>
#include "Station.h"
using std::vector;
using std::string;
using std::set;

class Train
{
private:
    // TrainID
    const int train_id_;

    // Capacity of the train
    const int capacity_;

    // The station number the train will pass by
    const int station_number_;

    // the stations the train will passed
    vector<Station> stations_;

    // each_available_seats_[i] means the available seat number from station[i] to staion[i+1]
    vector<int> each_available_seats_;

    vector<int> max_sold_seats_;

    
public:
    // TODO: id
    Train(int capacity, int station_number, int train_id);

    // Try to buy ticket
    // Notice: the station id starts from 0 and to_station must greater than from_station
    bool buyTicket(int from_station, int to_station);

    // check if enough tickets
    // Notice: the station id starts from 0 and to_station must greater than from_station
    bool isEnoughTickets(int from_station, int to_station);

    // get available ticker number
    int getTicketNumber(int from_station, int to_station);

    int getTrainID();
    int getStationNumber();

    // Converts the relative station ID of a train to an absolute ID
    int getAbsoluteStationID(int id);

    void refundTicket(int from_station, int to_station);
   

    

    // the train quantity, for determining the trainID
    static int train_quantity_;

    


};