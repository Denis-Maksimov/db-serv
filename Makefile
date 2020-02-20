#----------------------------------

#libs
LIBS:= -ldl

# -- POSIX threads --
LIBS+= -lpthread 

#flags
CFLAGS:= -c -O2 -g

#include "local.h"
CFLAGS+= -I./lib
CFLAGS+= -I./src

#uncomment if using GTK+
#CFLAGS+= `pkg-config --cflags --libs gtk+-3.0`
#LIBS+= `pkg-config --libs gtk+-3.0` -rdynamic

CFLAGS+= -I./src/Serv
CFLAGS+= -I./src/GUI
CFLAGS+= -I./lib/sqlite-amalgamation-3071300
CFLAGS+= -I/lib/x86_64-linux-gnu/glib-2.0/include

#----------------------------------

SRC:= ./src/main.cpp
OBJ:= ./main.o

#--GUI
SRC+= ./src/GUI/main_GUI.cpp
OBJ+= ./main_GUI.o


#--Server
SRC+= ./src/Serv/main_server.cpp
OBJ+= ./main_server.o

SRC+= ./src/Serv/Network.cpp
OBJ+= ./Network.o

SRC+= ./src/Serv/http/http.cpp
OBJ+= ./http.o


#--Базы данных
SRC+= ./src/Querry/file1.cpp
OBJ+= ./file1.o

SRC+= ./src/Querry/main_Querry.cpp
OBJ+= ./main_Querry.o

SRC+= ./lib/sqlite-amalgamation-3071300/sqlite.c
OBJ+= ./sqlite3.o

#--Разное
SRC+= ./src/miscellane/direct.cpp
OBJ+= ./direct.o


#SRC+= ./lib/thread.c
#OBJ+= ./thread.o
#----------------------------------

build_all: $(OBJ)
		#
		#building
		g++ $(OBJ) $(LIBS) -o ./execute_me/run

#----------------------------------

main.o: ./src/main.cpp
		#
		#compilling main.cpp
		g++  ./src/main.cpp $(CFLAGS)

#----------------------------------

file1.o: ./src/Querry/file1.cpp
		#
		#compilling file1.cpp
		g++  ./src/Querry/file1.cpp $(CFLAGS)

#----------------------------------

main_Querry.o: ./src/Querry/main_Querry.cpp
		#
		#compilling main_Querry.cpp
		g++  ./src/Querry/main_Querry.cpp $(CFLAGS)

#----------------------------------

sqlite3.o: ./lib/sqlite-amalgamation-3071300/sqlite3.c
		#
		#compilling sqlite3.c
		gcc $(CFLAGS) ./lib/sqlite-amalgamation-3071300/sqlite3.c

#----------------------------------

main_GUI.o: ./src/GUI/main_GUI.cpp
		#
		#compilling main_GUI.cpp
		g++  ./src/GUI/main_GUI.cpp $(CFLAGS)

#----------------------------------

main_server.o: ./src/Serv/main_server.cpp
		#
		#compilling main_server.cpp
		g++  ./src/Serv/main_server.cpp $(CFLAGS)

#----------------------------------

Network.o: ./src/Serv/Network.cpp
		#
		#compilling main.cpp
		g++  ./src/Serv/Network.cpp $(CFLAGS)

#----------------------------------

http.o: ./src/Serv/http/http.cpp
		#
		#compilling http.cpp
		g++  ./src/Serv/http/http.cpp $(CFLAGS)

#----------------------------------

direct.o: ./src/miscellane/direct.cpp
		#
		#compilling http.cpp
		g++  ./src/miscellane/direct.cpp $(CFLAGS)

#----------------------------------
clean:
		rm *.o


