#include<opencv2/opencv.hpp>
using namespace cv;

#define WIN_NAME "输出图像"
Mat src, dst;
int contrast = 20, bright = 20;

void onChange(int, void*) {
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			//saturate_cast<uchar>    溢出保护：if(data<0) data=0;    if(data>255) data=255;
			dst.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(src.at<Vec3b>(i, j)[0] * contrast*0.01 + bright);
			dst.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(src.at<Vec3b>(i, j)[1] * contrast*0.01 + bright);
			dst.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(src.at<Vec3b>(i, j)[2] * contrast*0.01 + bright);
		}
	}
	imshow("原图", src);
	imshow(WIN_NAME, dst);
}

void main() {
	src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	dst = Mat::zeros(src.size(), src.type());
	//Mat::zeros();//将矩阵元素置为0
	//Mat::ones();//置1
	namedWindow(WIN_NAME, CV_WINDOW_AUTOSIZE);
	createTrackbar("对比度", WIN_NAME, &contrast, 300, onChange, 0);
	createTrackbar("亮  度", WIN_NAME, &bright, 200, onChange, 0);

	onChange(contrast, 0);//回调函数初始化
	onChange(bright, 0);

	waitKey(0);

}