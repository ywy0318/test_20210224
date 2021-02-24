/*
!!!!!!!!!!待续有问题
角点检测(Corner Detection)是计算机视觉系统中用来获取图像特诊搞得一种方法;
广泛应用于运动检测,图像匹配,视觉跟踪,三维建模和目标识别等领域中,
也称之为特征点检测

角点通常被定义为两条边的交点,角点的局部邻域应该具有两个不同邻域的不同方向的边界;
实际应用中,大多数所谓的角点检测方法检测的是拥有特定的图像点,而不仅仅是角点;
这些特征点在图像中有具体的坐标，并且具有某些数学特征,如局部最大或者最小灰度,
某些梯度特征;

兴趣点(interest points)也被称作关键点(key points),特征点(feature points)
它被大量用于解决物体识别,图像识别,图像匹配,视觉跟踪,三维重建,等一系列问题;


图像特征类型可以被分为如下三种:
1.>边缘
2.>角点(感兴趣关键点)
3.>斑点(Blobs)(感兴趣区域)

如果某一点在任意方向的一个微小变动都会引起灰度很大的变化,那么我们把它称之为角点;
角点作为图像上的特征点,包含有重要的信息,在图像融合和目标跟踪及三维重建中
有重要的应用价值;

角点位于两条边缘的交点处,代表了两个边缘变化的方向上的点,
它们是可以精确定位的二维特征,甚至达到亚像素的精度; 
由于其图像梯度有很高的变化,这种变化是可以用来帮助检测角点的;
角点与位于相同强度区域上的点不同,与物体轮廓上的点也不同,因为
轮廓点难以在相同的其他物体上精确定位;

角点的描述有一下几种:
一阶导数(即灰度的梯度)的局部最大所对应的的像素点;
两条及两条以上边缘的交点;
图像中的梯度值和梯度方向的变化速率都很高的点;
角点处的一阶导数最大,二阶导数为0,指示了物体边缘变化不连续的方向;

10.1.2角点检测
现在的角点检测算法并不是十分的健壮;很多方法都要求有大量的训练集
和冗余数据来防止或减少错误特征的出现;
另外,角点检测方法的一个很重要的评价标准是其对多幅图像中相同
或相似特征的检测能力,并且能够应该光照变化,图像旋转等图像变化;

在当前的图像处理领域,角点检测算法可以归纳为以下三类:
1.>基于灰度图像的角点检测
2.>基于二值图像的角点检测
3.>基于轮廓曲线的角点检测


基于灰度图像的角点检测又可分为基于梯度,
基于模板和基于模板梯度组合三类方法;

基于模板的方法主要考虑像素领域点的灰度变化即图像亮度
的变化,将与邻点亮度对比足够大的点定义为角点;
常见的基于模板的角点检测的算法有:
Kitchen-Rosenfeld角点检测算法,Harris角点检测算法,
KLT角点检测算法及SUSAN角点检测算法;

10.1.3 harris角点检测
harris角点检测是一种直接基于灰度图像的角点提取算法,稳定性高,
尤其对L型角点检测精度高;但是由于采用了高斯滤波,运行速度相对较慢,
角点信息有丢失和位置偏移的现象,而且角点提取有聚簇现象;

10.1.4实现Harris角点检测:cornerHarris()函数
cornerHarris函数用于在OpenCV中运行Harris角点检测算子
来进行角点检测;
和cornerMineigenVal()以及cornerEigenValsandVecs()函数
类似,cornerHarris函数对于每一个像素点(x,y)在blockSize*blockSize
邻域内,计算2*2梯度的协方差矩阵M(x,y),接着它记下如下式子:

dst(x,y)=detM(x,y)-k*(trM(x,y))^2;
就可以找出输出图中的局部最大值,即找出了角点

C++:void cornerHarris(InputArray src,OutputArray dst,int blockSize,int ksize,double k,
int borderType=BORDER_DEFAULT)

第一个参数:InputArray类型的src,输入图像,即源图像,填Mat类的对象即可,且须为单通道8位或者浮点型图像;
第二个参数:OutputArray类型的dst,函数调用后的运算结果保存在这里,即这个参数用于存放harris角点检测
的输出结果,和源图片有一样的尺寸和类型;
第三个参数:int类型的blockSize,表示邻域的大小,更多的详细信息在cornerEigenValsAndVecs()中有讲;
第四个参数:int类型的ksize,表示Sobel()算子的孔径大小
第五个参数:double类型的k,Harris参数
第六个参数:int类型的borderType,图像像素的边界模式;注意它有默认值BORDER_DEFAULT;

*/

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img,normalize_img,scaled_img;

int thresh = 30;
int thresh_max = 175;

void on_cornerHarris(int ,void*);

void cornerHarris_1()
{
	//进行Harris角点检测找出角点
	Mat cornerStrength;
	cornerHarris(src_img,cornerStrength,2,3,0.01);
	//对灰度图进行阈值操作,得到二值图并显示
	Mat harrisCorner;
	threshold(cornerStrength,harrisCorner,0.00001,255,THRESH_BINARY);
	imshow("src_img",src_img);
	imshow("harrisCorner", harrisCorner);
	waitKey(0);
}

void cornerHarris_2()
{
	imshow("src_img", src_img);
	temp_img = src_img.clone();
	//保留一张灰度图
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
	
	createTrackbar("阈值:","on_cornerHarris",&thresh,thresh_max,on_cornerHarris);
	on_cornerHarris(0,0);
	//namedWindow("on_cornerHarris", WINDOW_AUTOSIZE);
	waitKey(0);
	return;
}
void on_cornerHarris(int, void*)
{
	dst_img = Mat::zeros(src_img.size(),CV_32FC1);
	edge_img = src_img.clone();

	//正式检测
	cornerHarris(gray_img,dst_img,2,3,0.04,BORDER_DEFAULT);
	//归一化与转换
	normalize(dst_img, normalize_img,0,255,NORM_MINMAX,CV_32FC1,Mat());
	convertScaleAbs(normalize_img, scaled_img);

	//将检测到的,且符合阈值条件的角点绘制出来
	for (size_t j = 0; j < normalize_img.rows; j++)
	{
		for (int i = 0; i < normalize_img.cols; i++)
		{
			if ((int)normalize_img.at<float>(j,i)>thresh+80)
			{
				circle(temp_img, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(scaled_img, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
			}
		}
	}
	imshow("on_cornerHarris",temp_img);
	imshow("scaled_img",scaled_img);
}
int main()
{
	//src_img = imread("1.jpg", 0);//读入图片数据
	src_img = imread("lena.jpg", 0);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//cornerHarris_1();
	cornerHarris_2();
	//imshow("src_img", src_img);
	//waitKey(0);
	system("pause");
	return 0;
}