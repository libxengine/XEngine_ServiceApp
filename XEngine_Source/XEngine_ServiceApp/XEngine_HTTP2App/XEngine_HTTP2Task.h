#pragma once
/********************************************************************
//    Created:     2022/04/14  16:42:38
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HTTP2App\XEngine_HTTP2Task.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HTTP2App
//    File Base:   XEngine_HTTP2Task
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     HTTP2任务处理代码
//    History:
*********************************************************************/
//任务处理池,用来获取一个完整包
XHTHREAD XCALLBACK XEngine_HTTP2Task_Thread(XPVOID lParam);
//任务处理相关函数,处理包的内容
bool XEngine_HTTP2Task_Handle(XENGINE_RFCCOMPONENTS_HTTP2_FRAME_TYPE enFrameType, int nStreamID, LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, RFCCOMPONENTS_HTTP2_HPACK** ppSt_ListHdr, int nHdrCount);