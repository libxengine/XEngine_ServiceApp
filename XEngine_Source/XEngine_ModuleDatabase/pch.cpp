#include "pch.h"
#include "ModuleDatabase_SQlite/ModuleDatabase_SQlite.h"
#include "ModuleDatabase_MySql/ModuleDatabase_MySql.h"
/********************************************************************
//    Created:     2022/03/01  09:17:08
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleDatabase\pch.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleDatabase
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出函数实现
//    History:
*********************************************************************/
bool DBModule_IsErrorOccur = false;
XLONG DBModule_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModuleDatabase_SQlite m_DBSQlite;
CModuleDatabase_MySql m_DBMysql;
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleDB_GetLastError(int* pInt_SysError)
{
	if (NULL != pInt_SysError)
	{
		*pInt_SysError = errno;
	}
	return DBModule_dwErrorCode;
}
/************************************************************************/
/*                         导出的SQLITE操作函数                         */
/************************************************************************/
extern "C" bool ModuleDatabase_SQlite_Init(LPCXSTR lpszSQLFile)
{
	return m_DBSQlite.ModuleDatabase_SQlite_Init(lpszSQLFile);
}
extern "C" bool ModuleDatabase_SQlite_Destory()
{
	return m_DBSQlite.ModuleDatabase_SQlite_Destory();
}
extern "C" bool ModuleDatabase_SQLite_UserRegister(XENGINE_PROTOCOL_USERINFO* pSt_UserInfo)
{
	return m_DBSQlite.ModuleDatabase_SQLite_UserRegister(pSt_UserInfo);
}
extern "C" bool ModuleDatabase_SQLite_UserQuery(LPCXSTR lpszUserName, XENGINE_PROTOCOL_USERINFO* pSt_UserInfo)
{
	return m_DBSQlite.ModuleDatabase_SQLite_UserQuery(lpszUserName, pSt_UserInfo);
}
/************************************************************************/
/*                         导出的MYSQL操作函数                          */
/************************************************************************/
extern "C" bool ModuleDatabase_MySql_Init(DATABASE_MYSQL_CONNECTINFO * pSt_MySQLConnector)
{
	return m_DBMysql.ModuleDatabase_MySql_Init(pSt_MySQLConnector);
}
extern "C" bool ModuleDatabase_MySql_Destory()
{
	return m_DBMysql.ModuleDatabase_MySql_Destory();
}
extern "C" bool ModuleDatabase_MySql_UserRegister(XENGINE_PROTOCOL_USERINFO* pSt_UserInfo)
{
	return m_DBMysql.ModuleDatabase_MySql_UserRegister(pSt_UserInfo);
}
extern "C" bool ModuleDatabase_MySql_UserQuery(LPCXSTR lpszUserName, XENGINE_PROTOCOL_USERINFO* pSt_UserInfo)
{
	return m_DBMysql.ModuleDatabase_MySql_UserQuery(lpszUserName, pSt_UserInfo);
}