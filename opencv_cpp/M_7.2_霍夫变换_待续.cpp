/*
7.2霍夫变换(Hough Transform)
在图像处理和计算机视觉中,如何从当前的图像中提取所需要的特征信息
是图像识别的关键所在;在许多应用场合中需要快速准确的检测出直线或
圆;其中一种非常有效的解决问题的方法就是霍夫(Hough)变换,其为图像处理中
从图像中识别集合形状的基本方法之一,
也有很多改进算法,最基本的霍夫变换是从黑白图像中检测直线(线段);

霍夫变换是图像处理中的一种特征提取技术,该过程在一个参数空间中通过
计算累计结果的局部最大值,得到一个符合该特定形状的集合作为霍夫变换结果;

这种方法的一个突出优点是分割结果的Robustness,即对数据的不完全或噪声
不是非常敏感;
霍夫变换运用两个坐标空间之间的变换将在一个空间中具有相同形状的曲线
或直线映射到另一个坐标空间的一个点上形成峰值,从而把检测任意形状的问题
转换为统计峰值问题;
霍夫线变换和霍夫圆变换;
霍夫线变换是一种用来寻找直线的方法,在使用霍夫线变换之前,首先要对图像进行边缘
检测的处理,即霍夫线变换的直接输入只能是边缘二值图像;
Opencv支持三种不同的霍夫线变换,他们分别是:标准霍夫变换(Standard Hough Transform,SHT),
多尺度霍夫变换(Multi-Scale Hough Transform MSHT),和累计概率霍夫变换(Progressive Probabilistic Hough Transform,PPHT);
多尺度霍夫变换为经典霍夫变换在多尺度下的一个变种;
而累计概率霍夫变换算法是标准霍夫变换算法的一个改进;
它在一定的范围内进行霍夫变换，计算单独线段的方向及范围,从而减少
计算量,缩短计算时间;
之所以称PPHT为概率,是因为并不将累加器平面内的所有可能的点累加,
而只累加其中一部分,该想法是如果峰值足够高,只用一部分时间去寻找它就够了,
按照猜想,可以实质的减少计算时间;

在OpenCV中,可以用HoughLines函数来调用标准霍夫变换(SHT)和多尺度霍夫变换(MSHT);
而HoughLinesP函数用于调用累计概率霍夫变换PPHT;累计概率霍夫变换执行效率
很高,所有相比于HoughLines函数,更倾向于HoughLineP函数;

标准霍夫变换和多尺度霍夫变换,由HoughLines函数调用;
累计概率霍夫变换由HoughLinesP函数调用;

标准霍夫变换:HoughLines()函数
此函数可以找出采用标准霍夫变换的二值图像线条;
C++:void HoughLines(InputArray image,OutputArray lines,double rho,
double theta,int threshold,double,srn=0,double srn=0)
第一个参数:需要单通道二进制图像,
第二个参数:经过调用HoughLines函数后存储了霍夫变换检测到线条的输出矢量;
每一条线由具有两个元素的矢量(p,q)表示;
p是离坐标原点(0,0)也就是图像左上角的距离,q表示弧度线条旋转角度(0度表示垂直线,PI/2表示水平线)
第三个参数:double类型的rho,以像素为单位的距离精度;另一种表述方式是直线搜索时的进步尺寸的单位角度;
第四个参数:double类型的theta,以弧度为单位的角度精度;另外一种表述方式是直线搜索时的
进步尺寸的单位角度;
第五个参数:int类型的threshold,累加平面的阈值参数;即识别某部分为图中的一条直线时,
它在累加平面必须达到的值;大于阈值threshold的线段才可以被检测通过并返回到结果中;
第六个参数:double类型的srn,有默认值0,对于多尺度的霍夫变换,这是第三个参数进步尺寸rho
的除数距离;粗略的累加器进步尺寸直接是第三个参数,精确的累加器进步尺寸为rho/sm;
第七个参数:double类型的stn,有默认值为0;对于多尺度霍夫变换,srn表示第四个参数
进步尺寸的单位角度theta的除数距离;如果srn和stn同时为0,就表示使用经典的霍夫变换,
否则,这两个参数应该都是为正数;


*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//进行边缘检测和转化为恢复图
	Canny(src_img, temp_img, 50, 200, 3);
	imshow("src_img", src_img);
	//imshow("temp_img", temp_img);
	//image.size().width==image.cols;        image.size().height==image.rows 
	cout << "src_img.dims:" << src_img.dims << endl;	
	//cout << "src_img.type():" << src_img.type() << endl;
	cout << "src_img.channels:" << src_img.channels() << endl;
	cout << "src_img.depth():" << src_img.depth() << endl;
	cout << "src_img.rows:" << src_img.rows << endl;
	cout << "src_img.cols:" << src_img.cols << endl;
	cout << "temp_img.channels():" << temp_img.channels() << endl;
	//waitKey(0);

	//转换边缘检测后的图为灰度图
	cvtColor(temp_img,gray_img,COLOR_BGR2GRAY);

	//进行霍夫线变换
	vector<Vec2f>lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
	HoughLines(temp_img,lines,1,CV_PI/180,150,0,0);

	//依次在图中绘制出每条线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0+1000*(-b));
		pt1.y = cvRound(y0+1000*(a));
		pt2.x = cvRound(x0-1000*(-b));
		pt2.y = cvRound(y0-1000*(a));
		//调节line(dst_img,pt1,pt2,Scalar(55,100,195),1,CV_AA);
		//中的Scalar(55,100,195)参数G,B,R颜色值的数值,得到图中想要的线条颜色
		line(gray_img, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
	}

	imshow("temp_img", temp_img);
	imshow("gray_img", gray_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
