#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2022/04/14  16:43:11
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HTTP2App\XEngine_HTTP2App.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HTTP2App
//    File Base:   XEngine_HTTP2App
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     主要入口函数
//    History:
*********************************************************************/
BOOL bIsRun = FALSE;
XLOG xhLog = NULL;
//HTTP2服务器
XHANDLE xhHTTP2Socket = NULL;
XHANDLE xhHTTP2Heart = NULL;
XHANDLE xhHTTP2Packet = NULL;
XHANDLE xhHTTP2Pool = NULL;
//配置文件
XENGINE_SERVICECONFIG st_ServiceConfig;

void ServiceApp_Stop(int signo)
{
	if (bIsRun)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("服务器退出..."));
		bIsRun = FALSE;
		//销毁HTTP资源
		NetCore_TCPXCore_DestroyEx(xhHTTP2Socket);
		SocketOpt_HeartBeat_DestoryEx(xhHTTP2Heart);
		RfcComponents_Http2Server_DestroyEx(xhHTTP2Packet);
		ManagePool_Thread_NQDestroy(xhHTTP2Pool);
		//销毁日志资源
		HelpComponents_XLog_Destroy(xhLog);
	}
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	exit(0);
}
//LINUX守护进程
static int ServiceApp_Deamon()
{
#ifndef _MSC_BUILD
	pid_t nPID = 0;
	int nStatus = 0;
	nPID = fork();
	if (nPID > 0)
	{
		exit(0);
	}

	close(2);
	while (1)
	{
		nPID = fork();
		if (nPID < 0)
		{
			exit(1);
		}
		if (nPID == 0)
		{
			return 0;
		}
		waitpid(nPID, &nStatus, 0);
		sleep(1);
	}
#endif
	return 0;
}

int main(int argc, char** argv)
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	bIsRun = TRUE;
	LPCTSTR lpszHTTPMime = _T("./XEngine_Config/HttpMime.types");
	LPCTSTR lpszLogFile = _T("./XEngine_Log/XEngine_Http2App.Log");
	HELPCOMPONENTS_XLOG_CONFIGURE st_XLogConfig;
	THREADPOOL_PARAMENT** ppSt_ListHTTPParam;

	memset(&st_XLogConfig, '\0', sizeof(HELPCOMPONENTS_XLOG_CONFIGURE));
	memset(&st_ServiceConfig, '\0', sizeof(XENGINE_SERVICECONFIG));

	st_XLogConfig.XLog_MaxBackupFile = 10;
	st_XLogConfig.XLog_MaxSize = 1024000;
	_tcscpy(st_XLogConfig.tszFileName, lpszLogFile);
	//初始化参数
	if (!XEngine_Configure_Parament(argc, argv, &st_ServiceConfig))
	{
		return -1;
	}
	//判断是否以守护进程启动
	if (st_ServiceConfig.bDeamon)
	{
		ServiceApp_Deamon();
	}
	//初始日志
	xhLog = HelpComponents_XLog_Init(HELPCOMPONENTS_XLOG_OUTTYPE_STD | HELPCOMPONENTS_XLOG_OUTTYPE_FILE, &st_XLogConfig);
	if (NULL == xhLog)
	{
		printf("启动服务中,启动日志失败,错误：%lX", XLog_GetLastError());
		goto XENGINE_SERVICEAPP_EXIT;
	}
	//设置日志打印级别
	HelpComponents_XLog_SetLogPriority(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,初始化日志系统成功"));

	signal(SIGINT, ServiceApp_Stop);
	signal(SIGTERM, ServiceApp_Stop);
	signal(SIGABRT, ServiceApp_Stop);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,初始化信号量成功"));
	//启动HTTP服务相关代码
	if (!RfcComponents_HttpConfig_InitMime(lpszHTTPMime, FALSE, FALSE))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("启动服务中,初始化HTTP2类型失败,错误：%lX"), HttpServer_GetLastError());
		goto XENGINE_SERVICEAPP_EXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,初始化HTTP2类型成功"));
	//HTTP2包处理器
	xhHTTP2Packet = RfcComponents_Http2Server_InitEx(st_ServiceConfig.st_XMax.nHTTP2Thread);
	if (NULL == xhHTTP2Packet)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("启动服务中,初始化HTTP2组包服务失败,错误：%lX"), HttpServer_GetLastError());
		goto XENGINE_SERVICEAPP_EXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,初始化HTTP2组包成功,IO线程个数:%d"), st_ServiceConfig.st_XMax.nHTTP2Thread);
	//启动心跳
	if (st_ServiceConfig.st_XTime.nHTTP2TimeOut > 0)
	{
		xhHTTP2Heart = SocketOpt_HeartBeat_InitEx(st_ServiceConfig.st_XTime.nHTTP2TimeOut, st_ServiceConfig.st_XTime.nTimeCheck, Network_Callback_HTTPHeart);
		if (NULL == xhHTTP2Heart)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("启动服务中,初始化HTTP2心跳服务失败,错误：%lX"), NetCore_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,初始化HTTP2心跳服务成功,时间:%d,次数:%d"), st_ServiceConfig.st_XTime.nHTTP2TimeOut, st_ServiceConfig.st_XTime.nTimeCheck);
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("启动服务中,HTTP2心跳服务被设置为不启用"));
	}
	//网络
	xhHTTP2Socket = NetCore_TCPXCore_StartEx(st_ServiceConfig.nHttp2Port, st_ServiceConfig.st_XMax.nMaxClient, st_ServiceConfig.st_XMax.nIOThread);
	if (NULL == xhHTTP2Socket)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("启动服务中,启动HTTP2网络服务器失败,错误：%lX"), NetCore_GetLastError());
		goto XENGINE_SERVICEAPP_EXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,启动HTTP2网络服务器成功,HTTP2端口:%d,IO:%d"), st_ServiceConfig.nHttp2Port, st_ServiceConfig.st_XMax.nIOThread);
	NetCore_TCPXCore_RegisterCallBackEx(xhHTTP2Socket, Network_Callback_HTTPLogin, Network_Callback_HTTPRecv, Network_Callback_HTTPLeave);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,注册HTTP2网络事件成功"));
	//HTTP任务池
	BaseLib_OperatorMemory_Malloc((XPPPMEM)&ppSt_ListHTTPParam, st_ServiceConfig.st_XMax.nHTTP2Thread, sizeof(THREADPOOL_PARAMENT));
	for (int i = 0; i < st_ServiceConfig.st_XMax.nHTTP2Thread; i++)
	{
		int* pInt_Pos = new int;

		*pInt_Pos = i;
		ppSt_ListHTTPParam[i]->lParam = pInt_Pos;
		ppSt_ListHTTPParam[i]->fpCall_ThreadsTask = XEngine_HTTP2Task_Thread;
	}
	xhHTTP2Pool = ManagePool_Thread_NQCreate(&ppSt_ListHTTPParam, st_ServiceConfig.st_XMax.nHTTP2Thread);
	if (NULL == xhHTTP2Pool)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("启动服务中,启动HTTP2线程池服务失败,错误：%lX"), ManagePool_GetLastError());
		goto XENGINE_SERVICEAPP_EXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,启动HTTP2线程池服务成功,启动个数:%d"), st_ServiceConfig.st_XMax.nHTTP2Thread);

	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("所有服务成功启动,服务运行中,XEngine版本:%s,服务版本:%s,发行次数;%d。。。"), XENGINE_VERSION_STR, st_ServiceConfig.st_XVer.pStl_ListVer->front().c_str(), st_ServiceConfig.st_XVer.pStl_ListVer->size());
	while (TRUE)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
XENGINE_SERVICEAPP_EXIT:
	if (bIsRun)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("有服务启动失败,服务器退出..."));
		bIsRun = FALSE;
		//销毁HTTP资源
		NetCore_TCPXCore_DestroyEx(xhHTTP2Socket);
		SocketOpt_HeartBeat_DestoryEx(xhHTTP2Heart);
		RfcComponents_Http2Server_DestroyEx(xhHTTP2Packet);
		ManagePool_Thread_NQDestroy(xhHTTP2Pool);
		//销毁日志资源
		HelpComponents_XLog_Destroy(xhLog);
	}
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}