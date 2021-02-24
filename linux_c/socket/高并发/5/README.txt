//Datagram

cc -o server-5 lab02-5-service.c 
cc -o client-5 lab02-5-client.c 
./server-5
./client-5 192.168.19.104

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











