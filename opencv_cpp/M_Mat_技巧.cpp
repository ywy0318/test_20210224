#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
/*
imwrite()函数将一个矩阵写入图像文件中
Mat的运算符"<<"可以用来查看实际值,但是只对二维矩阵有效;
Mat不但是一个非常有用的图像容器类,也是一个通用的矩阵类,我们可以用它来创建和操作多维矩阵;

对于二维多通道图像,首先要定义其尺寸,即行数和列数;然后需要指定存储元素的数据类型及
每个矩阵点的通道数

CV_[The number of bits per item][signed or Unsigned][Type Prefix][The channel number]
即:CV_[位数][带符号与否][类型前缀]C[通道数]
CV_8UC3表示使用8位的unsigned char型,每个像素由三个元素组成三通道;
而预先定义的通道数可以多达4个;
Scalar是个short型的向量能够使用指定的定制化值来初始化矩阵,还可以用于表示颜色


*/
int main(int argc, char* argv[])
{
	
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

	//对小矩阵使用都好分割式初始化函数
	Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cout << "C=" << endl << "" << C << endl<<endl;

	//为已存在的对象创建新信息头
	//使用成员函数clone()或copyTo()为一个已存在的Mat对象创建一个新的信息头,
	Mat rowclone = C.row(1).clone();
	cout << "rowclone=" << endl << "" << rowclone << endl << endl;

	Mat E = Mat::eye(4, 4, CV_64F);
	cout << "E=" << "" << E << endl;

	Mat O = Mat::ones(2, 2, CV_32F);
	cout << "O=" << O << endl;

	Mat Z = Mat::zeros(3, 3, CV_8UC1);
	cout << "Z=" << Z << endl;

	Mat Ma;
	//利用Mat类中的Create()成员函数进行Mat类的初始化操作
	//此创建方法不能为矩阵设置初始值,只是在改变尺寸时,重新为矩阵数据开辟内存而已
	Ma.create(4,4,CV_8UC(2));
	cout << "Ma=" << endl << "" << Ma << endl << endl;

	//为已存在的IplImage指针创建信息头
	IplImage* img_11 = cvLoadImage("1.jpg",1);

	//Mat mtx(img_11);//转换IplImage*->Mat ---有问题

	int sz[3] = {2,2,2};
	Mat L(3,sz,CV_8UC3,Scalar::all(0));//<<不能输出三维的


	Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
	//cout << "M=" << M << endl;

	while (true)
	{

	}

	//mat是opencv基本的数据结构，定义一个图像矩阵类型
	Mat src_img, des_img;//******仅创建信息头部分
	src_img = imread(imgpath4, 1);//读入图片数据--//这里为矩阵开辟内存
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	Mat B(src_img);//使用拷贝构造函数

	des_img = src_img;//赋值运算符
	//以上三个Mat对象最终都指向同一个也是唯一一个数据矩阵，虽然他们的信息头不同,
	//但是通过任何一个对象所做的改变也会影响其他,实际上不同的对象只是访问相同数据的不同途径而已

	Mat D(src_img, Rect(10, 10, 100, 100));//使用矩形界定
	//Mat E = D(Range:all(), Range(1, 3)); // 用行和列来界定----有问题
	//Mat E = src_img(Range:all(), Range(1, 3));// 用行和列来界定
	//引申一下，创建只因用部分数据的头信息，比如想要创建一个感兴趣区域(ROI),
	//只需要创建包含边界信息的信息头;

	//由于矩阵属于多个Mat对象,当不再需要它的时候,最后一个使用它的对象负责清理数据矩阵;
	//具体实现是通过引用计数机制来实现的,当复制一个Mat对象的信息头的时候，就会增加矩阵的引用次数
	//当一个头被释放之后,这个计数器被减少,当计数器值为0的时候,矩阵会被清理;

	//复制矩阵本身(不只是信息头和矩阵指针),使用函数clone()或者copyTo()
	//F或者G就不会影响Mat信息头所指向的矩阵
	Mat F = src_img.clone();
	Mat G;
	src_img.copyTo(G);

	system("pause");

	/**********/

	imshow("srcimg", src_img);
	//getStructuringElement的返回值是指定形状，指定尺寸的内和矩阵
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//erode(src_img, des_img, element);

	//进行均值滤波操作
	blur(src_img, des_img, Size(15, 15));

	imshow("after blur", des_img);

	waitKey(0);
	system("pause");
	return 0;
}