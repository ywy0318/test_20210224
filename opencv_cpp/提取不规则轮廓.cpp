#include "opencv2/opencv.hpp"
using namespace cv;

void main() {
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\25.jpg");
	imshow("src", srcImg);
	Mat dstImg = srcImg.clone();  //ԭͼ����
	Mat tempImg = srcImg.clone();  //ԭͼ����
	Mat tempImg2(srcImg.size(), CV_8UC3, Scalar::all(0));  //����ȫ�ڵĺ�ԭͼһ����С��ͼ��
	Mat draw(srcImg.size(), CV_8UC3, Scalar::all(0));
	Mat tempImg3(srcImg.size(), CV_8UC3, Scalar::all(0));

	GaussianBlur(srcImg, srcImg, Size(3, 3), 0, 0);
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY); //��ֵ��
	imshow("threshold", srcImg);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	while (1)
	{
		for (int i = 0; i<contours.size(); i++)
		{
			tempImg2.copyTo(draw);  //ÿ�ν��뽫draw���Ϊȫ��
			tempImg2.copyTo(tempImg3);
			//drawContours(dstImg, contours, i, Scalar(0, 255, 0), 5, 8);    
			drawContours(draw, contours, i, Scalar(255, 255, 255), -1, 8);
			Mat mask;  //��������
			cvtColor(draw, mask, CV_BGR2GRAY);
			tempImg.copyTo(tempImg3, mask);  //��tempImg ���Ƶ�tempImg3(ֻ��mask���ֱ�����)
			imshow("draw", draw);
			imshow("result", tempImg3);
			char key = waitKey();
			if (key == 27)  //����Esc������forѭ��
				break;
		}
		break;
	}
}