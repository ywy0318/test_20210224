/*
10.2.1--Shi---Tomasi角点检测概述
除了利用Harris进行角点检测之外,通常还可以利用Shi-Tomasi方法进行角点检测;
Shi-Tomasi算法是Harris算法的改进,此算法最原始的定义是将矩阵M的行列式与M
的迹相减,再将插值同预先给定的阈值进行比较;后来Shi-Tomasi提出了改进算法,
若两个特征值中较小的一个大于最小阈值,则会得到强角点;

确定图像强角点:googFeatureToTrack()函数
C++:void goodFeatureToTrack(InputArray image,OutputArray corners,int maxCorners,
double qualityLevel,double  minDistance,InputArray mask=noArray(),int blockSize=3,
bool useHarrisDetector=false,double k=0.4)

第一个参数:InputArray类型的image,输入图像,须为8位或者浮点型32为的单通道图像
第二个参数:OutputArray类型的corners,检测到的角点的输出向量;
第三个参数,int类型的maxCorners,角点的最大数量;
第四个参数:double类型的qualityLevel,角点检测可接受的最小特征值;
实际用于过滤角点的最小特征值是qualityLeval与图像中最大特征值的乘积;
所以qualityLevel通常不会超过1(常用值为0.1或者0.01)，
而检测完所有的角点后,还要进一步剔除一些距离较近的角点;

第五个参数:double类型的minDistance,角点之间的最小距离,此参数用于
保证返回的角点之间的距离不小于minDistance个像素;
第六个参数:InputArray类型的mask,可选参数,表示感兴趣区域,有默认值
noArray(),若此参数非空(需要为CV_8UC1类型,且和第一个参数image有相同
的尺寸,),便用于指定角点检测区域;
第七个参数:int类型的blockSize,有默认值3,是计算导数自相关矩阵时,指定的邻域
范围;
第八个参数:bool类型的useHarrisDector,默认值为false,指示是否使用harris
角点检测;
第九个参数:double类型的k,有默认值0.04,为用于设置Hessian自相关矩阵行列式
的相对权重的权重系数;

goodFeatureToTrack函数可用来初始化一个基于点的对象跟踪操作;

//综合示例:Shi--Tomasi角点检测

*/


#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int g_maxCornerNumber = 33;
int g_maxTrackBarNumber = 500;
RNG g_rng(12345);
void on_good_feature_to_track(int,void*);
int main()
{

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
	namedWindow("Shi_Tomasi", WINDOW_AUTOSIZE);
	createTrackbar("最大角点数:","Shi_Tomasi",&g_maxCornerNumber,g_maxTrackBarNumber, on_good_feature_to_track);
	on_good_feature_to_track(0,0);
	imshow("Shi_Tomasi",src_img);
	waitKey(0);
	return 0;
}
void on_good_feature_to_track(int, void*)
{
	//对变量小于等于1时的处理
	if (g_maxCornerNumber<=1)
	{
		g_maxCornerNumber = 1;
	}
	//Shi-Tomasi算法(goodFeatureTotrack函数)的参数准备
	vector<Point2f> corners;
	double qualityLevel = 0.01;//角点检测可接受的最小特征值
	double minDistance = 10;//角点之间的最小距离
	int blockSize = 3;//计算导数自相关矩阵时指定的邻域范围
	double k = 0.04;//权重系数
	Mat copy = src_img.clone();//复制源图像到一个临时变量中,作为感兴趣区域
	//Shi-Tomasi角点检测
	//检测到的角点的输出向量
	//角点的最大数量
	//角点检测可接受的最小特征值
	//角点之间最小的距离
	//感兴趣区域
	//计算导数自相关矩阵时的邻域范围
	//不使用harrsi角点检测
	goodFeaturesToTrack(gray_img,corners,g_maxCornerNumber,qualityLevel,minDistance,Mat(),blockSize,false,k);

	//输出文字信息
	cout << ">此次检测到的角点数量为:" << corners.size() << endl;
	//绘制检测到的角点
	int r = 4;
	for (size_t i = 0; i < corners.size(); i++)
	{
		//以随机的颜色绘制出角点
		circle(copy,corners[i],r,Scalar(g_rng.uniform(0,255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)),-1,8,0);
	}
	imshow("Shi_Tomasi",copy);
}