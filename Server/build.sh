g++ -c Server.cc
g++ -c server_main.cc
g++ Server.o server_main.o -o TicketGoServer
./TicketGoServer