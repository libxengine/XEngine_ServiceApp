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
BOOL __stdcall Network_Callback_SimpleLogin(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam)
{
	_tprintf(_T("业务客户端:%s,连接到服务器"), lpszClientAddr);
	return TRUE;
}
void __stdcall Network_Callback_SimpleRecv(LPCTSTR lpszClientAddr, SOCKET hSocket, LPCTSTR lpszRecvMsg, int nMsgLen, LPVOID lParam)
{
	_tprintf(_T("业务客户端:%s,接受到数据,大小:%d,内容:%s"), lpszClientAddr, nMsgLen, lpszRecvMsg);
}
void __stdcall Network_Callback_SimpleLeave(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam)
{
	_tprintf(_T("业务客户端:%s,离开服务器"), lpszClientAddr);
}
//////////////////////////////////////////////////////////////////////////
BOOL XEngine_Network_Send(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	if (IPPROTO_TCP == nType)
	{
		//发送数据给指定客户端
		if (!NetCore_TCPXCore_SendEx(xhTCPSocket, lpszClientAddr, lpszMsgBuffer, nMsgLen))
		{
			return FALSE;
		}
	}
	else
	{
		//发送数据给指定客户端
		if (!NetCore_UDPXCore_SendEx(xhUDPSocket, lpszClientAddr, lpszMsgBuffer, &nMsgLen))
		{
			return FALSE;
		}
	}
	return TRUE;
}