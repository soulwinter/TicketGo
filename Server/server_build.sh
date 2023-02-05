g++ -c ../Entity/Task.cc
g++ -c ../Entity/Train.cc
g++ -c ../Entity/Ticket.cc
g++ -c ../Entity/Station.cc


g++ -c Server.cc
g++ -c server_main.cc
g++ -pthread Task.o  Ticket.o Station.o Train.o Server.o server_main.o -o TicketGoServer

./TicketGoServer