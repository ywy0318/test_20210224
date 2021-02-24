#include<stdlib.h>
#include<string.h>
#include<unistd.h>


int main()
{
    char _pcFactoryID[1000]="aasasasaszxzxzx.";
	char *pos = NULL;
	printf("\n");
	printf("_pcFactoryID =%s",_pcFactoryID);
	printf("\n");

	if((pos = strstr((char*)_pcFactoryID, ".")) != NULL)
	{
		printf("pos = %p  pos[1] = %p,pos[1] = %c ,pos[0] = %p,pos[0] = %c\n");
			
	}

	printf("(true or false)= %d",(pos[1] == '\0'));
	

    if((pos = strstr((char*)_pcFactoryID, ".")) != NULL && pos[1] == '\0')
    {
        pos[0] = '\0';
	printf("pos = %p  pos[1] = %p,pos[1] = %c ,pos[0] = %p,pos[0] = %c\n");
    }	
printf("_pcFactoryID =%s",_pcFactoryID);			

}
