#include "opencv2/opencv.hpp"
using namespace cv;
void main()
{
	//---简单车牌字符分隔
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\15.jpg");
	Mat dstImg = srcImg.clone();  //原图备份
	medianBlur(srcImg, srcImg, 5);  //中值滤波
	cvtColor(srcImg, srcImg, CV_BGR2GRAY); //转为灰度图
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY); //二值化
	imshow("threshold", srcImg);
	imwrite("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\999.jpg", srcImg);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_TREE, CHAIN_APPROX_NONE); //查找所有轮廓
	vector<Rect> boundRect(contours.size()); //定义外接矩形集合
	int x0 = 0, y0 = 0, w0 = 0, h0 = 0;
	for (int i = 0; i<contours.size(); i++)
	{
		boundRect[i] = boundingRect((Mat)contours[i]); //查找每个轮廓的外接矩形
		x0 = boundRect[i].x;
		y0 = boundRect[i].y;
		w0 = boundRect[i].width;
		h0 = boundRect[i].height;
		if (w0>srcImg.cols / 12 && w0<srcImg.cols / 5 && h0>srcImg.rows / 6 && h0<srcImg.rows * 5 / 6)
		{
			char pic_name[10];
			sprintf(pic_name, "F:\\%d.bmp", i);
			Mat ROI = dstImg(Rect(x0, y0, w0, h0));
			imwrite(pic_name, ROI);
			rectangle(dstImg, Point(x0, y0), Point(x0 + w0, y0 + h0), Scalar(0, 255, 0), 2, 8); //绘制第i个外接矩形
		}
	}
	imshow("boundRect", dstImg);
	waitKey(0);
}