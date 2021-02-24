#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat logo = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\6.jpg");
	Mat mask = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\6.jpg", 0);//以灰度图的形式读入
	bitwise_not(mask, mask);//图像取反，白色背景变黑
	imshow("mask", mask);
	threshold(mask, mask, 50, 255, THRESH_BINARY);//二值化，50这个取值是经过调试后选择的，若取值为100则左下角的标志会消失
	imshow("threshold", mask);

	Mat ROI = img(Rect(20, 20, logo.cols, logo.rows));//x,y,w,h    xy坐标，宽度，高度
	logo.copyTo(ROI, mask);//logo复制到ROI上面

	imshow("img", img);
	waitKey(0);
}