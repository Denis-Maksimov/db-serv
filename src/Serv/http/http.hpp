#ifndef HTTP_HPP
#define HTTP_HPP
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void parse(char* buf,int connfd);
long* split_to_spaces(char* buf,int* argc);
void response(const char* name_file,int sockfd);
int GET_handle_adress(char* adress);
void handle_GET(char* buf, int connfd, int lines,long* lines_array);
void handle_POST(char* buf, int connfd, int lines,long* lines_array);
void handle_MY_METHOD(char* buf, int connfd, int lines,long* lines_array);
void handle_ERROR(int connfd);

#endif
