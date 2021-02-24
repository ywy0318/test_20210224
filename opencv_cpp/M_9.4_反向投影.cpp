/*
9.4反向投影
一副图像的区域中显示的是一种结构纹理或者
一个独特的物体,那么这个区域的直方图可以看做一个概率函数,
其表现形式是某个像素属于该纹理或物体的概率;

反向投影(back projection)就是一种记录给定图像中的像素点
如何适应直方图模型像素分布方式的一种方法;

反向投影就是首先计算某一特征的直方图模型,然后使用模型去
寻找图像中存在的该特征的方法;

使用模型直方图(代表手掌的皮肤色调)来检测测试图中的皮肤区域;
检测步骤如下:
1.>对测试图像中的每个像素(p(i,j)),获取色调数据并找到该色调(Hij,sij)
在直方图中的bin的位置;
2.>查询模型直方图中对应bin的数值;
3.>将次数值存储在新的反射投影图像中;也可以先归一化直方图数值到0-255，
这样可以直接显示反射投影图像(单通道图像);
4.>通过对测试图像中的每个像素采取以上步骤,得到最终的反射投影图像;
5.>使用统计学的语言进行分析;反向投影中储存的数值代表了测试图像中
该像素属于皮肤区域的概率;
亮起的区域是皮肤区域的概率更大,更暗的区域则表示皮肤的概率更低;
手掌内部和边缘的阴影影响了检测的精度;

9.4.3反向投影的作用
反向投影用于在输入图像(通常较大)中查找与特定图像(通常较小或者
仅一个像素,以下称为模板图像)最匹配的点或者区域,也就是定位模板
图像出现在输入图像的位置;
9.4.4反向投影的结果
反向投影的结果包含了以每个输入图像像素点位起点的直方图对比结果;
可以把它看成是一个二维的浮点型数组,二维矩阵,或者单通道的浮点型图像;


计算反向投影:calcBackProject()函数
calcBackProject()函数用于计算直方图的反向投影

C++:void calcBackProject(
const Mat*images,
int nimages,
const int*channels,
InputArray hist,
OutputArray backProject,
const float**ranges,
double scale=1,
bool uniform=true
)
第一个参数:输入的数组或者数组集,数组集要有相同的深度和尺寸,通道数则任意;
第二个参数:int类型的nimages,输入数组的个数,也就是第一个参数中放了多少张"图像",
有几个原数组;
第三个参数:const int*类型的channels,需要统计的通道(dim)索引;第一个数组通道从
0到images[0].channels()-1,而第二个数组通道从images[0].channels()计算到
images[0].channels()+images[1].channels()-1;
第四个参数:InputArray类型的hist,输入的直方图;
第五个参数:OutputArray类型的backProject,目标反向投影阵列,需要为单通道,
并且和imags[0]有相同的大小和深度;
第六个参数:const float**类型的ranges,表示每一个维度数组(第六个参数dims)的每一维
的边界阵列,可以理解为每一维数值的取值范围;
第七个参数:double scale,默认值为1,输出的方向投影可选的缩放因子,默认为1;
第八个参数:bool类型的uniform,指示直方图是否均匀的标识符,默认值为true;

---------------
通道复制:
mixChannels()函数
此函数由输入参数复制某通道到输出参数特定的通道中;

C++:void mixChannels(const Mat*src,size_t nsrcs,Mat* dst,size_t ndsts,const int*fromTo);
第一个参数:输入的数组,有相同的尺寸和深度;
第二个参数:src输入的矩阵数
第三个参数:输出的数组,所有矩阵必须被初始化,且大小和深度必须与src[0]相同
第四个参数:第三个参数dst输入的矩阵数
第五个参数：对指定的通道进行赋值的数组索引
第六个参数:fromTo的索引数


C++:void minChannels(const vector<Mat>&src,vector<Mat>&dst,const int* fromTo,size_t npairs)

第一个参数:输入的矩阵向量,所有的矩阵必须有相同的尺寸和深度
第二个参数:输出的矩阵向量,所有矩阵需要被初始化,且大小和深度须与src[0]相同
第三个参数:对指定的通道进行复制的数组索引
第四个参数:fromTo的索引数

此函数为重排图像通道提供了比较先进的机制;之前接触到的
split()和merge(),以及cvtColor()的某些形式,都是mixChannels()的一部分;
*/

/*
将4通道的RGBA图像转换为三通道BGR(R通道和B通道交换),和一个单独的Alpha通道的图像;
Mat rgba(100,100,CV_8UC4,Scalar(1,2,3,4));
Mat bgr(rgba.rows,rgba.cols,CV_8UC3);
Mat alpha(rgba.rows,rgba.cols,CV_8UC1);

//组成数组矩阵来进行操作
Mat out[]={bgr,alpha};
//说明:rgba[0]->bgr[2],rgba[1]->bgr[1]
//说明:rgna[2]->bgr[0],rgba[3]->alpha[0]
int from_to[]={0,2,1,1,2,0,3,3};
mixChannels(&rgba,1,out,2,from_to,4);
*/
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int g_bins = 30;//直方图组距
void on_BinChange(int, void*);
int main()
{

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	cvtColor(src_img,temp_img,COLOR_BGR2HSV);
	//分离hue色调通道
	edge_img.create(temp_img.size(),temp_img.depth());
	int ch[] = {0,0};
	mixChannels(&temp_img, 1, &edge_img, 1, ch, 1);

	//创建Trackbar来输入bin的数目
	namedWindow("src_img",WINDOW_AUTOSIZE);
	createTrackbar("色调组距","src_img",&g_bins,180,on_BinChange);
	on_BinChange(0,0);
	imshow("src_img",src_img);
	waitKey(0);
	return 0;
}
void on_BinChange(int, void*)
{
	//参数准备
	MatND hist;
	int histSize = MAX(g_bins,2);
	float hue_range[] = { 0,180 };
	const float*range = { hue_range };
	//计算直方图并归一化
	calcHist(&edge_img,1,0,Mat(),hist,1,&histSize,&range,true,false);
	normalize(hist,hist,0,255,NORM_MINMAX,-1,Mat());
	//计算反向投影
	MatND backproj;
	calcBackProject(&edge_img,1,0,hist,backproj,&range,1,true);
	//显示反向投影
	imshow("反向投影图",backproj);
	//绘制直方图的参数准备
	int w = 400;
	int h = 400;
	int bin_w = cvRound((double)w/histSize);
	Mat histImg = Mat::zeros(w,h,CV_8UC3);
	//绘制直方图
	for (size_t i = 0; i < g_bins; i++)
	{
		{
			rectangle(histImg,Point(i*bin_w,h),Point((i+1)*bin_w,h-cvRound(hist.at<float>(i)*h/255.0)),
				Scalar(100,123,255),-1);
		}
	}
	//显示直方图窗口
	imshow("直方图", histImg);
}