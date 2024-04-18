#pragma once
/********************************************************************
//    Created:     2022/03/01  09:27:15
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Define.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleProtocol
//    File Base:   ModuleProtocol_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出协议模块定义
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleProtocol_GetLastError(int *pInt_SysError = NULL);
/************************************************************************/
/*                         导出的协议打包函数                           */
/************************************************************************/
/********************************************************************
函数名称：ModuleProtocol_Packet_Hello
函数功能：打包一个通用回复消息
 参数.一：ptszMSGBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打好包的JSON数据信息
 参数.二：pInt_MSGLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_ProtocolHdr
  In/Out：In
  类型：数据结构指针
  可空：Y
  意思：输入要打包的协议头,如果为NULL,不打包协议头
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的错误码
 参数.五：lpszMSGBuffer
  In/Out：In
  类型：数据结构指针
  可空：Y
  意思：常量字符指针
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_Comm(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_PROTOCOLHDR* pSt_ProtocolHdr = NULL, int nCode = 0, LPCXSTR lpszMSGBuffer = _X("success"));
/************************************************************************/
/*                         导出的协议解析函数                           */
/************************************************************************/
/********************************************************************
函数名称：ModuleProtocol_Parse_Hello
函数功能：解析一个HELLO消息
 参数.一：ptszMSGBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打好包的JSON数据信息
 参数.二：pInt_MSGLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：lpszMSGBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的JSON缓冲区
 参数.四：nMSGLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_Hello(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszMSGBuffer, int nMSGLen);