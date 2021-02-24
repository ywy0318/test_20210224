/*
//6.3形态学滤波,腐蚀与膨胀
数学生态学:是一门建立在格伦与拓扑学基础之上的图像分析学科,
是数学形态学图像处理的基础理论,其基本的运算包括:二值腐蚀和膨胀,
二值开闭运算,骨架抽取，极限腐蚀,击中击不中变换,形态学梯度,
Top-hat变换,颗粒分析,流域变换,灰值腐蚀和膨胀,灰值开算运算,灰值形态学梯度

形态学操作就是基于形状的一系列图像操作处理,分别是膨胀(dilate)和腐蚀(erode)

膨胀与腐蚀能实现多种多样的功能:
消除噪声;
分割(isolate)出独立的图像元素,在图像中连接(join)相邻的元素;
寻找图像中的明显的极大值区域或者极小值区域
求出图像的梯度;

腐蚀和膨胀是对白色(高亮部分)而言,不是黑色部分；
膨胀是图像中的高亮部分进行膨胀,类似于"领域扩张",
效果图拥有比原图更大的高亮区域;
腐蚀是原图中的高亮部分被腐蚀,类似于"领域被蚕食"
效果图拥有比原图更小的高亮区域;

膨胀或腐蚀操作是将图像(图像的一部分区域,)与核进行卷积;

核可以是任何形状和大小,拥有一个单独定义出来的参考点,称之为锚点(anchorpoint),
多数情况下，核是一个小的，中间带有参考单和实心正方形或圆盘，其实可以把核视为
模板或者掩码;

膨胀(dilate)是求局部最大值的操作;
图形与核进行卷积,计算核覆盖的区域的像素点的最大值,并把这个最大值
赋值给参考点指定的像素;这样会使图像中的高亮区域逐渐增长,

腐蚀(erode)是相反的一对操作,所以就是求局部最小值的操作;


//膨胀:dilate函数
dilate函数使用像素邻域内的局部极大运算符来膨胀一张图片,从src输入,
由dst输出,支持就地(in-place)操作

void dilate(InputArray src,OutputArray dst,InputArray kernel,Point anchor=Point(-1,-1),
int iterations=1,
int borderType=BORDER_CONSTRANT,const Scalar& borderValue=morphologyDefaultBorderValue());
第一个参数:图像深度应为CV_8U,CV_16U,CV_16S,CV_32F或CV_64F
第二个参数:尺寸和类型应该和目标图像一样,
第三个参数:膨胀操作的核,当为NULL时，表示使用参考点位于中心3X3的核

一般使用函数 getStructuringElement配合这个参数使用;
getStructuringElement函数会返回指定形状和尺寸的结构元素(内核矩阵),
getStructuringElement函数的第一个参数表示内核的形状,
有三种形状可以选择:
矩形:MORPH_RECT;
交叉形:MORPH_CROSS;
椭圆形:MORPH_ELLIPSE;
第二个参数和第三个参数分别是内核的尺寸及锚点的位置;
一般在调用erode及dilate函数之前，先定一个Mat类型的变量来获得
getStructuringElement函数的返回值;对应锚点的位置,默认值Point(-1,-1),
表示锚点在于中心,此外需要注意的是,十字形的element形状唯一依赖于锚点的位置,
而在其他情况下,锚点只是影响了形态学运算结果的偏移;

getStructuringElement函数相关的调用示例代码
int g_nStructElementSize=3;//结构元素(内核矩阵)的尺寸
//获取自定义核
Mat element=getStructuringElement(MORPH_RECT,Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1)
,Point(2*g_nStructElementSize+1,2*g_nStructElementSize+1));

调用之后，可以在接下来调用erode或dilate函数 时,在第三个参数填保存了
getStructuringElement返回值的Mat类型变量;
第四个参数:Point类型的anchor,锚点的位置,默认值(-1,-1),表示锚点位于中心;
第五个参数:int 类型的iterations,迭代使用erode()函数的次数,默认值为1，
第六个参数:int类型的borderType,用于推断图像外部像素的某种边界模式;
默认值为BORDER_DEFAULT
第七个参数:const Scalar&类型的borderValue,当边界为常数时的边界值,
有默认值morphologyDefaultBorderValue(),一般不用去管它,
需要时去查看官方文档中createMorphologyFilter()函数,


腐蚀:erode函数
erode函数使用像素邻域内的局部极小运算符来腐蚀一张图片,支持就地(in-place)
操作
C++:void erode(InputArray src,OutputArray dst,InputArray kernel,Point anchor=Point(-1,-1),
int iterations=1,int borderType=BORDER_CONSTRANT,
const Scalar& borderValue=morphologyDefaultBorderValue());
*/

#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;



int main()
{
	Mat src_img, dst_img, gray_img, edge;

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img");
	namedWindow("erode");
	imshow("src_img",src_img);

	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	//腐蚀操作
	//erode(src_img,dst_img,element);

	imshow("erode", dst_img);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
