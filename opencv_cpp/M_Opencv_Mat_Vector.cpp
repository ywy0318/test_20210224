/*
OpenCV轮廓vector vector
轮廓周围绘制矩形框
vector<vector<Point>>,vector<Vec4i>,vector<Rect>,
vector<RotatedRect>


vector<vector<Point>>;vector容器里面放了一个vector容器,子容器里面放点;
vector<Vec4i>:放了4维int向量
vector<Rect>:像素width*height from位置(x,y)
vector<RotatedRect>:如图三个成员
angle:0 center:[0,0] size:[0*0]
angle:-88.4926 center:[119.147,237.399] size:[115.697*43.9322]

*/
/*
opencv中Mat 数据类型中data,size,depth,channels,elesize,rows,
cols等属性内涵

data:uchar类型的指针,指向Mat数据矩阵的首地址
dims:Mat矩阵的维度,若Mat是一个二维矩阵,则dims=2
三维则dims=3,大多数情况下处理的都是二维矩阵,是一个平面上
的矩阵
rows:Mat矩阵的行数
cols:Mat矩阵的列数
size():首先size是一个结构体,定义了Mat类型矩阵内数据的分布形式,
数值上有关系式:
image.size().width=image.cols;image.size().height=image.rows;
channels():
Mat矩阵元素拥有的通道数;例如:常见的RGB彩色图像,channels==3,而
灰度图像只有一个灰度分量信息,channels=1;
表示的是一个矩阵中的每个元素分别有几个值,例如一个4*3的矩阵,有12个
元素,每个元素如果有三个值,则此矩阵有三个通道,每个元素有四个值,则
此矩阵有四个通道;
depth:
用来度量每一个像素中每一个通道的精度,但它本身与图像的通道数无关;depth
数值越大,精度越高,在Opencv中Mat.depth()得到的事一个0-6的数字,
分别代表不同的位数;
enum{CV_8U=0,CV_8S=1,CV_16U=2,CV_16S=3,CV_32S=4,CV_32F=5,CV_64F=6}
其中U是unsigned的意思,S表示 signed,也就是有符号和无符号数;

eleSize:
表示矩阵中每一个元素的数据大小,
如果Mat中的数据类型是CV_8UC1,那么elemSize=1;
如果是CV_8UC3或者CV_8SC3,那么elemSize=3;
如果CV_16UC3或者CV_16SC3,那么elemSize==6;
即elemSize是以8位(一个字节)为一个单位,乘以通道数
和8位的整数倍;
elemSize1:
1可以认为是元素内一个通道的意思,这样从命名上拆分后就很容易解释
这个属性了;表示Mat矩阵中每一个元素单个通道的数据大小,以字节为
一个单位,所以eleSize1=elemSize/channels;
step:
Mat矩阵中每一行的"步长",以字节为基本单位,每一行中所有元素的字节总量,
累计了一行中所有元素,所有通道,所有通道的elemSize1之后的值;
step1():
以字节为基本单位,Mat矩阵中每一个像素的大小,累计了所有通道,
所有通道的elemSize1之后的值,所以有
step1=step/elemSize1;

type:
Mat矩阵的类型,包含有矩阵中元素的类型以及通道数信息,type的命名
格式为CV_(位数)+(数据类型)+(通道数),所有取值如下:
CV_8UC1,   
CV_8SC1,
CV_16UC1,
CV_16SC1,
CV_32SC1,
CV_32FC1,
CV_64FC1,

CV_8UC2,
CV_8SC2,
CV_16UC2,
CV_16SC2,
CV_32SC2,
CV_32FC2,
CV_64FC2,

CV_8UC3,
CV_8SC3,
CV_16UC3,
CV_16SC3,
CV_32SC3,
CV_32FC3,
CV_64FC3,

CV_8UC4,
CV_8SC4,
CV_16UC4,
CV_16SC4,
CV_32SC4,
CV_32FC4,
CV_64FC4,

各种画图片的函数,修改函数值的程序
*/


#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img,bin_out_img;

int test_vector()
{
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img",CV_WINDOW_AUTOSIZE);
	namedWindow("dst_img", CV_WINDOW_AUTOSIZE);
	imshow("src_img", src_img);

	cvtColor(src_img,gray_img,CV_BGR2GRAY);
	blur(gray_img,gray_img,Size(10,10),Point(-1,-1),BORDER_DEFAULT);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	threshold(gray_img,bin_out_img,144,255,0);
	findContours(bin_out_img,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

	vector<vector<Point>> contour_poly(contours.size());
	vector<Rect> poly_rects(contours.size());
	vector<RotatedRect> minRect(contours.size());
	//取点
	for (size_t i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]),contour_poly[i],3,true);//减少轮廓点数
		poly_rects[i] = boundingRect(contour_poly[i]);//获取绘制矩形数据
		if (contour_poly[i].size()>5)
		{
			minRect[i] = minAreaRect(contour_poly[i]);//获取会之旋转矩形数据
		}
	}
	//开始绘制
	src_img.copyTo(dst_img);
	Point2f pst[4];//存储单个旋转矩形的四个点
	cout << "-----Point2f pst[4]" << endl;

	for (size_t i = 0; i < contours.size(); i++)
	{
		rectangle(dst_img,poly_rects[i],Scalar(255,0,0),2,8);//绘制矩形框
		minRect[i].points(pst);//用线段画矩形,将RotatedRect类型转换为4个点 
		for (size_t u = 0; u < 4; u++)
		{
			line(dst_img, pst[u], pst[(u + 1) % 4], Scalar(0, 255, 0), 2, 8);
			cout << pst[u];//显示pst的数据
		}
		cout << endl;
		Rect brect = minRect[i].boundingRect();//返回包含旋转矩形的最小矩形
		rectangle(dst_img,brect,Scalar(0,0,255));
	}
	cout << endl;
	
	cout << "-----vector<vector<Point>>cotours_poly----" << endl;
	for (size_t i = 0; i < contour_poly.size(); i++)
	{
		cout << "第" << i << "行:";
		for (size_t j = 0; j < contour_poly[i].size(); j++)
		{
			cout << contour_poly[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << "---vector<Vec4i>-hierarchy---" << endl;
	for (size_t i = 0; i < hierarchy.size(); i++)
	{
		cout << hierarchy[i] << endl;
	}
	cout << endl;

	cout << "---vector<Rect> poly_rects---" << endl;
	for (size_t i = 0; i < poly_rects.size(); i++)
	{
		cout << poly_rects[i] << endl;
	}
	cout << endl;
	cout << "---vector <rotatedRect>- minRect---" << endl;
	for (size_t i = 0; i < minRect.size(); i++)
	{
		cout << "angle:" << minRect[i].angle << "center:" << minRect[i].center
			<< "size:" << minRect[i].size << endl;
	}
	cout << endl;
	imshow("dst_img", dst_img);
	waitKey(0);
	return 0;
}
int main()
{
	test_vector();
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}