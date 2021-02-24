//面向数据流协议编程

cc -o server-1 lab02-1-service.c -lpthread
cc -o client-1 lab02-1-client.c -lpthread
./server-1
./client-1

cc -o server-2 lab02-2-service.c -lpthread
cc -o client-2 lab02-2-client.c 
./server-2 5678
./client-2 localhost 5678 "www.ingben.com"

//ipv4
cc -o server-3 lab02-3-server-3.c 
cc -o client-3 lab02-2-client.c 
./server-3
./client-3

//ipv6
cc -o server-4 lab02-4-server.c
cc -o client.4 lab02-4-client.c 
./server-4
./client-4::1 d











