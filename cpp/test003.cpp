/*�������ļ��ж�ȡһ���ַ���Ȼ��Ӹ��ո�д�뵽����ļ���*/
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int main()
{
	ofstream outfile("out_file");
	ifstream infile("in_file");
	if (!infile)
	{
		cerr << "error:unable to open infile\n"  ;
		return -1;
	}
	if (!outfile)
	{
		cerr << "error:unable to open outfile\n"  ;
		return -2;
	}

	string word;
	while (infile>>word)
	{
		outfile << word << ' ';
	}

	system("pause");
	return 0;

}