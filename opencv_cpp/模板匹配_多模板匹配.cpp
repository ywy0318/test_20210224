#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void main()
{
	Mat srcImg = imread("E://src.png");
	Mat templateImg = imread("E://temp.png");
	Mat resultImg;
	Mat showImg = srcImg.clone();

	int resultImg_cols = srcImg.cols - templateImg.cols + 1;
	int resultImg_rows = srcImg.rows - templateImg.rows + 1;

	resultImg.create(resultImg_cols, resultImg_rows, CV_32FC1);
	matchTemplate(srcImg, templateImg, resultImg, CV_TM_CCOEFF_NORMED); //化相关系数匹配法(最好匹配1)
	normalize(resultImg, resultImg, 0, 1, NORM_MINMAX);
	Mat midImg = resultImg.clone();

	//多目标模板匹配---方法一
	/*double matchValue;
	int count0=0;
	int tempW=0, tempH=0;
	char matchRate[10];

	for(int i=0; i<resultImg_rows; i++)
	{
	for(int j=0; j<resultImg_cols; j++)
	{
	matchValue = resultImg.at<float>(i, j);
	sprintf(matchRate, "%0.2f", matchValue);
	if(matchValue>=0.85 && (abs(j - tempW)>5) && (abs(i - tempH)>5) )
	{
	count0++;
	putText(showImg, matchRate, Point(j-5, i-5), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1);
	rectangle(showImg, Point(j, i), Point(j + templateImg.cols, i + templateImg.rows), Scalar(0, 255, 0), 2);
	tempW = j;
	tempH = i;
	}
	}
	}
	cout<<"count="<<count0<<endl;
	imshow("resultImg", resultImg);
	imshow("dst", showImg);*/

	//多目标模板匹配---方法二
	double minValue, maxValue;
	Point minLoc, maxLoc;
	Point matchLoc;
	char matchRate[10];

	for (int i = 0; i<100; i++)
	{
		int startX = maxLoc.x - 4;
		int startY = maxLoc.y - 4;
		int endX = maxLoc.x + 4;
		int endY = maxLoc.y + 4;
		if (startX<0 || startY<0)
		{
			startX = 0;
			startY = 0;
		}
		if (endX > resultImg.cols - 1 || endY > resultImg.rows - 1)
		{
			endX = resultImg.cols - 1;
			endY = resultImg.rows - 1;
		}
		Mat temp = Mat::zeros(endX - startX, endY - startY, CV_32FC1);
		//Mat ROI = resultImg(Rect(Point(startX, startY), temp.cols, temp.rows));
		temp.copyTo(resultImg(Rect(startX, startY, temp.cols, temp.rows)));
		minMaxLoc(resultImg, &minValue, &maxValue, &minLoc, &maxLoc);
		if (maxValue<0.8)    break;

		cout << "max_value= " << maxValue << endl;
		sprintf(matchRate, "%0.2f", maxValue);
		putText(showImg, matchRate, Point(maxLoc.x - 5, maxLoc.y - 5), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1);
		rectangle(showImg, maxLoc, Point(maxLoc.x + templateImg.cols, maxLoc.y + templateImg.rows), Scalar(0, 255, 0), 2);

	}
	imshow("midImg", midImg);
	imshow("resultImg", resultImg);
	imshow("dst", showImg);

	waitKey(0);
}