#include<opencv2/opencv.hpp>
using namespace cv;

//不改变图像大小
Mat imgTranslate(Mat &src, int x_off, int y_off) {//x方向偏移,y方向偏移
	int rows = src.rows;//行
	int cols = src.cols;//列
	Mat dst = Mat::zeros(src.size(), src.type());//创建一个全黑图像
	for (int i = 0; i < rows; i++)//遍历行
	{
		for (int j = 0; j < cols; j++)//遍历列
		{

			int x = j + x_off;//列坐标+x方向偏移=当前x坐标
			int y = i + y_off;
			if (x >= 0 && y >= 0 && x<cols&&y<rows) {
				dst.at<Vec3b>(y, x) = src.at<Vec3b>(i, j);//赋值，（y,x）对应(i,j)，详情见下面图示
			}
		}
	}
	return dst;
}
//改变图像大小
Mat imgTranslate2(Mat &src, int x_off, int y_off) {
	int rows = src.rows + y_off;
	int cols = src.cols + x_off;
	Mat dst = Mat::zeros(rows, cols, src.type());//注意与上面的差别，行列重新选值
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{

			int x = j + x_off;
			int y = i + y_off;
			if (x >= 0 && y >= 0 && x<cols&&y<rows) {
				dst.at<Vec3b>(y, x) = src.at<Vec3b>(i, j);
			}
		}
	}
	return dst;
}

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dst=imgTranslate(src,20,30);
	//Mat dst = imgTranslate2(src, -20, -30);
	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
}