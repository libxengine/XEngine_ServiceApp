#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2022/04/15  14:24:53
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_WebSocketApp\XEngine_WSTask.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_WebSocketApp
//    File Base:   XEngine_WSTask
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     WS任务处理代码
//    History:
*********************************************************************/
XHTHREAD CALLBACK XEngine_WSTask_Thread(XPVOID lParam)
{
	//任务池是编号1开始的.
	int nThreadPos = *(int*)lParam;
	nThreadPos++;
	while (bIsRun)
	{
		//等待编号1的任务池触发一个组完包的事件
		if (!RfcComponents_WSPacket_WaitEventEx(xhWSPacket, nThreadPos))
		{
			continue;
		}
		int nListCount = 0;
		XENGINE_MANAGEPOOL_TASKEVENT** ppSt_ListClient;
		//获得编号1的所有待处理任务的客户端列表(也就是客户端发送过来的数据已经组好了一个包,需要我们处理)
		RfcComponents_WSPacket_GetPoolEx(xhWSPacket, nThreadPos, &ppSt_ListClient, &nListCount);
		for (int i = 0; i < nListCount; i++)
		{
			//先循环客户端
			int nMsgLen = 0;
			XCHAR* ptszMsgBuffer = NULL;                          //客户端负载内容
			ENUM_XENGINE_RFCOMPONENTS_WEBSOCKET_OPCODE enOPCode;  //包协议
			if (RfcComponents_WSPacket_GetMemoryEx(xhWSPacket, ppSt_ListClient[i]->tszClientAddr, &ptszMsgBuffer, &nMsgLen, &enOPCode))
			{
				//在另外一个函数里面处理数据
				XEngine_WSTask_Handle(ppSt_ListClient[i]->tszClientAddr, ptszMsgBuffer, nMsgLen, enOPCode);
				//释放内存
				if (nMsgLen > 0)
				{
					BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
				}
			}
			BaseLib_Memory_Free((XPPPMEM)&ppSt_ListClient, nListCount);
		}
	}
	return 0;
}
bool XEngine_WSTask_Handle(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, ENUM_XENGINE_RFCOMPONENTS_WEBSOCKET_OPCODE enOPCode)
{
	//开始处理协议
	if (ENUM_XENGINE_RFCOMPONENTS_WEBSOCKET_OPCODE_CONTINUE == enOPCode)
	{

	}
	else if (ENUM_XENGINE_RFCOMPONENTS_WEBSOCKET_OPCODE_TEXT == enOPCode)
	{
		//发送数据给客户端,发什么我们返回什么
		XEngine_Network_Send(lpszClientAddr, lpszMsgBuffer, nMsgLen, enOPCode);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("WEBSOCKET客户端:%s,发送数据给服务器处理成功,大小:%d,内容:%s"), lpszClientAddr, nMsgLen, lpszMsgBuffer);
	}
	else if (ENUM_XENGINE_RFCOMPONENTS_WEBSOCKET_OPCODE_BINARY == enOPCode)
	{

	}
	else if (ENUM_XENGINE_RFCOMPONENTS_WEBSOCKET_OPCODE_CLOSE == enOPCode)
	{

	}
	else if (ENUM_XENGINE_RFCOMPONENTS_WEBSOCKET_OPCODE_PING == enOPCode)
	{

	}
	else if (ENUM_XENGINE_RFCOMPONENTS_WEBSOCKET_OPCODE_PONG == enOPCode)
	{

	}
	else
	{
		//其他帧不用处理
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("WEBSOCKET客户端:%s,协议错误"), lpszClientAddr);
	}
	return true;
}