#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	//Canny��Ե���
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\7.jpg", 0); //0��ʾ�ԻҶ�ͼ����,��ɫͼ�ͻҶ�ͼ���б�Ե���ʱ���в�ͬ,����ʹ�ûҶ�ͼ
	medianBlur(srcImg, srcImg,5);//��ֵ�˲�
	imshow("src", srcImg);

	Mat dstImg;
	Canny(srcImg, dstImg, 30, 80);
	imshow("Canny", dstImg);
	waitKey(0);
}