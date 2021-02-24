/*
7.2.7霍夫梯度法的原理
霍夫梯度法的原理:
1.>首先对图像应用边缘检测,比如用canny边缘检测
2.>然后,对边缘图像中的每一个非零点,考虑其局部梯度,用Sobel()函数
计算x和y方向的Sobel一阶导数得到梯度;
3.>利用得到的梯度,由斜率指定的直线上每一个点都在累加器中累加,
这里的斜率是从一个指定的最小值到指定的最大值的距离;
4.>同时,标记边缘图像中每一个非零像素的位置;
5.>然后从二维累加器中这些点中选择候选的中心,这些中心都大于给定
阈值并且大于其所选近邻;这些候选的中心按照累加值降序排列,
以便于最支持像素的中心首次出现;
6.>对每一个中心,考虑所有非0像素;
7.>这些像素按照其余中心的距离排序;从到最大半径的最小距离,
算计,选择非0像素最支持的一条半径;
8.>如果一个中心收到边缘图像非0像素最充分的支持,并且到前期
被选择的中心有足够的距离,那么它就会被保留下来;

这个实现可以是算法执行起来更高效,或许更加看重的是,能够解决
三维累加器中会产生噪声并且使得结果不稳定的稀疏分布问题;
7.2.8霍夫梯度法的缺点
1.>在霍夫梯度法中,我们使用sobel倒数来计算局部梯度;
它可以视作等同一条局部切线,这并不是一个数值稳定的做法;
在大多数情况下,这样做会得到正确的结果,或许会在输出中
产生一些噪声;
2.>在边缘图像中的整个非0像素集被看做每个中心的候选部分;
因此,如果把累加器的阈值设置偏低,算法将要消耗比较长的时间;
此外,因为每一个中心只选择一个圆,如果有同心圆,就只能选择其中
一个;
3.>因为中心是按照其关联的累加器值的升序排列的,并且如果
新的中心过于接近之前已经接受的中心的话,就不会被保留下来;
且当有许多同心圆或者近似的同心圆时,霍夫梯度法的倾向是保留最大的
一个圆;可以说这是一种比较极端的做法,因为在这里默认Sobel倒数会产生噪声,
若是对于无穷分辨率的平滑图像而言的话,这才是必须的;

霍夫圆变换:HoughCircles()函数
HoughCircles函数可以利用霍夫变换算法检测出来灰度图中的圆;
它相比之前的HoughLines和HoughLinesP,比较明显的一个区别是
不需要源图是二值的,而HoughLines和HoughLinesP都需要源图为二值图像;
C++:void HoughCircles(InputArray img,OutputArray circles,int method,
double dp,double minDist,double param1=100,double param2=100,
int minRadius=0,int maxRadius=0)

第二个参数:经过调用HoughCircles函数后此参数存储了检测到的圆的输出矢量,
每个矢量由包含了3个元素的浮点矢量(x,y,radius)表示;

第三个参数:int类型的method,即使用的检测方法,目前opencv中就
霍夫梯度法一种可以使用,它的标识符为HOUGH_GRADIENT

第四个参数:double类型的dp,用来检测圆心的累加器图像的
分辨率于输入图像之比的倒数,且此参数允许创建一个比输入图像分辨率低
的累加器;如果dp=1时,累加器和输入图像具有相同的分辨率;如果dp=2,
累加器便有输入图像一半那么大的宽度和高度;

第五个参数:double类型的minDist,为霍夫变换检测到的圆的圆心之间的
最小距离,即让算法能明显区分的两个不同圆之间的最小距离,
这个参数如果太小的话,多个相邻的圆可能被错误的检测呈一个圆;
反之,这个参数设置太大,某些圆就不能被检测出来;

第六个参数:double类型的param1,默认值100,它是第三个参数method设置的
检测方法的对应的参数,对当前唯一的方法霍夫梯度法CV_HOUGH_GRADIENT,
它表示传递给canny边缘检测算子的高阈值;而低阈值为高阈值的一半;

第七个参数:double类型的param2,默认100，第三个参数method设置的
检测方法的对应的参数,对当前唯一的方法霍夫梯度法CV_HOUGH_GRADIENT,
它表示在检测阶段圆心的累加器阈值;它越小,就越可以检测到更多
根本不存在的圆,越大的话,能通过检测的圆就更加接近完美的圆形了;
第八个参数:int 类型的minRadius,有默认值为0,表示圆半径的最小值;
第九个参数:int类型的maxRadius,有默认值为0,表示圆半径的最大值;

需要注意的是:使用次函数可以很容易的检测出圆的圆心;但是它可能找不到
合适的圆半径,可以通过第八个参数minRadius和第九个参数maxRadius
指定最小和最大的圆半径,来辅助圆检测的结果;
或者,可以直接忽略返回半径,他们都有默认值0,只用HoughCircles函数
检测出来的圆心,然后用额外的一些步骤来进一步确定半径;

*/

#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int main()
{

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);

	//转换为恢复图像并进行图像平滑,转换边缘检测后的图为灰度图
	cvtColor(src_img,temp_img,COLOR_BGR2BGRA);
	//
	GaussianBlur(temp_img,temp_img,Size(9,9),2,2);
	//进行霍夫圆变换
	vector<Vec3f> circles;

	
	HoughCircles(temp_img,circles,HOUGH_GRADIENT,1.5,10,200,100,0,0);
	cout << circles.size() << endl;
	while (true)
	{

	}
	//一次在图中绘制出圆
	for (size_t i = 0; i < circles.size(); i++)
	{
		//参数定义
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心
		circle(src_img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(src_img,center,radius,Scalar(155,50,255),3,8,0);

	}
	imshow("src_img",src_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
