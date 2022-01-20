RELEASE = 0
UNICODE = 0
#编译的选项参数
FLAGS = RELEASE=$(RELEASE)
#要编译的模块
MODULE_CONFIGURE_PATH = ./XEngine_ModuleConfigure
APP_CENTER_PATH = ./XEngine_ServiceApp/XEngine_CenterApp
APP_HTTP_PATH = ./XEngine_ServiceApp/XEngine_HttpApp

XENGINE_MODULES = libXEngine_ModuleConfigure.so XEngine_CenterApp.exe XEngine_HttpApp.exe

.PHONY:MakeAll 
MakeAll:$(XENGINE_MODULES)

libXEngine_ModuleConfigure.so:
	make -C $(MODULE_CONFIGURE_PATH) $(FLAGS)
	
XEngine_CenterApp.exe:
	make -C $(APP_CENTER_PATH) $(FLAGS)
XEngine_HttpApp.exe:
	make -C $(APP_HTTP_PATH) $(FLAGS)

SetFlags_Install:
	export FLAGS=InstallAll
InstallAll:SetFlags_Install $(NETENGINE_LIB) 
 
SetFlags_Clean:
	export FLAGS=CleanAll
CleanAll:SetFlags_Clean $(NETENGINE_LIB) 
