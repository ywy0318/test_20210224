/*
10.3亚像素级角点检测
若进行图像处理的目的不是提取用于识别的特征点而是进行几何测量,
通常需要更高的精度,而函数goodFeatureTotrack()只能提供简单的像素的
坐标值,也就是,有时候会需要实数坐标值而不是整数坐标值;

亚像素角点检测的位置在摄像机标定,跟踪并重建摄像机轨迹,或者重建
被跟踪目标的三维结构时,是一个基本的测量值;

寻找亚像素角点:cornerSubPix()函数

cornerSubPix函数用于寻找亚像素点位置(不是整数类型的位置,而是更精确的浮点类型位置)
C++:void cornerSubPix(InputArray image,InputOutputArray corners,Size winSize,
size zeroZone,TermCriteria criteria)

第一个参数:InputArray 类型的image,输入图像,即源图像
第二个参数:InputOutputArray类型的corners,提供输入角点的初始坐标和精确的输出坐标;
第三个参数:Size类型的winSize,搜索窗口的一半尺寸;若winSize=Size(5,5),那么就表示
使用(5*2+1)*(5*2+1)=11*11大小的搜索窗口
第四个参数:Size类型的zeroZone,表示死区的一半尺寸;而死区为不对搜索区的中央位置做
求和运算的区域,用来避免自相关矩阵出现的某些可能的奇异性,值为(-1,-1)表示没有死区;
第五个参数:TermCriteria类型的Criteria,求角点的迭代过程的终止条件;
即角点位置的确定,要么迭代数目大于某个设定值,或者是精确度达到某个设定值;
criteria可以是最大迭代数目,或者是设定的精确度,也可以是他们的组合;


10.3.3综合示例:亚像素级角点检测
*/

/*
自己制作角点检测的函数,需要用到cornerMinEigenVal函数和minMaxLoc函数;
最后的特征点选取,判断条件要根据自己的情况编辑，
如果对特征点,角点的精度要求更高,可以用cornerSubPix函数将角点定位到子像素;

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
void on_good_feature_to_track(int, void*);
int main()
{

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
	namedWindow("Shi_Tomasi", WINDOW_AUTOSIZE);
	createTrackbar("最大角点数:", "Shi_Tomasi", &g_maxCornerNumber, g_maxTrackBarNumber, on_good_feature_to_track);
	on_good_feature_to_track(0, 0);
	imshow("Shi_Tomasi", src_img);
	waitKey(0);
	return 0;
}
void on_good_feature_to_track(int, void*)
{
	//对变量小于等于1时的处理
	if (g_maxCornerNumber <= 1)
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
	goodFeaturesToTrack(gray_img, corners, g_maxCornerNumber, qualityLevel, minDistance, Mat(), blockSize, false, k);

	//输出文字信息
	cout << ">此次检测到的角点数量为:" << corners.size() << endl;
	//绘制检测到的角点
	int r = 4;
	for (size_t i = 0; i < corners.size(); i++)
	{
		//以随机的颜色绘制出角点
		circle(copy, corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)), -1, 8, 0);
	}
	//显示窗口
	imshow("Shi_Tomasi", copy);

	//亚像素角点检测的参数设置
	Size winSize = Size(5,5);
	Size zeroZone = Size(-1, -1);
	//opencv2
	//TermCriteria criteria=TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,40,0.001);

	//opencv3
	TermCriteria criteria=TermCriteria(TermCriteria::EPS+TermCriteria::MAX_ITER,40,0.001);
	//计算出亚像素角点位置
	cornerSubPix(gray_img,corners,winSize,zeroZone,criteria);
	//输出角点信息
	for (size_t i = 0; i < corners.size(); i++)
	{
		cout << "\t>>精确角点坐标:[" << i << "](" << corners[i].x << "," << corners[i].y << ")" << endl;
	}
}