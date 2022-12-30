#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2022/12/30  09:56:17
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_SimpleApp\XEngine_SimpleApp.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_SimpleApp
//    File Base:   XEngine_SimpleApp
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     入口函数头文件
//    History:
*********************************************************************/
BOOL bIsRun = FALSE;
//套接字句柄
XHANDLE xhCenterSocket = NULL;

void ServiceApp_Stop(int signo)
{
	if (bIsRun)
	{
		bIsRun = FALSE;
		//销毁业务资源
		NetCore_TCPXCore_DestroyEx(xhCenterSocket);
	}
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	exit(0);
}

int main(int argc, char** argv)
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	bIsRun = TRUE;

	signal(SIGINT, ServiceApp_Stop);
	signal(SIGTERM, ServiceApp_Stop);
	signal(SIGABRT, ServiceApp_Stop);
	//启动网络
	xhCenterSocket = NetCore_TCPXCore_StartEx(8880, 1000, 4);
	if (NULL == xhCenterSocket)
	{
		goto XENGINE_SERVICEAPP_EXIT;
	}
	//绑定网络事件
	NetCore_TCPXCore_RegisterCallBackEx(xhCenterSocket, Network_Callback_SimpleLogin, Network_Callback_SimpleRecv, Network_Callback_SimpleLeave);
	
	while (TRUE)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
XENGINE_SERVICEAPP_EXIT:
	if (bIsRun)
	{
		bIsRun = FALSE;
		//销毁业务资源
		NetCore_TCPXCore_DestroyEx(xhCenterSocket);
	}
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}