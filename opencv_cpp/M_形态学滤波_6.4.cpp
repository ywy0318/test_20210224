/*
6.4形态学滤波(2):开运算，闭运算，形态学梯度，顶帽,黑帽,
膨胀和腐蚀是最基本的形态学操作，可以实现更高级的形态学变换;
高级的形态学都是建立在腐蚀和膨胀基础上的;

开运算(Opening Operation),其实就是先腐蚀后膨胀的过程;
dst=open(src,element)=dilate(erode(src,element))
开运算可以用消除小物体，在纤细点处分离物体，并且在平滑较大物体的
边界的同时不改变其面积

闭运算:线膨胀后腐蚀的过程称为闭运算(Closing Operation);
dst=clese(src,element)=erode(dilate(src,element));
闭运算能够排除小型黑洞(黑色区域);

形态学梯度(Morphological Gradient)是膨胀图与腐蚀图之差,
dst=morph-grad(src,element)=dilate(src,element)-erode(src,element);
对二值图像进行这一操作，可以将团块(blob)的边缘突出出来，用形态学梯度来保留物体
的边缘轮廓;

顶帽运算(Top Hat)又被称为"礼帽"运算,
顶帽运算:是原图像与开运素的结果图之差,
dst=tophat(src,element)=src-open(src,element)
开运算带来的结果是放大了裂缝或者局部低亮度的区域,
因此，从原图中减去开运算后的图，得到的效果图突出了比原图
轮廓周围的区域更明亮的区域，这一次操作与选择的核的大小相关;

顶帽运算往往用来分离比临近点亮一些的斑点,在一幅图像具有
大幅的背景，而微小物品比较有规律的情况下，可以使用
顶帽运算进行背景提取;

黑帽(Black Hat)运算是闭运算的结果图与原图像之差,
dst=blackhat(src,element)=close(src,element)-src
黑帽运算后的效果图突出了比原图轮廓周围的区域更暗的区域，
这一操作和选择的核的大小相关;

morphologyEx函数利用基本的膨胀和腐蚀技术，来执行更加高级形态学变换;
这些操作可以进行就地操作(in-place)操作，对于多通道图像，每一个通道都
单独进行操作;
morphologyEx:还可以实现腐蚀和膨胀操作;
C++:void morphologyEx(
InputArray src,
OutputArray dst,
int op,
InputArray kernel,
Point anchor=Point(-1,-1),
intiterations=1,
intborderType=BORDER_CONSTANT,
const Scalar& borderValue=morphologyDefaultBorderValue());

第三个参数:int类型的op,表示形态学运算的类型,
MORPH_OPEN  开运算
MORPH_CLOSE 闭运算
MORPH_GRADIENT 形态学梯度
MORPH_TOPHAT 顶帽
MORPH_BLACKHAT 黑帽
MORPH_ERODE    腐蚀
MORPH_DILATE   膨胀
第四个参数:InputArray类型的kernel,形态学运算的内核,若为NULL,
表示的是使用参考点位于中心3X3的核,一般使用函数
getStructuringElement配合这个参数的使用
第六个参数:int类型的iterations,迭代使用函数的次数，默认值为1;
*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, edge; 
int g_nElementShape = MORPH_RECT;//元素结构的形状

//接收TrcakBar位置参数
int g_nMaxIterationNum = 10;

int g_nOpenCloseNum = 10;
int g_nErodeDilateNum = 10;
int g_nTopBlackHatNum = 10;

void on_OpenClose(int, void*);//回调函数
void on_ErodeDilate(int ,void*);
void on_TopBlackHat(int,void*);

int main()
{
	
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img",1);
	imshow("src_img",src_img);

	namedWindow("开运算闭运算", 1);
	namedWindow("腐蚀膨胀", 1);
	namedWindow("顶帽黑帽", 1);

	//分别为三个窗口创建滚动条
	createTrackbar("迭代值", "开运算闭运算", &g_nOpenCloseNum, g_nMaxIterationNum * 2 + 1, on_OpenClose);
	createTrackbar("迭代值", "腐蚀膨胀", &g_nErodeDilateNum, g_nMaxIterationNum * 2 + 1, on_ErodeDilate);
	createTrackbar("迭代值", "顶帽黑帽", &g_nTopBlackHatNum, g_nMaxIterationNum * 2 + 1, on_TopBlackHat);
	
	while (true)
	{
		int c;
		on_OpenClose(g_nOpenCloseNum,0);
		on_ErodeDilate(g_nErodeDilateNum,0);
		on_TopBlackHat(g_nTopBlackHatNum,0);
		//获取按键
		c = waitKey(0);
		//按下Q键或者ECS,程序退出
		if ((char)c=='q'||(char)c==27)
		{
			break;
		}
		//按下键盘1，使用椭圆(Elliptic)结构元素MORPH_ELLIPSE
		if ((char)c==49)
		{
			g_nElementShape = MORPH_ELLIPSE;
		}
		//50矩形 按下2
		else if((char)c == 50)
		{
			g_nElementShape = MORPH_RECT;
		}
		//51矩形 按下3
		else if ((char)c == 51)
		{
			g_nElementShape = MORPH_CROSS;
		}
		//空格键,在矩形,椭圆，十字形中循环
		else if ((char)c == ' ')
		{
			g_nElementShape = (g_nElementShape+1)%3;
		}

	}
	//定义核
	//Mat element = getStructuringElement(MORPH_RECT,Size(15,15));

	//进行形态学操作--如果要选取其他形态学的操作，只需要改变第三个参数
	//--MORPH_OPEN--MORPH_CLOSE--MORPH_GRADIENT--MORPH_TOPHAT--MORPH_BLACKHAT--MORPH_ERODE--MORPH_DILATE
	//morphologyEx(src_img,dst_img, MORPH_DILATE,element);
	//imshow("dst_img", dst_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}

void on_OpenClose(int, void*)
{
	//偏移量的定义
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;

	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));

	if (offset<0)
	{
		morphologyEx(src_img,dst_img,MORPH_OPEN,element);
	}
	else
	{
		morphologyEx(src_img, dst_img, MORPH_CLOSE, element);
	}
	imshow("开运算闭运算",dst_img);
}

void on_ErodeDilate(int, void*)
{
	//偏移量的定义
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;

	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));

	if (offset<0)
	{
		//morphologyEx(src_img, dst_img, MORPH_TOPHAT, element);
		erode(src_img,dst_img,element);
	}
	else
	{
		//morphologyEx(src_img, dst_img, MORPH_BLACKHAT, element);
		dilate(src_img,dst_img,element);
	}
	imshow("腐蚀膨胀", dst_img);
}

void on_TopBlackHat(int, void*)
{
	//偏移量的定义
	int offset = g_nTopBlackHatNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;

	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));

	if (offset<0)
	{
		morphologyEx(src_img, dst_img, MORPH_TOPHAT, element);
	}
	else
	{
		morphologyEx(src_img, dst_img, MORPH_BLACKHAT, element);
	}
	imshow("顶帽黑帽", dst_img);
}