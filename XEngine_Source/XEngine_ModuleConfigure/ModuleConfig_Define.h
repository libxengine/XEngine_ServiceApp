#pragma once
/********************************************************************
//    Created:     2021/12/02  16:09:03
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleConfigure\ModuleConfig_Define.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleConfigure
//    File Base:   ModuleConfig_Define
//    File Ext:    h
//    Project:     XEngine(����ͨ������)
//    Author:      qyt
//    Purpose:     ����ģ�鵼������
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                        ���������ݽṹ
//////////////////////////////////////////////////////////////////////////
typedef struct tag_XEngine_ServiceConfig
{
	TCHAR tszIPAddr[128];                     //����IP��ַ,������Ҫ����
	BOOL bDeamon;                             //�Ƿ����ػ���������,LINUX��Ч
	int nTCPPort;                             //TCP�˿�,<=0������
	int nHttpPort;                            //HTTP����˿�
	struct
	{
		int nMaxClient;                       //���ͻ��˸���
		int nMaxQueue;                        //�����и���
		int nIOThread;                        //����IO�߳���
		int nTCPThread;                       //TCP�������߳���
		int nHttpThread;                      //HTTP�������߳���
	}st_XMax;
	struct
	{
		int nTimeCheck;                       //������
		int nTCPTimeOut;                      //TCP��ʱʱ��
		int nHttpTimeOut;                     //HTTP��ʱʱ��
	}st_XTime;                                //����*ʱ��=��ʱ
	struct
	{
		int nMaxSize;                         //�����־��С
		int nMaxCount;                        //�����־����
		int nLogLeave;                        //��־�ȼ�
	}st_XLog;
}XENGINE_SERVICECONFIG;
//////////////////////////////////////////////////////////////////////////
//                        ������������
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD ModuleConfigure_GetLastError(int* pInt_ErrorCode = NULL);
/************************************************************************/
/*                        �ļ����ö�ȡ                                  */
/************************************************************************/
/********************************************************************
�������ƣ�ModuleConfigure_Json_File
�������ܣ���ȡJSON�����ļ�
 ����.һ��lpszConfigFile
  In/Out��In
  ���ͣ������ַ�ָ��
  �ɿգ�N
  ��˼������Ҫ��ȡ�������ļ�
 ����.����pSt_ServerConfig
  In/Out��Out
  ���ͣ����ݽṹָ��
  �ɿգ�N
  ��˼���������������Ϣ
����ֵ
  ���ͣ��߼���
  ��˼���Ƿ�ɹ�
��ע��
*********************************************************************/
extern "C" BOOL ModuleConfigure_Json_File(LPCTSTR lpszConfigFile, XENGINE_SERVICECONFIG* pSt_ServerConfig);