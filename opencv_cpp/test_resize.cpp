#include<iostream>
#include<opencv2\opencv.hpp>
#include "highgui.h"
#include"cvaux.h"
#include"cxcore.h"
#include"opencv2/imgproc.hpp"
#include<string>
using namespace std;
using namespace cv;
/*
ʹ��resize�����ı�ͼ��ĳߴ�

����ԭ�ͣ�

void resize(InputArray src, OutputArray dst, Size dsize, double fx=0, double fy=0, int interpolation=INTER_LINEAR )

srcԴͼ�� dstĿ��ͼ�� dsizeĿ��ͼ��Ĵ�С ��������������Ƚ�ֱ�ۣ�
������Ҫע�����dsize��fx��fy���벻��ͬʱΪ�㣬
Ҳ����˵Ҫôdsize��Ϊ���fx��fyͬʱ����Ϊ0��ҪôdsizeΪ0��fx��fy��ͬʱΪ0��
resize������Ŀ���С����������Ĵ�С�����Բ����ֳ�����ʣ�
ɾ�������ػ�������������ֵͨ��interpolation���ڲ壩���ƣ� 
fx��fy�ֱ�ָˮƽ�ʹ�ֱ����ı��ʣ�
���dsize Ϊ�㣬��Ŀ��ͼ��Ĵ�С��ͨ������������������ģ�
Ŀ��ͼ��Ŀ��Ϊԭͼ��Ŀ��*fx,ͬ��Ŀ��ͼ��ĸ߶�Ϊԭͼ��ĸ߶�*fy; 
���dsize��Ϊ��,fx,fy���Զ����㣺 fx=dsize.width/src.cols; fy=dsize.height/src.rows; 
���dsize�ͣ�fx,fy��ֻ����������һ��������һ����Ϊ��Ϳ����ˡ�
interpolationȡֵ�� INTER_NN - ����ڲ�ֵ�� INTER_LINEAR - ˫���Բ�ֵ (ȱʡʹ��)�� 
INTER_AREA - ʹ�����ع�ϵ�ز�����
��ͼ����Сʱ�򣬸÷������Ա��Ⲩ�Ƴ��֡�
��ͼ��Ŵ�ʱ�������� INTER_NN ������ INTER_CUBIC - ������ֵ��
*/
int main()
{
	Mat src_img, des_img0;
	
	string path = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	src_img = imread(path, IMREAD_COLOR);
	if (src_img.empty())
	{
		cout << "imread file failed" << endl;
	}
	cout <<"src_img.type():"<< src_img.type() << endl;
	Mat des_img1(src_img.rows*0.5, src_img.cols*0.5, src_img.type());
	namedWindow("src_img", WINDOW_AUTOSIZE);
	imshow("src_img", src_img);
	namedWindow("des_img1", WINDOW_AUTOSIZE);
	imshow("des_img1",des_img1);

	//
	
	//˫���Բ�ֵ
	resize(src_img,des_img0,Size(),0.5,0.5);
	//������ֵ
	resize(src_img, des_img1, des_img1.size(), INTER_CUBIC);
	namedWindow("resize des_img0", WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	namedWindow("resize des_img1", WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	imshow("resize des_img0", des_img0);
	imshow("resize des_img1",des_img1);

	waitKey(0);
	system("pause");
	return 0;
}