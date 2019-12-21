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

//--------------------------------------------------------------------------

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

//--------------------------------------------------------------------------

void Network::working(int* do_working){
    int n=0;
    //char* bubu=(char*)malloc(1);
    //int bubu_size=0;

    while(!(*do_working)) {
            puts("before accept");
            connfd = accept(listenfd, (struct sockaddr*)0L, 0L);


        /////////////////
        ///  Receive 
        /// Пока есть буфер отправляем в стдоут
        /////////////////
 //       while ( (n = read(connfd, recvBuff, MTU-1)) > 0)
   //     {
            //в новый буфер бахаем
          //  realloc(bubu, bubu_size+n);
           // strncpy(bubu+bubu_size, recvBuff, n);
     //       bubu_size += n;

            n = read(connfd, recvBuff, MTU-1);
            recvBuff[n] = 0;
            if(fputs(recvBuff, stdout) ==  -1)
            {
                printf("\n Error : fputs error\n");
            }

            // if(strstr(recvBuff,"пиздец")>=0){
            //     do_working=false;

            // }
     //   }//END_WHILE

        if(n < 0)
        {
            printf("\n Read error \n");
        }

        parse(recvBuff,connfd);
       // free(bubu);

        /////////////////////////////////////////////////////////////
      //      sprintf(sendBuff, "HTTP/1.1 200 OK\r\n\r\nHello\0");
     //       send(connfd, sendBuff, strlen(sendBuff),0);

            close(connfd);
            memset(recvBuff,0,MTU);
            sleep(1);

     }
puts("end work");
}


//--------------------------------------------------------------------------

//<ip of server>
int Network::send_(int port, const char *ip_adr) {
    //Инициализации
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
    sleep(1);
    send(sockfd, sendBuff, strlen(sendBuff), 0); 

  //  int flags=fcntl(sockfd,F_GETFL,0);
  //  fcntl(sockfd,F_SETFL,flags|O_NONBLOCK);

      /////////////////
     ///  Receive  ///
     /// Пока есть буфер отправляем в стдоут
     /////////////////
    
    do {
//        n = recv(sockfd,recvBuff,MTU-1,0);
        printf("\nFFF!!!\n");
        
       n = read(sockfd, recvBuff, MTU-1);
        if(n==0)break;

        
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) ==  -1)
        {
            printf("\n Error : Fputs error\n");
        }
        printf("\nFFF%i\n",n);
        
    }while (n);
    close(sockfd);

    if(n < 0)
    {
        printf("\n Read error \n");
    }
    return 0;
}

//--------------------------------------------------------------------------

//<ip of serve>
int Network::send_termin(int port, const char *ip_adr){

    //Инициализации
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
    sleep(1);
    send(sockfd, sendBuff, strlen(sendBuff), 0); 

  //  int flags=fcntl(sockfd,F_GETFL,0);
  //  fcntl(sockfd,F_SETFL,flags|O_NONBLOCK);

    
    close(sockfd);
    return 0;
 
}

//--------------------------------------------------------------------------
