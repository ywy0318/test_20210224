#include<opencv2/opencv.hpp>
using namespace cv;

#define WIN_NAME "���ͼ��"
Mat src, dst;
int contrast = 20, bright = 20;

void onChange(int, void*) {
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			//saturate_cast<uchar>    ���������if(data<0) data=0;    if(data>255) data=255;
			dst.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(src.at<Vec3b>(i, j)[0] * contrast*0.01 + bright);
			dst.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(src.at<Vec3b>(i, j)[1] * contrast*0.01 + bright);
			dst.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(src.at<Vec3b>(i, j)[2] * contrast*0.01 + bright);
		}
	}
	imshow("ԭͼ", src);
	imshow(WIN_NAME, dst);
}

void main() {
	src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	dst = Mat::zeros(src.size(), src.type());
	//Mat::zeros();//������Ԫ����Ϊ0
	//Mat::ones();//��1
	namedWindow(WIN_NAME, CV_WINDOW_AUTOSIZE);
	createTrackbar("�Աȶ�", WIN_NAME, &contrast, 300, onChange, 0);
	createTrackbar("��  ��", WIN_NAME, &bright, 200, onChange, 0);

	onChange(contrast, 0);//�ص�������ʼ��
	onChange(bright, 0);

	waitKey(0);

}