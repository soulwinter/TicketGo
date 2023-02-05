#include "Station.h"

Station::Station(const char* name, int distance) : distance_(distance), station_id_(station_quantity_)
{
    strcpy(name_, name);
    station_quantity_++;
}

int Station::getDistanceBetween(const Station& station)
{
    return abs(distance_ - station.distance_);
}

char* Station::getName()
{
    return name_;
}

int Station::getStationID()
{
    return station_id_;
}

int Station::getDistance()
{
    return distance_;
}