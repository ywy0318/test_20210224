#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	//HoughLinesP()�÷�
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\8.jpg");
	Mat dstImg = src.clone();
	imshow("src", src);

	cvtColor(src, src, CV_BGR2GRAY);
	Canny(src, src, 50, 200);
	vector<Vec4i> lines;  //����ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	HoughLinesP(src, lines, 1, CV_PI / 180, 150, 50, 10);
	//������ͼ�л��Ƴ�ÿ���߶�
	for (size_t i = 0; i<lines.size(); i++)
	{
		Vec4i p = lines[i];
		line(dstImg, Point(p[0], p[1]), Point(p[2], p[3]), Scalar(0, 255, 0), 2, 8); //20
	}
	imshow("dst", dstImg);
	waitKey(0);
	destroyAllWindows();
}