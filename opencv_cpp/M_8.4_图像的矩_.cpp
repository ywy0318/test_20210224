/*
8.4图像的矩
矩函数在图像分析中有着广泛的应用;如模式识别,
目标分类,目标识别与方位估计,图像编码与重构;

一个从一幅数字图形中计算出来的矩集,通常描述了
该图像形状的全局特征;并提供了大量的关于该图像的不同类型的
集合特性信息,比如大小,位置,方向及形状;

图像矩的这种特性描述能力被广泛的应用在各种图像处理,
计算机视觉和机器人技术领域的目标识别与方位估计中;
一阶矩与形状有关;
二阶矩显示曲线围绕直线平均值的扩展程度;
三阶矩则是关于平均值的对称性的测量;

二阶矩和三阶矩可以到处一组共7个不变矩;
而不变矩是图像的统计特性,满足平移,伸缩，旋转均不变
的不变性在图像识别领域得到广泛的应用;

一般由moments,contourArea,arcLength三个函数配合求取;
使用moments计算图像所有的矩(最高到三阶);
使用contourArea来计算轮廓面积;
使用arcLength来计算轮廓或曲线长度;


矩的计算:moments()函数
moments()函数用于计算多边形和光栅形状的最高达三阶的所有矩;
矩用来计算形状的重心,面积,主轴和其他形状特征;如7Hu不变量等;
C++:Moments moments(InputArray array,bool binaryImage=false)
第一个参数:可以是光栅图像(单通道,8位或浮点的二维数组)或二维数组(1N或N1);
第二个参数:bool类型的binaryImage,有默认值false,若此参数取true,
则返回所有非零像素为1,此参数仅对图像使用; 
此函数的返回值返回运行后的结果

计算轮廓面积:contourArea()函数
contourArea()函数用于计算整个轮廓或部分轮廓的面积
C++:double contourArea(InputArray contour,bool oriented=false)
第一个参数:InputArray 类型的contour,输入的变量,二维点(轮廓点),
可以为std::vector或Mat类型
第二个参数:bool类型的oriented,面向区域标识符;若其为true,该函数返回一个带符号
的面积值,其正负取决于轮廓的方向(顺时针还是逆时针);
根据这个特性我们可以根据面积的符号来确定轮廓的位置,需要注意的是,
这个参数有默认值false,表示以绝对值返回,不带符号;

vector<Point> contour;
contour.push_back(Point2f(0,0));
contour.push_back(Point2f(10,0));
contour.push_back(Point2f(10,10));
contour.push_back(Point2f(5,4));

double area_0=contourArea(contour); 

vector<Point> approx;
approxPolyDP(contour,approx,5,true);
double area_1=contourArea(approx);

cout<<"area_0="<<area_0<<endl<<
	"area_1="<<area_1<<endl<<
	"approx poly vertices"<<approx.size()<<endl;

计算轮廓长度:arcLength()函数
arcLength()函数用于计算封闭轮廓的周长与曲线的长度
C++:double arcLength(InputArray curve,bool closed);
第二个参数:bool类型的closed,一个用于指示曲线是否封闭的标识符,
有默认值closed,表示曲线封闭;
 
*/

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;

int g_nThresh = 100;
int g_nthresh_max = 255;
RNG g_rng(12345);

vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;
void on_ThreshChange(int,void*);

int main()
{

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
	blur(gray_img,gray_img,Size(3,3));
	namedWindow("src_img",CV_WINDOW_AUTOSIZE);
	imshow("src_img", src_img);
	//创建滚动条并进行初始化
	createTrackbar("阈值:","src_img",&g_nThresh,g_nthresh_max,on_ThreshChange);
	on_ThreshChange(0,0);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
void on_ThreshChange(int,void*)
{
	//使用Canny检测边缘
	Canny(gray_img,edge_img,g_nThresh,g_nThresh*2,3);
	//找到轮廓
	findContours(edge_img,g_vContours,g_vHierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));
	//计算矩
	vector<Moments> mu(g_vContours.size());
	for (size_t i = 0; i < g_vContours.size(); i++)
	{
		mu[i] = moments(g_vContours[i],false);
	}
	//计算中心距
	vector<Point2f> mc(g_vContours.size());
	for (size_t i = 0; i < g_vContours.size(); i++)
	{
		mc[i] = Point2f(static_cast<float>(mu[i].m10/mu[i].m00),static_cast<float>(mu[i].m01 / mu[i].m00));
	}
	//绘制轮廓
	Mat draw_img = Mat::zeros(edge_img.size(), CV_8UC3);
	for (size_t i = 0; i < g_vContours.size(); i++)
	{
		//随机生成颜色值
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		//绘制外层和内层轮廓
		drawContours(draw_img, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
		//绘制圆
		circle(draw_img,mc[i],4,color,-1,8,0);
	}
	namedWindow("draw_img",CV_WINDOW_AUTOSIZE);
	imshow("draw_img", draw_img);

	printf("\t输出内容:面积和轮廓长度\n");
	for (size_t i = 0; i < g_vContours.size(); i++)
	{
		printf(">通过m00计算出轮廓[%d]的面积:(M_00)=%.2f\nOPENCV函数计算出来的面积=%.2f,长度:%.2f\n\n",i,mu[i].m00
		,contourArea(g_vContours[i]),arcLength(g_vContours[i],true));
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255),g_rng.uniform(0, 255));
		drawContours(draw_img,g_vContours,i,color,2,8,g_vHierarchy,0,Point() );
		circle(draw_img, mc[i], 4, color, -1, 8, 0);
	}
}