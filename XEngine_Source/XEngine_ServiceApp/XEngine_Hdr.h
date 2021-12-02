#pragma once
//����ϵͳͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <signal.h>
#include <errno.h>
#include <thread>
#ifdef _WINDOWS
#include <Windows.h>
#include <tchar.h>
#include <io.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#endif
using namespace std;
//����XEngineͷ�ļ�
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Core/NetCore_Define.h>
#include <XEngine_Include/XEngine_Core/NetCore_Error.h>
#include <XEngine_Include/XEngine_Core/ManagePool_Define.h>
#include <XEngine_Include/XEngine_Core/ManagePool_Error.h>
#include <XEngine_Include/XEngine_HelpComponents/XLog_Define.h>
#include <XEngine_Include/XEngine_HelpComponents/XLog_Error.h>
#include <XEngine_Include/XEngine_HelpComponents/Packets_Define.h>
#include <XEngine_Include/XEngine_HelpComponents/Packets_Error.h>
#include <XEngine_Include/XEngine_RfcComponents/HttpServer_Define.h>
#include <XEngine_Include/XEngine_RfcComponents/HttpServer_Error.h>
//������Ŀ���ͷ�ļ�
#include "../XEngine_ModuleConfigure/ModuleConfig_Define.h"
#include "../XEngine_ModuleConfigure/ModuleConfig_Error.h"
//�����Լ���ͷ�ļ�
#include "XEngine_Configure.h"
#include "XEngine_Network.h"
#include "XEngine_TCPTask.h"
#include "XEngine_HTTPTask.h"
/********************************************************************
//    Created:     2021/12/02  16:34:41
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_Hdr.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp
//    File Base:   XEngine_Hdr
//    File Ext:    h
//    Project:     XEngine(����ͨ������)
//    Author:      qyt
//    Purpose:     ����ͷ�ļ�
//    History:
*********************************************************************/
extern BOOL bIsRun;
extern XLOG xhLog;
//TCP������
extern XNETHANDLE xhTCPSocket;
extern XNETHANDLE xhTCPHeart;
extern XNETHANDLE xhTCPPool;
extern XHANDLE xhTCPPacket;
//HTTP������
extern XNETHANDLE xhHTTPSocket;
extern XNETHANDLE xhHTTPHeart;
extern XNETHANDLE xhHTTPPool;
extern XHANDLE xhHTTPPacket;
//�����ļ�
extern XENGINE_SERVICECONFIG st_ServiceConfig;

//�������Ͷ���
#define XENGINE_CLIENT_NETTYPE_TCP 1
#define XENGINE_CLIENT_NETTYPE_HTTP 2


//���ӿ�
#ifdef _WINDOWS
#ifdef _WIN64
#pragma comment(lib,"../x64/Release/XEngine_ModuleConfigure.lib")
#else
#ifdef _DEBUG
#pragma comment(lib,"../Debug/XEngine_ModuleConfigure.lib")
#else
#pragma comment(lib,"../Release/XEngine_ModuleConfigure.lib")
#endif
#endif
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib.lib")
#pragma comment(lib,"XEngine_Core/XEngine_Core.lib")
#pragma comment(lib,"XEngine_Core/XEngine_ManagePool.lib")
#pragma comment(lib,"XEngine_HelpComponents/HelpComponents_XLog.lib")
#pragma comment(lib,"XEngine_HelpComponents/HelpComponents_Packets.lib")
#pragma comment(lib,"XEngine_RfcComponents/RfcComponents_HttpServer.lib")
#pragma comment(lib,"Ws2_32.lib")
#endif