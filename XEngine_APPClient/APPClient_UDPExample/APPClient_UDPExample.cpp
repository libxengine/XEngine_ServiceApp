#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib.lib")
#pragma comment(lib,"XEngine_Client/XClient_Socket.lib")
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Client/XClient_Define.h>
#include <XEngine_Include/XEngine_Client/XClient_Error.h>
#include "../../XEngine_Source/XEngine_UserProtocol.h"

//需要优先配置XEngine
//WINDOWS支持VS2022 x86 and x64,release or debug 编译调试
//linux and macos 编译命令:g++ -std=c++17 -Wall -g APPClient_UDPExample.cpp -o APPClient_UDPExample.exe -lXEngine_BaseLib -lXClient_Socket

int main(int argc, char** argv)
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	XSOCKET m_Socket;
	LPCXSTR lpszServiceAddr = _X("127.0.0.1");
	LPCXSTR lpszMsgBuffer = _X("123456789aaa");
	if (!XClient_UDPSelect_Create(&m_Socket))
	{
		printf("连接失败！错误:%lX\n", XClient_GetLastError());
		return 0;
	}
	XClient_UDPSelect_Connect(m_Socket, lpszServiceAddr, 8880);

	if (!XClient_UDPSelect_SendMsg(m_Socket, lpszMsgBuffer, strlen(lpszMsgBuffer)))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	XClient_UDPSelect_Close(m_Socket);
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}