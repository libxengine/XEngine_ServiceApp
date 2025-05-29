#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2022/01/20  14:35:20
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_CenterApp\XEngine_Network.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_CenterApp
//    File Base:   XEngine_Network
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     网络IO相关代码
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////下面是业务网络IO相关代码处理函数
bool XCALLBACK Network_Callback_SimpleLogin(LPCXSTR lpszClientAddr, XSOCKET hSocket, XPVOID lParam)
{
	_xtprintf(_X("业务客户端:%s,连接到服务器\n"), lpszClientAddr);
	return true;
}
void XCALLBACK Network_Callback_SimpleTCPRecv(LPCXSTR lpszClientAddr, XSOCKET hSocket, LPCXSTR lpszRecvMsg, int nMsgLen, XPVOID lParam)
{
	_xtprintf(_X("TCP业务客户端:%s,接受到数据,大小:%d,内容:%s\n"), lpszClientAddr, nMsgLen, lpszRecvMsg);
}
void XCALLBACK Network_Callback_SimpleUDPRecv(LPCXSTR lpszClientAddr, XSOCKET hSocket, LPCXSTR lpszRecvMsg, int nMsgLen, XPVOID lParam)
{
	_xtprintf(_X("UDP业务客户端:%s,接受到数据,大小:%d,内容:%s\n"), lpszClientAddr, nMsgLen, lpszRecvMsg);
}
void XCALLBACK Network_Callback_SimpleLeave(LPCXSTR lpszClientAddr, XSOCKET hSocket, XPVOID lParam)
{
	_xtprintf(_X("业务客户端:%s,离开服务器\n"), lpszClientAddr);
}
//////////////////////////////////////////////////////////////////////////
bool XEngine_Network_Send(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	if (IPPROTO_TCP == nType)
	{
		//发送数据给指定客户端
		if (!NetCore_TCPXCore_SendEx(xhTCPSocket, lpszClientAddr, lpszMsgBuffer, nMsgLen))
		{
			return false;
		}
	}
	else
	{
		//发送数据给指定客户端
		if (!NetCore_UDPXCore_SendEx(xhUDPSocket, lpszClientAddr, lpszMsgBuffer, nMsgLen))
		{
			return false;
		}
	}
	return true;
}