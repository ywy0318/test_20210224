#include <stdio.h>
#include <stdlib.h>
//#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>
pthread_mutex_t mutex;
int main()
{
        pthread_mutex_init(&mutex,NULL);
        while(1)
        {
                printf("%s (%d) \n",__FUNCTION__,__LINE__);
                pthread_mutex_lock(&mutex);
                sleep(3);
                printf("%s (%d) \n",__FUNCTION__,__LINE__);
                //pthread_mutex_unlock(&mutex);
                printf("%s (%d) \n",__FUNCTION__,__LINE__);
        }
        return 0;
}
