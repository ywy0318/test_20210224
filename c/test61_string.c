#define _CRT_SECURE_NO_WARNINGS
#include<dos.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<conio.h>


//'\0','0',"0"
//printf("%s (%d) -%s : \n",__FILE__,__LINE__,__FUNCTION__);

char *mystrcpy(char *dest,const char *source)
{
	while(*source!='\0')
	{
		*dest=*source;
		dest++;
		source++;
	}
	*dest='0';
}



char *mystrncpy(char *des,const char *src,int n)
{
	int i=0;
	char *st=des;
	while(i<n)
	{		
		*des=*src;
		des++;
		src++;
		i++;		
	}
	*des='0';
	return st;
}

char *mystrncat(char *des,char *src,int n)
{
	int i=0;
	char *tmp=des;
	char *tp=src;

	while(*tmp!='\0')//????????????
	{
		tmp++;
	}
	while(*tp!='0')
	{
		if(i>n)
		{
			*tmp='\0';
			break;
		}
		*tmp=*tp;
		tp++;
		tmp++;
		i++;
	}
	return des;
}

//�����ַ�ָ������ַ���������ַ�����ʱ�򣬲�Ҫֱ�Ӳ�������������ָ��(ָ��Ҫ�����ַ�����ָ��),
//Ȼ�����ָ��ĵ�ַ
//������ ����'\0';
char *mystrcat(char *dd,char *ff)
{
	int i=0;
	char *temp=dd;
	char *tf=ff;
	//printf("1:%d,%c\n",temp,*temp);
	while(*temp!='\0')
	{
		//i++;
		temp++;
		//printf("%c,%d\n",*temp,temp);
	}

	/*dd+=i;*/
	//return i;
	while(*tf!='\0')
	{
		//*(dd+i)=*ff;
		//(dd+i)+=1;
		//dd+i+1;
		//ff++;
		*temp=*tf;
		//printf("%c,%d\n",*temp,temp);
		temp++;
		//*temp=*tf;
		tf++;
	}
	*temp='\0';
	return dd;
}

char * mystrchr(char *p,char c)
{
	//int i=0;
	char *i=0;
	char *tmp=p;
	while(*tmp!='\0')
	{
		if(*tmp==c)
		{
			i=tmp;
			break;
		}
		tmp++;
	}
	if(i==0)
	{
		return NULL;
	}
	else
	{
		return i;
	}
	/*if(*tmp!='\0')
	{
		return tmp;
	}
	else
	{
		return NULL;
	}*/
}
char * mystrrchr(char *p,char c)
{
	char* ir=0;
	char *tmpr=p;
	while(*tmpr!='\0')
	{
		if(*tmpr==c)
		{
			//break;
			ir=tmpr;
		}
		tmpr++;
	}
	//if(*tmpr!='\0')
	//{
	//	return ir;
	//}
	//else
	//{
	//	return NULL;
	//}
	if(ir==0)
	{
		return NULL;
	}
	else
	{
		return ir;
	}
}
/***/
int mystrcmp(const char *str,const char *str1)
{

}




//�ַ���int����ת��,����



//���Խṹ��λ�����ʱ�ĸߵ�λ����
typedef struct				//   11
	{
		unsigned char a: 1;//��λ
		unsigned char b: 1;
		unsigned char c: 1;
		unsigned char d: 1;

		unsigned char e: 1;
		unsigned char f: 1;
		unsigned char g: 1;
		unsigned char h: 1;//��λ
	} signal2_3;


int main()
{	
	char dd[]="asd";
	char ff[]="zxc";

	char df[10]="((()))";

	char c[100]="qssswertyuiopasdfqwghj";
	char *p;
	char d[20]={"0"};
	char de[20]={"0"};
	int x=0x41412020;
	//long xw=2E323102;
	int xs=0;
	int y=x<<2;//���Ƽ�λ�൱�ڳ���(2�ļ��η�)
	int z=x<<3;
	int i=0;
	int j=0;
	//char *p=ff;

	char *a="ABCDEF";
	char *b="abcdef";
	char *qq="abCdeF";
	char *bd="ABCDEF";
	//strcmp(const char *s1, const char *s2) //�Ƚ�ascii,�����ͬ����Ϊ0,���s1����s2,�򷵻ش���0��,���s2С��s1�򷵻�С��0����ֵ;
	// A��ASCII����65,a��ASCII����97
	 signal2_3 s={0};

	 for(i=0;i<strlen(c);i++)
	 {
		if(c[i]=='w')
		{
			j=i;
			//printf("%d\n",i);
			break;
		}
		
	 }
	 //-1,0,1
	 printf("%d,%d,%d\n",strcmp(a,b),strcmp(a,bd),strcmp(b,qq));

	 //printf("%d\n",j);

	 //p=strchr(c,'w');//����ֵ�Ǹ���ַ
	 //p=mystrchr(c,'Z');
	 //printf("c=%d,'w'=%d,'w'=c[%d],c[4]=%c\n",c,strchr(c,'w'),(strchr(c,'w')-c),c[4]);
	 //printf("c=%d,'w'=%d,'w'=c[%d],c[4]=%c\n",c,mystrchr(c,'Z'),(mystrchr(c,'Z')-c),c[4]);
	// printf("c=%d,'w'=%d,'q'=c[%d],c[7]=%c\n",c,mystrrchr(c,'q'),(mystrrchr(c,'q')-c),c[17]);
	 //printf("%d\n",c);
	 //printf("%d\n",p);

	 //printf("%d\n",p-c);//����ֵ��0��ʼ

	 //printf("%x:%x\n",x,xw);
	 //printf("%x\n",x);

	//while(c[i]!='\0')
	//{
	//	//printf("%c",c[i]);
	//	i++;
	//}

	/* for(i=1;i<10;i++)
	 {
		printf("%d , 0x%x  ",i+10,i+10);
		if(i%2==0)
		{
			printf("\n");
		}
	 }
	 printf("\n");*/

	//����λ��
	//s.a=1;
	//s.b=1;
	//s.c=1;
	//s.d=1;

	//s.e=1;
	//s.f=1;
	//s.g=1;
	//s.h=1;


	//if(s.a)
	//{
	//	printf("a\n");
	//	s.a=1;
	//}

	//printf("%d\n",s);



	//////����ָ�����ַ���
	////while(*p!='\0')
	////{
	////	j++;
	////	p++;
	////}


	////printf("%d,%p,%d,%d,%p\n",j,p,p,ff,ff);
	////printf("%d,%p\n",p-ff,p-ff);
	//printf("dd:%s\n",dd);
	//printf("ff:%s\n",ff);
	////strcpy(d,c);
	/////strncpy(d,c,3);
	//strcat(ff,ff);

	//strncat(c,df,20);
	//mystrncat(c,df,20);
	//printf("%s\n",c);
	//printf("%s (%d) -%s : \n",__FILE__,__LINE__,__FUNCTION__);
	////mystrcat(dd,ff);
	//printf("dd:%s\n",dd);
	//printf("ff:%s\n",ff);
	////x=mystrcat(dd,ff);
	//mystrcat(dd,ff);

	//printf("%s\n",d);
	//printf("dd:%s\n",dd);
	//printf("ff:%s\n",ff);
	//printf("%d\n",mystrcat(dd,ff));
	//mystrcpy(de,c);
	//mystrncpy(de,c,3);
	
	//printf("dd:%s\n",dd);
	//printf("d:%s\n",dff);
	//printf("?: %s\n",de);
	//printf("%d %d\n",y,z);
	//printf("%d\n",sizeof(c));



	system("pause");
	return 0;
}