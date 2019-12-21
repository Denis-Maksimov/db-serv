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
#ifndef FILE1_HPP
#define FILE1_HPP

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sqlite3.h"//using -ldl -lpthread
#include "querys.hpp"

class setup_from_files{
    protected:
        setup_from_files();
        ~setup_from_files();
        /**************************************************
         * 
         * \brief создаёт массив начал строк в файле
         * 
         * 
         * TODO: принимает только открытый файл (нет проверок)
         * размер буфера не регулируются 
         * 
         * \return возвращает указатель на массив
         * 
         * ***********************************************/
        long int* pos_lines_in_file(FILE* stream);


        /**************************************************
         * 
         * \brief 
         * Возвращает позиции некомментированных строк
         * комментировать можно решёткой 
         * 
         * TODO: принимает только открытый файл (нет проверок)
         * размер буфера не регулируются 
         * 
         * \return возвращает указатель на массив
         * 
         * ***********************************************/
        long* parse_file_to_querrys(FILE* stream,int* argc);

        /**************************************************
         * 
         * \brief 
         * 
         * TODO: 
         * 
         * \return 
         * 
         * ***********************************************/
        char** any(void);



};



//namespace SQLquerys{

    class SQLquery: public setup_from_files
    {
    private:
        const char* querys_ini;
        long* lines;
        int count_of_lines;
        static int callback(void* var_ifce, int argc, char**argv, char**azColName);
        /* data */
    public:
        SQLquery(const char* file_ini);
        ~SQLquery();
        char* get_line(int line_number,char* buffer,std::size_t size_of_bufer);
        char* execute_querry(const char* patch_to_db,int num);

        
    };


    


//};//namespace SQLquerrys

#endif
