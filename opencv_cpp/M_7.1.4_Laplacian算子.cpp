/*
Laplacian算子是n维欧几里德空间中的一个二阶微分算子,
根据图像处理的原理可知，二阶导数可以用来进行检测边缘,
因为图像是"二维的",需要在两个方向上进行求导,
使用Laplacian算子将会使求导过程变得简单;
由于Laplacian算子使用了图像梯度,它内部的代码其实是调用了
Sobel算子;
让一幅图像减去它的Laplacian算子可以增强对比度;
Laplacian()函数可以计算出图像经过拉普拉斯变换后的结果;
C++:void Laplacian(InputArray src,OutputArray dst,int ddepth,
int ksize=1,double=scale=1,double delta=0,intborderType=BORDER_DEFAULT);
ddepth,目标图像的深度
double类型的scale,计算拉普拉斯值的时候可选的比例因子,默认值为1;
第六个参数:double类型的delta,表示在结果存入目标图(第二个参数dst)
之前可选的delta值,默认值为0;

*/#include<iostream>
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
	imshow("src_img", src_img);
	//使用高斯滤波消除噪声
	GaussianBlur(src_img,src_img,Size(3,3),0,0,BORDER_DEFAULT);
	//转换为灰度图
	cvtColor(src_img,gray_img,COLOR_RGB2BGRA);
	//使用Laplacian函数
	Laplacian(gray_img,dst_img,CV_16S,3,1,0,BORDER_DEFAULT);
	//计算绝对值,并将结果转换成8位
	convertScaleAbs(dst_img, temp_img);
	imshow("dst_img",temp_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
