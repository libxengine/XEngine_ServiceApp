# XEngine_ServiceFramework

## Introduction
c c++网络后台服务器开发框架 
c c++ network backend server development framework  
It is a development framework code based on XEngine. This set of code uses the most basic code to demonstrate how to write a back-end server  
You can write your own backend server directly on the basis of this code  

## Software feature
support feature list:  
1. use standard private protocol to handle network communication
2. Support http protocol
3. Support task pool
4. Support thread pool processing tasks
5. Support Log Management

## install

#### Requirements
support system above windows 7sp1 and linux(ubuntu20.04,centos8)  
XEngine need V7.25 or above  

## complie

#### Windows
use vs2019 x86(debug or release) x64(only release) open and complie  
You need to configure the environment in the following way, otherwise you may need to set the library directory in the project yourself  

#### Linux
Linux use Makefile complie  
UBUNTU20.04 x64 or CENTOS8 x64  

#### XEngine Env
install XEngine can be refer to xengine Readme docment
GITEE:https://gitee.com/xyry/libxengine
GITHUB:https://github.com/libxengine/xengine

##### Screenshot of the program
execute command in XEngine_Source path   
make complie  
make FLAGS=InstallAll Install File  
make FLAGS=CleanAll Clear Complie  

## test server
address:app.xyry.org or 159.75.200.173
port :tcp port 5300,websocket port 5301,Transmission verification password: no encryption

## Participate in contribution

1.  Fork this code
2.  Create new Feat_xxx branch
3.  Submit the code
4.  New Pull Request

## Follow us
If you think this software is helpful to you, please give us a START

## post issues

if you have eny quest.post issues...