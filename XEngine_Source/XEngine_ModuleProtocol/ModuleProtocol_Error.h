#pragma once
/********************************************************************
//    Created:     2022/03/01  09:27:20
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Error.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleProtocol
//    File Base:   ModuleProtocol_Error
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出协议模块错误
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                        导出的打包协议错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_MODULE_PROTOCOL_PACKET_PARAMENT 0xB0001                     //打包错误,参数错误
//////////////////////////////////////////////////////////////////////////
//                        导出的解析协议错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_MODULE_PROTOCOL_PARSE_PARAMENT 0xB1001                     //解析错误,参数错误
#define ERROR_MODULE_PROTOCOL_PARSE_JSON 0xB1002                         //解析JSON数据失败