#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;

/*
使用r矩阵的定义,需要注意的是,可以通过用randu()函数来产生的随机值来填充矩阵,
需要给定一个上限和一个下限来确保随机值在期望的范围内;
*/



int main(int argc, char* argv[])
{
	Mat img, resimg;//mat是opencv基本的数据结构，定义一个图像矩阵类型
					//--1--双右斜线法
	string imgpath0 = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	//--2--双左斜线法
	string imgpath1 = "E://Visual Studio 2010//Projects//opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--3--单左斜线法
	string imgpath2 = "E:/Visual Studio 2010/Projects/opencv_2018_12_21/opencv_2018_12_21/1.jpg";
	//--4--以上三种混合
	string imgpath3 = "E:/Visual Studio 2010//Projects\\opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--5--相对路径法
	string imgpath4 = "1.jpg";
	//--6--命令行参数法
	//string imgpath5 = argv[1];

	Mat r = Mat(10, 3, CV_8UC3);
	randu(r,Scalar::all(0),Scalar::all(255));//对矩阵的初始化
	//opencv默认风格输出
	cout << "r(opencv默认风格)=" << r << ";" << endl << endl;

	//python3风格的输出方式
	cout << "r(python)=" << format(r, Formatter::FMT_PYTHON) << ";" << endl << endl;

	//逗号分隔风格(CSV)
	cout << "r=(逗号分隔风格)=" << format(r, Formatter::FMT_CSV) << ";" << endl << endl;

	//numpy风格
	cout << "r(numpy风格)=" << format(r, Formatter::FMT_NUMPY) << endl << ";" << endl << endl;


	//C语言风格
	cout << "r(C语言风格)=" << format(r, Formatter::FMT_C) << ";" << endl << endl;

	while (true)
	{

	}

	img = imread(imgpath4, 1);//读入图片数据
	if (img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}




	//cout<<img.
	cout << " open or find the img" << endl;
	cout << "img.channels：" << img.channels() << endl;
	
	cout << "img.elemSize:" << img.elemSize() << endl;
	cout << "img.type:" << img.type() << endl;
	cout << "img.depth:" << img.depth() << endl;
	cout << "img.step1:" << img.step1() << endl;

	namedWindow("IMG", WINDOW_AUTOSIZE);//创建一个窗口
	imshow("IMG", img);
	/* 翻转模式，flipCode == 0垂直翻转（沿X轴翻转），
	flipCode>0水平翻转（沿Y轴翻转），
	flipCode<0水平垂直翻转（先沿X轴翻转，再沿Y轴翻转，等价于旋转180°） */
	flip(img, resimg, 1);

	

	namedWindow("水平翻转", WINDOW_AUTOSIZE);
	imshow("水平翻转", resimg);

	flip(img, resimg, 0);
	namedWindow("垂直翻转", WINDOW_AUTOSIZE);
	imshow("垂直翻转", resimg);

	flip(img, resimg, -1);
	namedWindow("水平垂直翻转", WINDOW_AUTOSIZE);
	imshow("水平垂直翻转", resimg);

	waitKey(0);
	system("pause");
	return 0;
}