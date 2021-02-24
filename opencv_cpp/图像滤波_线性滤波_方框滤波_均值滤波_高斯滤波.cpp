#include<opencv2/opencv.hpp>
using namespace cv;
//没看出啥效果来

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dst;
	//方框滤波器，-1代表原图像深度，size内核大小，true按权重相加（此时等于均值滤波），false按原像素相加（所以很多像素点都大于了255，如上图所示）
//	boxFilter(src, dst, -1, Size(3, 3), Point(-1, -1), true);
//	blur(src,dst,Size(5,5));//均值滤波
	//GaussianBlur(src,dst, Size(5, 5),1);//高斯滤波
//	 medianBlur(src, dst, 5);//中值滤波
  	bilateralFilter(src, dst, 5, 10.0, 2.0);//双边滤波
	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
}