#pragma once
/********************************************************************
//    Created:     2021/12/02  17:06:56
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_TCPTask.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp
//    File Base:   XEngine_TCPTask
//    File Ext:    h
//    Project:     XEngine(����ͨ������)
//    Author:      qyt
//    Purpose:     TCP���������
//    History:
*********************************************************************/
//�������,������ȡһ��������
XHTHREAD CALLBACK XEngine_TCPTask_Thread(LPVOID lParam);
//��������غ���,�����������
BOOL XEngine_TCPTask_Handle(XENGINE_PROTOCOLHDR* pSt_ProtocolHdr, LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen);