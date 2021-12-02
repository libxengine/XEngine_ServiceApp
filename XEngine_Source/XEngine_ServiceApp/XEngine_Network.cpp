#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2021/12/02  16:40:28
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_Network.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp
//    File Base:   XEngine_Network
//    File Ext:    cpp
//    Project:     XEngine(����ͨ������)
//    Author:      qyt
//    Purpose:     ����IO��ش���
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////������TCP����IO��ش��봦����
BOOL __stdcall Network_Callback_TCPLogin(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam)
{
	//�ͻ������Ӻ�Ҫ�ѿͻ��˲��������������в���Ч
	SocketOpt_HeartBeat_InsertAddrEx(xhTCPHeart, lpszClientAddr);
	//���һ�Ҫ����һ��TCP������������,��Ȼ�޷����
	HelpComponents_Datas_CreateEx(xhTCPPacket, lpszClientAddr, 0);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("TCP�ͻ���:%s,���ӵ�������"), lpszClientAddr);
	return TRUE;
}
void __stdcall Network_Callback_TCPRecv(LPCTSTR lpszClientAddr, SOCKET hSocket, LPCTSTR lpszRecvMsg, int nMsgLen, LPVOID lParam)
{
	//���ܵ����ݺ�ֱ��Ͷ�ݸ�TCP��������,��Ϊ���ܲ���һ�������İ�,�������ǵ�������ͨ���˵õ�һ�������İ�
	if (!HelpComponents_Datas_PostEx(xhTCPPacket, lpszClientAddr, lpszRecvMsg, nMsgLen))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("TCP�ͻ���:%s,Ͷ�����ݰ����������ʧ�ܣ�����:%lX"), lpszClientAddr, Packets_GetLastError());
		return;
	}
	//��Ҫ����һ��
	SocketOpt_HeartBeat_ActiveAddrEx(xhTCPHeart, lpszClientAddr);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_DEBUG, _T("TCP�ͻ���:%s,Ͷ�����ݰ���������гɹ�,��С:%d"), lpszClientAddr, nMsgLen);
}
void __stdcall Network_Callback_TCPLeave(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam)
{
	//����ָ������������ͻ����뿪��Ϣ
	XEngine_Network_Close(lpszClientAddr, XENGINE_CLIENT_NETTYPE_TCP, FALSE);
}
void __stdcall Network_Callback_TCPHeart(LPCSTR lpszClientAddr, SOCKET hSocket, int nStatus, LPVOID lParam)
{
	//ͬ��
	XEngine_Network_Close(lpszClientAddr, XENGINE_CLIENT_NETTYPE_TCP, TRUE);
}
//////////////////////////////////////////////////////////////////////////������HTTP����IO��ش��봦����
BOOL __stdcall Network_Callback_HTTPLogin(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam)
{
	SocketOpt_HeartBeat_InsertAddrEx(xhHTTPHeart, lpszClientAddr);
	RfcComponents_HttpServer_CreateClientEx(xhHTTPPacket, lpszClientAddr, 0);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP�ͻ���:%s,���ӵ�������"), lpszClientAddr);
	return TRUE;
}
void __stdcall Network_Callback_HTTPRecv(LPCTSTR lpszClientAddr, SOCKET hSocket, LPCTSTR lpszRecvMsg, int nMsgLen, LPVOID lParam)
{
	if (!RfcComponents_HttpServer_InserQueueEx(xhHTTPPacket, lpszClientAddr, lpszRecvMsg, nMsgLen))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP�ͻ���:%s,Ͷ��HTTP���ݰ�����Ϣ����ʧ�ܣ�����:%lX"), lpszClientAddr, HttpServer_GetLastError());
		return;
	}
	SocketOpt_HeartBeat_ActiveAddrEx(xhHTTPHeart, lpszClientAddr);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_DEBUG, _T("HTTP�ͻ���:%s,Ͷ�����ݰ���������гɹ�,��С:%d"), lpszClientAddr, nMsgLen);
}
void __stdcall Network_Callback_HTTPLeave(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam)
{
	XEngine_Network_Close(lpszClientAddr, XENGINE_CLIENT_NETTYPE_HTTP, FALSE);
}
void __stdcall Network_Callback_HTTPHeart(LPCTSTR lpszClientAddr, SOCKET hSocket, int nStatus, LPVOID lParam)
{
	XEngine_Network_Close(lpszClientAddr, XENGINE_CLIENT_NETTYPE_HTTP, TRUE);
}
//////////////////////////////////////////////////////////////////////////����IO�رղ���
void XEngine_Network_Close(LPCTSTR lpszClientAddr, int nIPProto, BOOL bHeart)
{
	if (XENGINE_CLIENT_NETTYPE_TCP == nIPProto)
	{
		//�ȹر����������,���������ص����������ǿ��Բ����������ùر�
		if (bHeart)
		{
			//������ʱ���������ر�,����Ҫ������������ر�
			NetCore_TCPXCore_CloseForClientEx(xhTCPSocket, lpszClientAddr);
		}
		else
		{
			//ͬ��
			SocketOpt_HeartBeat_DeleteAddrEx(xhTCPHeart, lpszClientAddr);
		}
		//��Ҫ����ɾ����ͻ��˶�Ӧ������������е���Դ
		HelpComponents_Datas_DeleteEx(xhTCPPacket, lpszClientAddr);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("TCP�ͻ���:%s,�뿪������"), lpszClientAddr);
	}
	else if (XENGINE_CLIENT_NETTYPE_HTTP == nIPProto)
	{
		if (bHeart)
		{
			NetCore_TCPXCore_CloseForClientEx(xhHTTPSocket, lpszClientAddr);
		}
		else
		{
			SocketOpt_HeartBeat_DeleteAddrEx(xhHTTPHeart, lpszClientAddr);
		}
		RfcComponents_HttpServer_CloseClinetEx(xhHTTPPacket, lpszClientAddr);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP�ͻ���:%s,�뿪������"), lpszClientAddr);
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("δ֪�ͻ���:%s,�뿪������"), lpszClientAddr);
	}
}
//////////////////////////////////////////////////////////////////////////
BOOL XEngine_Network_Send(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, int nIPProto)
{
	//���ݿͻ���������������ҵ���߼�
	if (XENGINE_CLIENT_NETTYPE_TCP == nIPProto)
	{
		//�������ݸ�ָ���ͻ���
		if (!NetCore_TCPXCore_SendEx(xhTCPSocket, lpszClientAddr, lpszMsgBuffer, nMsgLen))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("TCP�ͻ���:%s,��������ʧ�ܣ�����:%lX"), lpszClientAddr, NetCore_GetLastError());
			return FALSE;
		}
		//���ͳɹ�����һ������
		SocketOpt_HeartBeat_ActiveAddrEx(xhTCPHeart, lpszClientAddr);
	}
	else if (XENGINE_CLIENT_NETTYPE_HTTP == nIPProto)
	{
		if (!NetCore_TCPXCore_SendEx(xhHTTPSocket, lpszClientAddr, lpszMsgBuffer, nMsgLen))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP�ͻ���:%s,��������ʧ�ܣ�����:%lX"), lpszClientAddr, NetCore_GetLastError());
			return FALSE;
		}
		SocketOpt_HeartBeat_ActiveAddrEx(xhHTTPHeart, lpszClientAddr);
	}
	else 
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("δ֪�ͻ���:%s,�������ݸ�ʧ�ܣ�����:%lX"), lpszClientAddr, NetCore_GetLastError());
	}
	return TRUE;
}