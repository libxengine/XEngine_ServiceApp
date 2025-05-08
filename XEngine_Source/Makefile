RELEASE = 0
UNICODE = 0
PLATFORM=linux
FLAGS = 

#要编译的模块
THIRDPART_MODULE_JSONCPP = ./XEngine_Depend/XEngine_Module/jsoncpp
THIRDPART_MODULE_REPORT = ./XEngine_Depend/XEngine_Module/XEngine_InfoReport

MODULE_CONFIGURE_PATH = ./XEngine_ModuleConfigure
MODULE_DATABASE_PATH = ./XEngine_ModuleDatabase
MODULE_PROTOCOL_PATH = ./XEngine_ModuleProtocol
APP_CENTER_PATH = ./XEngine_ServiceApp/XEngine_CenterApp
APP_HTTP_PATH = ./XEngine_ServiceApp/XEngine_HttpApp
APP_HTTP2_PATH = ./XEngine_ServiceApp/XEngine_HTTP2App
APP_WEBSOCKET_PATH = ./XEngine_ServiceApp/XEngine_WebSocketApp
APP_SIMPLE_PATH = ./XEngine_ServiceApp/XEngine_SimpleApp

ifeq ($(PLATFORM),linux)
	FILEEXT = so
else ifeq ($(PLATFORM),mac)
	FILEEXT = dylib
endif

XENGINE_MODULES = libjsoncpp.so libXEngine_InfoReport.so                    \
                  libXEngine_ModuleConfigure.so libXEngine_ModuleDatabase.so libXEngine_ModuleProtocol.so                 \
				  XEngine_CenterApp.exe XEngine_HttpApp.exe XEngine_Http2App.exe XEngine_WebSocketApp.exe XEngine_SimpleApp.exe

.PHONY:MakeAll 
MakeAll:$(XENGINE_MODULES)

libjsoncpp.so:
ifeq ($(FLAGS), InstallAll)
	cp $(THIRDPART_MODULE_JSONCPP)/libjsoncpp.$(FILEEXT) ../XEngine_Release/
else
	make -C $(THIRDPART_MODULE_JSONCPP) PLATFORM=$(PLATFORM) RELEASE=$(RELEASE) $(FLAGS)
endif
libXEngine_InfoReport.so:
ifeq ($(FLAGS), InstallAll)
	cp $(THIRDPART_MODULE_REPORT)/libXEngine_InfoReport.$(FILEEXT) ../XEngine_Release/
else
	make -C $(THIRDPART_MODULE_REPORT) PLATFORM=$(PLATFORM) RELEASE=$(RELEASE) $(FLAGS)
endif

libXEngine_ModuleConfigure.so:
	make -C $(MODULE_CONFIGURE_PATH) UNICODE=$(UNICODE) PLATFORM=$(PLATFORM) RELEASE=$(RELEASE) $(FLAGS)
libXEngine_ModuleDatabase.so:
	make -C $(MODULE_DATABASE_PATH) UNICODE=$(UNICODE) PLATFORM=$(PLATFORM) RELEASE=$(RELEASE) $(FLAGS)
libXEngine_ModuleProtocol.so:
	make -C $(MODULE_PROTOCOL_PATH) UNICODE=$(UNICODE) PLATFORM=$(PLATFORM) RELEASE=$(RELEASE) $(FLAGS)

XEngine_CenterApp.exe:
	make -C $(APP_CENTER_PATH) UNICODE=$(UNICODE) PLATFORM=$(PLATFORM) RELEASE=$(RELEASE) $(FLAGS)
XEngine_HttpApp.exe:
	make -C $(APP_HTTP_PATH) UNICODE=$(UNICODE) PLATFORM=$(PLATFORM) RELEASE=$(RELEASE) $(FLAGS)
XEngine_Http2App.exe:
	make -C $(APP_HTTP2_PATH) UNICODE=$(UNICODE) PLATFORM=$(PLATFORM) RELEASE=$(RELEASE) $(FLAGS)
XEngine_WebSocketApp.exe:
	make -C $(APP_WEBSOCKET_PATH) UNICODE=$(UNICODE) PLATFORM=$(PLATFORM) RELEASE=$(RELEASE) $(FLAGS)
XEngine_SimpleApp.exe:
	make -C $(APP_SIMPLE_PATH) UNICODE=$(UNICODE) PLATFORM=$(PLATFORM) RELEASE=$(RELEASE) $(FLAGS)
