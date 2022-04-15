#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2022/04/15  14:18:24
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HTTP2App\XEngine_HTTP2Task.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HTTP2App
//    File Base:   XEngine_HTTP2Task
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     HTTP2任务处理代码
//    History:
*********************************************************************/
XHTHREAD CALLBACK XEngine_HTTP2Task_Thread(LPVOID lParam)
{
	//任务池是编号1开始的.
	int nThreadPos = *(int*)lParam;
	nThreadPos++;
	while (bIsRun)
	{
		//等待编号1的任务池触发一个组完包的事件
		if (!RfcComponents_Http2Server_EventWaitEx(xhHTTP2Packet, nThreadPos))
		{
			continue;
		}
		int nListCount = 0;
		RFCCOMPONENTS_HTTP_PKTCLIENT** ppSst_ListAddr;
		//获得编号1的所有待处理任务的客户端列表(也就是客户端发送过来的数据已经组好了一个包,需要我们处理)
		RfcComponents_Http2Server_GetPoolEx(xhHTTP2Packet, nThreadPos, &ppSst_ListAddr, &nListCount);
		//先循环客户端
		for (int i = 0; i < nListCount; i++)
		{
			int nStreamCount = 0;
			RFCCOMPONENTS_HTTP2_PKTSTREAM** ppSt_PKTStream;    //流列表,每个流ID可能有单独的列表
			RfcComponents_Http2Server_GetStreamEx(xhHTTP2Packet, ppSst_ListAddr[i]->tszClientAddr, &ppSt_PKTStream, &nStreamCount);
			for (int j = 0; j < nStreamCount; j++)
			{
				//最后根据流列表来循环包个数
				for (int k = 0; k < ppSt_PKTStream[j]->nPktCount; k++)
				{
					//得到一个指定客户端的完整数据包
					int nMsgLen = 0;                                    //客户端发送的数据大小,不包括头
					int nHdrCount = 0;                                  //头字段列表
					TCHAR* ptszMsgBuffer;                               //客户端发送的数据,只有DATA包类型才有,一般POST会跟上DATA
					XENGINE_RFCCOMPONENTS_HTTP2_FRAME_TYPE enFrameType; //帧类型
					RFCCOMPONENTS_HTTP2_HPACK** ppSt_ListHdr;           //HPACK字段列表
					if (RfcComponents_Http2Server_GetClientEx(xhHTTP2Packet, ppSst_ListAddr[i]->tszClientAddr, ppSt_PKTStream[j]->nStreamID, &enFrameType, &ptszMsgBuffer, &nMsgLen, &ppSt_ListHdr, &nHdrCount))
					{
						//在另外一个函数里面处理数据
						XEngine_HTTP2Task_Handle(enFrameType, ppSt_PKTStream[j]->nStreamID, ppSst_ListAddr[i]->tszClientAddr, ptszMsgBuffer, nMsgLen, ppSt_ListHdr, nHdrCount);
						//释放内存
						if (nMsgLen > 0)
						{
							BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
						}
						BaseLib_OperatorMemory_Free((XPPPMEM)&ppSt_ListHdr, nHdrCount);
					}
				}
			}
			BaseLib_OperatorMemory_Free((XPPPMEM)&ppSt_PKTStream, nStreamCount);
		}
		BaseLib_OperatorMemory_Free((XPPPMEM)&ppSst_ListAddr, nListCount);
	}
	return 0;
}
BOOL XEngine_HTTP2Task_Handle(XENGINE_RFCCOMPONENTS_HTTP2_FRAME_TYPE enFrameType, int nStreamID, LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, RFCCOMPONENTS_HTTP2_HPACK** ppSt_ListHdr, int nHdrCount)
{
	int nLen = 4096;
	LPCTSTR lpszMethodPost = _T("POST");
	LPCTSTR lpszMethodGet = _T("GET");
	TCHAR tszMsgBuffer[4096];
	TCHAR* ptszMsgBuffer = NULL;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数
	RFCCOMPONENTS_HTTP_REQPARAM st_HTTPRequest;

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));
	memset(&st_HTTPRequest, '\0', sizeof(RFCCOMPONENTS_HTTP_REQPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.nStreamID = nStreamID;
	//处理类型
	if (XENGINE_RFCCOMPONENTS_HTTP2_FRAME_TYPE_HEADERS == enFrameType)
	{
		//header 如果是POST,都跟上数据,get可能不带数据
		RfcComponents_HttpHelp_HTTP2HdrConvert(&st_HTTPRequest, &ppSt_ListHdr, nHdrCount);
		if (0 == _tcsnicmp(lpszMethodPost, st_HTTPRequest.tszHttpMethod, _tcslen(lpszMethodPost)))
		{
			//只有POST才有后续数据
			RfcComponents_Http2Server_GetClientEx(xhHTTP2Packet, lpszMsgBuffer, nStreamID, &enFrameType, &ptszMsgBuffer, &nMsgLen);
			//编写自己的代码,参考GET
		}
		else if (0 == _tcsnicmp(lpszMethodGet, st_HTTPRequest.tszHttpMethod, _tcslen(lpszMethodGet)))
		{
			//编写自己的代码
			LPCTSTR lpszMsgBuffer = _T("Hello World");
			//首先发送HEADERS包
			RfcComponents_Http2Server_PKTHeaderEx(xhHTTP2Packet, tszMsgBuffer, &nLen, &st_HDRParam, 6);
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nLen);
			//最后发送DATA数据包
			RfcComponents_Http2Server_PKTDataEx(xhHTTP2Packet, tszMsgBuffer, &nLen, st_HDRParam.nStreamID, lpszMsgBuffer, _tcslen(lpszMsgBuffer));
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP2客户端:%s,发送GET请求给服务器"), lpszClientAddr);
		}
	}
	else if (XENGINE_RFCCOMPONENTS_HTTP2_FRAME_TYPE_PRIORITY == enFrameType)
	{

	}
	else if (XENGINE_RFCCOMPONENTS_HTTP2_FRAME_TYPE_RST_STREAM == enFrameType)
	{

	}
	else if (XENGINE_RFCCOMPONENTS_HTTP2_FRAME_TYPE_SETTINGS == enFrameType)
	{
		//第一次登录需要发送SETTING同步
		RfcComponents_Http2Server_PKTSettingEx(xhHTTP2Packet, tszMsgBuffer, &nLen, 100, 1024000, 1024000, 8196);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nLen);
	}
	else if (XENGINE_RFCCOMPONENTS_HTTP2_FRAME_TYPE_PUSH_PROMISE == enFrameType)
	{

	}
	else if (XENGINE_RFCCOMPONENTS_HTTP2_FRAME_TYPE_PING == enFrameType)
	{

	}
	else if (XENGINE_RFCCOMPONENTS_HTTP2_FRAME_TYPE_GOAWAY == enFrameType)
	{

	}
	else
	{
		//其他帧不用处理
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("HTTP2客户端:%s,协议错误"), lpszClientAddr);
	}
	return TRUE;
}