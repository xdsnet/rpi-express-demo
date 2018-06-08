# localSvc
是rpi-express-demo中本地硬件支持部分。

## 目录结构
1. makefile:编译用文件
2. server.c: 服务程序，需要root运行以实现硬件控制

4. READMD.md: 本说明文件

## 编译与使用
1. 在本目录下执行`make`将在bin子目录下生成`rootServer`可执行文件。**注意**编译需要wiringPi库的支持，请提前安装好。
2. 使用root权限运行`./rootServer`，或者普通用户下以`sudo ./rootServer`运行。并保持运行，以实现服务。