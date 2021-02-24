/*
5.3.1通道分离:split()函数
split函数用于将一个多通道数组分离成几个单通道数组,
C++版本的函数原型
void split(const Mat&src,Mat*mvbegin);
void split(InputArray m,OutputArrayOfArray  mv);
第一个参数:InputArray类型的m或者const Mat&类型的src,
填我们需要进行分离的多通道数组
第二个参数:OutputArrayOfArrays类型的mv,填函数的输出数组
或者输出的vector容器;
split函数分割多通道数组转换成独立的单通道数组
mv[c](I)=src(I)c;
5.3.2通道合并:merge()函数
merge()函数是split()函数的逆向操作---将多个数组合并成一个多通道的数组;
它通过组合一些给定的单通道数组,将这些鼓励的单通道数组合并成一个多通道的
数组,从而创建出一个由多通达阵列组成的多通道阵列;

void merge(const Mat*mv,size_t count,OutputArray dst)
void merge(InputArrayOfArrays mv,OutputArray dst)
第一个参数:mv;填需要被合并的输入矩阵或vector容器的阵列;
这个mv参数中所有的阵列必须有着一样的尺寸和深度;
第二个参数,count;当mv为一个空白C数组时,代表输入矩阵的个数,这个参数显然大于1;
第三个参数,dst;即输出阵列;和mv[0]拥有一样的尺寸和深度,并且通道的数量
是矩阵阵列中通道的总数;
merge函数的功能是将一些数组合并成一个多通道的数组;
输出阵列中的每一个元素都是输出数组的串接;
第i个输入数组的元素mv[i],
C一般用其中的Mat::at()方法来对某个通道进行存取;
channels.at(0);
Mat::at()方法返回一个引用到指定的数组元素;
相当于两者等价;
如果需要从多通道数组中提取特定的单通道数组,或者要实现一些复杂的通道组合,
可以使用mixChannels()函数

*/



#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
//opencv进行canny边缘检测
//载入图像,转换为灰度图,blur进行图像模糊降噪，然后用canny进行边缘检测

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
	string imgpath5 = "lena.jpg";
	//--6--命令行参数法
	//string imgpath5 = argv[1];
	//mat是opencv基本的数据结构，定义一个图像矩阵类型
	Mat src_img, des_img, gray_img, edge,src_img_1;
	vector<Mat> channels;
	vector<Mat> channels_1;
	vector<Mat> channels_2;
	Mat image_blue_channel;
	Mat image_green_channel;
	Mat image_red_channel;
	
	src_img = imread(imgpath5, 1);//读入图片数据
	des_img = imread(imgpath5, 1);//读入图片数据
	gray_img = imread(imgpath5, 1);//读入图片数据
	edge = imread(imgpath5, 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	src_img_1 = imread("2.jpg", 0);//读入图片数据,flag=0;表示读入灰度图像
	if (src_img_1.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}

	//把一个三通道图像转换成3个单通道图像
	split(src_img, channels);//分离色彩通道
	split(src_img, channels_1);//分离色彩通道
	split(src_img, channels_2);//分离色彩通道
	 image_blue_channel= channels.at(0);
	 image_green_channel = channels_1.at(1);
	 image_red_channel = channels_2.at(2);

	 addWeighted(image_blue_channel(Rect(0,0, src_img.cols,src_img.rows)),1.0, src_img_1,0.5,0.0,
		 image_blue_channel(Rect(0, 0, src_img.cols, src_img.rows)));

	 merge(channels, src_img);

	 addWeighted(image_green_channel(Rect(0, 0, src_img.cols, src_img.rows)), 1.0, src_img_1, 0.5, 0.0,
		 image_green_channel(Rect(0, 0, src_img.cols, src_img.rows)));

	 merge(channels_1, des_img);

	 addWeighted(image_red_channel(Rect(0, 0, src_img.cols, src_img.rows)), 1.0, src_img_1, 0.5, 0.0,
		 image_red_channel(Rect(0, 0, src_img.cols, src_img.rows)));
	 merge(channels_2, gray_img);

	 imshow("src_img_blue", src_img);
	 imshow("src_img_green", des_img);
	 imshow("src_img_red", gray_img);
	 //imshow("image_blue_channel", image_blue_channel);

	 imshow("src", imread(imgpath5, 1));
	 
	 //gray_img(Rect(0,0,src_img.cols/2,src_img.rows/2)));
	//des_img = channels.at(2);
	//imshow("des_img before addWeighted", des_img);
	//addWeighted(des_img(Rect(0,0, src_img.cols,src_img.rows)),1.0, src_img,0.5,0.0,gray_img);
		//gray_img(Rect(0,0,src_img.cols/2,src_img.rows/2)));
	//merge(channels, edge);
	//namedWindow("sample");
	
	//imshow("des_img(Rect", des_img(Rect(0, 0, src_img.cols/2, src_img.rows/2 )));
	//imshow("des_img", edge);
	//imshow("srcimg", src_img);
	//imshow("srcimg", gray_img);
	//创建跟src_img同类型和大小的矩阵
	//des_img.create(src_img.size(), src_img.type());


	//将原始图像转换为灰度图像
	//opencv2版本
	//cvtColor(src_img, gray_img, CV_BGR2GRAY);


	//opencv3版本
	//cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
	//使用3x3内核来降噪
	//blur(gray_img, edge, Size(3, 3));

	//getStructuringElement的返回值是指定形状，指定尺寸的内和矩阵
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//erode(src_img, des_img, element);

	//Canny算子
	//Canny(edge, edge, 3, 9, 3);

	//imshow("after erode", edge);

	waitKey(0);
	system("pause");
	return 0;
}