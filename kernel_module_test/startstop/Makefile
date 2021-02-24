#hello-1.c 4.19.132
#make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
#make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
#rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions *.order *symvers *Module.markers
#载入模块的时候，如果不指定参数就是上面的默认值，如果要指定参数的话
#可以像下面这样来指定参数。insmod hello-5.ko mystring="superc" myint=444 
#那么Makefile编译的时候需要设置成这样:
obj-m += startstop.o
startstop-objs:=start.o stop.o
all:
	make -C /lib/modules/4.19.132/build M=$(PWD) modules
clean:
#make -C /lib/modules/4.19.132/build M=$(PWD) clean
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions *.order *symvers *Module.markers
