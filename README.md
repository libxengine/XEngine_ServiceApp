# XEngine_ServiceFramework

## 介绍
c c++网络后台服务器开发框架 
c c++ network backend server development framework  
这是基于XEngine的一个开发框架代码.这套代码使用最基础的代码演示了如何编写一个后台服务器  
你们可以直接在这套代码的基础之上编写自己的后台服务器  
代码拥有详细的注释,你可以非常方便的了解它是如何运作的    

## 软件特性
支持以下技术  
1. 支持私有协议通信
2. 支持HTTP协议通信
3. 支持任务池
4. 支持线程池处理任务
5. 支持日志管理

## 安装教程

#### 版本需求
支持WINDOWS 7SP1和LINUX(UBUNT20.04,CENTOS8)以上系统  
XEngine版本需要V7.25或者以上版本    

## 编译

#### Windows
使用VS2019 x86或者x64打开并且编译 你需要按照下面的方式配置环境,不然你可能需要自己在项目中设置库目录

#### Linux
Linux使用Makefile编译  
UBUNTU20.04 x64或者CENTOS8 x64均可  

##### 编译命令
在XEngine_Source目录下执行命令  
make 编译  
make FLAGS=InstallAll 安装库程序  
make FLAGS=CleanAll 清理编译  

#### XEngine环境
安装XEngine可以参考其Readme文档  
GITEE:https://gitee.com/xyry/libxengine  
GITHUB:https://github.com/libxengine/xengine  

## 如何开发
XEngine_CenterApp 服务主要是用于TCP协议,可在这里面编写你的业务服务相关处理代码  
XEngine_HttpApp 服务主要用于HTTP协议,可在这里编写你的HTTP操作相关处理代码

## 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request 

## 关注我们
如果你觉得这个软件对你有帮助,请你给我们一个START吧

## 提交问题

如果你有问题,可以在issues中提交