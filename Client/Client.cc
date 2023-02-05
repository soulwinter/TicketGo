#include "Client.h"

int Client::init()
{
    if ((sock_ = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failed");
		return FAIL_INIT;
    }

    address_.sin_family = AF_INET;
    address_.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &address_.sin_addr) <= 0) 
    {
        perror("Invalid address");
        return FAIL_INIT;
    }

    if ((client_fd_ = connect(sock_, (struct sockaddr*)&address_, sizeof(address_))) < 0) 
    {
        perror("连接失败 Connection failed（可能是未打开服务端）");
        exit(-1);
        return FAIL_INIT;
    }

    return 0;

}

void Client::welcomePrinter()
{
    printf("========================================\n");
    printf("欢迎使用 TicketGo 订票系统！\n");
    printf("本系统默认采用优化后的放票模式。因本系统为简单 Demo，不基于数据库，因此系统将不会保存您的购买信息。\n");
}

int Client::operations()
{
    printf("========================================\n");
    printf("请输入您想进行的操作前面的数字！\n");
    printf("[1] 购票\n");
    printf("[2] 查看订单\n");
    printf("[3] 退票\n");
    printf("[4] 查询余票\n");
    printf("[5] 查看车票收益\n");
    int operation_number;
    scanf("%d", &operation_number);
    return operation_number;
}

int Client::showAllTrains()
{
    printf("========================================\n");
    printf("以下为当前开设的列车\n");  
    if (sendRequest("2") == 0)
    {
        return 0;
    } else {
        printf("出错了，请重试。\n");  
    };
    printf("========================================\n");
    
}

int Client::buyTicketByTrain()
{
    showAllTrains();
    printf("请选择您想要购买的列车序号、起始站序号、终点站序号（以空格分隔）。\n");
    printf("例如，选择列车[1],第(1)站至第(4)站，请输入 \"1 1 4\"\n请输入：");
    int train_id, from_station, to_station;
    char toSend[MAX_BUFFER];
    scanf("%d%d%d", &train_id, &from_station, &to_station);
    sprintf(toSend, "1 %d %d %d 1", train_id, from_station, to_station);
    if (sendRequest(toSend) == 0)
    {
        return 0;
    } else {
        printf("出错了，请重试。\n");  
    };
    printf("========================================\n");
            
    return 0;
}

int Client::checkAvailableSeats()
{
    showAllTrains();
    printf("请选择您想要查询余票的列车序号、起始站序号、终点站序号（以空格分隔）。\n");
    printf("例如，选择列车[1],第(1)站至第(4)站，请输入 \"1 1 4\"\n请输入：");
    int train_id, from_station, to_station;
    char toSend[MAX_BUFFER];
    scanf("%d%d%d", &train_id, &from_station, &to_station);
    sprintf(toSend, "1 %d %d %d 0", train_id, from_station, to_station);
    if (sendRequest(toSend) == 0)
    {
        return 0;
    } else {
        printf("出错了，请重试。\n");  
    };
    printf("========================================\n");
    return 0;
}

// just send all input string entered by user
int Client::core()
{
    welcomePrinter();
    while (true)
    {
        int oper = operations();
        switch (oper)
        {
            case 1:
                buyTicketByTrain();
                break;
            case 2:
                printf("以下为您的所有订单：\n");  
                checkMyTickets();
                break;
            case 3:
                refund();
                break;
            case 4:
                checkAvailableSeats();
                break;
            case 5:
                checkIncome();
                break;
            default:
                printf("出错了。请检查您的输入，再试一次。\n");

        }
    }
        
    return 0;
}

int Client::checkIncome()
{
    printf("========================================\n");
    
    if (sendRequest("5") == 0)
    {
        return 0;
    } else {
        printf("出错了，请重试。\n");  
    };
    printf("========================================\n");
}

int Client::checkMyTickets()
{
    printf("========================================\n");
    
    if (sendRequest("3") == 0)
    {
        return 0;
    } else {
        printf("出错了，请重试。\n");  
    };
    printf("========================================\n");
}

int Client::refund()
{
    printf("以下为您的所有订单（含已退票），请输入想要退票的订单号：\n");  
    checkMyTickets();
    int order_id;
    scanf("%d", &order_id);
    char toSend[MAX_BUFFER];
    sprintf(toSend, "4 %d", order_id);
    if (sendRequest(toSend) == 0)
    {
        return 0;
    } else {
        printf("出错了，请重试。\n");  
    };
}

int Client::sendRequest(const char* content)
{
    send(sock_, content, strlen(content), 0);
    valread_ = read(sock_, buffer_, MAX_BUFFER);
    // set the receiving data length
    buffer_[valread_] = '\0';
    // print receiving data
    printf("%s\n", buffer_);
    return 0;
}