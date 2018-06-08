# rpi-express-demo
一个树莓派上express远程监控硬件的demo

## 源起
因为树莓派升级后，nodejs相关访问gpio的模块不能及时得到更新，所以直接用nodejs开发远程硬件控制就变得比较麻烦，这里提出了利用本地服务间接提供可供nodejs调用的方法来解决这样问题的策略。本项目就是基于此的一个演示性实现。

## 目录结构
1. expressServer: 利用nodejs+express开发，具体express实现远程服务，提供远程api接口。
2. localSvc:：用C开发，本地硬件访问支持模块等，提供nodejs调用，使其能不用root权限即可监控硬件。