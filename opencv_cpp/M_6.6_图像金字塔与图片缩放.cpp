/*
6.6图像金字塔与图片尺寸缩放
将某种尺寸的图像转换为其他尺寸的图像,放大或缩小尺寸
resize函数,最直接的方式
pyrUp(),pyrDown()函数,金字塔相关的两个函数,对图像
进行向上采样与向下采样,
pyrUp,pyrdown起始和专门用作放大缩小图像尺寸的resize在功能上差不多,
披着图像金字塔的皮,说白了还是对图像进行缩放，
pyrUp和pyrDown在opencv/imgproc模块中的ImageFiltering子模块里;
resize在imgproc模块中Geometric Image Transformations子模块中

图像金字塔是图像中多尺度表达的一种，最主要用于图像的分割,以多分辨率
来解释图像的有效但概念简单的结构;

图像金字塔最初用于机器视觉和图像压缩,一幅图像的金字塔是一系列以金字塔形状排列
的,分辨率逐步降低且来源于同一张原始图的图像集合,其通过
梯次向下采样获得, 直到达到某个终止条件才停止采样;

金字塔的底部是待处理图像的高分辨率表示,而顶部是低分辨率的近似;
图像比喻成金字塔，层级越高，图像越小，分辨率越低;

高斯金字塔---用来向下采样,主要的图像金字塔
拉普拉斯金字塔---用来从金字塔底层图像重建上层未采样图像,
在数字图像处理中也就是预测残差，可以对图像进行最大程度还原,
配合高斯金字塔一起使用;
两者的简要区别在于:高斯金字塔用来向下降采样图像;
拉普拉斯金字塔则用来从金字塔底层图像中向上采样，重建一个图像;

要从金字塔第i层生成第i+1层(将第i+1层表示为Gi+1),先用
高斯核对Gi层进行卷积,然后删除所有偶数行和偶数列,新得到图像面积
会变为原图像的1/4,按照上述过程对输入图像G0执行操作就可产生整个金字塔;

图像金字塔的上层移动,尺寸和分辨率会降低;Opencv中,金字塔中上一级
图像生成下一级图像可以PRyDown,而通过PryUp将现有的图像在每个维度
都放大两边;

对图像向上采样--pyrUp函数---尺寸加倍;
对图像向下采样--pyrDown函数---尺寸减半;
向上和向下采样,针对图像的尺寸而言的(和金字塔的方向相反),
向上就是图像尺寸的加倍,向下就是图像尺寸减半;

PyrUp和PyrDown不是互逆的,即PyrUp不是降采样的逆操作;
这种情况下，图像首先在每个维度上扩大为原来的两倍,
新增的行(偶数行)以0填充,然后给指定的滤波器进行卷积
(实际上是一个在每个维度都扩大为原来的两倍的过滤器),
去估计"丢失"像素的近似值;
PyrDown()是一个丢失信息的函数;为了恢复原来更高的分辨率
的图像,我们要获得由降采样操作丢失的信息,这些数据就和
拉普拉斯金字塔有关系了;

高斯金字塔:
高斯金字塔是通过高斯平滑和亚采样获得一系列采样图像,
也就是说第K层金字塔通过平滑,亚采样就可以获得
K+1层高斯图像;高斯金字塔包好了一系列低通滤波器,
其截至频率从上一层到下一层以因子2逐渐增加,
所以高斯金字塔可以跨越很大的频率范围;

另外,每一层都是按从下向上的次序编号,层级Gi+1(表示为Gi+1尺寸小于第i层Gi);

1.>对图像的向下取样
为了获取层级为Gi+1的金字塔图像,采用如下方法:
(1)对图像Gi进行高斯内核卷积;
(2)将所有偶数行和列去除; 
得到的图像即为Gi+1的图像;显而易见,结果图像只有原图的1/4;通过
对输入图像Gi(原始图像)不停迭代以上步骤得到整个金字塔,向下
取样会逐渐丢失图像的信息;
向下操作->缩小图像;
2.对图像的向上取样
如果相放大图像，则需要通过向上取样操作得到;
1.>将图像在每个方向扩大为原来的2倍，新增的行和列以0填充;
2.>使用先前同样的内核(乘以4)与放大后的图像卷积，获得"新增图像"
的近似值;
得到的图像即为放大后的图像,但是与原来的图像相比会发觉比较模糊
因为在缩放的过程中已经丢失了一些信息;如果想在缩小和放大整个过程中
减少信息的丢失,这些数据就形成了拉普拉斯金字塔;

拉普拉斯金字塔第i层的数学定义:
Li=Gi-UP(Gi+1)O*g5x5(卷积);
Gi表示第i层的图像,UP()操作是将源图像中位置为(x,y)的像素映射到目标
图像的(2x+1,2y+1)位置,即在进行向上取样,卷积操作,G5x5的高斯内核;
opencv进行拉普拉斯运算:Li=Gi-PyrUp(Gi+1);
也就是说,拉普拉斯金字塔是通过源图像减去先缩小后再放大的图像的一系列
构成的,拉普拉斯金字塔是高斯金字塔的逆形式;

图像金字塔非常重要的一个应用就是图像分割;图像分割的话,先建立一个图像金字塔,
然后对Gi和Gi+1,的像素直接依照对应的关系,建立起"父子"关系,而快速初始分割可以在
金字塔高层的低分辨率图像上完成，然后逐层对分割加以优化;


尺寸调整:resize()函数
次函数将源图像精确地转换为指定尺寸的目标图像;如果源图像中设置了ROI,
那么resize()函数会对源图像的ROI区域进行调整图像尺寸的操作来输出到目标图像中;
若目标图像中已经设置了ROI区域,不难理解resize()将会对源图像进行尺寸调整
并填充到目标图像的ROI中;
C++:void resize(InputArray src,OutputArray dst,Size dsize,double fx=0,
double fy=0,int interpolation=INTER_LINEAR)
输出图像的尺寸由第三个参数决定,dszie,如果dsize等于0,
那么dsize=Size(round(fx*src.cols),round(fy*src.rows))
其中dsize,fx,fy都不能为0;
第四个参数,double类型的fx,沿水平轴的缩放系数,默认值为0;
当fx=0时,(double)dsize.width/src.cols
第五个参数:double类型的fy,沿垂直轴的缩放系数,默认值为0;
当fy=0时，(double)dsize.height/src.rows

第六个参数:int类型的interpolation,用于指定插值方式,
默认为INTER_LINEAR(线性插值)
INTER_NEAREST===最近邻插值
INTER_LINEAR====线性插值(默认值)
INTER_AREA===区域插值(利用像素区域关系的重采样插值)
INTER_CUBIC==三次样条插值(超过4X4像素邻域内的双三次插值)
INTER_LANCZOS4===Lanczos插值(超过8X8像素邻域的Lanczos插值)

若要缩小图像,一般情况下最好用CV_INTER_AREA来插值;
若要放大图像,一般情况下最好用CV_INTER_CUBIC(效率不高,慢,不推荐使用)
或CV_INTER_LINEAR(效率较高,速度较快,推荐使用)


Mat dst_img=Mat::zeros(512,512,CV_8UC3);//创建一个512*512尺寸的图片
Mat src_img=imread("1.jpg");
//显示指定dsize=dst_img.size();//fx与fy会计算出来,不用额外指定
resize(src_img,dst_img,dst_img.size());


Mat dst_img;
Mat src_img=imread("1.jpg");
resize(src_img,dst_img,Size(),0.5,0.5);

1.>向上采样:pyrUp()函数
pyrUp()函数的作用是向上采样并模糊一张图像,说白了就是放大一张图片
C++::void pyrUp(InputArray src,OutputArray dst,const Size& dstsize=Size(),
int borderType=BORDER_DEFAULT)
第三个参数:const Size&类型的dstsize,输出图像大小;有默认值Size();
即默认情况下,由Size(src.cols*2,src.rows*2)来进行计算,需要满足一下条件
|dstsize.width-src.cols*2|<<(dstsize.width mod2)
|dstsize.height-src.rows*2|<<(dstsize.height mod2)

pyrUp函数执行高斯金字塔的采样操作,也可以用于拉普拉斯金字塔;
首先,通过插入可为0的行与列,对源图像进行向上取样操作,然后
将结果与pyrDown()*4的内核做卷积

2.>采样:pyrDown()函数
pyrDown()函数的作用是向下采样并模糊一张图片,说白了缩小一张图片
C++:void pyrDown(InputArray src,OutputArray dst,const Size& dstsize=Size()
,int borderType=BORDER_DEFAULT)

第三个参数:输出图像的大小,默认值为Size(),
默认情况下,由Size Size((src.cols+1)/2,(src.rows+1)/2))
来进行计算
|dstsize.width*2-src.cols|<<2
|dstsize.heigh*2-src.rows|<<2

该pyrDown函数执行了高斯金字塔建造的向下采样的步骤,
它将源图像与如下内核做卷积运算:
1/256|5*5矩阵|
接着，他通过对图像的偶数行和列做插值来进行向下采样操作;

*/

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int main()
{

	Mat src_img, dst_img, gray_img, mask_img,temp_img;

	src_img = imread("lena.jpg", 1);//读入图片数据

	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img",src_img);
	temp_img = src_img;
	pyrUp(temp_img,dst_img,Size(temp_img.cols*2,temp_img.rows*2));
	//resize(temp_img,dst_img,Size(temp_img.cols/2,temp_img.rows/2),(0,0),(0,0),3);
	pyrDown(temp_img,gray_img,Size(temp_img.cols/2,temp_img.rows/2));
	
	//resize(temp_img, gray_img, Size(temp_img.cols *2, temp_img.rows *2), (0, 0), (0, 0), 3);

	imshow("dst_img", dst_img);
	imshow("gray_img", gray_img);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
