#pragma once
/********************************************************************
//    Created:     2022/03/01  09:12:45
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleDatabase\ModuleDB_Define.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleDatabase
//    File Base:   ModuleDB_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     数据库操作导出定义
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleDB_GetLastError(int *pInt_SysError = NULL);
/************************************************************************/
/*                         导出的SQLITE操作函数                         */
/************************************************************************/
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
extern "C" bool ModuleDatabase_SQlite_Init(LPCXSTR lpszSQLFile);
/********************************************************************
函数名称：ModuleDatabase_SQlite_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_SQlite_Destory();
/********************************************************************
函数名称：ModuleDatabase_SQLite_UserRegister
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
extern "C" bool ModuleDatabase_SQLite_UserRegister(XENGINE_PROTOCOL_USERINFO* pSt_UserInfo);
/********************************************************************
函数名称：ModuleDatabase_SQLite_UserQuery
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
extern "C" bool ModuleDatabase_SQLite_UserQuery(LPCXSTR lpszUserName, XENGINE_PROTOCOL_USERINFO* pSt_UserInfo = NULL);
/************************************************************************/
/*                         导出的MYSQL操作函数                          */
/************************************************************************/
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
extern "C" bool ModuleDatabase_MySql_Init(DATABASE_MYSQL_CONNECTINFO* pSt_MySQLConnector);
/********************************************************************
函数名称：ModuleDatabase_MySql_Destory
函数功能：销毁MYSQL数据库资源链接
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_MySql_Destory();
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
extern "C" bool ModuleDatabase_MySql_UserRegister(XENGINE_PROTOCOL_USERINFO* pSt_UserInfo);
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
extern "C" bool ModuleDatabase_MySql_UserQuery(LPCXSTR lpszUserName, XENGINE_PROTOCOL_USERINFO* pSt_UserInfo = NULL);