#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat logo = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\6.jpg");
	Mat mask = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\6.jpg", 0);//�ԻҶ�ͼ����ʽ����
	bitwise_not(mask, mask);//ͼ��ȡ������ɫ�������
	imshow("mask", mask);
	threshold(mask, mask, 50, 255, THRESH_BINARY);//��ֵ����50���ȡֵ�Ǿ������Ժ�ѡ��ģ���ȡֵΪ100�����½ǵı�־����ʧ
	imshow("threshold", mask);

	Mat ROI = img(Rect(20, 20, logo.cols, logo.rows));//x,y,w,h    xy���꣬��ȣ��߶�
	logo.copyTo(ROI, mask);//logo���Ƶ�ROI����

	imshow("img", img);
	waitKey(0);
}