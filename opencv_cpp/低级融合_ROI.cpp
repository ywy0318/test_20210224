#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat logo = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\6.jpg");
	Mat ROI = img(Rect(20, 20, logo.cols, logo.rows));//x,y,w,h    xy坐标，宽度，高度
													  //Mat ROI=img(Range(20,20+logo.rows),Range(20,20+logo.cols));//纵坐标范围，行坐标范围
	logo.copyTo(ROI);//logo复制到ROI上面

	imshow("img", img);
	waitKey(0);
}