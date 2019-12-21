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
#include "Network.hpp"

Network::Network(unsigned int s):MTU(s){
    sendBuff=(char*)malloc(MTU);
    recvBuff=(char*)malloc(MTU);
    memset(sendBuff, 0, sizeof(sendBuff));
    memset(sendBuff, 0, sizeof(recvBuff));
    memset(&serv_addr, 0, sizeof(serv_addr));
}
Network::~Network(){
    free(sendBuff);
    free(recvBuff);
}
void Network::init(int port)
{
    listen_port=port;
    /////////////////////////////////////////////////////////////
    /// дескрипторы для сокетов клиента 
    /////////////////////////////////////////////////////////////
    connfd = 0;

    /////////////////////////////////////////////////////////////
    /// структура адреса сокета 
    /////////////////////////////////////////////////////////////
    
    

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    //Привязываем к адресу
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    listen(listenfd, 10);

}

void Network::working(){
    int n=0;
    while(1) {
            connfd = accept(listenfd, (struct sockaddr*)0L, 0L);


        /////////////////
        ///  Receive  ///
        /// Пока есть буфер отправляем в стдоут
        /////////////////
        while ( (n = read(connfd, recvBuff, sizeof(recvBuff)-1)) > 0)
        {
            //////////////////////////////
            recvBuff[n] = 0;
            if(fputs(recvBuff, stdout) ==  -1)
            {
                printf("\n Error : Fputs error\n");
            }
        }

        if(n < 0)
        {
            printf("\n Read error \n");
        }


/////////////////////////////////////////////////////////////
            sprintf(sendBuff, "HTTP/1.1 200 OK\r\n\r\nHello");
            write(connfd, sendBuff, strlen(sendBuff));

            close(connfd);
            sleep(1);
     }

}




//<ip of server>
int Network::send_(int port, const char *ip_adr) {

    int sockfd = 0, n = 0;


    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, ip_adr, &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    

      /////////////////
     ///  Connect  ///
    /////////////////
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }

    send(sockfd, sendBuff, strlen(sendBuff), 0); 





      /////////////////
     ///  Receive  ///
     /// Пока есть буфер отправляем в стдоут
     /////////////////
    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) ==  -1)
        {
            printf("\n Error : Fputs error\n");
        }
    }

    if(n < 0)
    {
        printf("\n Read error \n");
    }

    return 0;
}