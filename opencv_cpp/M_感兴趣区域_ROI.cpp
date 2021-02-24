/*
ROI,region of interest
����ROI���������ַ���:
��һ����ʹ�ñ�ʾ���������Rect;��ָ�����ε����Ͻ�����(���캯����ǰ��������)�;��εĳ���(���캯���ĺ���������)

Mat imageROI=image(Rect(500,250,logo.cols,logo.rows));

��һ�ֶ���ROI�ķ�ʽ��ָ������Ȥ�л����еķ�Χ(Range);
Range��ָ����ʼ��������ֹ����(��������ֹ����)��һ������������;
cRange������������Range;
���ʹ��Range������ROI
//����2

Mat imageROI=image(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols))

*/


#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int main()
{
	string imgpath4 = "1.jpg";
	Mat img = imread(imgpath4, 1);//����ͼƬ����
	if (img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	string imgpath2 = "2.jpg";
	Mat img_2 = imread(imgpath2, 1);//����ͼƬ����
	if (img_2.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}

	//����һ��Mat���Ͳ������趨ROI����
	Mat image_ROI = img(Rect(200,250,img_2.cols,img_2.rows));
	//��������(�����ǻҶ�ͼ)
	Mat mask = imread(imgpath2,0);
	
	//�����븴�Ƶ�ROI
	img_2.copyTo(image_ROI, mask);
	//��ʾ���
	namedWindow("<1>����ROIʵ��ͼ�����ʵ������");
	imshow("<1>����ROIʵ��ͼ�����ʵ������",img);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
