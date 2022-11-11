#include <vector>
using std::vector;

class Train
{
private:
    // Capacity of the train
    const int capacity_;

    // The station number the train will pass by
    const int station_number_;

    // each_available_seats_[i] means the available seat number from station[i] to staion[i+1]
    vector<int> each_available_seats_;
    
public:
    Train(int capacity, int station_number);

    // Try to buy ticket
    // Notice: the station id starts from 0 and to_station must greater than from_station
    bool buyTicket(int from_station, int to_station);

    // check if enough tickets
    // Notice: the station id starts from 0 and to_station must greater than from_station
    bool isEnoughTickets(int from_station, int to_station);

    // get available ticker number
    int getTicketNumber(int from_station, int to_station);


};

