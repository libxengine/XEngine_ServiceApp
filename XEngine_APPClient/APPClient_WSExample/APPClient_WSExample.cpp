#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib,"Ws2_32")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_Client/XClient_Socket")
#pragma comment(lib,"XEngine_RfcComponents/RfcComponents_WSProtocol")
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Client/XClient_Define.h>
#include <XEngine_Include/XEngine_Client/XClient_Error.h>
#include <XEngine_Include/XEngine_Core/ManagePool_Define.h>
#include <XEngine_Include/XEngine_Core/ManagePool_Error.h>
#include <XEngine_Include/XEngine_RfcComponents/WSProtocol_Define.h>
#include <XEngine_Include/XEngine_RfcComponents/WSProtocol_Error.h>

//需要优先配置XEngine
//WINDOWS支持VS2022 x86 and x64,release or debug 编译调试
//linux and macos 编译命令:g++ -std=c++17 -Wall -g APPClient_WSExample.cpp -o APPClient_WSExample.exe -lXEngine_BaseLib -lXClient_Socket -lRfcComponents_WSProtocol

int main()
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	
	int nLen = 0;
	XCHAR tszKeyBuffer[1024];
	XCHAR tszMsgBuffer[1024];

	memset(tszKeyBuffer, '\0', sizeof(tszKeyBuffer));
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));

	if (!RfcComponents_WSConnector_Connect(tszKeyBuffer, tszMsgBuffer, &nLen))
	{
		printf("RfcComponents_WSConnector_Connect:%lX", WSFrame_GetLastError());
		return -1;
	}

	XSOCKET hSocket = 0;
	if (!XClient_TCPSelect_Create(&hSocket, _X("127.0.0.1"), 5003))
	{
		printf("NetClient_TCPSelect_Create:%lX", XClient_GetLastError());
		return -1;
	}

	if (!XClient_TCPSelect_SendMsg(hSocket, tszMsgBuffer, nLen))
	{
		printf("NetClient_TCPSelect_SendMsg:%lX", XClient_GetLastError());
		return -1;
	}

	int nPos = 0;
	nLen = 1024;
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	if (!XClient_TCPSelect_RecvMsg(hSocket, tszMsgBuffer, &nLen))
	{
		printf("NetClient_TCPSelect_RecvMsg:%lX", XClient_GetLastError());
		return -1;
	}
	if (!RfcComponents_WSConnector_VerConnect(tszKeyBuffer, tszMsgBuffer, &nPos))
	{
		printf("RfcComponents_WSConnector_VerConnect:%lX", WSFrame_GetLastError());
		return -1;
	}

	if (nPos > 0)
	{
		printf("%s\n", tszMsgBuffer + nPos);
	}
	int nRVLen = 6;
	XCHAR tszRecvBuffer[2048];

	memset(tszRecvBuffer, '\0', sizeof(tszRecvBuffer));
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));

	if (RfcComponents_WSCodec_EncodeMsg("123456", tszMsgBuffer, &nRVLen, ENUM_XENGINE_RFCOMPONENTS_WEBSOCKET_OPCODE_TEXT, true))
	{
		if (XClient_TCPSelect_SendMsg(hSocket, tszMsgBuffer, nRVLen))
		{
			printf("NetClient_TCPSelect_SendMsg:%d\n", nRVLen);
		}
	}

	nRVLen = 2048;
	memset(tszRecvBuffer, '\0', sizeof(tszRecvBuffer));
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));

	if (XClient_TCPSelect_RecvMsg(hSocket, tszRecvBuffer, &nRVLen))
	{
		if (!RfcComponents_WSCodec_DecodeMsg(tszRecvBuffer, &nRVLen, tszMsgBuffer))
		{
			printf("RfcComponents_WSCodec_DecodeMsg:%lX\n", WSFrame_GetLastError());
		}
		printf("%s\n", tszMsgBuffer);
	}

	XClient_TCPSelect_Close(hSocket);
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}