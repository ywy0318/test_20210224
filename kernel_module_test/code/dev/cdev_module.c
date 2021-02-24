#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <linux/sched.h>


static int major = 0;
static int minor = 0;
const int count = 1;
#define DEVNAME "demo"
#define DEVFILENAME "jisen"
static dev_t devnum;
static struct cdev *demop = NULL;

static struct class *mydemo_class;

//打开设备
static int demo_open(struct inode *inode,struct file *filp){

    //get command and pid
    printk(KERN_INFO "(%s:pid=%d),%s : %s : %d\n",current->comm,current->pid,__FILE__,__func__,__LINE__);

    //get major and minor from inode
    printk(KERN_INFO "(major=%d,minor=%d),%s : %s: %d\n",imajor(inode),iminor(inode),__FILE__,__func__,__LINE__);

    return 0;
}

//关闭设备
static int demo_release(struct inode *inode,struct file *filp){

    //get command and pid
    printk(KERN_INFO "(%s:pid=%d),%s : %s : %d\n",current->comm,current->pid,__FILE__,__func__,__LINE__);
    //get major and minor from inode
    printk(KERN_INFO "(major=%d,minor=%d, %s : %s : %d\n",imajor(inode),iminor(inode),__FILE__,__func__,__LINE__);

    return 0;
}

//读设备
static ssize_t demo_read(struct file *flip,char __user *buf,size_t size,loff_t *offset){

    struct inode *inode = flip->f_path.dentry->d_inode;

    //get command and pid
    printk(KERN_INFO "(%s:pid=%d),%s : %s : %d\n",current->comm,current->pid,__FILE__,__func__,__LINE__);

    //get major and minor from inode
    printk(KERN_INFO "(major=%d,minor=%d),%s : %s : %d\n",imajor(inode),iminor(inode),__FILE__,__func__,__LINE__);

    return 0;
}

//写设备
static ssize_t demo_write(struct file *filp,const char __user *buf,size_t size,loff_t *offset){

    struct inode *inode = filp->f_path.dentry->d_inode;

    //get command and pid
    printk(KERN_INFO "(%s:pid=%d),%s : %s : %d\n",current->comm,current->pid,__FILE__,__func__,__LINE__);

    //get major and minor from inode
    printk(KERN_INFO "(major=%d,minor=%d),%s : %s : %d\n",imajor(inode),iminor(inode),__FILE__,__func__,__LINE__);

    return 0;
}

//操作方法集
static struct file_operations fops = {

    .owner = THIS_MODULE,
    .open = demo_open,
    .release = demo_release,
    .read = demo_read,
    .write = demo_write,

};

static int __init demo_init(void){

    
    int ret;
    // get command and pid
    printk(KERN_INFO "(%s:pid=%d),%s : %s : %d\n",current->comm,current->pid,__FILE__,__func__,__LINE__);

    // alloc cdev obj
    demop = cdev_alloc();

    if(NULL == demop){
        return -ENOMEM;
    }

    // 2 init cdev obj
    cdev_init(demop,&fops);
    ret = alloc_chrdev_region(&devnum,minor,count,DEVNAME); //获取设备号
    if(ret){
        goto ERR_STEP;
    }

    major = MAJOR(devnum);

    // register cdev obj
    ret = cdev_add(demop,devnum,count);
    if(ret){
        goto ERR_STEP1;
    }

    //创建设备文件，这样模块注册到内核以后在/dev下就能找到设备
    mydemo_class = class_create(THIS_MODULE,DEVFILENAME); //第二个参数是设备文件名，可以修改
    device_create(mydemo_class,NULL,devnum,NULL,DEVFILENAME);

    //get command and pid
    printk(KERN_INFO "(%s:pid=%d),%s : %s : %d - ok.\n",current->comm,current->pid,__FILE__,__func__,__LINE__);

    return 0;

ERR_STEP1:
    unregister_chrdev_region(devnum,count);

ERR_STEP:
    cdev_del(demop);
    //get command and pid
    printk(KERN_INFO "(%s:pid=%d),%s : %s : %d - fail.\n",current->comm,current->pid,__FILE__,__func__,__LINE__);

    return ret;
}

static void __exit demo_exit(void){

    // get command and pid
    printk(KERN_INFO "(%s:pid=%d),%s : %s : %d - leave.\n",current->comm,current->pid,__FILE__,__func__,__LINE__);
    unregister_chrdev_region(MKDEV(major,minor),count);
    class_destroy(mydemo_class);
    cdev_del(demop);
}

module_init(demo_init);
module_exit(demo_exit);

MODULE_LICENSE("GPL");