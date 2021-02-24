#include<stdio.h>
#include<unistd.h>
#include<sys/type.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main()
{
	int sfd cfd;
	int ch = 'k';
	struct sockaddr_in saddr,caddr;
	sfd = socket(AF_INET,SOCK_STREAM,0);
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(29008);
	bind (sfd,(struct sockaddr *)&saddr,sizeof(saddr));
	listen(sfd,1);
	while(1)
	{
		printf("Server waiting \n");
		cfd = accept(sfd,(struct sockaddr *)NULL,NULL);
		if(read(cfd,&ch,1) < 0)
		{
			perror("read");
		}
		ch++;
		if(write(cfd,&ch,1) < 0)
		{
			perror("write");
		}
		close(cfd);
	}
}