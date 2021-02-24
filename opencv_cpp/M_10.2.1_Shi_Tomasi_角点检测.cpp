/*
10.2.1--Shi---Tomasi�ǵ������
��������Harris���нǵ���֮��,ͨ������������Shi-Tomasi�������нǵ���;
Shi-Tomasi�㷨��Harris�㷨�ĸĽ�,���㷨��ԭʼ�Ķ����ǽ�����M������ʽ��M
�ļ����,�ٽ���ֵͬԤ�ȸ�������ֵ���бȽ�;����Shi-Tomasi����˸Ľ��㷨,
����������ֵ�н�С��һ��������С��ֵ,���õ�ǿ�ǵ�;

ȷ��ͼ��ǿ�ǵ�:googFeatureToTrack()����
C++:void goodFeatureToTrack(InputArray image,OutputArray corners,int maxCorners,
double qualityLevel,double  minDistance,InputArray mask=noArray(),int blockSize=3,
bool useHarrisDetector=false,double k=0.4)

��һ������:InputArray���͵�image,����ͼ��,��Ϊ8λ���߸�����32Ϊ�ĵ�ͨ��ͼ��
�ڶ�������:OutputArray���͵�corners,��⵽�Ľǵ���������;
����������,int���͵�maxCorners,�ǵ���������;
���ĸ�����:double���͵�qualityLevel,�ǵ���ɽ��ܵ���С����ֵ;
ʵ�����ڹ��˽ǵ����С����ֵ��qualityLeval��ͼ�����������ֵ�ĳ˻�;
����qualityLevelͨ�����ᳬ��1(����ֵΪ0.1����0.01)��
����������еĽǵ��,��Ҫ��һ���޳�һЩ����Ͻ��Ľǵ�;

���������:double���͵�minDistance,�ǵ�֮�����С����,�˲�������
��֤���صĽǵ�֮��ľ��벻С��minDistance������;
����������:InputArray���͵�mask,��ѡ����,��ʾ����Ȥ����,��Ĭ��ֵ
noArray(),���˲����ǿ�(��ҪΪCV_8UC1����,�Һ͵�һ������image����ͬ
�ĳߴ�,),������ָ���ǵ�������;
���߸�����:int���͵�blockSize,��Ĭ��ֵ3,�Ǽ��㵼������ؾ���ʱ,ָ��������
��Χ;
�ڰ˸�����:bool���͵�useHarrisDector,Ĭ��ֵΪfalse,ָʾ�Ƿ�ʹ��harris
�ǵ���;
�ھŸ�����:double���͵�k,��Ĭ��ֵ0.04,Ϊ��������Hessian����ؾ�������ʽ
�����Ȩ�ص�Ȩ��ϵ��;

goodFeatureToTrack������������ʼ��һ�����ڵ�Ķ�����ٲ���;

//�ۺ�ʾ��:Shi--Tomasi�ǵ���

*/


#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int g_maxCornerNumber = 33;
int g_maxTrackBarNumber = 500;
RNG g_rng(12345);
void on_good_feature_to_track(int,void*);
int main()
{

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
	namedWindow("Shi_Tomasi", WINDOW_AUTOSIZE);
	createTrackbar("���ǵ���:","Shi_Tomasi",&g_maxCornerNumber,g_maxTrackBarNumber, on_good_feature_to_track);
	on_good_feature_to_track(0,0);
	imshow("Shi_Tomasi",src_img);
	waitKey(0);
	return 0;
}
void on_good_feature_to_track(int, void*)
{
	//�Ա���С�ڵ���1ʱ�Ĵ���
	if (g_maxCornerNumber<=1)
	{
		g_maxCornerNumber = 1;
	}
	//Shi-Tomasi�㷨(goodFeatureTotrack����)�Ĳ���׼��
	vector<Point2f> corners;
	double qualityLevel = 0.01;//�ǵ���ɽ��ܵ���С����ֵ
	double minDistance = 10;//�ǵ�֮�����С����
	int blockSize = 3;//���㵼������ؾ���ʱָ��������Χ
	double k = 0.04;//Ȩ��ϵ��
	Mat copy = src_img.clone();//����Դͼ��һ����ʱ������,��Ϊ����Ȥ����
	//Shi-Tomasi�ǵ���
	//��⵽�Ľǵ���������
	//�ǵ���������
	//�ǵ���ɽ��ܵ���С����ֵ
	//�ǵ�֮����С�ľ���
	//����Ȥ����
	//���㵼������ؾ���ʱ������Χ
	//��ʹ��harrsi�ǵ���
	goodFeaturesToTrack(gray_img,corners,g_maxCornerNumber,qualityLevel,minDistance,Mat(),blockSize,false,k);

	//���������Ϣ
	cout << ">�˴μ�⵽�Ľǵ�����Ϊ:" << corners.size() << endl;
	//���Ƽ�⵽�Ľǵ�
	int r = 4;
	for (size_t i = 0; i < corners.size(); i++)
	{
		//���������ɫ���Ƴ��ǵ�
		circle(copy,corners[i],r,Scalar(g_rng.uniform(0,255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)),-1,8,0);
	}
	imshow("Shi_Tomasi",copy);
}