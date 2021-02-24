#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\8.jpg");
	Mat dst;
	imshow("src", src);

	Canny(src, src, 50, 200);
	imshow("Canny", src);
	//cvtColor(src, dst, CV_BGR2GRAY);//��ɫͼת�Ҷ�ͼ������䲻�ܷ���canny��Ե����canny����ͼ���Ϊ�˻Ҷ�ͼ��
	cvtColor(src, dst, CV_GRAY2BGR);//�Ҷ�ͼת��ɫͼ

									//���л����߱任
	vector<Vec2f> lines;  //����ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	HoughLines(src, lines, 1, CV_PI / 180, 150);//����150���߶βű���⵽

												//������ͼ�л��Ƴ�ÿ���߶�
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));//cvRound(double value) ��������һ��double�������������룬����һ������
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dst, pt1, pt2, Scalar(55, 100, 195), 2, 8);
	}

	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();
}