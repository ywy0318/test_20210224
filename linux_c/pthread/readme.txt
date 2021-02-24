Linux-C 线程
Linux-C 线程
一、简述

   记--线程的相关练习，线程锁：互斥锁、读写锁、条件变量。一个进程可以有多个线程，线程共享进程的资源(也就是说一个进程的多个线程操作的是同一片内存空间，但是线程具有独立的线程栈)，可以使用man手册查看相关函数的使用。

    注：进程是资源分配的最小单位,线程是CPU调度的最小单位。

二、线程的基本操作

线程的创建、退出(本身执行退出操作)、取消(由其他线程执行，如在主线程a取消线程b)

pthread_create()函数
功能	创建线程
头文件	#include <pthread.h>
原型	int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
参数	
thread：用于存放线程id （用来标识新创建的线程，类似于描述符）传入pthread_t变量类型的地址，用于存放线程id值

attr：线程的属性设置，可以通过pthread_attr_init来去初始化这个结构体：pthread_attr_t
            如果设置为NULL则代表按照线程默认属性来设置。

start_routine：线程启动之后执行的第一个函数 的函数指针。

arg：传输给start_routine函数的参数。

返回值	
成功：返回0

失败：返回错误变量值，你可以通过strerror这个函数将这个错误值转化为错误信息输出

           EINVAL  设置的属性无效

备注	
引用线程，在编译的时候需要链接线程库，编译时添加：-pthread

线程的属性设置中该注意的地方：
    在线程的创建函数pthread_create中，第二参数代表线程的属性，其中它具备以下特点：
        1，如果填入NULL，则按照线程的默认属性来创建线程
        2，如果想要设置线程的属性，需要先初始化pthread_attr_t的属性，用到以下函数
    
线程属性初始化
    #include <pthread.h>

       int pthread_attr_init(pthread_attr_t *attr);//初始化属性

       int pthread_attr_destroy(pthread_attr_t *attr);//销毁属性


线程属性获取函数：
    pthread_getattr_np获取线程属性pthread_attr_t
    #define _GNU_SOURCE             /* See feature_test_macros(7) */
       #include <pthread.h>

       int pthread_getattr_np(pthread_t thread, pthread_attr_t *attr);
    thread：需要获取的线程属性的TID
    attr：属性将会存放到这里


    pthread_self：获取线程自己的TID
        pthread_t pthread_self(void);


线程的分离属性
    int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
        设置线程的分离属性：
        detachstate有两种状态：
                PTHREAD_CREATE_DETACHED：分离（线程创建之后，不需要接合，结束后直接释放其资源）
                PTHREAD_CREATE_JOINABLE：接合

       int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
        获取线程分离属性


线程的栈属性
    posix_memalign：申请指定的栈内存地址
        #include <stdlib.h>

               int posix_memalign(void **memptr, size_t alignment, size_t size);
            memptr：栈的内存起始地址将会放到这里
            alignment：采用多少个字节对齐内存
            size：申请多大的内存，以字节为单位

    设置栈的大小及内存开始地址：
        int pthread_attr_setstack(pthread_attr_t *attr,
                                 void *stackaddr, size_t stacksize);
        attr：线程的属性变量
        stackaddr：栈的起始地址
        stacksize：栈的大小

               int pthread_attr_getstack(const pthread_attr_t *attr,
                                 void **stackaddr, size_t *stacksize);
        获取栈信息，同上


    直接设置栈内存大小，而不指定内存地址
        int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
            attr：线程的属性变量
            stacksize：栈的大小

               int pthread_attr_getstacksize(const pthread_attr_t *attr, size_t *stacksize);
            获取栈的大小信息，参数同上


线程的优先级调度属性
    非实时系统上层软件设置不了静态优先级

静态优先级0-99:
    0：非实时普通线程
    1-99：实时线程（数字越高优先级越高）


动态优先级：
    -20-》19
    数字越大，优先级越低


调度策略：
    OTHER：非实时线程的调度策略
    RR：轮询调度，每一个线程都会分配时间片
    FIFO：抢占式调度
 

pthraed_exit()函数
功能	退出当前线程
头文件	#include <pthread.h>
原型	void pthread_exit(void *retval);
参数	retval：传输给接合它的线程的数据的 存放地址
返回值	无返回值
备注	线程内部自己执行退出
pthread_join()函数
功能	接合一个终止的线程(等待某个线程的终止)
头文件	#include <pthread.h>
原型	int pthread_join(pthread_t thread, void **retval);
参数	
thread：要接合的线程的id

retval：用来接收所接合线程的返回值。

返回值	
成功：返回0

失败：返回错误号

备注	可以使用strerror()函数将错误号对应的错误信息以字符串的形式输出
三、互斥锁
如果在man手册中没有相关函数的信息则需要更新man手册。
           更新posix手册man，使用apt在线更新命令：apt-get-install manpages-posix-dev
		   
    创建线程一般先创建先运行，但是也有可能由于CPU等资源的原因，某个线程被阻塞而没能够先运行。
	就算是先运行了但是也有可能由于资源不足等原因而执行"缓慢",导致某一些操作"异常"（有一些条件已经可能被其它的线程所更改，
	但还是以之前的条件执行操作）。因此，对于某一些执行动作的条件或者是资源进行暂时的“加锁”操作，等操作完成在进行"解锁"操作。

应用场景：多线程访问共有资源的时候需要加锁。

                   例如：假设a线程，b线程都需要对全局变量num进行操作，num的初值为300，a线程需要-50，b线程需要+100，

                             正常来说：a、b线程都操作完之后num的值应该变为：300-50+100=350；即：a读取num的值(300)，然后将num-50==>250，再将num的结果值(250)写回去，然后b程序读取num的值(250)，然后将num+100==>350，将num的值（350）写回去。（也可以是b线程先操作）                      
若是在a线程做完-50操作，还没来得及见num写回去，b线程就开始读取了，那么a线程的操作结果可能会被覆盖而失效。

互斥锁：对资源进行加锁，防止在操作的时候，某一些条件被其他线程改变。在a已经加锁的情况下b想要加锁，b会被阻塞，等待；直到a把锁解开，b才可以加锁。

pthread_mutex_init()函数
功能	初始化互斥锁
头文件	#include <pthread.h>
原型	int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
参数	
mutex：锁变量，一般定义为全局变量。其中restrict 限定符只适用于指针，表明该指针是访问一个 数据对象的唯一且初始的方式。

attr：互斥锁的属性，设置为NULL，则按照默认设置去配置锁的属性。

返回值	
成功：返回0

失败：返回错误号

备注	 
pthread_mutex_lock()函数
功能	锁定互斥锁
头文件	#include <pthread.h>
原型	int pthread_mutex_lock(pthread_mutex_t *mutex);
参数	mutex：锁变量
返回值	
成功：返回0

失败：返回错误号

备注	当“资源”已经被其它线程加锁了，此时加锁会被阻塞，等待直到资源被其它线程解锁之后才可以加锁。
而pthread_mutex_trylock()函数则是尝试性地加锁，如果已经被其它线程加锁了则不会等待，会立即返回。
 

pthread_mutex_unlock()函数
功能	解开互斥锁
头文件	#include <pthread.h>
原型	int pthread_mutex_unlock(pthread_mutex_t *mutex);
参数	mutex：锁变量
返回值	
成功：返回0

失败：返回错误号

备注	 
 

pthread_mutex_destroy函数
功能	销毁互斥锁
头文件	#include <pthread.h>
原型	int pthread_mutex_destroy(pthread_mutex_t *mutex);
参数	mutex：锁变量
返回值	
成功：返回0

失败：返回错误号

备注	 


四、读写锁

读写锁：可以分为读锁、写锁。有时候a线程加锁只是防止某一些条件被其他线程改变，本身a也没有想修改条件，只想读取。
其实这种情况下，a、b多个线程可以同时读取；因此，可以加读锁，防止在读取并用来操作的过程 条件值被修改，
但是大家都可以读取（读取的时候不会被阻塞）。要是加上写锁，就会互斥，阻塞，就像互斥锁一样。
也就是说，a加了读锁，同时b也可以加读锁；但是a加了写锁，b就不能加锁(包括读、写锁)，等待a解锁之后才可以加锁。
 

pthread_rwlock_init()函数
功能	初始化读写锁
头文件	#include <pthread.h>
原型	 int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,const pthread_rwlockattr_t *restrict attr);
参数	
rwlock：锁变量

attr：读写锁的属性，设置为NULL，则按照默认设置去配置锁的属性。

返回值	
成功：返回0

失败：返回错误号

          EINVAL 属性值无效

备注	 
 

pthread_rwlock_rdlock()函数
功能	加读锁
头文件	#include <pthread.h>
原型	int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
参数	rwlock：锁变量
返回值	
成功：返回0

失败：返回错误号

备注	
如果“资源”已经被其它线程加了读锁，可以同时加读锁，不会阻塞。

如果被其它线程加了写锁，那么会被阻塞。pthread_rwlock_tryrdlock()函数尝试加锁，无论是否成功都立即返回。

 

pthread_rwlock_init()函数
功能	加写锁
头文件	#include <pthread.h>
原型	int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
参数	rwlock：锁变量
返回值	
成功：返回0

失败：返回错误号

备注	当“资源”已经被其它线程加锁了，此时加锁会被阻塞，等待直到资源被其它线程解锁之后才可以加锁。而pthread_rwlock_trywrlock()函数则是尝试性地加锁，如果已经被其它线程加锁了则不会等待，会立即返回。
 

pthread_rwlock_unlock()函数
功能	解开读写锁
头文件	#include <pthread.h>
原型	int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
参数	rwlock：锁变量
返回值	
成功：返回0

失败：返回错误号

备注	 
 

pthread_rwlock_destroy()函数
功能	销毁读写锁
头文件	#include <pthread.h>
原型	int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
参数	rwlock：锁变量
返回值	
成功：返回0

失败：返回错误号

备注	 

五、线程的取消机制

        

pthread_cancel()函数
功能	取消某个线程（例如主线程取消子线程）
头文件	#include <pthread.h>
原型	int pthread_cancel(pthread_t thread);
参数	thread：指定线程的ID，当这个线程收到取消请求之后，默认在遇到取消点函数(具体内参照man 7 pthreads)的时候退出线程；
返回值	
成功：返回0

失败：返回非0的错误号

备注	通常用于主线程取消子线程，或者是释放资源的时候
 

pthread_setcancelstate()函数
功能	设置线程的取消机制的状态
头文件	#include <pthread.h>
原型	int pthread_setcancelstate(int state, int *oldstate);
参数	state：
            PTHREAD_CANCEL_ENABLE：默认设置，代表该线程可取消
            PTHREAD_CANCEL_DISABLE：代表该线程不可取消
        oldstate：用来保存旧的取消状态，设置为NULL，则不保存
返回值	成功：返回0
失败：返回非0的错误号
备注	
有关安全取消点函数，详情：man 7 pthreds



 

pthread_setcanceltype()函数
功能	设置线程的响应方式
头文件	#include <pthread.h>
原型	int pthread_setcanceltype(int type, int *oldtype);
参数	
type： PTHREAD_CANCEL_DEFERRED 遇到取消点的时候取消（默认设置）
            PTHREAD_CANCEL_ASYNCHRONOUS 立即取消线程

        oldtype：用来保存旧的设置，设置为NULL，则不保存

返回值	成功：返回0
失败：返回非0的错误号
备注	例如正在执行某一些重要的函数，不希望被随意打断的，一般默认不会立即取消，直到执行完成并执行到的是可以取消的"位置"。(关于取消点 具体内参照man 7 pthreads)
pthread_cleanup_push()函数
功能	登记函数（添加在线程收到取消通知的时候，在取消前补充执行的函数，取消前要执行的函数，比如释放资源、保存数据等）
头文件	#include <pthread.h>
原型	void pthread_cleanup_push(void (*routine)(void *),void *arg);
参数	routine：需要在退出前执行的函数 的函数指针
arg：执行函数(routine)的参数
返回值	无
备注	原则：和栈一样，后入先出；对应入栈操作。
pthread_cleanup_pop()函数
功能	在线程取消的压栈函数后，将登记的函数清除出去
头文件	#include <pthread.h>
原型	void pthread_cleanup_pop(int execute);
参数	
execute：0代表清除登记的函数，不执行里面的函数 （出栈的时候不执行函数）
                 非0代表，清除出去，并且执行里面的函数 （出栈的时候执行函数）

                这个参数并不影响异常终止时清理函数的执行。调用 pthread_exit()和取消点终                   止（pthread_cancel()）都将执行pthread_cleanup_push()所指定的清理函数。

返回值	无
备注	对应出栈操作。


六、条件变量(一般配合互斥锁使用)

        应用场景：某线程想要操作某个全局资源、在操作时需要加锁，但是加锁之后发现资源尚未满足进一步的操作条件，此时需要等待资源变化并满足条件，但是由于已经加锁，别的线程无法改变资源条件，所以需要解锁再等待。直到资源满足并被唤醒，对资源进行加锁并进行相应的操作。使用条件变量来帮我们做：加锁、等待、唤醒、加锁。

pthread_cond_init()函数
功能	初始化条件变量
头文件	#include <pthread.h>
原型	int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
参数	
cond:条件变量

attr：条件变量的属性，设置为NULL，则使用默认设置。

返回值	
成功：返回0

失败：返回错误号

备注	 
pthread_cond_wait()函数
功能	等待条件条件
头文件	#include <pthread.h>
原型	int pthread_cond_wait(pthread_cond_t *restrict cond,  pthread_mutex_t *restrict mutex);
参数	
cond:条件变量 （需要进入睡眠的条件变量）

mutex：锁变量（需要操作的互斥锁）

返回值	
成功：返回0

失败：返回错误号

备注	若是条件不满足则让线程进入睡眠并解锁muext互斥锁，一直等到（条件满足）cond被唤醒，，唤醒之后再给mutex上锁。注：其中的解锁操作就是为了让“别人”改变资源条件。
pthread_cond_signal()函数
功能	发出信号（唤醒单个条件变量等待线程）
头文件	#include <pthread.h>
原型	int pthread_cond_signal(pthread_cond_t *cond);
参数	cond：条件变量
返回值	
成功：返回0

失败：返回错误号

备注	 
pthread_cond_broadcast()函数
功能	唤醒所有（因某个条件变量而）睡眠的线程
头文件	#include <pthread.h>
原型	int pthread_cond_broadcast(pthread_cond_t *cond);
参数	cond：条件变量
返回值	
成功：返回0

失败：返回错误号

备注	先睡眠的线程先被唤醒（类似排队）。
pthread_cond_destroy()函数
功能	销毁条件变量
头文件	#include <pthread.h>
原型	int pthread_cond_destroy(pthread_cond_t *cond);
参数	cond：条件变量
返回值	
成功：返回0

失败：返回错误号

备注	 


七、线程池

通常在多任务时，用来管理线程。
应用场景：在多任务时，需要多线程来提高效率。有时候任务比较多，有时候任务又比较少。
在任务多的时候，需要创建多个线程需要时间、不需要的时候又要释放资源，
如果是不断的创建线程、然后不断的释放线程会比较浪费CPU资源，并且相应时间也较慢。
为此如果提前创建好线程的话，就可以省去创建线程的时间，以提高执行效率。
提前创建好的合适数量的线程、有任务的时候直接响应、如果没有任务则进入休眠、任务多的时候再添加线程。
总之维持最少线程数、以及最大线程数来确保执行了效率。可以想象有一个装有已经创建好的线程的 池塘，
有任务时我们可以直接拿来用、没有任务时、线程进入休眠。线程池的线程数量维持在一定数量，根据任务的多少进行调整，
但是会保持一定最少数量和最大数量。或者说线程池就是一个说法，用来形容我们管理线程与任务的方式。
