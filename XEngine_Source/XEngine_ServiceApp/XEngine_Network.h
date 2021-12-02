#pragma once
/********************************************************************
//    Created:     2021/12/02  16:39:22
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_Network.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp
//    File Base:   XEngine_Network
//    File Ext:    h
//    Project:     XEngine(����ͨ������)
//    Author:      qyt
//    Purpose:     ����IO��ش���
//    History:
*********************************************************************/
//TCP���
BOOL __stdcall Network_Callback_TCPLogin(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam);                                  //�û�����
void __stdcall Network_Callback_TCPRecv(LPCTSTR lpszClientAddr, SOCKET hSocket, LPCTSTR lpszRecvMsg, int nMsgLen, LPVOID lParam); //���ܵ�����
void __stdcall Network_Callback_TCPLeave(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam);                                  //�û��뿪
void __stdcall Network_Callback_TCPHeart(LPCSTR lpszClientAddr, SOCKET hSocket, int nStatus, LPVOID lParam);                      //������ʱ
//HTTP���
BOOL __stdcall Network_Callback_HTTPLogin(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam);
void __stdcall Network_Callback_HTTPRecv(LPCTSTR lpszClientAddr, SOCKET hSocket, LPCTSTR lpszRecvMsg, int nMsgLen, LPVOID lParam);
void __stdcall Network_Callback_HTTPLeave(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam);
void __stdcall Network_Callback_HTTPHeart(LPCTSTR lpszClientAddr, SOCKET hSocket, int nStatus, LPVOID lParam);
//�ر��뷢��
void XEngine_Network_Close(LPCTSTR lpszClientAddr, int nIPProto, BOOL bHeart);
BOOL XEngine_Network_Send(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, int nIPProto);