[中文](README.md) ||  [English](README.en.md)  
# XEngine_ServiceFramework
只要仓库不是在暂停状态,那么就会有人一直维护和开发,请放心使用  

## 介绍
c c++网络后台服务器开发框架 
c c++ network backend server development framework  
这是基于XEngine的一个开发框架代码.这套代码使用最基础的代码演示了如何编写一个后台服务器  
你们可以直接在这套代码的基础之上编写自己的后台服务器  
代码拥有详细的注释,你可以非常方便的了解它是如何运作的    

## 软件特性
支持以下技术示例  
1. 支持私有协议通信
2. 支持HTTP协议通信
3. 支持HTTP2协议
4. 支持WEBSOCKET协议
5. 简单服务器
6. 支持任务池
7. 支持线程池处理任务
8. 支持日志管理

## 安装教程

#### XEngine环境
必须安装XEngine,版本需要V9或者以上版本,安装XEngine可以参考其Readme文档  
GITEE:https://gitee.com/libxengine/libxengine  
GITHUB:https://github.com/libxengine/libxengine

###### 快速部署
git clone https://gitee.com/libxengine/libxengine.git 或者 git clone https://github.com/libxengine/libxengine.git  
window执行XEngine_WINEnv.bat 脚本.  
Linux执行:sudo ./XEngine_LINEnv.sh -i 3  
macos执行:./XEngine_LINEnv.sh -i 3  

#### sub module
由于依赖的子模块,在你checkout仓库后,在仓库目录下执行下面的命令拉取子模块  
git submodule init  
git submodule update  
如果github访问失败,你也可以clone该项目,在主目录下使用命令:git clone https://gitee.com/xengine/XEngine_OPenSource.git XEngine_Source/XEngine_DependLibrary

#### Windows
使用VS打开并且编译,支持WINDOWS 7SP1以上系统  
直接运行即可

#### Linux
Linux使用Makefile编译,UBUNTU22.04或者RockyLinux9以及以上系统  
在控制台运行

###### 编译命令
在XEngine_Source目录下执行命令  
make RELEASE=0 调试编译  
make RELEASE=1 发布编译  
make FLAGS=InstallAll 安装库程序  
make FLAGS=CleanAll 清理编译  

#### Macos
使用makefile编译,控制台运行,需要mac 13以及以上版本  
在控制台运行,编译命令参考linux

## 如何开发
XEngine_CenterApp 服务主要是用于TCP协议,可在这里面编写你的业务服务相关处理代码  
XEngine_HttpApp 服务主要用于HTTP协议,可在这里编写你的HTTP操作相关处理代码  
XEngine_Http2App 服务主要用于HTTP2协议,可在这里编写你的HTTP2操作相关处理代码  
XEngine_WebSocketApp 服务主要用于WEBSOCKET协议,可在这里编写你的WEBSOCKET操作相关处理代码  
XEngine_SimpleApp 最少代码演示一个TCP和UDP服务器  

#### 视频教程
你也可以观看视频教程来了解我们的代码框架情况:https://www.bilibili.com/video/BV1Hv421y7g9

## 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request 

## 关注我们
如果你觉得这个软件对你有帮助,请你给我们一个START吧

## 提交问题

如果你有问题,可以在issues中提交