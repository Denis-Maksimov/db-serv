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
#ifndef HTTP_HPP
#define HTTP_HPP
//подключаем стандартные библиотеки
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "../../miscellane/direct.hpp"
//выделяем отдельное пространство имён 
//(для танкистов - на размер и производительность программы не влияет)
namespace http{

    //для свитча распределения метода
    enum tag_method{
        EMPTY=0,    //метод не определён
        GET,        //метод GET
        POST,       //метод POST
        MY_METHOD   //пользовательский метод
    };
    //для свитча распределения адреса
    enum tag_branch{
        E404=0,     //404
        INDEX,      //index.html
        SETTINGS,   //settings.html
        ABOUT,      //about.html
        EXISTENCE_FILE       // ./*
    };

/***************************************************
 * @parse:
 * *************************************************
* @brief Обработка запроса
* @arg принимает исследуемый буфер и открытый сокет
* для отправки клиенту ответа
* @return void
* --------------------------------------------------
* @split_to_spaces:
* *****************************************************
* @brief Кромсаем буфер по строкам 
* @arg принимает исследуемый буфер и адрес под 
* переменную для количества строк
* @return возвращает массив смещений от начала
* первой строки до начала i-й строки;
* заполняет в argc число строк в буффере
* ***************************************************
*
* -------------------------------------------------
* @response_code:
*****************************************************
* @brief Обработка кода ошибки
* отправляет HTTP заголовок ответа
* @arg принимает код ошибки и сокет
* ***************************************************
*
* -------------------------------------------------
* @response:
*****************************************************
* @brief Отправляет файл 
* @arg принимает путь к файлу и сокет
* ***************************************************
* -------------------------------------------------
* @get_handle_adress: 
*****************************************************
* @brief Обработка адреса
* @arg принимает строку адреса
* @return возвращает ветку поведения по запросу
* ***************************************************
*
* -------------------------------------------------
* @handle_get:
* *****************************************************
* @brief Парсинг GET-запроса 
* @arg принимает буфер с запросом, открытый сокет
* число строк, массив смещений строк
* @return void
* 
* -------------------------------------------------
* @handle_post:
*****************************************************
* TODO:
* @brief Парсинг POST-запроса 
* @arg принимает буфер с запросом, открытый сокет
* число строк, массив смещений строк
* @return void
* 
* -------------------------------------------------
* @handle_my_method:
*****************************************************
* TODO:
* @brief Парсинг пользовательско протокола over TCP 
* @arg принимает буфер с запросом, открытый сокет
* число строк, массив смещений строк
* @return void

* -------------------------------------------------
* @handle_error:
*****************************************************
* TODO:
* @brief обработка ошибки в случае, когда не удалось
* определить протокол передачи
* @arg принимает буфер с запросом, открытый сокет
* число строк, массив смещений строк
* @return void
* -------------------------------------------------
* 
* *******************************/
    void parse(char* buf,int connfd);
    long* split_to_spaces(char* buf,int* argc);
    void response_code(int code,int sockfd);
    void response(const char* name_file,int sockfd);
    tag_branch GET_handle_adress(char* adress);
    void handle_GET(char* buf, int connfd, int lines,long* lines_array);
    void handle_POST(char* buf, int connfd, int lines,long* lines_array);
    void handle_MY_METHOD(char* buf, int connfd, int lines,long* lines_array);
    void handle_ERROR(int connfd);
}
#endif
