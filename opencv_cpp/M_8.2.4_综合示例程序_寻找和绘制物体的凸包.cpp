/*
8.2.4�ۺ�ʾ������:Ѱ�Һͻ��������͹��
��ϻ�����,ͨ��������������ֵ,�õ���ͬ��͹�����Ч��
*/
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;

int g_nThresh = 50;
int g_nThresh_max = 255;
RNG g_rng(12345);
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
Mat src_img_copy = src_img.clone();
vector<vector<Point>> g_vContours;
vector<Vec4i> g_nHierarchy;
void on_ThreshChange(int, void*);

int main()
{

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
	blur(gray_img,gray_img,Size(3,3));
	namedWindow("src_img", CV_WINDOW_AUTOSIZE);
    imshow("src_img", src_img);
	//����������
	createTrackbar("��ֵ:","src_img",&g_nThresh,g_nThresh_max,on_ThreshChange);
	on_ThreshChange(0,0);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
void on_ThreshChange(int, void*)
{
	//��ͼ����ж�ֵ��,������ֵ
	threshold(gray_img,edge_img,g_nThresh,255,THRESH_BINARY);
	//Ѱ������
	findContours(edge_img,g_vContours,g_nHierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));
	//����ÿ������,Ѱ����͹��
	vector<vector<Point>> hull(g_vContours.size());
	for (size_t i = 0; i < g_vContours.size(); i++)
	{
		convexHull(Mat(g_vContours[i]),hull[i],false);
	}
	//�����������͹��
	Mat draw_img = Mat::zeros(edge_img.size(), CV_8UC3);
	for (size_t i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(draw_img,g_vContours,i,color,1,8,vector<Vec4i>(),0,Point());
		drawContours(draw_img,hull,i,color,1,8,vector<Vec4i>(),0,Point());
	}
	imshow("draw_img",draw_img);
}
