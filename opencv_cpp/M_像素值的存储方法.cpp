#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;

/*

二值就是只有黑和白，灰度就是有不同深度的灰色和黑白两色，彩色就是彩色啦。
区别就是可以表现的东西，二值只能表现两种颜色，灰度可以表现不同深度的灰色，就像素描，
彩色就可以表现大部分东西了。占用空间二值最小，灰度其次，彩色最多。

如何存储像素值:
存储像素值需要指定颜色空间和数据类型;
颜色空间是指针对一个给定的颜色,如何组合颜色元素以对其编码,
最简单的颜色空间，要属于灰度级空间，只处理黑色和白色,对他们进行组合就可以产生不同程度的灰色;

彩色方式则有更多种类的颜色空间,不论哪种方式,都是把颜色分成三个元素或者四个元素,
通过组合基本元素就可以产生所有的颜色;
RGB颜色空间是最常用的一种颜色空间,它也是人眼内部构成颜色的,
有时候为了表示透明颜色也会加入第四个元素alpha(A);

RGB是最常见的,和人眼采用相似的工作机制,被显示设备所采用
HSV和HLS把颜色分解成色调,饱和度和亮度/明度,这是颜色更自然的描述方式
比如可以通过抛弃最后一个元素,使算法对输入图像的光照条件不敏感

YCrCb在JPEG图像格式中广泛使用
CIE L*a*b是一种在感知上均匀的颜色空间,它适合用来度量两个颜色之间的距离
每个组成元素都有其自己的定义域,而定义域取决于其数据类型,如何存储一个元素决定了
我们在其定义域上能够控制的精度;
增加元素的尺寸也会增加图像所占的内存空间

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

	Mat src_img, des_img;//mat是opencv基本的数据结构，定义一个图像矩阵类型

	src_img = imread(imgpath4, 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
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