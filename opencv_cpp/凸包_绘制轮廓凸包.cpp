#include<opencv2/opencv.hpp>
using namespace cv;

void main()
{
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	imshow("src", srcImg);
	Mat dstImg2 = srcImg.clone();
	Mat tempImg(srcImg.rows, srcImg.cols, CV_8UC3, Scalar::all(0));  //���ڻ���͹��
	Mat dstImg(srcImg.rows, srcImg.cols, CV_8UC3, Scalar::all(0));  //���ڻ�������
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY); //��ֵ��

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	vector<vector<Point>> hull(contours.size());
	for (int i = 0; i<contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], true);     //����͹��
		drawContours(dstImg, contours, i, Scalar(255, 255, 255), -1, 8);  //��������
																		  //drawContours(dstImg, hull, i, Scalar(rand()%255, rand()%255, rand()%255), 2, 8);
		drawContours(tempImg, hull, i, Scalar(255, 255, 255), -1, 8);
	}
	imshow("hull", tempImg);
	imshow("contours", dstImg);

	Mat diffImg;
	absdiff(tempImg, dstImg, diffImg);  //ͼ�����
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	erode(diffImg, diffImg, element);
	imshow("diff", diffImg);

	vector<vector<Point>> contours2;
	vector<Vec4i> hierarcy2;
	cvtColor(diffImg, diffImg, CV_BGR2GRAY); //תΪ�Ҷ�ͼ
	threshold(diffImg, diffImg, 100, 255, CV_THRESH_BINARY); //��ֵ��
	findContours(diffImg, contours2, hierarcy2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	drawContours(dstImg2, contours2, -1, Scalar(0, 0, 255), 2, 8);  //��ɫ����ȱ������
	imshow("defects", dstImg2);
	waitKey(0);
}