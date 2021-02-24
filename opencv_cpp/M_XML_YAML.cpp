/*
XML和YAML文件简介
XML:eXtensible Markup Language 翻译成中文为"可扩展标识语言"
XML是一种元标记语言,所谓"元标记",就是开发者根据自身需要定义自己的
标记,比如可以定义标记<book><name>;
任何满足XML命名规则的名称都可以标记,这就向不同的应用程序打开了大门
XML,是一种语义，结构化语言,描述了文档的结构和语义;
*******
YAML:这种语言以数据为中心,而不是以置标语言为重点,而用返璞词进行
重新命名,YAML是一种可读性高,用来表达资料序列的格式,
参考了多种语言,XML,C,Python,Perl,电子邮件格式RFC2822

.yml和.yaml同为YAML格式的后缀名
YAML试图用一种比XML更敏捷的方式,来完成XML所完成的任务;

FileStorage类操作文件的使用引导
XML和YAML是使用非常广泛的文件格式,可以利用XML或者YAML
格式的文件存储和还原各式各样的数据结构,还可以存储和载入任意
复杂的数据结构,包括opencv相关周边相关的数据结构,以及各种原始数据类型
如:整数和浮点数字和文本字符串

写入或者读取到XML或者YAML文件中的过程
1.>实例化一个FileStorage类的对象,用默认带参数的构造函数完成初始化
或者用FileStorage::open()成员函数辅助初始化;
2.>使用流操作符<<进行文件写入操作,或者使用>>进行
文件读取操作,类似C++中的文件输入输出流;
3.>使用FileStorage::release()函数析构掉FileStorage
类对象,同时关闭文件;

*/
#include"opencv2/opencv.hpp"
#include<time.h>
using namespace cv;
using namespace std;

void test_XML_YAML_write()
{
	//初始化
	FileStorage fs("test.yaml",FileStorage::WRITE);
	
	//开始文件写入
	fs << "frameCount" << 5;
	time_t rawtime;
	time(&rawtime);
	fs << "calibrationDate" << asctime(localtime(&rawtime));
	Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
	Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0, 001, 0, 0);
	fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
	fs << "features" << "[";
	for (size_t i = 0; i < 3; i++)
	{
		int x = rand() % 640;
		int y = rand() % 480;
		uchar lbp = rand() % 256;
		fs << "{:" << "x" << x << "y" << y << "lbp" << lbp;
		for (size_t j = 0; j < 8; j++)
		{
			fs << ((lbp >> j) & 1);
			fs << "]" << "}";
		}
		fs << "]";
		fs.release();

		print("文件读写完毕，请在工程目录下查看生成的文件");
		system("pause");
		return ;
	}
}

void test_XML_YAML_read()
{
	//改变console字体颜色
	system("color 6F");
	//初始化
	FileStorage fs_2("test.yaml",FileStorage::READ);
	//第一种方法:对FileNode操作
	int frameCount = (int)fs_2["frameCount"];
	std::string date;
	//第二种方法,使用FileNode运算符>>
	fs_2["calibrateDate"] >> date;
	Mat cameraMatrix2, distCoeffs2;
	fs_2["cameraMatrix2"] >> cameraMatrix2;
	fs_2["distCoeffs2"] >> distCoeffs2;

	cout << "frameCount:" << frameCount << endl;
	cout << "calibrateDate" << date << endl;
	cout << "cameraMatrix2" << cameraMatrix2 << endl;
	cout << "distCoeffs2" << distCoeffs2 << endl;

	FileNode features = fs_2["features"];
	FileNodeIterator it = features.begin(), it_end = features.end();
	int idx = 0;
	std::vector<uchar> lbqval;

	//使用FileNodeIterator遍历序列
	for (; it !=it_end; it++,idx++)
	{
		cout << "features #" << idx << ":";
		cout << "x=" << (int)(*it)["x"] << ",y=" << (int)(*it)["y"]
			<< ",lbp:(";
		//还可以使用filenode>>std::vector操作符来很容易的读数值阵列
		(*it)["lbp"] >> lbqval;
		for (size_t i = 0; i < (int)lbqval.size(); i++)
		{
			cout << "" << (int)lbqval[i];
			cout << ")" << endl;

		}
	}
	
	fs_2.release();
	printf("\n文件读取完毕,请输入任意键结束程序");
	system("pause");
	return;
}

//............待续
int main()
{
	test_XML_YAML_write();
	test_XML_YAML_read();
}