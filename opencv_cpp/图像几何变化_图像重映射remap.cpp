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
				xMap.at<float>(i, j) = j;//�����в���
				//yMap.at<float>(i, j) = i + 5 * ctg(j / 10.0);//tanˮ��Ч��
				yMap.at<float>(i, j) = i + 5 * tan(j / 10.0);//tanˮ��Ч��
			 //yMap.at<float>(i,j)=i+5*sin(j/10.0);//sinˮ��Ч��
			// yMap.at<float>(i, j) = i + 5 * cos(j / 10.0);//cosˮ��Ч�� �������
			//	yMap.at<float>(i, j) = rows - i;//���·�ת
		}
	}
	remap(src, dst, xMap, yMap, CV_INTER_LINEAR);

	imshow("src", src);
	//namedWindow("des", CV_WINDOW_NORMAL);
	imshow("dst", dst);
	waitKey(0);
}