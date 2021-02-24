#include<iostream>
#include<opencv2\opencv.hpp>
#include "highgui.h"
#include"cvaux.h"
#include"cxcore.h"
#include"cv.h"
#include"opencv2/imgproc.hpp"
#include<string>
using namespace std;
using namespace cv;
/*
��OpenCV�У�û���ֳɵĺ���ֱ������ʵ��ͼ����ת�������÷���任����warpAffine��ʵ�ֵģ�
�˺���Ŀǰ֧��4�ֲ�ֵ�㷨������ڡ�˫���ԡ�˫���Ρ�����˹��ֵ�� ����ԭ�ͣ�
void warpAffine(InputArray src, OutputArray dst, InputArray M, Size dsize, int flags=INTER_LINEAR, int borderMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar())

*/

Mat rotateImg(Mat img, int degree)
{
	degree = -degree;
	double angle = degree*CV_PI / 180;//����
	double a = sin(angle), b = cos(angle);
	int width = img.cols;
	int height = img.rows;
	int width_rotate = int(height*fabs(a) + width*fabs(b));
	int height_rotate = int(width*fabs(a) + height*fabs(b));
	//��ת����map
	//[m0,m1,m2]===>[A11,A12,b1]
	//[m3,m4,m5]===>[A21,A22,b2]
	float map[6];
	Mat map_matrix = Mat(2,3,CV_32F,map);
	//��ת����
	CvPoint2D32f center = cvPoint2D32f(width / 2, height / 2);
	CvMat map_materix2 = map_matrix;
	cv2DRotationMatrix(center,degree,1.0,&map_materix2);
	map[2] += (width_rotate - width) / 2;
	map[5] += (height_rotate - height) / 2;
	Mat img_rotate;
	//��ͼ��������任
	//CV_WARP_FILL_OUTLIERS--����������ͼ�������
	//�������������������ͼ��ı߽��⣬��ô���ǵ�ֵ�趨Ϊfillval
	//CV_WARP_INVERSE_MAP---ָ��map_matrix�����ͼ������ͼ��ķ��任
	warpAffine(img,img_rotate,map_matrix,Size(width_rotate,height_rotate),1,0,0);
	return img_rotate;
}
int main()
{
	Mat src_img, des_img0;

	string path = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	src_img = imread(path, IMREAD_COLOR);
	if (src_img.empty())
	{
		cout << "imread file failed" << endl;
	}
	cout << "src_img.type():" << src_img.type() << endl;
	namedWindow("src_img", WINDOW_AUTOSIZE);
	imshow("src_img", src_img);

	des_img0 = rotateImg(src_img,120);
	namedWindow("des_img0",WINDOW_AUTOSIZE);
	imshow("des_img0",des_img0);
	waitKey(0);
	system("pause");
	return 0;
}