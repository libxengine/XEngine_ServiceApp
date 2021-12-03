#include "XEngine_Hdr.h"

BOOL bIsRun = FALSE;
XLOG xhLog = NULL;
//TCP服务器
XNETHANDLE xhTCPSocket = 0;
XNETHANDLE xhTCPHeart = 0;
XNETHANDLE xhTCPPool = 0;
XHANDLE xhTCPPacket = NULL;
//HTTP服务器
XNETHANDLE xhHTTPSocket = 0;
XNETHANDLE xhHTTPHeart = 0;
XNETHANDLE xhHTTPPool = 0;
XHANDLE xhHTTPPacket = NULL;
//配置文件
XENGINE_SERVICECONFIG st_ServiceConfig;

void ServiceApp_Stop(int signo)
{
	if (bIsRun)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("服务器退出..."));
		bIsRun = FALSE;
		//销毁TCP资源
		NetCore_TCPXCore_DestroyEx(xhTCPSocket);
		SocketOpt_HeartBeat_DestoryEx(xhTCPHeart);
		HelpComponents_Datas_Destory(xhTCPPacket);
		ManagePool_Thread_NQDestroy(xhTCPPool);
		//销毁HTTP资源
		NetCore_TCPXCore_DestroyEx(xhHTTPSocket);
		SocketOpt_HeartBeat_DestoryEx(xhHTTPHeart);
		RfcComponents_HttpServer_DestroyEx(xhHTTPPacket);
		ManagePool_Thread_NQDestroy(xhHTTPPool);
		//销毁日志资源
		HelpComponents_XLog_Destroy(xhLog);
	}
#ifdef _WINDOWS
	WSACleanup();
#endif
	exit(0);
}
//LINUX守护进程
static int ServiceApp_Deamon()
{
#ifndef _WINDOWS
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
#ifdef _WINDOWS
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	bIsRun = TRUE;
	LPCTSTR lpszHTTPMime = _T("./XEngine_Config/HttpMime.types");
	LPCTSTR lpszHTTPCode = _T("./XEngine_Config/HttpCode.types");
	LPCTSTR lpszLogFile = _T("./XEngine_Log/XEngine_MQServiceApp.Log");
	HELPCOMPONENTS_XLOG_CONFIGURE st_XLogConfig;
	THREADPOOL_PARAMENT** ppSt_ListTCPParam;
	THREADPOOL_PARAMENT** ppSt_ListHTTPParam;

	memset(&st_XLogConfig, '\0', sizeof(HELPCOMPONENTS_XLOG_CONFIGURE));
	memset(&st_ServiceConfig, '\0', sizeof(XENGINE_SERVICECONFIG));

	st_XLogConfig.XLog_MaxBackupFile = 10;
	st_XLogConfig.XLog_MaxSize = 1024000;
	_tcscpy(st_XLogConfig.tszFileName, lpszLogFile);

	signal(SIGINT, ServiceApp_Stop);
	signal(SIGTERM, ServiceApp_Stop);
	signal(SIGABRT, ServiceApp_Stop);
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
	//启动TCP服务相关代码
	if (st_ServiceConfig.nTCPPort > 0)
	{
		//组包器
		xhTCPPacket = HelpComponents_Datas_Init(st_ServiceConfig.st_XMax.nMaxQueue, 0, st_ServiceConfig.st_XMax.nTCPThread);
		if (NULL == xhTCPPacket)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("启动服务中,初始化TCP组包器失败,错误：%lX"), Packets_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,启动TCP组包器成功"));
		//启动心跳
		if (st_ServiceConfig.st_XTime.nTCPTimeOut > 0)
		{
			if (!SocketOpt_HeartBeat_InitEx(&xhTCPHeart, st_ServiceConfig.st_XTime.nTCPTimeOut, st_ServiceConfig.st_XTime.nTimeCheck, Network_Callback_TCPHeart))
			{
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("启动服务中,初始化TCP心跳服务失败,错误：%lX"), NetCore_GetLastError());
				goto XENGINE_SERVICEAPP_EXIT;
			}
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,初始化TCP心跳服务成功,句柄:%llu,时间:%d,次数:%d"), xhTCPHeart, st_ServiceConfig.st_XTime.nTCPTimeOut, st_ServiceConfig.st_XTime.nTimeCheck);
		}
		else
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("启动服务中,TCP心跳服务被设置为不启用"));
		}
		//启动网络
		if (!NetCore_TCPXCore_StartEx(&xhTCPSocket, st_ServiceConfig.nTCPPort, st_ServiceConfig.st_XMax.nMaxClient, st_ServiceConfig.st_XMax.nIOThread))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("启动服务中,启动TCP网络服务器失败,错误：%lX"), NetCore_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,启动TCP网络服务器成功,TCP端口:%d,网络IO线程个数:%d"), st_ServiceConfig.nTCPPort, st_ServiceConfig.st_XMax.nIOThread);
		//绑定网络事件
		NetCore_TCPXCore_RegisterCallBackEx(xhTCPSocket, Network_Callback_TCPLogin, Network_Callback_TCPRecv, Network_Callback_TCPLeave);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,注册TCP网络事件成功"));
		//启动任务池
		BaseLib_OperatorMemory_Malloc((XPPPMEM)&ppSt_ListTCPParam, st_ServiceConfig.st_XMax.nTCPThread, sizeof(THREADPOOL_PARAMENT));
		for (int i = 0; i < st_ServiceConfig.st_XMax.nTCPThread; i++)
		{
			int* pInt_Pos = new int;

			*pInt_Pos = i;
			ppSt_ListTCPParam[i]->lParam = pInt_Pos;
			ppSt_ListTCPParam[i]->fpCall_ThreadsTask = XEngine_TCPTask_Thread;
		}
		if (!ManagePool_Thread_NQCreate(&xhTCPPool, &ppSt_ListTCPParam, st_ServiceConfig.st_XMax.nTCPThread))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("启动服务中,启动TCP线程池服务失败,错误：%lX"), ManagePool_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,启动TCP线程池服务成功,启动个数:%d"), st_ServiceConfig.st_XMax.nTCPThread);
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("启动服务中,TCP消息服务没有被启用"));
	}
	//启动HTTP服务相关代码
	if (st_ServiceConfig.nHttpPort > 0)
	{
		//HTTP包处理器
		xhHTTPPacket = RfcComponents_HttpServer_InitEx(lpszHTTPCode, lpszHTTPMime, st_ServiceConfig.st_XMax.nHTTPThread);
		if (NULL == xhHTTPPacket)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("启动服务中,初始化HTTP组包失败,错误：%lX"), HttpServer_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,初始化HTTP组包成功,IO线程个数:%d"), st_ServiceConfig.st_XMax.nHTTPThread);
		//启动心跳
		if (st_ServiceConfig.st_XTime.nHTTPTimeOut > 0)
		{
			if (!SocketOpt_HeartBeat_InitEx(&xhHTTPHeart, st_ServiceConfig.st_XTime.nHTTPTimeOut, st_ServiceConfig.st_XTime.nTimeCheck, Network_Callback_HTTPHeart))
			{
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("启动服务中,初始化HTTP心跳服务失败,错误：%lX"), NetCore_GetLastError());
				goto XENGINE_SERVICEAPP_EXIT;
			}
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,初始化HTTP心跳服务成功,句柄:%llu,时间:%d,次数:%d"), xhHTTPHeart, st_ServiceConfig.st_XTime.nHTTPTimeOut, st_ServiceConfig.st_XTime.nTimeCheck);
		}
		else
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("启动服务中,HTTP心跳服务被设置为不启用"));
		}
		//网络
		if (!NetCore_TCPXCore_StartEx(&xhHTTPSocket, st_ServiceConfig.nHttpPort, st_ServiceConfig.st_XMax.nMaxClient, st_ServiceConfig.st_XMax.nIOThread))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("启动服务中,启动HTTP网络服务器失败,错误：%lX"), NetCore_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,启动HTTP网络服务器成功,HTTP端口:%d,IO:%d"), st_ServiceConfig.nHttpPort, st_ServiceConfig.st_XMax.nIOThread);
		NetCore_TCPXCore_RegisterCallBackEx(xhHTTPSocket, Network_Callback_HTTPLogin, Network_Callback_HTTPRecv, Network_Callback_HTTPLeave);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,注册HTTP网络事件成功"));
		//HTTP任务池
		BaseLib_OperatorMemory_Malloc((XPPPMEM)&ppSt_ListHTTPParam, st_ServiceConfig.st_XMax.nHTTPThread, sizeof(THREADPOOL_PARAMENT));
		for (int i = 0; i < st_ServiceConfig.st_XMax.nHTTPThread; i++)
		{
			int* pInt_Pos = new int;

			*pInt_Pos = i;
			ppSt_ListHTTPParam[i]->lParam = pInt_Pos;
			ppSt_ListHTTPParam[i]->fpCall_ThreadsTask = XEngine_HTTPTask_Thread;
		}
		if (!ManagePool_Thread_NQCreate(&xhHTTPPool, &ppSt_ListHTTPParam, st_ServiceConfig.st_XMax.nHTTPThread))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("启动服务中,启动HTTP线程池服务失败,错误：%lX"), ManagePool_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中,启动HTTP线程池服务成功,启动个数:%d"), st_ServiceConfig.st_XMax.nHTTPThread);
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("启动服务中,HTTP消息服务没有被启用"));
	}

	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("所有服务成功启动,服务运行中。。。"));
	while (bIsRun)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
XENGINE_SERVICEAPP_EXIT:
	if (bIsRun)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("有服务启动失败,服务器退出..."));
		bIsRun = FALSE;
		//销毁TCP资源
		NetCore_TCPXCore_DestroyEx(xhTCPSocket);
		SocketOpt_HeartBeat_DestoryEx(xhTCPHeart);
		HelpComponents_Datas_Destory(xhTCPPacket);
		ManagePool_Thread_NQDestroy(xhTCPPool);
		//销毁HTTP资源
		NetCore_TCPXCore_DestroyEx(xhHTTPSocket);
		SocketOpt_HeartBeat_DestoryEx(xhHTTPHeart);
		RfcComponents_HttpServer_DestroyEx(xhHTTPPacket);
		ManagePool_Thread_NQDestroy(xhHTTPPool);
		//销毁日志资源
		HelpComponents_XLog_Destroy(xhLog);
	}
#ifdef _WINDOWS
	WSACleanup();
#endif
	return 0;
}
