#pragma once
#include <cmath>
#include <cstring>
#include <vector>
using std::vector;


class Station
{
private:
    int station_id_;
    char name_[50];
    // using for sort and making a price
    int distance_;
public:
    static int station_quantity_;
    Station(const char*, int);
    char *getName();
    int getDistance();
    int getStationID();
    int getDistanceBetween(const Station& station);
};


