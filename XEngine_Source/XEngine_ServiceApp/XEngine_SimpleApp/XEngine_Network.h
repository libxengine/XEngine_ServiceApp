#pragma once
/********************************************************************
//    Created:     2022/12/30  09:53:59
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_SimpleApp\XEngine_Network.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_SimpleApp
//    File Base:   XEngine_Network
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     网络IO相关代码
//    History:
*********************************************************************/
//业务相关
BOOL __stdcall Network_Callback_SimpleLogin(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam);                                  //用户连接
void __stdcall Network_Callback_SimpleRecv(LPCTSTR lpszClientAddr, SOCKET hSocket, LPCTSTR lpszRecvMsg, int nMsgLen, LPVOID lParam); //接受到数据
void __stdcall Network_Callback_SimpleLeave(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam);                                  //用户离开
//关闭与发送
BOOL XEngine_Network_Send(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen);