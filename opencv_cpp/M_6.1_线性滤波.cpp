/*
6.1.1平滑处理
平滑处理(smoothing)也称为模糊处理(bluring),是一种简单且使用频率
很高的图像处理方法;
平滑处理是用来减少图像上的噪点，或者失真;降低图像分辨率;

图像滤波与滤波器
图像滤波，指在尽量保留图像细节特征的条件下对目标图像的噪声进行抑制,
是图像处理中不可缺少的操作,其处理效果的好坏将直接影响到后续图像处理
和分析的有效性和可靠性;

消除图像中的噪声成分叫做图像的平滑化或滤波操作;
信号或图像的能量大部分集中在幅度谱的低频和中频段,
而在较高频段，有用的信息经常被噪声淹没;
因此一个能降低高频成分幅度的滤波器就能减弱噪声的影响;

滤波的目的有两个:一个是抽出对象的特征作为图像识别的特征模式;
另一个是为适应图像处理的要求,消除图像数字化时所混入的噪声;

图像滤波处理的要求有两个:一是不能损坏图像的轮廓及边缘等重要信息;
二是使图像清晰视觉效果好;

平滑滤波是低频增强的空间域滤波技术;目的有两类:一类是模糊,另一类是消除噪音;


空间域的平滑滤波一般采用简单平均法进行,就是求临近像元点的平均亮度;
邻域的大小与平滑的效果直接相关,邻域越大平滑的效果越好,但是邻域过大，
平滑也会使便于那信息损失的越大,从而使输出的图像变得更模糊,
因此需合理选择邻域的大小;

关于滤波器:一种形象的比喻是:可以把滤波器想象成一个加权系数的窗口,
当使用这个滤波器平滑处理图像时,就把这个窗口放到图像之上,透过这个窗口
来看我们得到的图像;

滤波器的种类有很多,5种常用的图像平滑处理的操作办法:

方框滤波---BoxBlur函数(线性滤波)
均值滤波(邻域平均滤波)---Blur函数(线性滤波)
高斯滤波---GaussianBlur函数(线性滤波)

中值滤波---medianBlur函数(非线性滤波)
双边滤波---bilateralFilter函数(非线性滤波)


线性滤波器:
低通滤波器:允许低频率通过;
高通滤波器:允许高频率通过;
带通滤波器:允许一定范围滤波通过;
带阻滤波器:阻止一定范围频率通过允许其他频率通过;
全通滤波器：允许所有频率通过,仅仅改变相位关系;
陷波滤波器(Band-Stop Filter):阻止一个狭窄频率范围通过,
是一种特殊的带阻滤波器;

滤波是将信号中特定波段频率滤除的操作,是抑制和防止干扰的一项重要措施;

滤波分为高通和低通两种,高斯滤波是指用高斯函数作为滤波函数的滤波操作,
至于是不是模糊，要看是高斯低通还是高斯高通，低通是模糊，高通是锐化;

高斯滤波是指高斯函数作为滤波函数的滤波操作;
高斯模糊是指高斯低通滤波;


邻域算子与线性邻域滤波
邻域算子(局部算子)是利用给定像素周围的像素值的决定此像素
的最终输出值的一种算子;而线性邻域滤波就是一种常用的邻域算子;
像素的输出值取决于输入像素的加权和;

邻域算子除用于局部色调调整以外，还可以用于图像滤波,以实现图像的
平滑和锐化，图像边缘增强或图像噪声的去除;


方框滤波(box Filter)
方框滤波(box Filter)被封装在一个名为boxblur的函数中,
boxblur函数是用方框滤波器来模糊一张图片(低通);

C++:void boxFilter(InputerArray src,OutputArray dst ,int ddepth,
Size ksize,Point anchor=Point(-1,-1),boolnormalize=true,int borderType=BORDER_DEFAULT)
第一个参数:待处理的图片深度应该为CV_8U,CV_16U,CV_16S,CV_32F以及CV_64F
第二个参数:目标图像,需要和源图片有一样的尺寸和类型;
第三个参数:int类型的ddepth,输出的图像的深度,-1代表使用原图深度,
src.depth();
第四个参数:Size类型的ksize,内核的大小;一般用的Size(w,h)来表示内核的大小,
其中w为像素宽度,h为像素高度;Size(3,3)表示3*3的核大小;
第五个参数:Point的类型的anchor,表示锚点(即被平滑的那个点),注意,它有默认值
Point(-1,-1);如果这个点坐标是负值的话,表示取核中心为锚点,所以
默认值Point(-1,-1)表示这个锚点在核的中心;
第六个参数:bool类型的normalize,默认值为true,一个标识符,表示
内核是否被其他区域归一化(normalized)了;
第七个参数:int 类型的borderType,用于推断图像外部像素的某种边界模式,
有默认值BORDER_DEFAULT;

当第六个参数,normalize=true的时候,方框滤波就变成了均值滤波,
也就是说,均值滤波是方框滤波的归一化(normalized)后的特殊情况;
归一化就是把要处理的量缩放到一个范围(比如(0,1)),以便
统一处理和直观量化;
非归一化(Unnormalized)的方框滤波用于计算每个像素邻域内的积分特性,
比如密集光流算法中用到的图像的倒数的协方差矩阵;
如果我们要在可变的窗口中计算像素综合,使用integral()函数;

6.17均值滤波
均值滤波,是最简单的一种滤波操作,输出图像的每一个像素是核窗口
内输入图像对应像素的平均值(所有像素加权系数相等),
归一化后的方框滤波,

均值滤波的缺陷:不能很好的保护图像细节,在图像去噪的同时也破坏了
图像的细节部分,从而使图像变得模糊,不能很好的去除噪声点;

C++:void blur(InputArray src OutputArray dst,Size ksize,Point anchor=Point(-1,-1),
int borderType=BORDER_DEFAULT)

6.18高斯滤波
高斯滤波是一种线性平滑滤波,可以消除高斯噪声,广泛应用于图像处理的减噪过程;
高斯滤波的具体操作:用一个模板(卷积,掩码)扫描图像中的每一个像素,用模板确定
的领域内像素的加权平均灰度值去代替模板中心像素点的值;

高斯平滑,高斯模糊的过程就是图像与正态分布做卷积,正太分布也叫作高斯分布,
所以也叫作高斯模糊;
高斯函数的傅里叶变换是另外一个高斯函数,高斯模糊对图像来说是一个低通
滤波操作;
C++:void GaussianBlur(InputArray src,OutputArray dst,Size ksize,double sigmaX,
double sigmaY=0,intborderType=BORDER_DEFAULT)
支持就地过滤(In-placefiltering)

sigmaX 表示高斯核函数在X方向的标准偏差;
sigmaY 表示高斯核函数在Y方向的标准偏差，
如果sigmaY为0,就设置为sigmaX;
如果sigmaX和sigmaY都是0;
那么就由ksize.width和ksize.height
Size,sigmaX和sigmaY要全部指定到;

*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img_1, dst_img_2, dst_img_3, dst_img_4, dst_img_5, gray_img, edge;

int g_nBoxfilter_Value = 3;//方框滤波参数值;
int g_nMeanBlur_Value = 3;//均值滤波参数值
int g_nGaussianBlur_Value = 3;//高斯滤波参数值
int g_nMedianBlur_Value = 10;//中值滤波参数值
int g_nBilateralFilter_Value = 10;//双边滤波参数值

//方框滤波
void on_BoxFilter(int a, void*)
{
	boxFilter(src_img,dst_img_1,-1,Size(g_nBoxfilter_Value+1, g_nBoxfilter_Value+1));
	imshow("on_BoxFilter", dst_img_1);
}
//均值滤波
void on_MeanBlur(int a, void*)
{
	blur(src_img, dst_img_2, Size(g_nMeanBlur_Value + 1, g_nMeanBlur_Value + 1),Point(-1,-1));
	imshow("on_MeanBlur", dst_img_2);
}
//高斯滤波
void on_GaussianBlur(int a,void*)
{
	GaussianBlur(src_img, dst_img_3, Size(41, 41), 0, 0);//----------------------待续有问题
	//GaussianBlur(src_img, dst_img_3, Size(g_nGaussianBlur_Value + 1, g_nGaussianBlur_Value + 1), 0, 0);
	//GaussianBlur(src_img, dst_img_3, Size(a + 1, a + 1), 0, 0);
	imshow("on_GaussianBlur",dst_img_3);
}

void on_medianBlur(int, void*)
{
	medianBlur(src_img,dst_img_4,g_nMedianBlur_Value*2+1);
	imshow("中值滤波",dst_img_4);
}

void on_BilateralFilter(int, void*)
{
	bilateralFilter(src_img, dst_img_5, g_nBilateralFilter_Value, g_nBilateralFilter_Value * 2,
		g_nBilateralFilter_Value / 2);
	imshow("双边滤波",dst_img_5);
}

int main()
{

	//Mat src_img, dst_img, gray_img, edge;

	system("color5E");

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}

	dst_img_1 = src_img.clone();
	dst_img_2 = src_img.clone();
	dst_img_3 = src_img.clone();

	namedWindow("src");
	imshow("src",src_img);
	//namedWindow("after_filter");

	namedWindow("on_BoxFilter",1);
	createTrackbar("内核值","on_BoxFilter",&g_nBoxfilter_Value,40, on_BoxFilter);
	on_BoxFilter(g_nBoxfilter_Value,0);


	namedWindow("on_MeanBlur", 1);

	createTrackbar("内核值","on_MeanBlur", &g_nMeanBlur_Value,40,on_MeanBlur);
	on_MeanBlur(g_nMeanBlur_Value,0);

	namedWindow("on_GaussianBlur", 1);
	createTrackbar("内核值","on_GaussianBlur",&g_nGaussianBlur_Value,40,on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlur_Value,0);



	namedWindow("中值滤波",1);
	createTrackbar("参数值","中值滤波",&g_nMedianBlur_Value,50,on_medianBlur);
	on_medianBlur(g_nMedianBlur_Value,0);


	namedWindow("双边滤波",1);
	createTrackbar("内核值","双边滤波",&g_nBilateralFilter_Value,100,on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilter_Value,0);

	//方框滤波操作
	//boxFilter(src_img, dst_img,-1,Size(5,5));

	//均值滤波操作
	//blur(src_img,dst_img,Size(7,7));

	//高斯滤波操作
	//GaussianBlur(src_img, dst_img, Size(3, 3), 0, 0);

	//imshow("after_filter", dst_img);
	waitKey(0);

	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
