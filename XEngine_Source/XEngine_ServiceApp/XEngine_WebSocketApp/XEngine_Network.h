#pragma once
/********************************************************************
//    Created:     2022/04/15  14:21:32
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_WebSocketApp\XEngine_Network.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_WebSocketApp
//    File Base:   XEngine_Network
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     网络IO相关代码
//    History:
*********************************************************************/
//HTTP相关
BOOL __stdcall Network_Callback_WSLogin(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam);
void __stdcall Network_Callback_WSRecv(LPCTSTR lpszClientAddr, SOCKET hSocket, LPCTSTR lpszRecvMsg, int nMsgLen, LPVOID lParam);
void __stdcall Network_Callback_WSLeave(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam);
void __stdcall Network_Callback_WSHeart(LPCTSTR lpszClientAddr, SOCKET hSocket, int nStatus, LPVOID lParam);
//关闭与发送
void XEngine_Network_Close(LPCTSTR lpszClientAddr, BOOL bHeart);
BOOL XEngine_Network_Send(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, ENUM_XENGINE_RFCOMPONENTS_WEBSOCKET_OPCODE enOPCode);