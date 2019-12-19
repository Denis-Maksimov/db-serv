
#include "main.h"
#include "Network.hpp"
#include <string.h>
enum{
    GUI=0,
    SERVER,
    MAIN
};





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
    thread_GUI.join();
    terminate=true;
    thread_SERVER.join();
    puts("terminated!");
   ////----этот-блок-работает-только-на-linux-вместо-потоков-тут-процессы---
    //    
    //-----fork()\--->fork()\-----> -----------> wait(0)-kill(Server)-exit()X...
    //            \          \----> Server()-------------------X...                   
    //             \----> GUI() -------------- exit().X...
    //
    //     pid_t pid[2];
    //     //-------------------------------------------
    //     //---Распараллеливание №1
    //     //-------------------------------------------
    //     pid[GUI]=fork();
    //     switch (pid[GUI])
    //     {
    //     case 0:/* new process GUI()*/
    //
    //         status[GUI]=main_GUI(argc,argv);
    //         puts("gui term");
    //         exit(status[GUI]);
    //         break;
    //     case -1:
    //         exit(-1);
    //         /* error */
    //         break;
    //
    //     default:
    //        /* main process */
    //         break;
    //     }
    //
    //     //-------------------------------------------
    //     //---Распараллеливание №2
    //     //-------------------------------------------
    //     pid[SERVER]=fork();
    //     switch (pid[SERVER])
    //     {
    //     case 0:/* new process SERVER()*/
    //
    //         int status[SERVER];
    //         status[SERVER]=main_Server(argc,argv);
    //         puts("server term");
    //         exit(status[SERVER]);
    //         break;
    //     case -1:
    //         exit(-1);
    //         /* error */
    //         break;
    //
    //     default:
    //        /* main process */
    //         break;
    //     }
    //
    //----------------------------------------------   
    //  // ждём завершения дочерних процессов
    //  //---------------------------------------------- 
    //     pid_t terminated_pid=0;
    //     status[MAIN]=0;
    //     //Ждём пока хотя бы один сын не завершится
    //     while(  (terminated_pid!=pid[GUI])  && 
    //             (terminated_pid!=pid[SERVER])   ){

    //         terminated_pid=wait(status+MAIN*sizeof(int));

    //     }

    //     if (terminated_pid==pid[GUI]) {
    //         puts("ok");
    //         kill(pid[SERVER],9);
    //     } else if (terminated_pid==pid[SERVER]) {
    //         puts("server error");
    //         kill(pid[GUI],9);
    //     }
    //     else
    //     {
    //         puts("fatal error");
    //         kill(pid[SERVER],9);
    //         kill(pid[GUI],9);
    //     }
    // 
   ////---конец-блока-для-процессорного-распараллеливания




 //-----------------------------------------------
 //   SQLquery obj("querys.data");   
 //   obj.execute_querry("TEST.db", Query::insert);
 //-----------------------------------------------
    

    return 0;

}




//подпрограмма графической оболочки
void _system_GUI(std::mutex &mtx, int& terminate_flag){

    //int main_GUI(int argc, char **argv);

}








#define PORT 12345
//подпрограмма сервера
void _system_Server(std::mutex &mtx, int& terminate_flag){

    int return_code=0;
    std::thread thread_SERVER_term(_Server_term,std::ref(mtx),std::ref(terminate_flag));
    //int main_Server(int argc, char **argv);
}

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
    //terminate
    Network client(100);
    client.send_(PORT,"127.0.0.1");



}
