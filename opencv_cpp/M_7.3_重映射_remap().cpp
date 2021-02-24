/*
7.3重映射
重映射的概念:
重映射,就是把一副图像中某位置的像素放置到另外一个图片
指定位置的过程;为了完成重映射,需要获得一些插值为非整数
像素的坐标,因为源图像与目标图像的像素坐标不是一一对应的,
实现重映射:remap()函数
remap()函数会根据指定的映射形式,将源图像进行重映射
几何变换,基于以下的公式:
dst(x,y)=src(mapx(x,y),mapy(x,y))
此函数不支持就地操作,
C++:void remap(InpuArray src,OutputArray dst,InputArray,map1,InputArray map2,
int interpolation,inteborderMode=BORDER_CONSTANT,const Scalar&borderValue=Scalar())

第三个参数:InputArray类型的map1,它有两种可能的表示对象;
表示点(x,y)的第一个映射
表示CV_16SC2,CV_32FC1,CV_32FC2类型的X值;

第四个参数:InputArray类型的map2,它也有两种可能的表示对象;
根据map1来确定表示那种对象
map1表示点(x,y)时,这个参数不代表任何值;
表示CV_16UC1,CV_32FC1类型的Y值(第二个值);
第五个参数,int类型的interpolation,插值方式,之前的resize()函数
中有讲到;
INTER_NEAREST--最近邻插值
INTER_LINEAR--双线性插值(默认值)
INTER_CUBIC--双三次样条插值(逾4X4像素邻域内的双三次插值)
INTER_LANCZOS4--Lanczos插值(逾8X8像素邻域的Lanczos插值)
第六个参数:int类型的border,边界模式
第七个参数:const Scalar&类型的borderValue,当有常数边界时使用的值,
默认值Scalar().默认值为0;


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
	Mat map_x, map_y;
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);
	//创建和原始图一样的效果图,x重映射图,y重映射图
	dst_img.create(src_img.size(),src_img.type());
	map_x.create(src_img.size(),CV_32FC1);
	map_y.create(src_img.size(), CV_32FC1);
	//双层循环,遍历每一个像素点,改变map_x,map_y的值
	for (size_t i = 0; i < src_img.rows; i++)
	{
		for (size_t j = 0; j < src_img.cols; j++)
		{
			//改变map_x,map_y的值
			map_x.at<float>(j, i) = static_cast<float>(i);
			map_y.at<float>(j, i) = static_cast<float>(src_img.rows - j);
		}
	}
	//进行重映射操作
	remap(src_img, dst_img, map_x, map_y, INTER_LINEAR,BORDER_DEFAULT,Scalar(0,0,0));
	imshow("dst_img",dst_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
