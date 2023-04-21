#pragma once
//加载系统头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <thread>
#include <list>
#include <string>
#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <arpa/inet.h>
#endif
using namespace std;
//加载XEngine头文件
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Core/NetCore_Define.h>
#include <XEngine_Include/XEngine_Core/NetCore_Error.h>
//加载项目相关头文件
#include "../../XEngine_UserProtocol.h"
//加载自己的头文件
#include "XEngine_Configure.h"
#include "XEngine_Network.h"
/********************************************************************
//    Created:     2022/12/30  09:52:40
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_SimpleApp\XEngine_Hdr.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_SimpleApp
//    File Base:   XEngine_Hdr
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     公用头文件
//    History:
*********************************************************************/
extern bool bIsRun;
//套接字句柄
extern XHANDLE xhTCPSocket;
extern XHANDLE xhUDPSocket;
//连接库
#ifdef _MSC_BUILD
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib.lib")
#pragma comment(lib,"XEngine_Core/XEngine_Core.lib")
#pragma comment(lib,"Ws2_32.lib")
#endif