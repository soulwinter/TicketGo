g++ -c ../Entity/Task.cc
g++ -c ../Entity/Train.cc


g++ -c Server.cc
g++ -c server_main.cc
g++ -pthread Task.o Train.o Server.o server_main.o -o TicketGoServer

./TicketGoServer