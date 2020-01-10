#include "main_Querry.hpp"


int main_Querry(int argc, const char** argv){
   // #define INI_FILE_WHITH_NAMES_OF_DATABASES argv[0]
   // #define INI_FILE_WHITH_NAMES_OF_QUERRYS argv[1]

    puts("db");
  //  char* get_line(int line_number,char* buffer,std::size_t size_of_bufer);
    //-----------------------------------------------
       SQLquery obj("./querys.data");   
  //     obj.execute_querry("./TEST1.db", Query::new_table);
       obj.execute_querry("./TEST1.db", Query::sellect);
    //-----------------------------------------------
    return 0;

}