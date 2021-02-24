/*
SURF,英文全称:SpeededUp Robust Features,加速版的具有鲁棒性的特征算法;
SURF是尺寸不变特征变换算法(SIFT)的加速版;
一般来说,标准SURF算子比SIFT算子快好几倍,并且在多幅图片下具有
更好的稳定性;SURF最大的特征在于采用了harr特征以及积分图像的概念,
这打大加快了程序的运行时间;
SURF可以应用于计算机视觉的物体识别及3D重构中;

11.1.2SURF算法原理


11.1.4绘制关键点:drawKeyPoints()函数
C++:void drawKeyPoints(const Mat&image,const vector<KeyPoint>&keypoints,
Mat&outImage,const Scalar& color=Scalar::all(-1),int flags=DrawMatchesFlags::DEFAULT)

第一个参数:const Mat&类型的src,输入图像
第二个参数:const vector<KeyPoint>&类型的keypoints,根据源图像得到的特征点,它是一个输出参数;
第三个参数:Mat&类型的outImage,输出图像,其内容取决于第五个参数标识符flags;
第四个参数:const Scalar&类型的color,关键点的颜色,默认值Scalar::all(-1);
第五个参数:int类型的flags,绘制关键点的特征标识符,默认值DrawMatchesFlags::DEFAULT;

struct DrawMatchesFlags
{
	enum
	{
		DEFAULT=0;//创建输出图像矩阵(使用Mat::create);//使用现存的输出图像绘制
		匹配对和特征点;且对每一个关键点,只绘制中间点;
		DRAW_OVER_OUTIMG=1;//不创建输出图像矩阵,而是在输出图像上绘制匹配对
		NOT_DRAW_SINGLE_POINTS=2;//单点特征点不被绘制
		DRAW_RICH_KEYPOINTS=4;//对每一个关键点,绘制带大小和方向的关键点圆圈;
	};
};

KeyPoint类
KeyPoint类是一个为特征点检测而生的数据结构,用于表示特征点;
class KeyPoint
{
	Point2f pt;//坐标
	float size;//特征点邻域直径
	float angle;//特征点的方向,值为[0,360],负值表示不使用
	float response;
	int octave;//特征点所在的图像金字塔的组;
	int class_id;//用于聚类的id;
}


*/

/*
示例程序:SURF特征点检测
1.>使用FeatureDetector接口来发现感兴趣点;
2.>使用SurfFeatureDetector以及其函数detector来实现检测过程;
3.>使用函数drawKeypoints绘制检测到的关键点;
D:\opencv\opencv_2413\opencv\build\include\opencv2\nonfree
*/
#include<iostream>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/nonfree/>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int main()
{
	system("color 2F");
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	temp_img = imread("lena_2.jpg", 1);//读入图片数据
	if (temp_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("temp_img", temp_img);
	//定义需要用到的变量和类
	int minHessian = 400;//定义SURF中hessian阈值特征点检测算子
	SurfFea

}