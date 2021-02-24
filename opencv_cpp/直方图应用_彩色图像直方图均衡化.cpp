#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	imshow("src", src);

	//�ָ�ͨ��
	vector<Mat>channels;
	split(src, channels);
	Mat blue, green, red, dst;
	blue = channels.at(0);
	green = channels.at(1);
	red = channels.at(2);
	//�ֱ��BGRͨ����ֱ��ͼ���⻯
	equalizeHist(blue, blue);
	equalizeHist(green, green);
	equalizeHist(red, red);
	//�ϲ�ͨ��
	merge(channels, dst);
	imshow("dst", dst);

	waitKey(0);
}