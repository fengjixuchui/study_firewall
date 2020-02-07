# 第四课 TDI层的网络过滤 

TDI（[Transport Driver Interface](https://docs.microsoft.com/en-us/previous-versions/windows/hardware/network/ff565094(v=vs.85)?redirectedfrom=MSDN)） 传输层接口,即将淘汰的技术,取代TDI的技术是WFP(windows过滤平台)，虽然TDI要被淘汰但是网络协议栈在以前版本中是最主要的网络层，在最新的系统上也不可能把这些支持的函数也一次性全部去掉，因此我们还是讲TDI的网络过滤器，TDI是最接近用户层的，也就是内核中的最上层，它下面就是NDIS层（这个下一节讲）。

当用户层使用socket的时候，就会调用一些基本的比如send、bind等函数。然而这些又分tcp协议、udp协议等，那这些是怎么调试的呢，答案是TDI可以理解为一个大驱动，然后他把每个协议创建一个设备对象，同时指定名称比如\Device\Tcp、\Device\Udp等。因些上层假如使用tcp它就会绑定到\Device\Tcp设备对象上。

好了基础知识讲到这里，现在我们要做一个TDI层的过滤器，那怎么写呢，思路就是我们附加到
* （只限XP) https://github.com/haidragon/TDIMon
* https://github.com/codereba/netmon
* https://github.com/haidragon/tdifw14





