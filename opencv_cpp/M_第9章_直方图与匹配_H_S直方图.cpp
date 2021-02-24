/*
物体图像和视频信息分析的过程,用直方图表示出来,得到比较直观的数据感官展示;
直方图可以用来描述各种不同的参数和事物,例如:物体的色彩分布,物体边缘梯度模板,
以及表示目标位置的当前假设的概率分布;

直方图广泛运用于计算机视觉中,通过标记帧与帧之间显著的边缘和颜色
的统计变化,来检测视频中场景的变化;在每个兴趣点设置一个有相似特征的
直方图所构成的"标签",用以确定图像中的兴趣点;边缘,色彩,角度等直方图
构成了可以被传递给目标识别分类器的一个通用特征类型;色彩和边缘的直方图序列
可以用来识别网络视频是否被复制;

直方图就是对数据进行统计的一种方法,并且将统计值组织到一系列实现定义好的bin当中;
bin为直方图中经常用到的一个概念,翻译为:"直条"或者"组距",数值和从数据中计算出来的
特征统计量,这些数据可以是诸如梯度,方向,色彩或任何其他特征;直方图获得
的是数据分布的统计图;通常直方图的维数要低于原始数据;直方图是计算机视觉中最经典的工具之一;

在统计学中,直方图(Histogram)是一种对数据分布情况的图形表示,是一种二维统计图表,它的两个坐标
分别是统计样本和该样本对应的某个属性的度量;

直方图的均衡化,是通过拉伸像素强度分布范围来增强图像对比度的一种方法;

图像直方图(image Histogram)是用以表示数字图像中亮度分布的直方图,
标绘了图像中每个亮度值的像素数,可以借助观察该直方图了解需要如何调整亮度分布;

这种直方图,横坐标的左侧为纯黑,较暗的区域,而右侧为较亮,纯白的区域;
因此,一张较暗图片的图像直方图中的数据多集中于左侧和中间部分,而整体明亮,
只有少量阴影的图像相反;

直方图的意义:
直方图是图像中像素强度分布的图形表达方式;
它统计了每一个强度值所具有的像素个数;

直方图是对数据的统计集合,并将统计结果分布与一系列预定义的bins中;
这里的数据不仅仅指的是灰度值,且统计数据可能是任何能有效描述图像的特征;

直方图并不局限于统计颜色灰度,而是可以统计任何图像特征,如梯度,方向;
dims:需要统计的特征的数目;dims=1因为仅统计了灰度值(灰度图像)
bins:每个特征空间子区段的数目,可以翻译成"直条","组距";
range:每个特征空间的取值范围;range=[0,255]


9.2直方图的计算与绘制

C++:void calcHist(const Mat* image,int nimage,const int* channels,InputArray mask,
OutputArray hist ,int dims,const,int* histSize,const float **range,bool uniform=true
,bool accumulate=false)

第一个参数:const Mat*类型的image,输入的数组(或者数据集),需要为相同的深度(CV_8U或者CV_32F)和相同的尺寸;
第二个参数:int类型的nimage,输入数组的个数,第一个参数中存放了多少张"图像",有几个原数组;
第三个参数:const int*类型的channels,需要统计的通道(dim)索引;第一个数组通道从0到images[0].channels()-1,
			第二个数组通道从images[0].channels()计算到images[0].channels()+images[1].channels()-1;
第四个参数:InputArray类型的mask,可选的操作掩码,如果此掩码不为空,那么它必须是8位的,并且与
images[i]有同样大小的尺寸;这里的非零掩码元素用于标记处统计直方图的数组元素数据;
第五个参数:OutputArray类型的hist,输出的目标直方图,一个二维数组;
第六个参数,int类型的dims,需要计算的直方图的维度,必须是正数,且不大于CV_MAX_DIMS(在当前版本的Opencv中等于32);
第七个参数:const int*类型的histSize,存放每个维度的直方图尺寸的数组;
第八个参数:const float**类型的ranges,表示一个维度数组(第六个参数dims)的每一维的边界阵列;
可以理解为每一维数组的取值范围;

第九个参数:bool类型的uniform,指示直方图是否均匀的标识符,默认为true;

第十个参数:bool类型的accumulate,累计标识符,默认值false;若其为true,直方图在配置阶段
不会被清零;此功能主要是允许多个阵列中计算单个直方图,或者用于在特定的时间更新直方图;
------------------
找寻最值:minMaxLoc()函数
minMaxLoc()函数的作用是在数组中找到全局最小值和最大值,有两个版本
C++:void minMaxLoc(InputArray src,double* minVal,double *maxVal=0,Point*minLoc=0,
Point *=maxLoc=0,InputArray mask=noArray())

第一个参数:InputArray类型的src,输入的单通道阵列
第二个参数:double*类型的minVal,返回最小值的指针,若无须返回，此值置为NULL;
第三个参数:double*类型的maxVal,返回的最大值的指针,若无须返回，此值置为NULL;
第四个参数:Point*类型的minLoc,返回最小位置的指针(二维情况下),若无须返回,
此值置为NULL;
第五个参数:Point*类型的maxLoc,返回最大位置的指针(二维情况下),若无须返回,
此值置为NULL;
第六个参数:InputArray类型的mask,用于选择子阵列的可选掩码;

*/
//计算彩色图像的色调,饱和度二维直方图
//色调(Hue),饱和度(Saturation);所以H-S直方图,就是色调--饱和度直方图;

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int main()
{
	src_img = imread("1.jpg", 1);//读入图片数据
	//src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	cvtColor(src_img,dst_img,COLOR_BGR2HSV);
	//参数准备
	//将色调量化为30个等级,将饱和度量化为32个等级;
	int hueBinNum = 30;//色调的直方图直条数量
	int saturationBinNum = 32;//饱和度的直方图直条数量
	int histSize[] = { hueBinNum ,saturationBinNum };
	//定义色调的变化范围为0-179
	float hueRanges[] = { 0,180 };
	//定义饱和度的变化范围为0(黑白灰)到255(纯光谱颜色)
	float saturationRanges[] = {0,256};
	const float*ranges[] = { hueRanges ,saturationRanges };
	MatND dstHist;
	//参数准备,calcHist函数中将计算第0通道和第1通道的直方图
	int channels[] = {0,1};
	//正式调用calcHist,进行直方图计算
	calcHist(&dst_img,//输入的数组
		1,//数组个数为1
		channels,//通达索引
		Mat(),//不使用掩码
		dstHist,//输出的目标直方图
		2,//需要计算的直方图的维度为2
		histSize,//存放每个维度的直方图尺寸的数组
		ranges,//每一维数组的取值范围数组
		true,//指示直方图是否俊宇的标识符,true表示均匀的直方图
		false//累计标识符,false表示直方图在配置阶段会被清零
	);
	//为绘制直方图准备参数
	double maxValue = 0;//最大值
	minMaxLoc(dstHist,0,&maxValue,0,0);//查找数组和子数组的全局最小值和最大值存入maxValue中
	int scale = 10;
	Mat histImg = Mat::zeros(saturationBinNum*scale,hueBinNum*10,CV_8UC3);
	//双层循环,进行直方图绘制
	for (size_t i = 0; i < hueBinNum; i++)
	{
		for (int saturation = 0; saturation < saturationBinNum; saturation++)
		{
			float binValue = dstHist.at<float>(i,saturation);//直方图直条的值
			int intensity = cvRound(binValue*255/maxValue);//强度
			//正式进行绘制
			rectangle(histImg,Point(i*scale,saturation*scale),
				Point((i+1)*scale-1,(saturation+1)*scale-1),Scalar::all(intensity),FILLED);
		}
		//显示效果图
		imshow("src_img",src_img);
		imshow("h-s_img", histImg);
		waitKey();
	}
}