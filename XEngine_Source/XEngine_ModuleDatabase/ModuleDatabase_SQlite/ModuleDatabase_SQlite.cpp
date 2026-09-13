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
bool CModuleDatabase_SQlite::ModuleDatabase_SQLite_UserRegister(XENGINE_PROTOCOL_USERINFO* pSt_UserInfo)
{
    DBModule_IsErrorOccur = false;

    XCHAR tszSQLStatement[1024] = {};

    if (ModuleDatabase_SQLite_UserQuery(pSt_UserInfo->tszUserName))
    {
        DBModule_IsErrorOccur = true;
        DBModule_dwErrorCode = ERROR_MODULE_DATABASE_EXIST;
        return false;
    }
    _xstprintf(tszSQLStatement, _X("INSERT INTO Authorize_UserInfo(UserName, Password, EmailAddr, PhoneNumber, IDCard, nUserLevel, CreateTime) values('%s','%s','%s',%lld,%lld,%d,datetime('now', 'localtime'))"), pSt_UserInfo->tszUserName, pSt_UserInfo->tszUserPass, pSt_UserInfo->tszEMailAddr, pSt_UserInfo->nPhoneNumber, pSt_UserInfo->nIDNumber, pSt_UserInfo->nUserLevel);
    if (!DataBase_SQLite_Exec(xhSQL, tszSQLStatement))
    {
        DBModule_IsErrorOccur = true;
        DBModule_dwErrorCode = DataBase_GetLastError();
        return false;
    }
    return true;
}
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
bool CModuleDatabase_SQlite::ModuleDatabase_SQLite_UserQuery(LPCXSTR lpszUserName, XENGINE_PROTOCOL_USERINFO* pSt_UserInfo /* = NULL */)
{
    DBModule_IsErrorOccur = false;

    int nRow = 0;
    int nColumn = 0;
    char** ppszResult = NULL;
    XCHAR tszSQLStatement[1024] = {};    //SQL语句
    
    _xstprintf(tszSQLStatement, _X("SELECT * FROM `Authorize_UserInfo` WHERE UserName = '%s'"), lpszUserName);
    //get table fields 
    if (!DataBase_SQLite_GetTable(xhSQL, tszSQLStatement, &ppszResult, &nRow, &nColumn))
    {
        DBModule_IsErrorOccur = true;
        DBModule_dwErrorCode = DataBase_GetLastError();
        return false;
    }
    //query if return 0
    if ((0 == nRow) || (0 == nColumn))
    {
        DBModule_IsErrorOccur = true;
        DBModule_dwErrorCode = ERROR_MODULE_DATABASE_NOTFOUND;
        return false;
    }
    //如果是NULL，表示不想知道结果
    if (NULL != pSt_UserInfo)
    {
        memset(pSt_UserInfo, '\0', sizeof(XENGINE_PROTOCOL_USERINFO));
        //ID
        int nFliedValue = nColumn;
        //用户名
        nFliedValue++;
        _tcsxcpy(pSt_UserInfo->tszUserName, ppszResult[nFliedValue]);
        //密码
        nFliedValue++;
        _tcsxcpy(pSt_UserInfo->tszUserPass, ppszResult[nFliedValue]);
        //电子邮件
        nFliedValue++;
        _tcsxcpy(pSt_UserInfo->tszEMailAddr, ppszResult[nFliedValue]);
        //电话
        nFliedValue++;
        pSt_UserInfo->nPhoneNumber = _ttxoll(ppszResult[nFliedValue]);
        //身份证ID
        nFliedValue++;
        pSt_UserInfo->nIDNumber = _ttxoll(ppszResult[nFliedValue]);
        //用户级别 -1表示封禁
        nFliedValue++;
        pSt_UserInfo->nUserLevel = _ttxoi(ppszResult[nFliedValue]);
        //登录日期
        nFliedValue++;
        if (NULL != ppszResult[nFliedValue] && _tcsxlen(ppszResult[nFliedValue]) > 0)
        {
            _tcsxcpy(pSt_UserInfo->tszLoginTime, ppszResult[nFliedValue]);
        }
        //注册日期
        nFliedValue++;
        _tcsxcpy(pSt_UserInfo->tszCreateTime, ppszResult[nFliedValue]);
    }
    DataBase_SQLite_FreeTable(ppszResult);
    return true;
}