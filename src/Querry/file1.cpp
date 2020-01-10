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
#include "file1.hpp"
#define f1 setup_from_files


/**************************************************
 **************************************************
 * 
 * \brief создаёт массив начал строк в файле
 * 
 * 
 * TODO: принимает только открытый файл (нет проверок)
 * размер буфера не регулируются 
 * 
 * \return возвращает указатель на массив
 * 
 * ************************************************
 * ***********************************************/
long int* f1::pos_lines_in_file(FILE* stream){
    /*********************************************
     * Выделяем с запасом в куче память 
     * под возвращаемый массив
     * *******************************************/
    long int* ret_array=(long int*) malloc(1024*sizeof(long int));

    /*********************************************
     * Переменная для элемента возвращаемого
     * массива
     * *******************************************/
    std::size_t iterator=0;

    /*********************************************
     * Запоминаем текущую позицию, чтоб не поломать
     * *******************************************/
    long int current_position=ftell(stream);

    /*********************************************
     * Переходим на начало файла
     * *******************************************/
    long int tmp_pos = fseek(stream, 0, SEEK_SET);

    ret_array[iterator]=tmp_pos;
    iterator++;
    tmp_pos++;

    /*********************************************
     * i-й символ в файле
     * *******************************************/    
    int character=0;

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
         * массив
         * **************************************/
        character=fgetc(stream);
        switch (character)
        {
        case EOF:
            goto LABEL_END;
        case '\n':
            flag |=1;
            break;
        default:
            if(flag){
                ret_array[iterator]=tmp_pos;
                iterator++;
                flag=0;
                break;
            }
            break;
        }
        tmp_pos++;
  

    }
    LABEL_END:
    /*********************************************
     * обрезаем лишнюю память 
     * *******************************************/
    ret_array = (long int*)realloc(ret_array,iterator*sizeof(long int));
    
    /*********************************************
     * восстанавливаем позицию указателя 
     * *******************************************/
    fseek(stream, current_position, SEEK_SET);
    return ret_array;
}//pos_lines_in_file



//-------------------------------------------------------------------------



/**************************************************
 **************************************************
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
 * ************************************************
 * ***********************************************/
long* f1::parse_file_to_querrys(FILE* stream,int* argc){
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

    /*********************************************
     * Запоминаем текущую позицию, чтоб не поломать
     * *******************************************/
    long int current_position=ftell(stream);

    /*********************************************
     * Переходим на начало файла
     * *******************************************/
    long int tmp_pos = fseek(stream, 0, SEEK_SET);

    ln[iterator]=tmp_pos;
    tmp_pos++;
    iterator++;
    /*********************************************
     * i-й символ в файле
     * *******************************************/    
    int character=0;

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
        character=fgetc(stream);
        switch (character)
        {
        case EOF:
            goto LABEL_END;
        case '\n':
            flag |=1;
            break;
        case '#':
            flag |=2;
            break;
        default:
            /************************************
             * Обрабатываем переносы
             * *********************************/
            if(1L==(flag & 1L)){
                ln[iterator]=tmp_pos-1;
                iterator++;
                flag &= ~(1L);
                
            }
            /************************************
             * Обрабатываем комменты
             * *********************************/
            if(2L==(flag & 2L)){
                //comment[iterator]=tmp_pos;
                iterator--;
                flag &= ~(2L);
                break;
            }
            break;
        }
        tmp_pos++;
  

    }
    LABEL_END:
    /*********************************************
     * обрезаем лишнюю память 
     * *******************************************/
    ln = (long int*)realloc(ln,iterator*sizeof(long int));

    /*********************************************
     * восстанавливаем позицию указателя 
     * *******************************************/
    
    fseek(stream, current_position, SEEK_SET);
    
    *argc=iterator;
    return ln;
}//pos_lines_in_file



//-------------------------------------------------------------------------


/**************************************************
 **************************************************
 * 
 * \brief 
 * 
 * TODO: 
 * 
 * \return 
 * 
 * ************************************************
 * ***********************************************/
char** f1::any(void){
    
    int argc=0;
    char** ret_val=0;
    char* tmp_line=0;
    FILE* stream = fopen("querys.data","r");
    long* lines = parse_file_to_querrys(stream, &argc);

    ret_val=(char**)malloc(argc*sizeof(char*));
    char* s=(char*)malloc(1024);
    /* ******************************************
     * делаем массив строк запросов
     * ****************************************/
    for (int i=0;i<argc;i++){

        fseek(stream,lines[i],SEEK_SET);
        fgets(s,1024,stream);
        tmp_line=(char*)malloc(sizeof(char)*strlen(s));

        memcpy(tmp_line,s,strlen(s));
        ret_val[i]=tmp_line;
    }
    fclose(stream);
    free(s);
    return ret_val;
}
//------------------------------------------------------------------------------
setup_from_files::setup_from_files(){

}
setup_from_files::~setup_from_files(){

}


/**************************************************
 * 
 * \brief возвращает строку по номеру из файла
 * 
 * 
 * 
 * ***********************************************/
char* SQLquery::get_line(int line_number,char* buffer,std::size_t size_of_bufer){

        FILE* stream=fopen(querys_ini,"r");

        long int a=lines[line_number];
        fseek(stream,a,SEEK_SET);

        fgets(buffer,size_of_bufer,stream);

        //удаляем переносы в конце строки
        while(char*del = strchr(buffer, '\n')){
            *del=0;
            puts("delliting");
        }
        fclose(stream);

        return buffer;
        
    }
//------------------------------------------------------------------------------


    SQLquery::SQLquery(const char* file_ini) : querys_ini(file_ini)
    {
        FILE* stream=fopen(querys_ini,"r");
        lines = parse_file_to_querrys(stream, &count_of_lines);
        fclose(stream);
    }

    SQLquery::~SQLquery()
    {
    }

/***********************************************************
 * \brief 
 * \param db_name - путь к БД
 * \param num - номер строки зароса файла querys.data
************************************************************/
char* SQLquery::execute_querry(const char* db_name,int num){

    //char* ret_val=(char*)malloc(256);
    sqlite3 *db = 0; // хэндл объекта соединение к БД
    char *err = 0;

    // открываем соединение
    if( sqlite3_open(db_name, &db) )
        fprintf(stderr, "Opening/creating db ERR: %s\n", sqlite3_errmsg(db));
        /// TODO: error handle
    else{
        
        //переменная под запрос из файла querys.data
        char* querry1=(char*)malloc(256);

        //такая же переменная, но вместо %s ужой значения
        char* querry=(char*)malloc(256);


        get_line(num,querry1,256);
        
        /// Конечный автомат для путя
        switch (num)
        {
        case Query::path_to_db:
            puts("path");
            break;
        case Query::new_table:
            sprintf(querry,querry1);
            puts("new_table");
            break;
        case Query::insert:
            sprintf(querry,querry1,"db_name","hi","bye");
            puts("insert");
            break;

        case Query::sellect:
             sprintf(querry,querry1);
             puts("sellect");
             break;
        default:

            break;
        }
       puts(querry);
        
        // выполняем SQL
        if ( sqlite3_exec(db, querry, callback, 0, &err) ){
            fprintf(stderr, "querry error: %s\n", err);
            sqlite3_free(err);
        }
        free(querry);
        free(querry1);
    }
    // закрываем соединение
    sqlite3_close(db);
    
    return 0;
    

}

/****************************************
 * \brief Функция для приёма данных с БД
 * XXX:
 * TODO: вместо stdout глобальный массив в RAM для своих данных для графиков и т.д.
 * \param var_ifce - 4-й аргумент в sqlite3_exec - пока что не используется
 * \param argc - число элементов пришедших от БД
 * \param argv - массив значений
 * \param azColName - массив названий колонок
 * \return 0
*****************************************/
int SQLquery::callback(void* var_ifce, int argc, char**argv, char**azColName){
    // int i;
 //   *(int*)var_ifce=(*(int*)var_ifce);

    //выводим в stdout все данные
    for (int i=0;i<argc;i++){
        printf("%s = %s\n",azColName[i],(argv[i]?argv[i]:"NULL"));

    }
    putchar('\n');
    return 0;
}

