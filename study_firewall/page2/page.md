# 第二课 基于SPI层的网络过滤
1. 什么是SPI？

SPI是winsock服务提供者接口（Server Provider InterFace),他是应该程序使用的服务，而它本身不是应该程序，它的作用是向加载这个服务的应该程序导出自己，它做中间层的作用。SPI由其中的俩个部分组成——传输服务提供者（Transport Service Provider)和命名空间服务提供者（Name Space Providers),它允许用户开发这俩种类型的服务提供者,如图所示。

![](./image/1.png)





