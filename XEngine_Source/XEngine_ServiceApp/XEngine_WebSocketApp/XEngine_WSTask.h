#pragma once
/********************************************************************
//    Created:     2022/04/15  14:21:57
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_WebSocketApp\XEngine_WSTask.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_WebSocketApp
//    File Base:   XEngine_WSTask
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     WS任务处理代码
//    History:
*********************************************************************/
//任务处理池,用来获取一个完整包
XHTHREAD CALLBACK XEngine_WSTask_Thread(XPVOID lParam);
//任务处理相关函数,处理包的内容
bool XEngine_WSTask_Handle(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, ENUM_XENGINE_RFCOMPONENTS_WEBSOCKET_OPCODE enOPCode);