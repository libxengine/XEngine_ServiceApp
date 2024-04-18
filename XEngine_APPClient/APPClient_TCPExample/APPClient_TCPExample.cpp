#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib.lib")
#pragma comment(lib,"XEngine_Client/XClient_Socket.lib")
#pragma comment(lib,"XEngine_HelpComponents/HelpComponents_Packets.lib")
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
#include <XEngine_Include/XEngine_Core/ManagePool_Define.h>
#include <XEngine_Include/XEngine_HelpComponents/Packets_Define.h>
#include <XEngine_Include/XEngine_HelpComponents/Packets_Error.h>
#include "../../XEngine_Source/XEngine_UserProtocol.h"

//需要优先配置XEngine
//WINDOWS支持VS2022 x86 and x64,release or debug 编译调试
//linux and macos 编译命令:g++ -std=c++17 -Wall -g APPClient_TCPExample.cpp -o APPClient_TCPExample.exe -lXEngine_BaseLib -lXClient_Socket -lHelpComponents_Packets


int main(int argc, char** argv)
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	XSOCKET m_Socket;
	LPCXSTR lpszServiceAddr = _X("127.0.0.1");
	LPCXSTR lpszMsgBuffer = _X("123456789aaa");
	if (!XClient_TCPSelect_Create(&m_Socket, lpszServiceAddr, 5000))
	{
		printf("连接失败！错误:%lX\n", XClient_GetLastError());
		return 0;
	}
	printf("连接成功！\n");
	//使用PACKET获取更好的组包体验
	XHANDLE xhPacket = HelpComponents_Datas_Init();
	if (NULL == xhPacket)
	{
		printf("HelpComponents_Datas_Init:%lX\n", Packets_GetLastError());
		return 0;
	}
	HelpComponents_Datas_CreateEx(xhPacket, lpszServiceAddr);

	XCHAR tszMsgBuffer[2048];
	XENGINE_PROTOCOLHDR st_ProtocolHdr;
	
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(&st_ProtocolHdr, '\0', sizeof(XENGINE_PROTOCOLHDR));
	//设置协议头属性
	st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
	st_ProtocolHdr.unOperatorType = ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_MSG;
	st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_MSG_TEXTREQ;
	st_ProtocolHdr.byVersion = 1;
	st_ProtocolHdr.byIsReply = true;           //获得处理返回结果
	st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;
	st_ProtocolHdr.unPacketSize = strlen(lpszMsgBuffer);
	int nLen = sizeof(XENGINE_PROTOCOLHDR) + st_ProtocolHdr.unPacketSize;
	//打包数据
	memcpy(tszMsgBuffer, &st_ProtocolHdr, sizeof(XENGINE_PROTOCOLHDR));
	memcpy(tszMsgBuffer + sizeof(XENGINE_PROTOCOLHDR), lpszMsgBuffer, st_ProtocolHdr.unPacketSize);

	if (!XClient_TCPSelect_SendMsg(m_Socket, tszMsgBuffer, nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	nLen = 2048;
	//也可以使用XClient_TCPSelect_RecvPkg 简单使用,不适合复杂网络环境
	if (!XClient_TCPSelect_RecvMsg(m_Socket, tszMsgBuffer, &nLen))
	{
		printf("接受数据失败！\n");
		return 0;
	}
	HelpComponents_Datas_PostEx(xhPacket, lpszServiceAddr, tszMsgBuffer, nLen);

	if (HelpComponents_Datas_WaitEventEx(xhPacket))
	{
		nLen = 0;
		memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
		memset(&st_ProtocolHdr, '\0', sizeof(XENGINE_PROTOCOLHDR));
		XCHAR* ptszMSGBuffer = NULL;
		if (HelpComponents_Datas_GetMemoryEx(xhPacket, lpszServiceAddr, &ptszMSGBuffer, &nLen, &st_ProtocolHdr))
		{
			printf("接受服务器返回数据,结果:%d,大小:%d,内容:%s\n", st_ProtocolHdr.wReserve, nLen, ptszMSGBuffer);
			//释放内存并且关闭客户端
			BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMSGBuffer);
		}
	}

	HelpComponents_Datas_DeleteEx(xhPacket, lpszServiceAddr);
	HelpComponents_Datas_Destory(xhPacket);
	XClient_TCPSelect_Close(m_Socket);
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}