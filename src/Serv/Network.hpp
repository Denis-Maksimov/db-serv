#ifndef CONNECTION_HPP
#define CONNECTION_HPP
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>

class Network{
public:


    //////////////////////////////////////
    /// Конструктор выделяет память для буффера
    /////////////////////////////////////
    Network(unsigned int MTU=1024);
    ~Network();

    //////////////////////////////////////
    /// Инициализации сервера
    /////////////////////////////////////
    void init(int port);
    

    ///////////////////////////////////////////////
    /// Отправка сообщения в роли клиента на адрес
    //////////////////////////////////////////////
    int send_(int port, const char *ip_adr);

    //////////////////////////////////////
    /// Бесконечный цикл сервера
    /////////////////////////////////////
    void working();
protected:

    //////////////////////////////////////
    /// Порт сервера
    /////////////////////////////////////
    int listen_port;

    //////////////////////////////////////
    /// Дескриптор на подключившийся сокет
    /////////////////////////////////////
    int connfd;

    //////////////////////////////////////
    /// Дескриптор на сокет сервера
    /////////////////////////////////////
    int listenfd;
    struct sockaddr_in serv_addr;
    
    //////////////////////////////////////
    /// Буфферы на приём и передачу
    /////////////////////////////////////
    int MTU;
    char* sendBuff;
    char* recvBuff;
public:
    char* get_send_buffer(){
        return sendBuff;
    }
};




#endif
