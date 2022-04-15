#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2022/04/15  14:22:38
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_WebSocketApp\XEngine_Network.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_WebSocketApp
//    File Base:   XEngine_Network
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     网络IO相关代码
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////下面是HTTP网络IO相关代码处理函数
BOOL __stdcall Network_Callback_WSLogin(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam)
{
	SocketOpt_HeartBeat_InsertAddrEx(xhWSHeart, lpszClientAddr);
	RfcComponents_WSPacket_CreateEx(xhWSPacket, lpszClientAddr, 0);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("WEBSOCKET客户端:%s,连接到服务器"), lpszClientAddr);
	return TRUE;
}
void __stdcall Network_Callback_WSRecv(LPCTSTR lpszClientAddr, SOCKET hSocket, LPCTSTR lpszRecvMsg, int nMsgLen, LPVOID lParam)
{
	BOOL bLogin = FALSE;
	RfcComponents_WSPacket_GetLoginEx(xhWSPacket, lpszClientAddr, &bLogin);
	if (bLogin)
	{
		if (!RfcComponents_WSPacket_PostEx(xhWSPacket, lpszClientAddr, lpszRecvMsg, nMsgLen))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("WEBSOCKET客户端:%s,投递HTTP数据包到消息队列失败，错误:%lX"), lpszClientAddr, WSFrame_GetLastError());
			return;
		}
		SocketOpt_HeartBeat_ActiveAddrEx(xhWSHeart, lpszClientAddr);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_DEBUG, _T("WEBSOCKET客户端:%s,投递数据包到组包队列成功,大小:%d"), lpszClientAddr, nMsgLen);
	}
	else
	{
		int nSDLen = nMsgLen;
		TCHAR tszHandsBuffer[1024];
		memset(tszHandsBuffer, '\0', sizeof(tszHandsBuffer));

		RfcComponents_WSConnector_HandShake(lpszRecvMsg, &nSDLen, tszHandsBuffer);
		RfcComponents_WSPacket_SetLoginEx(xhWSPacket, lpszClientAddr);
		NetCore_TCPXCore_SendEx(xhWSSocket, lpszClientAddr, tszHandsBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("WEBSOCKET客户端:%s 与服务器握手成功"), lpszClientAddr);
	}
}
void __stdcall Network_Callback_WSLeave(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam)
{
	XEngine_Network_Close(lpszClientAddr, FALSE);
}
void __stdcall Network_Callback_WSHeart(LPCTSTR lpszClientAddr, SOCKET hSocket, int nStatus, LPVOID lParam)
{
	XEngine_Network_Close(lpszClientAddr, TRUE);
}
//////////////////////////////////////////////////////////////////////////网络IO关闭操作
void XEngine_Network_Close(LPCTSTR lpszClientAddr, BOOL bHeart)
{
	if (bHeart)
	{
		NetCore_TCPXCore_CloseForClientEx(xhWSSocket, lpszClientAddr);
	}
	else
	{
		SocketOpt_HeartBeat_DeleteAddrEx(xhWSHeart, lpszClientAddr);
	}
	RfcComponents_WSPacket_DeleteEx(xhWSPacket, lpszClientAddr);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("WEBSOCKET客户端:%s,离开服务器"), lpszClientAddr);
}
//////////////////////////////////////////////////////////////////////////
BOOL XEngine_Network_Send(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, ENUM_XENGINE_RFCOMPONENTS_WEBSOCKET_OPCODE enOPCode)
{
	//打包成WEBSOCKET协议包
	TCHAR tszPKTBuffer[8196];
	memset(tszPKTBuffer, '\0', sizeof(tszPKTBuffer));

	RfcComponents_WSCodec_EncodeMsg(lpszMsgBuffer, tszPKTBuffer, &nMsgLen, enOPCode);
	//发送数据给指定客户端
	if (!NetCore_TCPXCore_SendEx(xhWSSocket, lpszClientAddr, tszPKTBuffer, nMsgLen))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("WEBSOCKET客户端:%s,发送数据失败，错误:%lX"), lpszClientAddr, NetCore_GetLastError());
		return FALSE;
	}
	//发送成功激活一次心跳
	SocketOpt_HeartBeat_ActiveAddrEx(xhWSHeart, lpszClientAddr);
	return TRUE;
}