#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2021/12/02  17:08:19
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_TCPTask.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp
//    File Base:   XEngine_TCPTask
//    File Ext:    cpp
//    Project:     XEngine(����ͨ������)
//    Author:      qyt
//    Purpose:     TCP���������
//    History:
*********************************************************************/
XHTHREAD CALLBACK XEngine_TCPTask_Thread(LPVOID lParam)
{
	int nThreadPos = *(int*)lParam;
	nThreadPos++;
	while (bIsRun)
	{
		if (!HelpComponents_Datas_WaitEventEx(xhTCPPacket, nThreadPos))
		{
			continue;
		}
		int nListCount = 0;
		XENGINE_PROTOCOLHDR st_ProtocolHdr;;
		HELPCOMPONENT_PACKET_CLIENT** ppSst_ListAddr;

		memset(&st_ProtocolHdr, '\0', sizeof(XENGINE_PROTOCOLHDR));

		HelpComponents_Datas_GetPoolEx(xhTCPPacket, nThreadPos, &ppSst_ListAddr, &nListCount);
		for (int i = 0; i < nListCount; i++)
		{
			for (int j = 0; j < ppSst_ListAddr[i]->nPktCount; j++)
			{
				int nMsgLen = 0;
				TCHAR* ptszMsgBuffer = NULL;
				if (!HelpComponents_Datas_GetMemoryEx(xhTCPPacket, ppSst_ListAddr[i]->tszClientAddr, &ptszMsgBuffer, &nMsgLen, &st_ProtocolHdr))
				{
					DWORD dwRet = Packets_GetLastError();
					if (ERROR_HELPCOMPONENTS_PACKETS_PROTOCOL_GET_ISNULL == dwRet)
					{
						XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("��ȡ��Ϣ����Э��ʧ�ܣ���ȡ���ݰ�ʧ�ܣ�����%lX"), dwRet);
					}
					continue;
				}
				XEngine_TCPTask_Handle(&st_ProtocolHdr, ppSst_ListAddr[i]->tszClientAddr, ptszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_FreeCStyle((VOID**)&ptszMsgBuffer);
			}
		}
		BaseLib_OperatorMemory_Free((XPPPMEM)&ppSst_ListAddr, nListCount);
	}
	return 0;
}
BOOL XEngine_TCPTask_Handle(XENGINE_PROTOCOLHDR* pSt_ProtocolHdr, LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen)
{
	//���￪ʼ��д��Ĵ���
	if (ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_NORMAL == pSt_ProtocolHdr->unOperatorType)
	{
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("TCP��Ϣ��:%s,��Э�����Э�飺%x"), lpszClientAddr, pSt_ProtocolHdr->unOperatorType);
	}
	return TRUE;
}