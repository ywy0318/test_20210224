#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	//������С��Ӿ��εĻ���
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\20.jpg");
	Mat dstImg = srcImg.clone();
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY); //��ֵ��
	imshow("threshold", srcImg);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	vector<Rect> boundRect(contours.size());  //������Ӿ��μ���
	vector<RotatedRect> box(contours.size()); //������С��Ӿ��μ���
	Point2f rect[4];
	for (int i = 0; i<contours.size(); i++)
	{
		box[i] = minAreaRect(Mat(contours[i]));  //����ÿ��������С��Ӿ���
		boundRect[i] = boundingRect(Mat(contours[i]));
		circle(dstImg, Point(box[i].center.x, box[i].center.y), 5, Scalar(0, 255, 0), -1, 8);  //������С��Ӿ��ε����ĵ�
		box[i].points(rect);  //����С��Ӿ����ĸ��˵㸴�Ƹ�rect����
		rectangle(dstImg, Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height), Scalar(0, 255, 0), 2, 8);
		for (int j = 0; j<4; j++)
		{
			line(dstImg, rect[j], rect[(j + 1) % 4], Scalar(0, 0, 255), 2, 8);  //������С��Ӿ���ÿ����
		}
	}
	imshow("dst", dstImg);
	waitKey(0);
}