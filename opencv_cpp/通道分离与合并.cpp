#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\6.jpg");
	Mat dst;
	vector<Mat>channels;//����Mat���͵�����

	split(img, channels);//ͨ������
	Mat blue = channels.at(0);
	Mat green = channels.at(1);
	Mat red = channels.at(2);

	threshold(blue, blue, 200, 255, THRESH_BINARY);//��ֵ��������200�ĸ�ֵ255��С��200�ĸ�ֵ0
	threshold(green, green, 200, 255, THRESH_BINARY);
	threshold(red, red, 200, 255, THRESH_BINARY);

	merge(channels, dst);//ͨ���ϲ�

	imshow("ԭͼ", img);
	imshow("blue", blue);
	imshow("green", green);
	imshow("red", red);
	imshow("dst", dst);
	waitKey(0);
}