CC = g++ -Wall -std=c++17 -fPIC
SHAREFLAG = -shared
SHAREDLL = so
RELEASE = 0
UNICODE = 0
INCLUDE = -I ./ 
LOADBIN = 0
LIB = -lHelpComponents_DataBase
LIBEX = -ldl -lpthread
LOADSO = -Wl,-rpath=./,--disable-new-dtags
LIBINCLUDE = ModuleDatabase_MySql.o ModuleDatabase_SQlite.o pch.o

ifeq ($(shell uname),Darwin)
	SHAREDLL = dylib
	SHAREFLAG = -dynamiclib
	LOADBIN = 
	LOADSO = 
else
	SHAREDLL = so
	SHAREFLAG = -shared
	LOADBIN = -L /usr/local/lib/XEngine_Release/XEngine_HelpComponents
endif

ifeq ($(RELEASE),1)
FLAGS = -c -O2 
DEBUG = 
else
FLAGS = -c
DEBUG = -g
endif

ifeq ($(UNICODE),1)
UNICODE = -D _UNICODE
else
UNICODE = 
endif


all:$(LIBINCLUDE)
	$(CC) $(DEBUG) $(LIBINCLUDE) -o libXEngine_ModuleDatabase.$(SHAREDLL) $(SHAREFLAG) -fPIC $(LOADBIN) $(LIB) $(LIBEX) $(LOADSO)

ModuleDatabase_MySql.o:./ModuleDatabase_MySql/ModuleDatabase_MySql.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./ModuleDatabase_MySql/ModuleDatabase_MySql.cpp 
ModuleDatabase_SQlite.o:./ModuleDatabase_SQlite/ModuleDatabase_SQlite.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./ModuleDatabase_SQlite/ModuleDatabase_SQlite.cpp 
						              
pch.o:./pch.cpp                 		       	    
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./pch.cpp


InstallAll:InstallSo 
InstallSo:./libXEngine_ModuleDatabase.$(SHAREDLL)
	cp ./libXEngine_ModuleDatabase.$(SHAREDLL) ../../XEngine_Release/libXEngine_ModuleDatabase.$(SHAREDLL)


CleanAll:CleanObj CleanMk
CleanObj:                                               
	rm *.o
CleanMk:                             
	rm *.$(SHAREDLL)                        