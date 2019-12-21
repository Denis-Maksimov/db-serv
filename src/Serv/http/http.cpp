#include "http.hpp"


enum tag_method{
    EMPTY=0,
    GET,
    POST,
    MY_METHOD
};
const char A[3]={'G','E','T'};
void parse(char* buf,int connfd){


    puts("in parse");
    //puts(buf);
    //число строк
    int lines;
 //   char* adress = strchr(buf,'/');
    long* lines_array = split_to_spaces(buf,&lines);
    tag_method method=EMPTY;
    puts(buf);
    //printf("adr %x / %i",buf, strstr(buf,A));
    if      (strstr(buf,"GET") == buf )method=GET;
    else if (strstr(buf,"POST")== buf )method=POST;
    else if (strstr(buf,"USER_MTH")== buf )method=MY_METHOD;
    
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
        handle_ERROR(connfd);//TODO
        break;
    }

    free(lines_array);

}


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
            goto LABEL_;
        case '\0':
            goto LABEL_;
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
                puts("space");
            }

            break;
        }
        tmp_pos++;
  

    }
    LABEL_:
    /*********************************************
     * обрезаем лишнюю память 
     * *******************************************/
    ln = (long int*)realloc(ln,iterator*sizeof(long int));

 
    //число элементов в массиве
    *argc=iterator;
    return ln;
}//pos_lines_in_file

//-----------------------------------------------------

void handle_GET(char* buf, int connfd, int lines,long* lines_array){

    int doing;

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

   printf("parse result is %i\n",doing);
   /****************************
    * Обработка запросов
   ****************************/
   switch (doing)
   {
    case 1:
       response("./index.html", connfd);
       break;
    case 2:
       response("./index.html", connfd);
       break;
    case 3:
       response("./index.html", connfd);
       break;
    case 4:
       response("./index.html", connfd);
       break;

   default:
        response("./index.html", connfd);
        break;
   }
    //

    return;
}
int GET_handle_adress(char* adress){
    int result=0;
    if(!strcmp(adress,"/")){result=1;}else 
    if(!strcmp(adress,"/index.html")){result=2;}else 
    if(!strcmp(adress,"/settings.html")){result=3;}else 
    if(!strcmp(adress,"/about.html")){result=4;}
    return result;
}

void response(const char* name_file,int sockfd){
    char buffer[256];
    memset(buffer,'\0',256);
    FILE* stream=fopen(name_file,"r");

    while(fgets(buffer,256,stream)>0){
        send(sockfd, buffer, strlen(buffer), 0); 
    }

    fclose(stream);
}
//--------------------------------------------------------------------

void handle_POST(char* buf, int connfd, int lines,long* lines_array){

    return;
}

void handle_MY_METHOD(char* buf, int connfd, int lines,long* lines_array){

    return;
}
void handle_ERROR(int connfd){
    return;
}
