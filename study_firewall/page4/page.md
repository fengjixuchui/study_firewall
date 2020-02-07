# 第四课 TDI层的网络过滤 

TDI（[Transport Driver Interface](https://docs.microsoft.com/en-us/previous-versions/windows/hardware/network/ff565094(v=vs.85)?redirectedfrom=MSDN)） 传输层接口,即将淘汰的技术,取代TDI的技术是WFP(windows过滤平台)，虽然TDI要被淘汰但是网络协议栈在以前版本中是最主要的网络层，在最新的系统上也不可能把这些支持的函数也一次性全部去掉，因此我们还是讲TDI的网络过滤器，TDI是最接近用户层的，也就是内核中的最上层，它下面就是NDIS层（这个下一节讲）。

当用户层使用socket的时候，就会调用一些基本的比如send、bind等函数。然而这些又分tcp协议、udp协议等，那这些是怎么调试的呢，答案是TDI可以理解为一个大驱动，然后他把每个协议创建一个设备对象，同时指定名称比如\Device\Tcp、\Device\Udp等。因些上层假如使用tcp它就会绑定到\Device\Tcp设备对象上。

好了基础知识讲到这里，现在我们要做一个TDI层的过滤器，那怎么写呢，思路就是既然每个协议都是一个设备对象，那我们附加到想到过滤的设备对象上去，设备对象具体是哪个驱动创建的我们不管，因为所有操作最后都是一些设备对象在使用，同时微软提供一个IoAttachDevice函数，这个函数就是实现附加的，把我们要过滤器的设备对象附加上去，比如我写一个驱动创建一个\Device\tcp_fiter,那我们把\Device\tcp_fiter附加到\Device\Tcp上，由于内核原理是这样的我们附加一个设备到设备栈上，它就会放到栈的顶层，所有调用操作是从栈顶开始，因此第一个处理的就是我们的过滤器。

这里还有一个问题，比如我又写一个驱动附加到上面那又是栈顶了，那不我以前那个不是第一个处理了，没错内核就是这么设计的，很多什么在内核中“打架“就是这个，一般在内核中你不管我不管你，和谐共处就行了，后面直接随便讲一个例子代码。
* （只限XP) https://github.com/haidragon/TDIMon
* https://github.com/codereba/netmon
* https://github.com/haidragon/tdifw14





