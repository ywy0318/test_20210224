#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/time.h>
//#include <linux/vermagic.h>


#define procfs_name "xtime"

struct proc_dir_entry *clock_proc_file;

static int procfile_read(char *page,char **start,off_t offset,int count,int *eof,void *data)
{
	int ret;
	struct timespec x_time=current_kernel_time();
	//struct timeval tv;
	//do_gettimeofday(&tv);
	printk(KERN_INFO"procfile_read(/proc/%s)called\n",procfs_name);

	//判断offset,这是很重要的，因为来自库的标准读函数将持续发布读系统调用直到内核答复没有更多信息
	//或它的缓冲区被填满。

	if(offset>0)
	{
		ret=0;
	}
	else{
	ret=sprintf(page,"tv_sec:%ld\ttv_nsec:%ld\n",x_time.tv_sec,x_time.tv_nsec);
	}
	return ret;
}

static int __init proc_init(void)
{
	clock_proc_file = create_proc_entry (procfs_name,0644,NULL);
	if(clock_proc_file==NULL)
	{
		remove_proc_entry(procfs_name,NULL);
		printk(KERN_ALERT"Error:Could not initialize /proc/%s\n",procfs_name);
		return -ENOMEM;
	}
	clock_proc_file->read_proc = procfile_read;
	clock_proc_file->owner=THIS_MODULE;
	clock_proc_file->mode=S_IFREG|S_IRUGO;
	clock_proc_file->uid=0;
	clock_proc_file->gid=0;
	printk(KERN_INFO"/proc/%s created\n",procfs_name);
	return 0;
}

static void __exit proc_exit(void)
{
	remove_proc_entry(procfs_name,NULL);
	printk(KERN_INFO"/proc/%s removed\n",procfs_name);
}
module_init(proc_init);
module_exit(proc_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("WuYang");

