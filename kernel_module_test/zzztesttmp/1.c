#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");

#define MY_MEM_SIZE PAGE_SIZE

static const char *name = "sandals";
static struct proc_dir_entry *proc_entry;
static char *mymem;
static unsigned long mylen;

int mywrite(struct file *filp, const char __user *buff,
                        unsigned long len, void *data)
{
    if (len > MY_MEM_SIZE) {
        printk(KERN_INFO "mywrite too large len.\n");
        return -ENOSPC;
    }

    if (copy_from_user(mymem, buff, len)) {
        printk(KERN_INFO "mywrite copy_from_user failed.\n");
        return -EFAULT;
    }

    mylen = len;
    mymem[mylen] = 0;

    return len;
}

int myread(char *page, char **start, off_t off,
                   int count, int *eof, void *data)
{
    int len;

    if (!mylen) {
        return 0;
    }

    if (count < mylen || off > 0) {
        *eof = 1;
        return 0;
    }

    len = sprintf(page, "%s\n", mymem);

    return len;
}

int my_module_init(void)
{
    int ret = 0;

    mylen = 0;
    mymem = NULL;

    mymem = (char *)vmalloc(MY_MEM_SIZE);
    if (!mymem) {
        printk(KERN_INFO "my_module vmalloc failed.\n");
        ret = -ENOMEM;
    }
    else {
        memset(mymem, 0, MY_MEM_SIZE);

        proc_entry = create_proc_entry(name, 0644, NULL);
        if (!proc_entry) {
            ret = -ENOMEM;
            vfree(mymem);
            mymem = NULL;
            printk(KERN_INFO "my_module create_proc_entry failed.\n");
        }
        else {
            proc_entry->read_proc = myread;
            proc_entry->write_proc = mywrite;
            printk(KERN_INFO "my_module_init called. Module is now loaded.\n");
        }
    }

    return ret;
}

void my_module_cleanup(void)
{
    remove_proc_entry(name, NULL);
    vfree(mymem);
    mymem = NULL;
    printk(KERN_INFO "my_module_cleanup called. Module is now unloaded.\n");
    return;
}

module_init(my_module_init);
module_exit(my_module_cleanup);




/********************* proc文件系统 *************************/
 
 

 static void *scull_seq_start(struct seq_file *s, loff_t *pos)

 {    

     if (*pos >= MEMDEV_NR_DEVS)        

         return NULL; /* No more to read */    

     return my_devices + *pos;

 }

 

 static void *scull_seq_next(struct seq_file *s, void *v, loff_t *pos)

 {

     (*pos)++;

     if (*pos >= MEMDEV_NR_DEVS)    

         return NULL;    

     return my_devices + *pos;

 }

 static void scull_seq_stop(struct seq_file *s, void *v)

 {    /* Actually, there's nothing to do here */}

 

 

 static int scull_seq_show(struct seq_file *s, void *v)

 {

     struct mem_dev *dev = (struct mem_dev *) v;

 

     seq_printf(s, "%d-%d: %s\n",MAJOR((dev->cdev).dev),MINOR((dev->cdev).dev),dev->data);

 

     return 0;

 }

 

 static struct seq_operations mem_seq_ops = {

     .start = scull_seq_start,   
     .next = scull_seq_next,
     .stop = scull_seq_stop,
     .show = scull_seq_show

 };
 

 static int mem_proc_open(struct inode *inode, struct file *file)

 {    
    return seq_open(file, &mem_seq_ops);
 }

 

 static struct file_operations mem_proc_ops = {    

     .owner = THIS_MODULE,    

     .open = mem_proc_open, /* 只要实现这个函数 */    

     .read = seq_read,    

     .llseek = seq_lseek,    

     .release = seq_release

 }; 

 static struct proc_dir_entry *mydir, *pfile;
 static int mem_create_proc(void)
 {    

     mydir = proc_mkdir("mydir", NULL);    // 创建目录
     if (!mydir) {
         printk(KERN_ERR "Can't create /proc/mydir\n");
         return -1;
     }

     pfile = create_proc_entry("pool", 0666, mydir); // 创建文件

     if (!pfile) {
         printk(KERN_ERR "Can't create /proc/mydir/pool\n");
         remove_proc_entry("mydir", NULL);
         return -1;
     }
     else
         pfile->proc_fops = &mem_proc_ops;
     return 0;

 }

 static void mem_remove_proc(void)

 {   
     remove_proc_entry("pool", mydir);
     remove_proc_entry("mydir", NULL);   
 } 
