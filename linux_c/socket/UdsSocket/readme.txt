Linux-C 本地套接字使用例子
       记--简单的使用本地套接字(UNIX套接字)双向通信的例子。       
	   三个进程使用本地套接字进行收发消息。

5.1 UDS(Unix Domain Socket) Unix域套接字

             用于本地进程间通信，类似UDP。

             头文件在sys/un.h, 可使用find或locate命令查找存放路径

             使用find命令在/usr路径下查找un.h