#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib,"Ws2_32")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_Client/XClient_APIHelp")
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Client/APIClient_Define.h>
#include <XEngine_Include/XEngine_Client/APIClient_Error.h>

//需要优先配置XEngine
//WINDOWS支持VS2022 x86 and x64,release or debug 编译调试
//linux and macos 编译命令:g++ -std=c++17 -Wall -g APPClient_HTTP2Example.cpp -o APPClient_HTTP2Example.exe -lXEngine_BaseLib -lXClient_APIHelp

int main()
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	int nLen = 0;
	XCHAR* ptszMsgBuffer = NULL;
	LPCXSTR lpszUrl = _X("http://127.0.0.1:5002");

	XCLIENT_APIHTTP st_HTTPParam;
	memset(&st_HTTPParam, '\0', sizeof(XCLIENT_APIHTTP));

	st_HTTPParam.bHTTP2Enable = true;
	if (!APIClient_Http_Request("GET", lpszUrl, NULL,NULL,&ptszMsgBuffer, &nLen, NULL, NULL, &st_HTTPParam))
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