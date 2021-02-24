#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
sudo insmod cdev_module.ko  #将设备注册进模块
cat /proc/devices    #查看设备有无挂着成功，即看看能不能找到自己命名的模块
ls -l /dev        #查看是否已经建立好设备文件；如果模块中不写创建设备文件的语句，可以自己手动创建

gcc -o testcdev testcdev.c  #编译测试程序

./testcdev /dev/jisen  #后面的参数就是/dev下的设备文件
*/

int main(int num,char *arg[]){

    if(2 != num){
        printf("Usage:%s /dev/devfile\n",arg[0]);  

        return -1;
    }

    int fd = open(arg[1],O_RDWR); 

    if(fd < 0){
        perror("open");
        return -1;
    }

    getchar();

    int ret = read(fd,0x321,0);
    printf("read: ret = %d.\n",ret);
    getchar();

    ret = write(fd,0x123,0);
    printf("write:ret = %d.\n",ret);

    getchar();
    close(fd);

    return 0;
}