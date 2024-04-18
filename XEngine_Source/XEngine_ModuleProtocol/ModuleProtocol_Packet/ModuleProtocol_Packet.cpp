#include "pch.h"
#include "ModuleProtocol_Packet.h"
/********************************************************************
//    Created:     2022/03/01  09:25:13
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Packet\ModuleProtocol_Packet.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Packet
//    File Base:   ModuleProtocol_Packet
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     协议打包类
//    History:
*********************************************************************/
CModuleProtocol_Packet::CModuleProtocol_Packet()
{
}
CModuleProtocol_Packet::~CModuleProtocol_Packet()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
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
  类型：常量字符指针
  可空：Y
  意思：输入错误信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_Comm(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_PROTOCOLHDR* pSt_ProtocolHdr /* = NULL */, int nCode /* = 0 */, LPCXSTR lpszMSGBuffer /* = _X("success") */)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	int nPos = 0;
	Json::Value st_JsonRoot;
	Json::StreamWriterBuilder st_JsonWBuilder;
	//JSON赋值
	st_JsonRoot["code"] = nCode;
	st_JsonRoot["msg"] = lpszMSGBuffer;

	*pInt_MSGLen = Json::writeString(st_JsonWBuilder, st_JsonRoot).length();
	//打包输出信息
	if (NULL != pSt_ProtocolHdr)
	{
		pSt_ProtocolHdr->unPacketSize = *pInt_MSGLen;
		memcpy(ptszMSGBuffer, pSt_ProtocolHdr, sizeof(XENGINE_PROTOCOLHDR));
		nPos = sizeof(XENGINE_PROTOCOLHDR);
	}
	memcpy(ptszMSGBuffer + nPos, Json::writeString(st_JsonWBuilder, st_JsonRoot).c_str(), *pInt_MSGLen);
	*pInt_MSGLen += nPos;
	return true;
}