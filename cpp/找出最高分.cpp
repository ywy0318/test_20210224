
/*0x77CDE394 (ntdll.dll)处(位于 cpp单文件.exe 中)引发的异常:
0xC0000005: 读取位置 0x00813AB8 时发生访问冲突。*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;

/*产生长度为n的随机字符串*/
char *generate_random_string(int n)
{
	int i = 0;
	int flag;
	char *string;
	//srand(time(0));
	if ((string = (char*)malloc(n + 1)) == NULL)
	{
		printf("malloc faild\n");
		return NULL;
	}
	for (i = 0; i < 5; i++)
	{
		flag = rand() % 2;
		switch (flag)
		{
		case 0:
			string[i] = 'A' + rand() % 25;
			break;
		case 1:
			string[i] = 'a' + rand() % 25;
			break;
		case 2:
			string[i] = '0' + rand() % 10;
			break;
		default:
			string[i] = 'X';
			break;
		}
	}
	string[n] = '\0';
	return string;
}

int  grand()
{
	//srand(time(0));
	//return (rand() % 50 + 51);
	return (rand() % 10 + 91);
}

//全局变量，每次随机从这里获取一个字符；
const unsigned char allchar[63] = "ASDFGHJKLQWERTYUIOPZXCVBNMasdfghjklqwertyuiopzxcvbnm0123456789";
void generate_string( char *string, unsigned int n)
{
	int i = 0;
	int ret;
	srand(time(0));
	for (i = 0; i < n; i++)
	{
		ret = rand() % 52;
		*string = allchar[ret];
		//printf("%c\n", allchar[ret]);
		string++;
	}
	*string = '\0';
}

class student
{
public:
	student();
	~student();
	int num;
	char name[20];
	int score;
	int compare(int max)
	{
		if (this->score > max)
		{
			return 1;
		}
		else if(this->score==max)
		{
			return 2;
		}
		else
		{
			return 3;
		}
	}
private:

};

student::student()
{
	this->num = 0;
	this->score = 0;
	memset(this->name,0,sizeof(this->name));
}

student::~student()
{
}


int main()
{
	int n = 0;
	int i = 0;
	int j = 0;
	int init_num = 18070;
	 char buf[20] = { '0' };
	 srand(time(0));
	do
	{
		cout << "please input num of the student(1-30):" << endl;
		cin >> n;
	} while ((n<=0)||(n>30));

	student* pStudents = new student[n];
	//cout << "input student info:" << endl;
	for ( i = 0; i < n; i++)
	{
		 pStudents[i].score= grand();
		 generate_string(buf,5);
		 strcpy(pStudents[i].name, buf);
		 memset(buf, 0, sizeof(buf));
		 pStudents[i].num = init_num + i;
		 Sleep(1000);
	}
	cout << "***" << endl;

	for (j = 0; j < n; j++)
	{
		cout << pStudents[j].num << ":";
		cout << pStudents[j].name << ":";
		cout << pStudents[j].score << endl;
	}

	cout << "****" << endl;
	student* pstudentmax = new student[1];
	int max_score = 0;
	int max_num = 1; //假装已经找到了一个最大的，
					//为了后面再找到一个score值相同的最大的
	for ( i = 0; i < n; i++)
	{
		switch (pStudents[i].compare(max_score))
		{
			case 1:
				max_score = pStudents[i].score;
				max_num = 1;
				if (pstudentmax != NULL)
				{
					delete[] pstudentmax;
				}
				pstudentmax = new student[1];
				pstudentmax[1] = pStudents[i];
				break;
			case 2:
				student* temp = pstudentmax;
				max_num += 1;
				pstudentmax = new student[max_num];
				for (j = 0; j < max_num-1; j++)
				{
					pstudentmax[j] = temp[j];
				}
				pstudentmax[max_num - 1] = pStudents[i];
				delete[] temp;
				break;
		}
	}
	cout <<"input max_score:"<<max_score<<endl;
	for ( i = 0; i < max_num; i++)
	{
		cout << pstudentmax[i].num;
		cout << pstudentmax[i].name << endl;
	}
	cout << "*****" << endl;
	

	delete[] pStudents;
	delete[] pstudentmax;
	system("pause");
	return 0;
}