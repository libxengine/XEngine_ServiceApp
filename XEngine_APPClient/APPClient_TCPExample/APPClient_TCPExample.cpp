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
//WINDOWS支持VS2019 x86 debug 编译调试
//linux使用下面的命令编译
//g++ -std=c++17 -Wall -g APPClient_TCPExample.cpp -o APPClient_TCPExample.exe -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_Client -lXEngine_BaseLib -lXClient_Socket
int main(int argc, char** argv)
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	SOCKET m_Socket;
	LPCTSTR lpszServiceAddr = _T("127.0.0.1");
	LPCTSTR lpszMsgBuffer = _T("123456789aaa");
	if (!XClient_TCPSelect_Create(&m_Socket, lpszServiceAddr, 5000))
	{
		printf("连接失败！错误:%lX\n", XClient_GetLastError());
		return 0;
	}
	printf("连接成功！\n");

	TCHAR tszMsgBuffer[2048];
	XENGINE_PROTOCOLHDR st_ProtocolHdr;
	
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(&st_ProtocolHdr, '\0', sizeof(XENGINE_PROTOCOLHDR));
	//设置协议头属性
	st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
	st_ProtocolHdr.unOperatorType = ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_MSG;
	st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_MSG_TEXTREQ;
	st_ProtocolHdr.byVersion = 1;
	st_ProtocolHdr.byIsReply = TRUE;           //获得处理返回结果
	st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;
	st_ProtocolHdr.unPacketSize = _tcslen(lpszMsgBuffer);
	int nLen = sizeof(XENGINE_PROTOCOLHDR) + st_ProtocolHdr.unPacketSize;
	//打包数据
	memcpy(tszMsgBuffer, &st_ProtocolHdr, sizeof(XENGINE_PROTOCOLHDR));
	memcpy(tszMsgBuffer + sizeof(XENGINE_PROTOCOLHDR), lpszMsgBuffer, st_ProtocolHdr.unPacketSize);

	if (!XClient_TCPSelect_SendMsg(m_Socket, tszMsgBuffer, nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	nLen = 0;
	TCHAR* ptszMsgBuffer = NULL;
	memset(&st_ProtocolHdr, '\0', sizeof(XENGINE_PROTOCOLHDR));
	if (!XClient_TCPSelect_RecvPkt(m_Socket, &ptszMsgBuffer, &nLen, &st_ProtocolHdr))
	{
		printf("接受数据失败！\n");
		return 0;
	}
	printf("接受服务器返回数据,结果:%d,大小:%d,内容:%s\n", st_ProtocolHdr.wReserve, nLen, ptszMsgBuffer);
	//释放内存并且关闭客户端
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	XClient_TCPSelect_Close(m_Socket);
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}