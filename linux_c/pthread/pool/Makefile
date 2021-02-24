CC = gcc
CFLAGS = -O0 -Wall -g -I include -lpthread
 
main:src/main.c src/thread_pool.c
	$(CC) $^ -o $@ $(CFLAGS)
 
debug:src/main.c src/thread_pool.c
	$(CC) $^ -o $@ $(CFLAGS) -DDEBUG
 
clean:
	$(RM) .*.sw? main debug *.o
 
.PHONY:all clean