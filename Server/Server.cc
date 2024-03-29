#include "Server.h"
extern vector<Station> all_stations;

Server::Server()
{
    for (i = 0; i < max_clients_; i++)
	{
		client_socket_[i] = 0;
	}
	// create a test train, station_number should be 11~15
	trains_.push_back(Train(100, 11, 0));
	trains_.push_back(Train(100, 13, 1));
	trains_.push_back(Train(100, 15, 2));
	trains_.push_back(Train(100, 12, 3));
	
	
    
	
}

// Work on every task on multi-threads
void Server::dealTask(int i)
{
	while (true)
	{
		std::unique_lock<std::mutex> locker(task_mutex_);
		
		
		if (!task_queue_.empty())
		{
			// get the to-do task and pop it
			Task to_deal_task = task_queue_.front();
			task_queue_.pop();
			// unlock immediately after get a task out
			locker.unlock();
			task_cond_.notify_all();

			// get the task type
			// see details in Task.h
			Message isOk = to_deal_task.doTask(trains_);
			if (isOk.code)
			{
				send(to_deal_task.getSd(), isOk.message , strlen(isOk.message) , 0);
				// print the available seats quantity
				// printf("seats: %d\n", test_train.getTicketNumber(to_deal_task.getRequestArguments()[0], to_deal_task.getRequestArguments()[1]));
				
			} else {
				send(to_deal_task.getSd(), isOk.message , strlen(isOk.message) , 0);
			}
			
		
		} else {
			// wait for unlock
			task_cond_.wait(locker);
		}
	}
	puts("Server out.\n");
}

int Server::addTaskToQueue(int sd, char content[])
{
	
	Task new_task(sd, content, tickets_);
	std::unique_lock<std::mutex> locker(task_mutex_);
	task_queue_.push(new_task);
	locker.unlock();
	task_cond_.notify_all();
}

int Server::initServer()
{
    //create a master socket
	if( (master_socket_ = socket(AF_INET , SOCK_STREAM , 0)) == 0)
	{
		perror("socket failed");
		return FAIL_INIT;
	}
	
	//set master socket to allow multiple connections
	if( setsockopt(master_socket_, SOL_SOCKET, SO_REUSEADDR, (char *)&opt_,
		sizeof(opt_)) < 0 )
	{
		perror("setsockopt");
		return FAIL_INIT;
	}
	
	//type of socket created
	address_.sin_family = AF_INET;
	address_.sin_addr.s_addr = INADDR_ANY;
	address_.sin_port = htons( PORT );
		
	//bind the socket to localhost port 8888
	if (bind(master_socket_, (struct sockaddr *)&address_, sizeof(address_))<0)
	{
		perror("bind failed");
		return FAIL_INIT;
	}
	printf("Listener on port %d \n", PORT);
		
	//try to specify maximum of 3 pending connections for the master socket
	if (listen(master_socket_, 3) < 0)
	{
		perror("listen");
		return FAIL_INIT;
	}
		
	// accept the incoming connection
	addrlen_ = sizeof(address_);
	puts("Waiting for connections ...");

	// Initialize and start the task_dealer threads
	for (int i = 0; i < TASK_DEALER_NUMBER; i++)
	{
		task_dealer_[i] = std::thread(&Server::dealTask, this, i);
	}
	for (int i = 0; i < TASK_DEALER_NUMBER; i++)
	{
		task_dealer_[i].detach();
	}

}

int Server::run()
{
	while(TRUE)
	{
		//clear the socket set
		FD_ZERO(&readfds_);
	
		//add master socket to set
		FD_SET(master_socket_, &readfds_);
		max_sd = master_socket_;
			
		//add child sockets to set
		for ( i = 0 ; i < max_clients_ ; i++)
		{
			//socket descriptor
			sd_ = client_socket_[i];
				
			//if valid socket descriptor then add to read list
			if(sd_ > 0)
				FD_SET( sd_ , &readfds_);
				
			//highest file descriptor number, need it for the select function
			if(sd_ > max_sd)
				max_sd = sd_;
		}
	
		//wait for an activity on one of the sockets , timeout is NULL ,
		//so wait indefinitely
		activity_ = select( max_sd + 1 , &readfds_ , NULL , NULL , NULL);
	
		if ((activity_ < 0) && (errno!=EINTR))
		{
			printf("select error");
		}
			
		//If something happened on the master socket ,
		//then its an incoming connection
		if (FD_ISSET(master_socket_, &readfds_))
		{
			if ((new_socket_ = accept(master_socket_,
					(struct sockaddr *)&address_, (socklen_t*)&addrlen_))<0)
			{
				perror("accept");
				exit(EXIT_FAILURE);
			}
			
			//inform user of socket number - used in send and receive commands
			printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket_ , inet_ntoa(address_.sin_addr) , ntohs(address_.sin_port));
		
				
			//add new socket to array of sockets
			for (i = 0; i < max_clients_; i++)
			{
				//if position is empty
				if( client_socket_[i] == 0 )
				{
					client_socket_[i] = new_socket_;
					printf("Adding to list of sockets as %d\n" , i);
						
					break;
				}
			}
		}
			
		//else its some IO operation on some other socket
		for (i = 0; i < max_clients_; i++)
		{
			
			sd_ = client_socket_[i];
				
			if (FD_ISSET( sd_ , &readfds_))
			{
				//Check if it was for closing , and also read the
				//incoming message
				if ((valread_ = read( sd_ , buffer_, MAX_BUFFER)) == 0)
				{
					//Somebody disconnected , get his details and print
					getpeername(sd_ , (struct sockaddr*)&address_, (socklen_t*)&addrlen_);
					printf("Host disconnected , ip %s , port %d \n", \
						inet_ntoa(address_.sin_addr) , ntohs(address_.sin_port));
						
					//Close the socket and mark as 0 in list for reuse
					close( sd_ );
					client_socket_[i] = 0;
				}
					
				else
				{
					//set the string terminating NULL byte on the end
					//of the data read
					buffer_[valread_] = '\0';
					printf("Received from [%d]: %s\n", sd_, buffer_);
					// add tasks to queue
					addTaskToQueue(sd_, buffer_);
					// send(sd_ , buffer_ , strlen(buffer_) , 0);
				}
			}
		}
	}
}

