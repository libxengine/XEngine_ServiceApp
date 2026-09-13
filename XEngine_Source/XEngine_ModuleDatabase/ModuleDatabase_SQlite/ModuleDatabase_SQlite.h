#pragma once
/********************************************************************
//    Created:     2022/03/01  09:20:01
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_SQlite\ModuleDatabase_SQlite.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_SQlite
//    File Base:   ModuleDatabase_SQlite
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     SQLITE操作类
//    History:
*********************************************************************/


class CModuleDatabase_SQlite
{
public:
	CModuleDatabase_SQlite();
	~CModuleDatabase_SQlite();
public:
	bool ModuleDatabase_SQlite_Init(LPCXSTR lpszSQLFile);
	bool ModuleDatabase_SQlite_Destory();
	bool ModuleDatabase_SQLite_UserRegister(XENGINE_PROTOCOL_USERINFO* pSt_UserInfo);               
	bool ModuleDatabase_SQLite_UserQuery(LPCXSTR lpszUserName, XENGINE_PROTOCOL_USERINFO* pSt_UserInfo = NULL);
private:
	XNETHANDLE xhSQL;
};