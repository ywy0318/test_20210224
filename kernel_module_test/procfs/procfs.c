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

    if (raw_copy_from_user(mymem, buff, len)) {
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

        proc_entry = remove_proc_entry(name, 0644, NULL);
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
