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
bool bIsRun = false;
bool bIsTest = false;

//套接字句柄
XHANDLE xhTCPSocket = NULL;
XHANDLE xhUDPSocket = NULL;

void ServiceApp_Stop(int signo)
{
	if (bIsRun)
	{
		bIsRun = false;
		//销毁业务资源
		NetCore_TCPXCore_DestroyEx(xhTCPSocket);
		NetCore_UDPXCore_DestroyEx(xhUDPSocket);
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
	bIsRun = true;
	int nRet = -1;
	signal(SIGINT, ServiceApp_Stop);
	signal(SIGTERM, ServiceApp_Stop);
	signal(SIGABRT, ServiceApp_Stop);
	//初始化参数
	if (!XEngine_Configure_Parament(argc, argv))
	{
		return -1;
	}
	//启动TCP网络
	xhTCPSocket = NetCore_TCPXCore_StartEx(8880, 1000, 4);
	if (NULL == xhTCPSocket)
	{
		goto XENGINE_SERVICEAPP_EXIT;
	}
	//绑定网络事件
	NetCore_TCPXCore_RegisterCallBackEx(xhTCPSocket, Network_Callback_SimpleLogin, Network_Callback_SimpleTCPRecv, Network_Callback_SimpleLeave);
	//启动UDP网络
	xhUDPSocket = NetCore_UDPXCore_StartEx(8880, 4);
	if (NULL == xhUDPSocket)
	{
		goto XENGINE_SERVICEAPP_EXIT;
	}
	//绑定网络事件
	NetCore_UDPXCore_RegisterCallBackEx(xhUDPSocket, Network_Callback_SimpleUDPRecv);

	while (true)
	{
		if (bIsTest)
		{
			nRet = 0;
			break;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
XENGINE_SERVICEAPP_EXIT:
	if (bIsRun)
	{
		bIsRun = false;
		//销毁业务资源
		NetCore_TCPXCore_DestroyEx(xhTCPSocket);
		NetCore_UDPXCore_DestroyEx(xhUDPSocket);
	}
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return nRet;
}