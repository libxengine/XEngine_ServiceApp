﻿#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib,"Ws2_32")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_NetHelp/NetHelp_APIClient")
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_NetHelp/APIClient_Define.h>
#include <XEngine_Include/XEngine_NetHelp/APIClient_Error.h>

//需要优先配置XEngine
//WINDOWS支持VS2022 x86 debug 编译调试
//linux:g++ -std=c++17 -Wall -g APPClient_HTTPExample.cpp -o APPClient_HTTPExample.exe -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_NetHelp -lXEngine_BaseLib -lNetHelp_APIClient
//Macos:g++ -std=c++17 -Wall -g APPClient_HTTPExample.cpp -o APPClient_HTTPExample.exe -lXEngine_BaseLib -lNetHelp_APIClient

int main()
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	int nLen = 0;
	XCHAR *ptszMsgBuffer = NULL;
	LPCXSTR lpszUrl = _X("http://127.0.0.1:5001");
	
	if (!APIClient_Http_Request("GET", lpszUrl, NULL, NULL, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}