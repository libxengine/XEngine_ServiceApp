#pragma once
/********************************************************************
//    Created:     2021/12/02  17:14:41
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HTTPTask.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp
//    File Base:   XEngine_HTTPTask
//    File Ext:    h
//    Project:     XEngine(����ͨ������)
//    Author:      qyt
//    Purpose:     HTTP���������
//    History:
*********************************************************************/
//�������,������ȡһ��������
XHTHREAD CALLBACK XEngine_HTTPTask_Thread(LPVOID lParam);
//��������غ���,�����������
BOOL XEngine_HTTPTask_Handle(RFCCOMPONENTS_HTTP_REQPARAM* pSt_HTTPParam, LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, TCHAR** pptszListHdr, int nHdrCount);