#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2021/12/02  16:34:09
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_Configure.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp
//    File Base:   XEngine_Configure
//    File Ext:    cpp
//    Project:     XEngine(����ͨ������)
//    Author:      qyt
//    Purpose:     �����ļ���д����
//    History:
*********************************************************************/
BOOL XEngine_Configure_Parament(int argc, char** argv, XENGINE_SERVICECONFIG* pSt_Configure)
{
	LPCTSTR lpszConfigFile = _T("./XEngine_Config/XEngine_Config.json");

	if (!ModuleConfigure_Json_File(lpszConfigFile, pSt_Configure))
	{
		printf("���������ļ�ʧ��,ModuleConfigure_Json_File:%lX\n", ModuleConfigure_GetLastError());
		return FALSE;
	}

	for (int i = 0; i < argc; i++)
	{
		if ((0 == _tcscmp("-h", argv[i])) || (0 == _tcscmp("-H", argv[i])))
		{
			XEngine_Configure_Help();
			return FALSE;
		}
		else if (0 == _tcscmp("-TP", argv[i]))
		{
			pSt_Configure->nTCPPort = _ttoi(argv[i + 1]);
		}
		else if (0 == _tcscmp("-HP", argv[i]))
		{
			pSt_Configure->nHttpPort = _ttoi(argv[i + 1]);
		}
		else if (0 == _tcscmp("-d", argv[i]))
		{
			pSt_Configure->bDeamon = _ttoi(argv[i + 1]);
		}
	}

	return TRUE;
}

void XEngine_Configure_Help()
{
	printf(_T("--------------------------��������������ʼ--------------------------\n"));
	printf(_T("������Ϣ���з����������������� ���� ����ֵ�����������ִ�Сд�ġ������ָ���������Ĭ�ϵ�ini�����ļ�����Ĳ���\n"));
	printf(_T("-h or -H����������������ʾ��Ϣ\n"));
	printf(_T("-TP��������Ϣ����TCP����˿ں�\n"));
	printf(_T("-HP��������Ϣ����HTTP����˿ں�\n"));
	printf(_T("-d��1 �����ػ����̣�2������\n"));
	printf(_T("--------------------------����������������--------------------------\n"));
}
