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
