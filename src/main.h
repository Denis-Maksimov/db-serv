#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <mutex>
///FIXME:
#include <unistd.h>


#include "file1.hpp"
#include "querys.hpp"
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

void _Server_term(std::mutex &mtx, int& terminate_flag);
