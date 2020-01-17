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

#include "http.hpp"

namespace http{

/*****************************************************
 * @brief Обработка запроса
 * @arg принимает исследуемый буфер и открытый сокет
 * для отправки клиенту ответа
 * @return void
 * ***************************************************/
void parse(char* buf,int connfd){

    //инициализации
    tag_method method = EMPTY;
    int lines;


    long* lines_array = split_to_spaces(buf,&lines);

    //определение метода
    if      (strstr(buf,"GET") == buf )method=GET;
    else if (strstr(buf,"POST")== buf )method=POST;
    else if (strstr(buf,"USER_MTH")== buf )method=MY_METHOD;
    
    printf("meth %i\n",method);
    //распределение в зависимости от метода
    switch (method)
    {
    case GET:
        puts("Calling GET");
        handle_GET(buf,connfd,lines,lines_array);//Ok
        break;
    case POST:
        puts("Calling OTHER");
        handle_POST(buf,connfd,lines,lines_array);//TODO
        break;
    case MY_METHOD:
        puts("Calling OTHER");
        handle_MY_METHOD(buf,connfd,lines,lines_array);//TODO
        break;
    default:
        puts("Calling ERROR");
        puts(buf);
        handle_ERROR(connfd);//TODO
        break;
    }
    //чистим за собой память
    free(lines_array);
    return;
}//void parse(char* buf,int connfd)

//------------------------------------------------------------

/*****************************************************
 * @brief Кромсаем буфер по строкам 
 * @arg принимает исследуемый буфер и адрес под 
 * переменную для количества строк
 * @return возвращает массив смещений от начала
 * первой строки до начала i-й строки;
 * заполняет в argc число строк в буффере
 * ***************************************************/
long* split_to_spaces(char* buf,int* argc){
    /*********************************************
     * Выделяем с запасом в куче память 
     * под возвращаемый массив
     * *******************************************/
    long* ln = (long int*) malloc(1024*sizeof(long int));

    /*********************************************
     * Переменная для элемента возвращаемого
     * массива
     * *******************************************/
    std::size_t iterator=0;


    ln[iterator]=0;
    int tmp_pos=1;
    iterator++;
 
    /*********************************************
     * флаг состояния
     * *******************************************/
    int flag=0;

    /*********************************************
     * !!!WORKING!!!
     * *******************************************/
    while(1){
        /*****************************************
         * Читаем посимвольно и на каждый перевод
         * строки, если не пустая строка,
         * добавляем позицию в возвращаемый
         * массив удаляем, если коммент
         * **************************************/
        switch (buf[tmp_pos])
        {
        case EOF:
            goto HTTP_LABEL_END;
        case '\0':
            goto HTTP_LABEL_END;
        case '\r':
            buf[tmp_pos]=0;
            flag |=1;
            break;
        case '\n':
            buf[tmp_pos];
            flag |=1;
            break;
        default:
            /************************************
             * Обрабатываем переносы
             * *********************************/
            if(1L==(flag & 1L)){
                ln[iterator]=tmp_pos;
                iterator++;
                flag &= ~(1L);
               // puts("space");
            }

            break;
        }
        tmp_pos++;
  
    }
    HTTP_LABEL_END:
    /*********************************************
     * обрезаем лишнюю память 
     * *******************************************/
    ln = (long int*)realloc(ln,iterator*sizeof(long int));

 
    //число элементов в массиве
    *argc=iterator;
    return ln;

}//long* split_to_spaces(char* buf,int* argc)

//-----------------------------------------------------

/*****************************************************
 * @brief Парсинг GET-запроса 
 * @arg принимает буфер с запросом, открытый сокет
 * число строк, массив смещений строк
 * @return void
 * ***************************************************/
void handle_GET(char* buf, int connfd, int lines,long* lines_array){
    
    //флаг распределения
    tag_branch doing;

    /**** Первая строка ****/

    //Выделяем адрес запроса
    char* adress=strchr(buf,'/');
    char* cursor=strchr(adress,' ');
    *cursor=0;

    
    doing = GET_handle_adress(adress);

    cursor++;

    //Выделяем протокол и версию (das ist unusing)
    char* protochol = cursor;
    char* version = strchr(protochol,'/');

    /**** Вторая строка ****/
    /// TODO: Это мне до фени пока что
    /*
        ...

    */

   printf("adr='%s' parse result is %i\n",adress,doing);
   /****************************
    * Обработка веток запросов
   ****************************/
   switch (doing)
   {
    case INDEX:
       response_code(200,connfd);
       response("./index.html", connfd);
       break;
    case SETTINGS:
        response_code(200,connfd);
       response("./settings.html", connfd);
       break;
    case ABOUT:
        response_code(200,connfd);
       response("./about.html", connfd);
       break;
    case E404:
        response_code(200,connfd);
       response("./404.html", connfd);
       break;
    case EXISTENCE_FILE:
        puts("exist");
        response_code(200,connfd);
        puts(adress+1);
        response(adress+1, connfd);
        break;
   default:
        response_code(404,connfd);
        response("./404.html", connfd);
        break;
   }

    return;

}//void handle_GET(char* buf, int connfd, int lines,long* lines_array)

//-----------------------------------------------------

/*****************************************************
 * @brief Обработка адреса
 * @arg принимает строку адреса
 * @return возвращает ветку поведения по запросу
 * ***************************************************/
tag_branch GET_handle_adress(char* adress){
    tag_branch result=E404;

    printf("handl%s",adress+1);
    //Обработка "исключительных" запросов
    if(!strcmp(adress,"/"))                 {result=INDEX;}else 
    if(!strcmp(adress,"/index.html"))       {result=INDEX;}else 
    if(!strcmp(adress,"/settings.html"))    {result=SETTINGS;}else 
    if(!strcmp(adress,"/about.html"))       {result=ABOUT;}else{

    char* t_adr=(char*)malloc(strlen(adress)+2);
    strcpy(t_adr+1,adress);
    t_adr[0]='.';
    if(touch(t_adr))            {result=EXISTENCE_FILE;
    puts(adress+1);}
    free(t_adr);
    }
    
    return result;

}//int GET_handle_adress(char* adress)

//-----------------------------------------------------

/*****************************************************
 * @brief Обработка кода ошибки
 * отправляет HTTP заголовок ответа
 * @arg принимает код ошибки и сокет
 * ***************************************************/
void response_code(int code,int sockfd){
    char buffer[256];
    memset(buffer,'\0',256);
        ///TODO: Описать отдельно ошибки и отдельно ОК
        sprintf(buffer,"HTTP/1.1 %i OK\r\n\r\n\0", code);
        send(sockfd, buffer, strlen(buffer), 0); 

}//void response_code(int code,int sockfd)

//------------------------------------------------------

/*****************************************************
 * @brief Отправляет файл 
 * @arg принимает путь к файлу и сокет
 * ***************************************************/
void response(const char* name_file,int sockfd){
    char buffer[256];
    memset(buffer,'\0',256);
    
    //открываем файл на бинарное чтение
    FILE* stream=fopen(name_file,"rb");

    //читаем порциями по 256 байт пока читается и отправляем клиенту
    while(fgets(buffer,256,stream)>0){
        send(sockfd, buffer, strlen(buffer), 0); 
    }
    //закрываем файл
    fclose(stream);

}//void response(const char* name_file,int sockfd)

//--------------------------------------------------------------------

/*****************************************************
 * TODO:
 * @brief Парсинг POST-запроса 
 * @arg принимает буфер с запросом, открытый сокет
 * число строк, массив смещений строк
 * @return void
 * ***************************************************/
void handle_POST(char* buf, int connfd, int lines,long* lines_array){
    ///TODO:
    return;
}


//--------------------------------------------------------------------

/*****************************************************
 * TODO:
 * @brief Парсинг пользовательско протокола over TCP 
 * @arg принимает буфер с запросом, открытый сокет
 * число строк, массив смещений строк
 * @return void
 * ***************************************************/
void handle_MY_METHOD(char* buf, int connfd, int lines,long* lines_array){
    ///TODO:
    return;
}

//--------------------------------------------------------------------

/*****************************************************
 * TODO:
 * @brief обработка ошибки в случае, когда не удалось
 * определить протокол передачи
 * @arg принимает буфер с запросом, открытый сокет
 * число строк, массив смещений строк
 * @return void
 * ***************************************************/
void handle_ERROR(int connfd){
    ///TODO:
    return;
}

//--------------------------------------------------------------------

}//namespace http
