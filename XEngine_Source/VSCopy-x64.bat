copy /y "%XEngine_Lib64%\XEngine_BaseLib\XEngine_BaseLib.dll" "./"
copy /y "%XEngine_Lib64%\XEngine_BaseLib\XEngine_Algorithm.dll" "./"
copy /y "%XEngine_Lib64%\XEngine_Core\XEngine_Core.dll" "./"
copy /y "%XEngine_Lib64%\XEngine_Core\XEngine_ManagePool.dll" "./"
::Websocket,http need this module
copy /y "%XEngine_Lib64%\XEngine_Core\XEngine_OPenSsl.dll" "./"
::Websocket,http need this module
copy /y "%XEngine_Lib64%\XEngine_SystemSdk\XEngine_SystemApi.dll" "./"

copy /y "%XEngine_Lib64%\XEngine_HelpComponents\HelpComponents_Packets.dll" "./"
copy /y "%XEngine_Lib64%\XEngine_HelpComponents\HelpComponents_XLog.dll" "./"
copy /y "%XEngine_Lib64%\XEngine_HelpComponents\HelpComponents_DataBase.dll" "./"
::http need this module
copy /y "%XEngine_Lib64%\XEngine_RfcComponents\RfcComponents_HttpProtocol.dll" "./"
::websocket need this module
copy /y "%XEngine_Lib64%\XEngine_RfcComponents\RfcComponents_WSProtocol.dll" "./"