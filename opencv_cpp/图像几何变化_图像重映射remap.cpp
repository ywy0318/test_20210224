#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\6.jpg");
	Mat dst;

	int rows = src.rows;
	int cols = src.cols;
	Mat xMap = Mat::zeros(src.size(), CV_32FC1);//map1
	Mat yMap = Mat::zeros(src.size(), CV_32FC1);//map2

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
				xMap.at<float>(i, j) = j;//保持列不变
				//yMap.at<float>(i, j) = i + 5 * ctg(j / 10.0);//tan水波效果
				yMap.at<float>(i, j) = i + 5 * tan(j / 10.0);//tan水波效果
			 //yMap.at<float>(i,j)=i+5*sin(j/10.0);//sin水波效果
			// yMap.at<float>(i, j) = i + 5 * cos(j / 10.0);//cos水波效果 随便试试
			//	yMap.at<float>(i, j) = rows - i;//上下翻转
		}
	}
	remap(src, dst, xMap, yMap, CV_INTER_LINEAR);

	imshow("src", src);
	//namedWindow("des", CV_WINDOW_NORMAL);
	imshow("dst", dst);
	waitKey(0);
}