CC = g++ -Wall -std=c++17
RELEASE = 0
UNICODE = 0  
LOADBIN = -L ../../XEngine_ThirdPart/jsoncpp -L ../../XEngine_ModuleConfigure -L ../../XEngine_ModuleDatabase -L ../../XEngine_ModuleProtocol
LIB = -lXEngine_BaseLib -lXEngine_Algorithm -lXEngine_Core -lXEngine_ManagePool -lHelpComponents_XLog -lRfcComponents_WSProtocol \
      -ljsoncpp -lXEngine_ModuleConfigure -lXEngine_ModuleDatabase -lXEngine_ModuleProtocol
LIBEX = -ldl -lpthread
LOADSO = -Wl,-rpath=./,--disable-new-dtags
LIBINCLUDE = XEngine_Configure.o XEngine_Network.o XEngine_WSTask.o XEngine_WebSocketApp.o

ifeq ($(shell uname),Darwin)
	LOADSO = 
else
	LOADBIN += -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_Core -L /usr/local/lib/XEngine_Release/XEngine_HelpComponents -L /usr/local/lib/XEngine_Release/XEngine_RfcComponents 
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
	$(CC) $(DEBUG) $(LIBINCLUDE) -o XEngine_WebSocketApp $(LOADBIN) $(LIB) $(LIBEX) $(LOADSO)
  
XEngine_Configure.o:./XEngine_Configure.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_Configure.cpp
XEngine_Network.o:./XEngine_Network.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_Network.cpp 
XEngine_WSTask.o:./XEngine_WSTask.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_WSTask.cpp
		
XEngine_WebSocketApp.o:./XEngine_WebSocketApp.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_WebSocketApp.cpp   


InstallAll:InstallApp
InstallApp:./XEngine_WebSocketApp
	cp -f ./XEngine_WebSocketApp ../../../XEngine_Release/XEngine_WebSocketApp

CleanAll:CleanObj CleanMk
CleanObj:                                              
	rm *.o
CleanMk:                                  
	rm XEngine_WebSocketApp     
	       
