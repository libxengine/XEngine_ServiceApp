#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2022/04/15  14:22:19
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_WebSocketApp\XEngine_Configure.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_WebSocketApp
//    File Base:   XEngine_Configure
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     配置文件操作代码
//    History:
*********************************************************************/
bool XEngine_Configure_Parament(int argc, char** argv, XENGINE_SERVICECONFIG* pSt_Configure)
{
	LPCXSTR lpszConfigFile = _X("./XEngine_Config/XEngine_WSConfig.json");
	LPCXSTR lpszVersionFile = _X("./XEngine_Config/XEngine_VersionList.json");
	if (!ModuleConfigure_Json_File(lpszConfigFile, pSt_Configure))
	{
		printf("解析配置文件失败,ModuleConfigure_Json_File:%lX\n", ModuleConfigure_GetLastError());
		return false;
	}
	if (!ModuleConfigure_Json_Version(lpszVersionFile, pSt_Configure))
	{
		printf("解析版本配置失败,ModuleConfigure_Json_Version:%lX\n", ModuleConfigure_GetLastError());
		return false;
	}

	for (int i = 0; i < argc; i++)
	{
		if (0 == _tcsxicmp("-h", argv[i]))
		{
			XEngine_Configure_Help();
			return false;
		}
		else if (0 == _tcsxicmp("-d", argv[i]))
		{
			pSt_Configure->bDaemon = _ttxoi(argv[i + 1]);
		}
		else if (0 == _tcsxicmp("-t", argv[i]))
		{
			bIsTest = true;
		}
		else if (0 == _tcsxicmp("-l", argv[i]))
		{
			LPCXSTR lpszLogLevel = argv[++i];
			if (0 == _tcsxicmp("debug", lpszLogLevel))
			{
				pSt_Configure->st_XLog.nLogLeave = XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_DEBUG;
			}
			else if (0 == _tcsxicmp("detail", lpszLogLevel))
			{
				pSt_Configure->st_XLog.nLogLeave = XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_DETAIL;
			}
			else if (0 == _tcsxicmp("info", lpszLogLevel))
			{
				pSt_Configure->st_XLog.nLogLeave = XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO;
			}
		}
	}

	return true;
}

void XEngine_Configure_Help()
{
	printf(_X("--------------------------启动参数帮助开始--------------------------\n"));
	printf(_X("网络服务启动参数：程序 参数 参数值，参数是区分大小写的。如果不指定将会加载默认的配置文件里面的参数\n"));
	printf(_X("-h or -H：启动参数帮助提示信息\n"));
	printf(_X("-d：1 启用守护进程，2不启用\n"));
	printf(_X("--------------------------启动参数帮助结束--------------------------\n"));
}
