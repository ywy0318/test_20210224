/*�ṹ���Լ�typedef��һЩ����*/

/*λ���λ��ǰ��*/
/*λ���λ������,��λ������*/
//#define stPACKED __attribute__((packed))

#include<stdlib.h>
#include<stdio.h>
#include<string.h>


typedef unsigned char				uint8;
typedef unsigned short				uint16;
typedef unsigned int				uint32;

typedef struct
{
	struct
	{
		uint16 station_id;						// վ����
		uint8 side_open_door;					// ���Ų�
		uint8 skip_flag;						// Խվ��־
	}station_id_1st;					// վ����

	struct
	{
		uint16 station_id;						// վ����
		uint8 side_open_door;					// ���Ų�
		uint8 skip_flag;						// Խվ��־
	}station_id_2nd;

	uint16 station_id_3rd;						// ����վ����
}STATION_INFO;

typedef struct 
	{
		uint8 a:1;
		uint8 b:1;
		uint8 c:1;
		uint8 d:1;

		uint8 e:1;
		uint8 f:1;
		uint8 g:1;
		uint8 h:1;
	} aa;
int main()
{
	

	//int d;
	aa s={0};
	s.h=1;
	printf("%d\n",s);
	printf("%d\n",sizeof(s));

	//struct MyStruct1
	//{
	//	int dc;
	//};
	//STATION_INFO s[1000] = {0};
	//d = sizeof(STATION_INFO);
	
	//printf("%d\n",d);

	system("pause");
	return 0;
}