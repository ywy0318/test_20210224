#include <time.h>
#include<stdio.h>
#include<sys/time.h>
typedef struct
{
	struct timespec ts;
}test;

int main ()
{
	test test1;
	clock_gettime(CLOCK_REALTIME, &test1.ts);
	printf("clock_gettime : tv_sec=%ld, tv_nsec=%ld\n", test1.ts.tv_sec, test1.ts.tv_nsec);
	return 0;

}