#include "Server.h"

// add some stations
vector<Station> all_stations;
int Station::station_quantity_ = 0;
// Ticket
int Ticket::ticket_quantity_ = 0;
int main()
{
    all_stations.push_back(Station("Beijing", 0));
	all_stations.push_back(Station("Shijiazhuang", 50));
	all_stations.push_back(Station("Tianjin", 100));
	all_stations.push_back(Station("Jinan", 200));
	all_stations.push_back(Station("Qingdao", 230));
	all_stations.push_back(Station("Weihai", 270));
	all_stations.push_back(Station("Xuzhou", 500));
	all_stations.push_back(Station("Nanjing", 600));
	all_stations.push_back(Station("Suzhou", 650));
	all_stations.push_back(Station("Suqian", 700));
	all_stations.push_back(Station("Wuhu", 800));
	all_stations.push_back(Station("Hefei", 900));
	all_stations.push_back(Station("Bengbu", 1000));
	all_stations.push_back(Station("Hangzhou", 1200));
	all_stations.push_back(Station("Shanghai", 1300));
	all_stations.push_back(Station("Shenzhen", 2000));
	all_stations.push_back(Station("Guangzhou", 2200));


    Server a;
    a.initServer();
    a.run();
}