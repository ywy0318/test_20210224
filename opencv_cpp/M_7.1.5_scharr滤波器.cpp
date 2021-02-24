/*7.1.5scharr滤波器
scharr滤波器,在opencv中主要是配合Sobel算子的运算而存在的;
1.>计算图像差分:Scharr()函数
使用Scharr滤波器运算符计算x与y方向的图像差分;其实它的
参数变量和Sobel基本上是一样的,除了没有ksize核的大小;
C++:void Scharr(InputArray src,OutputArray dst,int ddepth,
int dx,int dy,double scale=1(缩放因子),double delta=0,int boederType=BORDER_DEFAULT)

Scharr(src,dst,ddepth,dx,dy,scale,delta,borderType)
Sobel(src,dst,ddepth,dx,dy,CV_SCHARR,scale,delta,borderType)
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
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);
	//x方向梯度
	Scharr(src_img,grad_x,CV_16S,1,0,1,0,BORDER_DEFAULT);
	convertScaleAbs(grad_x,abs_grad_x);
	imshow("abs_grad_x",abs_grad_x);

	//y方向梯度
	Scharr(src_img,grad_y,CV_16S,0,1,1,0,BORDER_DEFAULT);
	convertScaleAbs(grad_y,abs_grad_y);
	imshow("abs_grad_y",abs_grad_y);
	
	//合并梯度(近似)
	addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,dst_img);
	imshow("addWeighted",dst_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
