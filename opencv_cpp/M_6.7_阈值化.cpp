/*
�ڶԸ���ͼ����д�������Ĺ�����,��Ҫ��ͼ���е���������ȡ�������,
ֱ���޳�һЩ���ڻ��߸���һ��ֵ������;
��ֵ���Ա�������򵥵�ͼ��ָ�ķ���;
���ַָ������ͼ���������뱳��֮��ĻҶȲ���,�˷ָ��������ؼ��ķָ�;

һ��ͼ������ȡ��������Ҫ�Ĳ���,��ͼ���е�ÿһ�����ص�ĻҶ�ֵ��ѡȡ����ֵ
���бȽϣ�������Ӧ���ж�;
��ֵ:��ѡȡ�����ھ��������;�������ڲ�ͬ��ͼ���п��ܻ��в���ͬ�ĻҶ�ֵ;
һ���ҵ�����Ҫ�ָ����������ص�,���Զ���Щ���ص��趨һЩ�ض���ֵ����ʾ;
����:���Խ�����������ص�ĻҶ�ֵ����Ϊ"0"(��ɫ);
���������ص�����Ϊ�Ҷ�ֵ"255"(��ɫ);
�̶���ֵ����:
Threshold()����
Threshold()�����Ե�ͨ������Ӧ�ù̶���ֵ����;�ú����ĵ���Ӧ����
�Ի�ɫͼ�������ֵ�����õ���ֵͼ��;(compare()�������Դﵽ��Ŀ��),
����ȥ������,������˺�С��ܴ������ֵ��ͼ���;
C++:double threshold(InputArray src,OutputArray dst,double thresh,
double maxval,int type)
����������:double thresh,��ֵ�ľ���ֵ;
���ĸ�����:double ���͵�maxval,�����������ֵ����typeȡ
CV_THRESH_BINARY��CV_THRESH_INVʱ��ֵ����ʱ�����ֵ;

���������:int ���͵�type����ֵ����,threshold()֧�ֶ�ͼ��ȡ��ֵ
�ķ�������ȷ��;


adaptiveThreshold()�����������ǶԾ����������Ӧ��ֵ����,֧�־͵ز���;
C++:void adaptiveThreshold(InputArray src,OutputArray dst,double maxValue,
int adaptiveMethod,int thresholdType,int blockSize,double C)

����������:double���͵�maxValue,�����ظ������������ķ���ֵ;
���ĸ�����,int���͵�adaptiveMethod,����ָ��Ҫʹ�õ�����Ӧ��ֵ�㷨,
��ȡֵΪADAPTIVE_THRESH_MEAN_C����ADAPTIVE_THRESH_GAUSSIAN_C;
���������:int���͵�thresholdType,��ֵ����,ȡֵ����Ϊ
THRESH_BINARY,THRESH_BINARY_INV;

����������:int���͵�blockSize,���ڼ�����ֵ��С��һ�����ص�����ߴ�;
ͨ��ȡֵ3,5,7;
���߸�����:double���͵�C,��ȥƽ�����߼�Ȩƽ��ֵ��ĳ���ֵ,ͨ��
Ϊ����,������������¿���Ϊ0���߸���;

*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img;
int g_nThresholdValue = 100;
int g_nThresholdType = 3;

void on_Threshold(int, void*);//�ص�����
int main()
{

	

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);
	cvtColor(src_img,gray_img,COLOR_RGB2GRAY);
	namedWindow("dst_img",WINDOW_AUTOSIZE);

	createTrackbar("ģʽ","dst_img",&g_nThresholdType,4,on_Threshold);
	createTrackbar("����ֵ", "dst_img",&g_nThresholdValue,255,on_Threshold);

	on_Threshold(0,0);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
void on_Threshold(int, void*)
{
	threshold(gray_img,dst_img,g_nThresholdValue,255,g_nThresholdType);
	imshow("dst_img",dst_img);
}
