#include "pch.h"
#include "ModuleDatabase_MySql.h"
/********************************************************************
//    Created:     2022/02/28  17:25:01
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_MySql\ModuleDatabase_MySql.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_MySql
//    File Base:   ModuleDatabase_MySql
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     MYSQL操作类
//    History:
*********************************************************************/
CModuleDatabase_MySql::CModuleDatabase_MySql()
{
}
CModuleDatabase_MySql::~CModuleDatabase_MySql()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleDatabase_MySql_Init
函数功能：初始化
 参数.一：lpszSQLFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要操作的SQL文件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_MySql::ModuleDatabase_MySql_Init(DATABASE_MYSQL_CONNECTINFO* pSt_MySQLConnector)
{
	DBModule_IsErrorOccur = false;
	//打开数据库
	if (!DataBase_MySQL_Connect(&xhSQL, pSt_MySQLConnector))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_MySql_Destory
函数功能：销毁MYSQL数据库资源链接
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_MySql::ModuleDatabase_MySql_Destory()
{
	DBModule_IsErrorOccur = false;

	DataBase_MySQL_Close(xhSQL);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_MySql_UserRegister
函数功能：用户注册处理数据库语句函数
 参数.一：pSt_UserInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：要插入的用户数据
返回值
  类型：逻辑型
  意思：是否插入成功
备注：
*********************************************************************/
bool CModuleDatabase_MySql::ModuleDatabase_MySql_UserRegister(XENGINE_PROTOCOL_USERINFO* pSt_UserInfo)
{
	DBModule_IsErrorOccur = false;

	XCHAR tszSQLStatement[1024] = {};    //SQL语句

	if (ModuleDatabase_MySql_UserQuery(pSt_UserInfo->tszUserName))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_MODULE_DATABASE_EXIST;
		return false;
	}
	_xstprintf(tszSQLStatement, _X("INSERT INTO `Authorize_UserInfo`(UserName, Password, EmailAddr, PhoneNumber, IDCard, nUserLevel, CreateTime) values('%s','%s','%s',%lld,%lld,%d,NOW())"), pSt_UserInfo->tszUserName, pSt_UserInfo->tszUserPass, pSt_UserInfo->tszEMailAddr, pSt_UserInfo->nPhoneNumber, pSt_UserInfo->nIDNumber, pSt_UserInfo->nUserLevel);
	if (!DataBase_MySQL_Execute(xhSQL, tszSQLStatement))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_MySql_UserQuery
函数功能：查询用户相对应的值
 参数.一：lpszUserName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：要查询的指定用户
 参数.二：pSt_UserInfo
  In/Out：Out
  类型：数据结构指针
  可空：Y
  意思：如果为空NULL，那么将只判断此用户是否存在
返回值
  类型：逻辑型
  意思：是否查询成功
备注：
*********************************************************************/
bool CModuleDatabase_MySql::ModuleDatabase_MySql_UserQuery(LPCXSTR lpszUserName, XENGINE_PROTOCOL_USERINFO* pSt_UserInfo)
{
	DBModule_IsErrorOccur = false;
	//查询
	XNETHANDLE xhTable = 0;
	__int64u nColumn = 0;
	__int64u nRow = 0;

	XCHAR tszSQLStatement[1024] = {};    //SQL语句

	_xstprintf(tszSQLStatement, _X("SELECT * FROM `Authorize_UserInfo` WHERE UserName = '%s'"), lpszUserName);

	if (!DataBase_MySQL_ExecuteQuery(xhSQL, &xhTable, tszSQLStatement, &nRow, &nColumn))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	if (nRow <= 0)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_MODULE_DATABASE_NOTFOUND;
		return false;
	}
	XCHAR** pptszResult = DataBase_MySQL_GetResult(xhSQL, xhTable);

	if (NULL != pSt_UserInfo)
	{
		memset(pSt_UserInfo, '\0', sizeof(XENGINE_PROTOCOL_USERINFO));
		//ID
		int nFliedValue = 0;
		//用户名
		nFliedValue++;
		if (NULL != pptszResult[nFliedValue])
		{
			_tcsxcpy(pSt_UserInfo->tszUserName, pptszResult[nFliedValue]);
		}
		//密码
		nFliedValue++;
		if (NULL != pptszResult[nFliedValue])
		{
			_tcsxcpy(pSt_UserInfo->tszUserPass, pptszResult[nFliedValue]);
		}
		//电子邮件
		nFliedValue++;
		if (NULL != pptszResult[nFliedValue])
		{
			_tcsxcpy(pSt_UserInfo->tszEMailAddr, pptszResult[nFliedValue]);
		}
		//QQ号
		nFliedValue++;
		if (NULL != pptszResult[nFliedValue])
		{
			pSt_UserInfo->nPhoneNumber = _ttxoll(pptszResult[nFliedValue]);
		}
		//身份证ID
		nFliedValue++;
		if (NULL != pptszResult[nFliedValue])
		{
			pSt_UserInfo->nIDNumber = _ttxoll(pptszResult[nFliedValue]);
		}
		//用户级别 -1表示封禁
		nFliedValue++;
		if (NULL != pptszResult[nFliedValue])
		{
			pSt_UserInfo->nUserLevel = _ttxoi(pptszResult[nFliedValue]);
		}
		//登录日期
		nFliedValue++;
		if (NULL != pptszResult[nFliedValue] && _tcsxlen(pptszResult[nFliedValue]) > 0)
		{
			_tcsxcpy(pSt_UserInfo->tszLoginTime, pptszResult[nFliedValue]);
		}
		//注册日期
		nFliedValue++;
		if (NULL != pptszResult[nFliedValue])
		{
			_tcsxcpy(pSt_UserInfo->tszCreateTime, pptszResult[nFliedValue]);
		}
	}
	DataBase_MySQL_FreeResult(xhSQL, xhTable);
	return true;
}