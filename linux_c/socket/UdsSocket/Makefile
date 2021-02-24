#Description:For UdsSocket Test
#Date:2020-02-04
#Author:Genven_Liang
 
CC=gcc
FLAG=-lpthread -Wall
TARGET=main
 
SRC := $(shell ls *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))
#OBJ=main.o udsSocket.o
 
$(TARGET):$(OBJ)
	@$(CC) -o $@ $^ $(FLAG)
	@echo "make successful!!!"
 
%.o:%.c
	@$(CC) -c -o $@ $<
 
.THONY:clean
clean:
	@rm -f $(TARGET) $(OBJ)
	@echo "clean finish!!!"