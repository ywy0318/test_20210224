#include "opencv2/opencv.hpp"
using namespace cv;

Mat src, dst;
int min_thres = 30, max_thres = 100;//不能直接命名为min，max，标准库std里有min和max方法

void onCanny(int, void*) {
	Canny(src, dst, min_thres, max_thres);
	imshow("src", src);
	imshow("Canny", dst);
}
//注意：canny边缘检测后，图像为灰度图！
//检测工件是否平整，检测布料是否平滑
void main()
{
	src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\7.jpg", 0);
	namedWindow("Canny", CV_WINDOW_AUTOSIZE);
	createTrackbar("min_thres", "Canny", &min_thres, 255, onCanny, 0);
	createTrackbar("max_thres", "Canny", &max_thres, 255, onCanny, 0);

	onCanny(min_thres, 0);//回调函数初始化
	onCanny(max_thres, 0);

	waitKey(0);
	destroyAllWindows();
}