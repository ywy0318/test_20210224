//SCTP
//rpm -qa | grep sctp

cc -o server-6 lab02-6-service.c -lsctp
cc -o client-6 lab02-6-client.c -lsctp
./server-6
./client-6 192.168.19.104













