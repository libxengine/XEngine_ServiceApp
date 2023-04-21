#include "pch.h"
#include "ModuleDatabase_SQlite.h"
/********************************************************************
//    Created:     2022/03/01  09:20:06
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_SQlite\ModuleDatabase_SQlite.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_SQlite
//    File Base:   ModuleDatabase_SQlite
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     SQLITE操作类
//    History:
*********************************************************************/
CModuleDatabase_SQlite::CModuleDatabase_SQlite()
{
}
CModuleDatabase_SQlite::~CModuleDatabase_SQlite()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleDatabase_SQlite_Init
函数功能：初始化SQLITE文件系统
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
bool CModuleDatabase_SQlite::ModuleDatabase_SQlite_Init(LPCXSTR lpszSQLFile)
{
	DBModule_IsErrorOccur = false;
	//打开数据库
	if (!DataBase_SQLite_Open(&xhSQL, lpszSQLFile))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_SQlite_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_SQlite::ModuleDatabase_SQlite_Destory()
{
	DBModule_IsErrorOccur = false;

	DataBase_SQLite_Close(xhSQL);
	return true;
}