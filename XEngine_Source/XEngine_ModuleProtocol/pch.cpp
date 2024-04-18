#include "pch.h"
#include "ModuleProtocol_Packet/ModuleProtocol_Packet.h"
#include "ModuleProtocol_Parse/ModuleProtocol_Parse.h"
/********************************************************************
//    Created:     2022/03/01  09:27:08
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleProtocol\pch.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleProtocol
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出协议模块实现
//    History:
*********************************************************************/
bool ModuleProtocol_IsErrorOccur = false;
XLONG ModuleProtocol_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModuleProtocol_Packet m_ProtocolPacket;
CModuleProtocol_Parse m_ProtocolParse;
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleProtocol_GetLastError(int* pInt_SysError)
{
	if (NULL != pInt_SysError)
	{
		*pInt_SysError = errno;
	}
	return ModuleProtocol_dwErrorCode;
}
/************************************************************************/
/*                         导出的协议打包函数                           */
/************************************************************************/
extern "C" bool ModuleProtocol_Packet_Comm(XCHAR * ptszMSGBuffer, int* pInt_MSGLen, XENGINE_PROTOCOLHDR * pSt_ProtocolHdr, int nCode, LPCXSTR lpszMSGBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_Comm(ptszMSGBuffer, pInt_MSGLen, pSt_ProtocolHdr, nCode, lpszMSGBuffer);
}
/************************************************************************/
/*                         导出的协议解析函数                           */
/************************************************************************/
extern "C" bool ModuleProtocol_Parse_Hello(XCHAR * ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszMSGBuffer, int nMSGLen)
{
	return m_ProtocolParse.ModuleProtocol_Parse_Hello(ptszMSGBuffer, pInt_MSGLen, lpszMSGBuffer, nMSGLen);
}