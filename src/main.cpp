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
////------------------------------ main.cpp -----------------------------------------/////
//////////////////////////////////////////////////////////////////////////////////////////
/// \brief Сперва разделяем программу на потоки. 
/// Общим интерфейсом потоков является переменная terminate, которая является признаком
/// того, что потоку пора закругляться и освобождать ресурсы
/// GUI() при завершении поднимает флаг terminate, чтобы остальные потоки завершились
/// Server() в силу блокирующей функции accept() вызывает подпоток, который проверяет
/// статус флага terminate и в случае "true" шлёт на сервер пустое сообщение, чтобы
/// сдёрнуть функцию accept() с блокировки и поток мог самостоятельно завершиться
/// main() вызывает потоки и ждёт их завершения
///
/// \author Максимов Денис Николаевич dn.maksimow@gmail.com
///
//////////////////////////////////////////////////////////////////////////////////////////
////-----Рисунок 1 - Структурная схема того как организованы в программе-------------/////
//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//-main()----\------->\------------------------------join(GUI)-|-----join(Server)--.X...//
//            \        \                                      \./                       //
//             \        \----> Server()-\-------------------X...                        //
//              \                        \           /.\                                //
//               \                        \term()--- >| .X...                           //
//                \                               / \                                   //
//                 \                               |                                    //
//                  \----> GUI() -------------- exit().X...                             //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
//
/**************
 * TODO: 
 * - выполнить проверку функций на возможные ошибки, исключая шанс одновременного
 * обращения потоков к stderr
 * 
 * - выполнить передачу аргументов получаемых при вызове в аргументы потоков
 * 
*********/

#include "main.h"


///////////////////////////
// определение ID потоков
///////////////////////////
enum{
    GUI=0,
    SERVER,
    MAIN
};


///////////////////////////////////
// порт на котором запустим сервак
///////////////////////////////////
#define PORT 8088

//////////////////////////////////////////////////////////////////////////
/// Главная программа, которая распределяет и вызывает потоки 
/// и пытается контролировать корректное завершение программы
/// т.н. менеджер
//////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv){


    printf(LZ25);
    
    int terminate = false;
    std::mutex mtx;

    std::thread thread_GUI(_system_GUI,std::ref(mtx),std::ref(terminate));
 

    std::thread thread_SERVER(_system_Server,std::ref(mtx),std::ref(terminate));
 
    //waiting first thread
    thread_GUI.join();
 
    mtx.lock();
     terminate=true;
    mtx.unlock();
 
    //waiting second thread
    thread_SERVER.join();
    puts("terminated!");

 //-----------------------------------------------
 //   SQLquery obj("querys.data");   
 //   obj.execute_querry("TEST.db", Query::insert);
 //-----------------------------------------------
    
    return 0;
}

//---------------------------------------------------



//////////////////////////////////////////////////////
/// подпрограмма графической оболочки
/// @brief обработчик потока для ГУЯ
/// Обеспечивает API для входа и выхода из потока
/// @arg принимает мютекс и флаг выхода из программы
/// мютекс обеспечивает безопасность доступа к 
/// общим данным
/// @note может быть любой HMI, в том числе CLI
//////////////////////////////////////////////////////
void _system_GUI(std::mutex &mtx, int& terminate_flag){
    puts("gui!");
    std::this_thread::yield();
    
    // Полезные действия
    int status=main_GUI(int(0), (char**)0);

    ///TODO: handle status 

    // Поднимаем флаг завершения программы
    mtx.lock();
        terminate_flag=true;
    mtx.unlock();

}//_system_GUI


//---------------------------------------------------




//////////////////////////////////////////////////////
/// подпрограмма сервера
/// @brief обработчик потока для сервера
/// Обеспечивает API для входа и выхода из потока
/// @arg принимает мютекс и флаг выхода из программы
/// мютекс обеспечивает безопасность доступа к 
/// общим данным
//////////////////////////////////////////////////////
void _system_Server(std::mutex &mtx, int& terminate_flag){

    
    std::thread thread_SERVER_term(_Server_term,std::ref(mtx),std::ref(terminate_flag));
    
    //готовим входные данные
    int argc=sizeof(int)*2;
    int _term=0;
    int port=PORT;

    //мне пох, кастомизирую как хочу
    //я в курсах как память распределяется
    char* t=(char*)&terminate_flag;
    char* p=(char*)(&port);
    char* argv[]={t,p};

    //execute
    int return_code = main_Server(argc, argv);

    ///TODO: handle status 

    printf("server terminated whith status %i\n",return_code);
    std::this_thread::yield();

    thread_SERVER_term.join();
    
}//_Server_term


//----------------------------------------------------



//////////////////////////////////////////////////////
/// @brief обработчик потока завершения сервера
/// в цикле проверяет флаг выхода и завершает поток
/// сервера (деликатно)
/// @arg принимает мютекс и флаг выхода из программы
/// мютекс обеспечивает безопасность доступа к 
/// общим данным
//////////////////////////////////////////////////////
void _Server_term(std::mutex &mtx, int& terminate_flag){
    int _term=0;

    //do
    while (true)
    {
        mtx.lock();
        _term=terminate_flag;
        mtx.unlock();
        if(_term) break;
        std::this_thread::yield();
    }
    std::this_thread::yield();

    //terminate
    Network client(1000);
    puts("client send");

    //сервер должен обидеться на мат и завершиться
    char msg[]="пиздец\n";

    char* SB=client.get_send_buffer();
    strcpy(SB,msg);

    client.send_termin(PORT,"127.0.0.1");
    puts("termOk");
}//_Server_term

//---------------------------------------------------

