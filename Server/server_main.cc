#include "Server.h"

// add some stations
vector<Station> all_stations;
int Station::station_quantity_ = 0;
int Ticket::ticket_quantity_ = 0;
int Ticket::total_income_ = 0;
void init_stations();

int main()
{
   
	init_stations();
    Server a;
    a.initServer();
    a.run();
}


void init_stations()
{
	all_stations = {
		{"北京", 0},
		{"石家庄", 50},
		{"天津", 100},
		{"济南", 200},
		{"青岛", 230},
		{"威海", 270},
		{"徐州", 500},
		{"南京", 600},
		{"苏州", 650},
		{"宿迁", 700},
		{"芜湖", 800},
		{"合肥", 900},
		{"杭州", 1000},
		{"舟山", 1200},
		{"上海", 1300},
		{"广州", 2000},
		{"深圳", 2200},
		};
}