/*
累计概率霍夫变换:HoughLineP()函数
HoughLineP()函数,可以用来找二值图像的直线
C++:void HoughLineP(InputArray image,OutputArray lines,double rho,
double theta,int threshold,double minLineLength=0,double maxLineGap=0)
第一个参数 ：需要8位的单通道二进制图像,可以将任意的源图像载入进来后由
函数修改成此格式后，再填到这里;
第二个参数:InputArray 类型的lines,经过调用HoughLineP函数后存储了检测到的线条
的输出矢量,每一条由具有4个元素的矢量(x_1,y_1,x_2,y_2)表示,其中
(x_1,y_1)和(x_2,y_2)是每个检测熬的线段的结束点;
第三个参数:double类型的rho,以像素为单位的距离精度;另一种表述方式是直线搜索时
的进步尺寸的单位半径
第四个参数:double类型的theta,以弧度为单位的角度精度;另一种表示方式是直线搜索时
的进步尺寸的单位角度;
第五个参数:int类型的threshold,累加平面的阈值参数,即识别某部分为图中的一条直线时,
它在累加平面中必须达到的值;大于阈值threshold的线段才可以被检测通过并且
返回到结果中;
第六个参数:double类型的minLineLength,有默认值为0,表示最低线段的长度,比这个设定参数
短的线段就不能被显现出来;
第七个参数:double类型的maxLineGap,有默认值为0,允许将同一行点与点之间连接起来的最大的距离

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
	//进行边缘检测和转换为灰度图
	Canny(src_img,temp_img,50,200,3);
	cvtColor(temp_img,dst_img,COLOR_GRAY2BGR);
	//进行霍夫线变换
	vector<Vec4i> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
	HoughLinesP(temp_img,lines,CV_PI/180,80,50,10);


	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dst_img,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(186,88,255),1,LINE_AA);
	}

	imshow("src_img", src_img);
	imshow("dst_img",dst_img);
	imshow("temp_img",temp_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
