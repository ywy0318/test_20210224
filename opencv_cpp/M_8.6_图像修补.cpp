/*
!!!!!!!!!!!!待续有问题
8.6图像修补
图像被噪声腐蚀,噪声可能是灰尘或者水滴或者是旧照片的划痕,或者图像本身已经损坏;
图像修复(Inpainting);
图像修复就是利用那些已经被破坏区域的边缘,边缘的颜色和结构,
繁殖和混合到损坏的图像中,以达到图像修补的目的;

图像修补:inpaint()函数
用来从扫描的照片中清扫灰尘和划痕,或者从静态图像或
视频中除去不需要的物体;
C++:void inpaint(InputArray src,InputArray inpaintMask,OutputArray dst,double inpaintRadius,
int flags)

第一个参数:8位单通道或者三通道图像
第二个参数:InputArray类型的inpaintMask,修复掩码,为8位的单通道图像;
其中的非零像素表示要修补的区域
第三个参数:和源图像一样的尺寸和类型
第四个参数:double类型的inpaintRadius,需要修补的每个点的圆形邻域,
为修复算法的参考半径
第五个参数:int类型的flags,修补方法的标识符;

INPAINT_NS---基于Navier-Stokes方程的方法
INPAINT_TELEA----Alexandru Telea方法

*/
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;

Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
Point previousPoint(-1,-1);//原来的点坐标

static void on_Mouse(int event, int x, int y, int flags, void*)
{
	//鼠标左键弹起消息
	if (event==EVENT_LBUTTONUP||!(flags&EVENT_FLAG_LBUTTON))
	{
		previousPoint = Point(-1,-1);
	}
	//鼠标左键按下消息
	else if (event==EVENT_LBUTTONDOWN)
	{
		previousPoint = Point(x,y);
	}
	//鼠标移动并且进行绘制
	else if(event==EVENT_MOUSEMOVE&&(flags&EVENT_FLAG_LBUTTON))
	{
		Point pt(x,y);
		if (previousPoint.x<0)
		{
			previousPoint = pt;			
		}
		line(mask_img, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		line(src_img, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		previousPoint = pt;
		imshow("src_img",src_img);
	}
}

int main()
{
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	temp_img = src_img.clone();
	mask_img = Mat::zeros(src_img.size(),src_img.type());
	namedWindow("src_img",WINDOW_AUTOSIZE);
	imshow("src_img", src_img);

	//设置鼠标回调消息
	setMouseCallback("src_img",on_Mouse,0);
	while (true)
	{
		char c = (char)waitKey();
		if (c == 27)
		{
			break;
		}
		if (c=='2')
		{
			edge_img = Scalar::all(0);
			src_img.copyTo(temp_img);
			imshow("src_img", src_img);
			//waitKey(0);
		}
		if (c=='1'||c==' ')
		{
			Mat inpainted_img;
			inpaint(temp_img, mask_img, inpainted_img,3,INPAINT_TELEA);
			
			namedWindow("inpainted_img", WINDOW_AUTOSIZE);
			imshow("inpainted_img", inpainted_img);
			//waitKey(0);
		}
		
	}
	return 0;
}