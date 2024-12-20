[中文](README.md) ||  [English](README.en.md)  
# XEngine_ServiceFramework
As long as the repository is not in suspended state, we will maintain and develop it all the time, please use it with confidence  

## Introduction
c c++网络后台服务器开发框架 
c c++ network backend server development framework  
It is a development framework code based on XEngine. This set of code uses the most basic code to demonstrate how to write a back-end server  
You can write your own backend server directly on the basis of this code  
The code has detailed comments, so you can easily understand how it works  

## Software feature
support feature list:  
1. use standard private protocol to handle network communication
2. Support http protocol
3. support http2 protocol
4. support websocket protocol
5. simple service
6. Support task pool
7. Support thread pool processing tasks
8. Support Log Management

## install

#### XEngine Evn
you must install XEngine,need V9 or above,install XEngine can be refer to xengine Readme docment  
GITEE:https://gitee.com/libxengine/libxengine  
GITHUB:https://github.com/libxengine/libxengine

##### fast to deployment 
git clone https://gitee.com/libxengine/libxengine.git or git clone https://github.com/libxengine/libxengine.git  
window Exection XEngine_WINEnv.bat   
Linux Exection:sudo ./XEngine_LINEnv.sh -i 3  
Macos Exection:./XEngine_LINEnv.sh -i 3

#### sub module
Due to the dependent sub-modules, after you checkout the warehouse, execute the following command in the warehouse directory to pull the sub-modules  
git submodule init  
git submodule update  

#### Windows
use vs open and compile,suport windows 7sp1 and above  
Just Run it

#### Linux
use makefile compile,UBUNTU22.04 x64 or RockyLinux9 x64  
Run it on the terminal

#### Macos
use makefile compile,mac 13 and above  
Run it on the terminal

##### Screenshot of the program
execute command in XEngine_Source path   
make complie  
make FLAGS=InstallAll Install File  
make FLAGS=CleanAll Clear Complie  

## How to develop
XEngine_CenterApp service is mainly used for TCP protocol, you can write your TCP(Business) operation related processing code here  
XEngine_HttpApp service is mainly used for HTTP protocol, you can write your HTTP operation related processing code here  
XEngine_Http2App service is mainly used for HTTP2 protocol, you can write your HTTP2 operation related processing code here  
XEngine_WebSocketApp service is mainly used for Websocket protocol, you can write your Websocket operation related processing code here  
XEngine_SimpleApp minimal code demonstrates a TCP and UDP server  

## Participate in contribution

1.  Fork this code
2.  Create new Feat_xxx branch
3.  Submit the code
4.  New Pull Request

## Follow us
If you think this software is helpful to you, please give us a START

## post issues

if you have eny quest.post issues...