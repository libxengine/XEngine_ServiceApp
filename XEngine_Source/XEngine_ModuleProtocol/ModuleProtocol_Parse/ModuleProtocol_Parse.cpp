#include "pch.h"
#include "ModuleProtocol_Parse.h"
/********************************************************************
//    Created:     2022/03/01  09:25:28
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Parse\ModuleProtocol_Parse.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Parse
//    File Base:   ModuleProtocol_Parse
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     协议解析类
//    History:
*********************************************************************/
CModuleProtocol_Parse::CModuleProtocol_Parse()
{
}
CModuleProtocol_Parse::~CModuleProtocol_Parse()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
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
bool CModuleProtocol_Parse::ModuleProtocol_Parse_Hello(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszMSGBuffer, int nMSGLen)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMSGBuffer) || (0 == pInt_MSGLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_MODULE_PROTOCOL_PARSE_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonRBuilder;
	//开始解析配置文件
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonRBuilder.newCharReader());
	if (!pSt_JsonReader->parse(lpszMSGBuffer, lpszMSGBuffer + nMSGLen, &st_JsonRoot, &st_JsonError))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_MODULE_PROTOCOL_PARSE_JSON;
		return false;
	}

	if (!st_JsonRoot["lpszMSGBuffer"].isNull())
	{
		_tcsxcpy(ptszMSGBuffer, st_JsonRoot["lpszMSGBuffer"].asCString());
	}
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Parse_Register
函数功能：解析用户信息
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的缓冲区
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入要解析的大小
 参数.三：pSt_UserInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Parse::ModuleProtocol_Parse_Register(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_PROTOCOL_USERINFO* pSt_UserInfo)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == lpszMsgBuffer) || (NULL == pSt_UserInfo))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_MODULE_PROTOCOL_PARSE_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_ReaderBuilder;

	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_ReaderBuilder.newCharReader());
	if (!pSt_JsonReader->parse(lpszMsgBuffer, lpszMsgBuffer + nMsgLen, &st_JsonRoot, &st_JsonError))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_MODULE_PROTOCOL_PARSE_JSON;
		return false;
	}
	Json::Value st_JsonProtocol = st_JsonRoot["st_UserInfo"];
	if (!st_JsonProtocol["tszUserName"].isNull())
	{
		_tcsxcpy(pSt_UserInfo->tszUserName, st_JsonProtocol["tszUserName"].asCString());
	}
	if (!st_JsonProtocol["tszUserPass"].isNull())
	{
		_tcsxcpy(pSt_UserInfo->tszUserPass, st_JsonProtocol["tszUserPass"].asCString());
	}
	if (!st_JsonProtocol["tszEMailAddr"].isNull())
	{
		_tcsxcpy(pSt_UserInfo->tszEMailAddr, st_JsonProtocol["tszEMailAddr"].asCString());
	}
	if (!st_JsonProtocol["tszLoginTime"].isNull())
	{
		_tcsxcpy(pSt_UserInfo->tszLoginTime, st_JsonProtocol["tszLoginTime"].asCString());
	}
	if (!st_JsonProtocol["tszCreateTime"].isNull())
	{
		_tcsxcpy(pSt_UserInfo->tszCreateTime, st_JsonProtocol["tszCreateTime"].asCString());
	}
	if (!st_JsonProtocol["nPhoneNumber"].isNull())
	{
		pSt_UserInfo->nPhoneNumber = st_JsonProtocol["nPhoneNumber"].asInt64();
	}
	if (!st_JsonProtocol["nIDNumber"].isNull())
	{
		pSt_UserInfo->nIDNumber = st_JsonProtocol["nIDNumber"].asInt64();
	}
	if (!st_JsonProtocol["nUserLevel"].isNull())
	{
		pSt_UserInfo->nUserLevel = st_JsonProtocol["nUserLevel"].asInt();
	}
	if (!st_JsonProtocol["nUserState"].isNull())
	{
		pSt_UserInfo->nUserState = st_JsonProtocol["nUserState"].asInt();
	}
	return true;
}