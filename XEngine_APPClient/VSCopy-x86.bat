copy /y "%XEngine_Lib32%\XEngine_BaseLib\XEngine_BaseLib.dll" "./"
copy /y "%XEngine_Lib32%\XEngine_BaseLib\XEngine_Algorithm.dll" "./"
copy /y "%XEngine_Lib32%\XEngine_Core\XEngine_ManagePool.dll" "./"
copy /y "%XEngine_Lib32%\XEngine_Client\XClient_Socket.dll" "./"
::Websocket,http need this module
copy /y "%XEngine_Lib32%\XEngine_Core\XEngine_OPenSsl.dll" "./"
::center need this module
copy /y "%XEngine_Lib32%\XEngine_HelpComponents\HelpComponents_Packets.dll" "./"
::websocket need this module
copy /y "%XEngine_Lib32%\XEngine_RfcComponents\RfcComponents_WSProtocol.dll" "./"