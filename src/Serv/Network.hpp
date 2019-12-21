//////////////////////////////////////////////////////////////////////////////////////////
////--------------------- Уведомление о лицензии GPL --------------------------------/////
//////////////////////////////////////////////////////////////////////////////////////////
/* Drying monitor
 * Copyright (C) 2019 Maksimov Denis dn.maksimow@gmail.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */
//////////////////////////////////////////////////////////////////////////////////////////
// Иными словами, 
// 1) при распространении программы, обязательно прикреплять к ней исходники
// или уведомление о том как их получить (БЕСПЛАТНО!!!)
// 2) GNU GPL — копилефтная лицензия, и требует, чтобы исходные коды производных работ были открытыми под ней же.
// 3) Обязательно в производные работы прикреплять уведомление выше
// Несоблюдение пунктов лицензии GNU GPL нарушает авторские права Free Software Foundation
//////////////////////////////////////////////////////////////////////////////////////////
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
