#----------------------------------

#libs
LIBS:= -ldl -lpthread `pkg-config --libs gtk+-3.0`

#flags
CFLAGS:= -c -O2 

#include "local.h"
CFLAGS+= -I./lib
CFLAGS+= -I./src `pkg-config --cflags --libs gtk+-3.0`
CFLAGS+= -I./src/Serv
CFLAGS+= -I./src/GUI
CFLAGS+= -I./lib/sqlite-amalgamation-3071300
CFLAGS+= -I/lib/x86_64-linux-gnu/glib-2.0/include

#----------------------------------

SRC:= ./src/main.cpp
OBJ:= ./main.o
#--GUI
SRC+= ./src/main_GUI.cpp
OBJ+= ./main_GUI.o
#--Server
SRC+= ./src/Serv/main_server.cpp
OBJ+= ./main_server.o

SRC+= ./src/Serv/Network.cpp
OBJ+= ./Network.o

SRC+= ./src/Serv/http/http.cpp
OBJ+= ./http.o
#--Базы данных
SRC+= ./src/file1.cpp
OBJ+= ./file1.o

SRC+= ./lib/sqlite-amalgamation-3071300/sqlite.c
OBJ+= ./sqlite3.o


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

file1.o: ./src/file1.cpp
		#
		#compilling file1.cpp
		g++  ./src/file1.cpp $(CFLAGS)

#----------------------------------

sqlite3.o: ./lib/sqlite-amalgamation-3071300/sqlite3.c
		#
		#compilling sqlite3.c
		gcc $(CFLAGS) ./lib/sqlite-amalgamation-3071300/sqlite3.c

#----------------------------------

main_GUI.o: ./src/GUI/main_GUI.cpp
		#
		#compilling main.cpp
		g++  ./src/GUI/main_GUI.cpp $(CFLAGS)

#----------------------------------

main_server.o: ./src/Serv/main_server.cpp
		#
		#compilling main.cpp
		g++  ./src/Serv/main_server.cpp $(CFLAGS)

#----------------------------------

Network.o: ./src/Serv/Network.cpp
		#
		#compilling main.cpp
		g++  ./src/Serv/Network.cpp $(CFLAGS)

#----------------------------------

http.o: ./src/Serv/http/http.cpp
		#
		#compilling main.cpp
		g++  ./src/Serv/http/http.cpp $(CFLAGS)

#----------------------------------
clean:
		rm *.o


