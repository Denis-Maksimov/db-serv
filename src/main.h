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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <mutex>
///FIXME:
#include <unistd.h>


//#include "file1.hpp"

#include "./Querry/main_Querry.hpp"
#include "./GUI/main_GUI.hpp"
#include "./Serv/main_server.hpp"

#include "./Serv/Network.hpp"
const char* LZ25=\
"\
#####################################################################\n\
###        ЗАО '25 ЛЕСОЗАВОД' группа компаний Титан               ###\n\
###                 энергослужба ЛП-3                             ###\n\
#####################################################################\n";

//подпрограмма графической оболочки
void _system_GUI(std::mutex &mtx, int& terminate_flag); //Оболочка

//int main_GUI(int argc, char **argv);

//подпрограмма сервера
void _system_Server(std::mutex &mtx, int& terminate_flag); //Оболочка

//int main_Server(int argc, char **argv);

void _Cyclycs_works(std::mutex &mtx, int& terminate_flag);

void semafor_db(int clock);