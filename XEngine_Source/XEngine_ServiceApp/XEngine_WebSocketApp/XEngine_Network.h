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
bool CALLBACK Network_Callback_WSLogin(LPCXSTR lpszClientAddr, XSOCKET hSocket, XPVOID lParam);
void CALLBACK Network_Callback_WSRecv(LPCXSTR lpszClientAddr, XSOCKET hSocket, LPCXSTR lpszRecvMsg, int nMsgLen, XPVOID lParam);
void CALLBACK Network_Callback_WSLeave(LPCXSTR lpszClientAddr, XSOCKET hSocket, XPVOID lParam);
void CALLBACK Network_Callback_WSHeart(LPCXSTR lpszClientAddr, XSOCKET hSocket, int nStatus, XPVOID lParam);
//关闭与发送
void XEngine_Network_Close(LPCXSTR lpszClientAddr, bool bHeart);
bool XEngine_Network_Send(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, ENUM_XENGINE_RFCOMPONENTS_WEBSOCKET_OPCODE enOPCode);