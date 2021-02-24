/*
8.1.4�ۺ�ʾ������:���Ҳ���������
����ͼ��ƽ������(blur()����)�ͱ�Ե��⼼��(canny()����),
���ݻ������ĵ���,��̬�ļ���ͼ�ε�����;
*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;

int g_nThresh = 80;
int g_nThresh_max = 255;
RNG g_rng(12345);
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

void on_ThreshChange(int, void*);

int main()
{
	system("color 1F");
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//ת�ɻҶȲ�ģ��������
	cvtColor(src_img,gray_img,COLOR_BGR2BGRA);
	blur(gray_img,gray_img,Size(3,3));
	namedWindow("src_img",CV_WINDOW_AUTOSIZE);
	imshow("src_img", src_img);
	//��������������ʼ��
	createTrackbar("canny��ֵ","src_img",&g_nThresh,g_nThresh_max,on_ThreshChange);
	on_ThreshChange(0,0);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
void on_ThreshChange(int, void*)
{
	//��Canny���Ӽ���Ե
	Canny(gray_img,edge_img,g_nThresh,g_nThresh*2,3);
	//Ѱ������
	findContours(edge_img, g_vContours, g_vHierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

	Mat draw_img = Mat::zeros(edge_img.size(),CV_8UC3);
	for (size_t i = 0; i < g_vContours.size(); i++)
	{
		//����ֵ
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(draw_img,g_vContours,i,color,2,8,g_vHierarchy,0,Point());
	}
	namedWindow("draw_img",CV_WINDOW_AUTOSIZE);
	imshow("draw_img",draw_img);
}