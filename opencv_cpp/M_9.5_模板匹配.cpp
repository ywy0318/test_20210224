/*
9.5ģ��ƥ��ĸ�����ԭ��
ģ��ƥ����һ����һ��ͼ����Ѱ��������һ��ģ��ͼ����ƥ��(����)���ֵļ���;
��opencv2��opencv3��,ģ��ƥ����MatchTemplate()�������;
ģ��ƥ�䲻�ǻ���ֱ��ͼ��,����ͨ��������ͼ���ϻ���ͼ���;
��ʵ�ʵ�ͼ��������ͼ�����ƥ���һ��ƥ�䷽��;

ʵ��ģ��ƥ��:matchTemplate()����
matchTemplate()��������ƥ�����ģ���ص���ͼ������
C++:void matchTemplate(InputArray image,InputArray temp1,OutputArray result,int method);
��һ������:InputArray���͵�image,��������ͼ��,��ҪΪ8λ����32λ������ͼ��;
�ڶ�������:InputArray���͵�temp1,����ģ��,��Ҫ��ԴͼƬ��һ������������,�ҳߴ粻�ܴ���Դͼ��;
����������:OutputArray���͵�result,�ȽϽ����ӳ��ͼ��;�����Ϊ��ͨ��,32λ������ͼ��,���
ͼ��ߴ�ʱW*H,��temp1�ߴ�ʱW*h,��˲���resultһ����(W-w+1)*(H-h+1);
���ĸ�����:int���͵�method,ָ����ƥ�䷽��;

1.ƽ����ƥ�䷨ method=TM_SQDIFF
���෽������ƽ�������ƥ��,���ƥ��Ϊ0;��ƥ��Խ��,ƥ��ֵԽ��;
2.��һ��ƽ����ƥ�䷨ method=TM_SQDIFF_NORMED
3.���ƥ�䷨ method=TM_CCORR
���෽������ģ���ͼ����ĳ˷�����,���Խϴ������ʾƥ��̶Ƚϸ�,0��ʾ���ƥ��Ч��;
4.��һ�����ƥ�䷨ method=TM_CCORR_NORMED
5.ϵ��ƥ�䷨ method=TM_CCOEFF
���෽����ģ������ֵ�����ֵ��ͼ������ֵ�����ֵ����ƥ��,
1��ʾ����ƥ��,-1��ʾ����ƥ��,��0��ʾû���κ������(�������)
6.��һ�����ϵ��ƥ�䷨method=TM_CCOEFF_NORMED

ͨ��,���ŴӼ򵥵Ĳ���(ƽ����)�������ӵĲ���(���ϵ��),���Ի��Խ��Խ׼ȷ��ƥ��;
ͬʱҲ����Խ��Խ��ļ�����Ϊ����;
�ȽϿ�ѧ�İ취�Ƕ�������Щ�취��β���ʵ��,�Ա�Ϊ�Լ���Ӧ��ѡ��ͬʱ����ٶȺ;���
����ѷ���;
*/

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int g_nMatch_Method;
int g_nMaxTrackbarNum = 5;
void on_Matching(int ,void* );
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int main()
{
	src_img = imread("111temp.png", 1);//����ͼƬ����
	//src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//ͼƬ��Ҫ�޸�
	dst_img = imread("111.png", 1);
	//dst_img = imread("lena.jpg",1);
	if (dst_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img",WINDOW_AUTOSIZE);
	namedWindow("dst_img", WINDOW_AUTOSIZE);
	//����������������һ�γ�ʼ��
	createTrackbar("����","src_img",&g_nMatch_Method,g_nMaxTrackbarNum,on_Matching);
	on_Matching(0,0);
	waitKey(0);
	return 0;
}
void on_Matching(int, void*)
{
	//���ֲ�������ʼ��
	src_img.copyTo(temp_img);
	//��ʼ�����ڽ������ľ���
	int resultImage_cols = src_img.cols - dst_img.cols + 1;
	int resultImage_rows = src_img.rows - dst_img.rows + 1;
	edge_img.create(resultImage_cols, resultImage_rows, CV_32FC1);
	//����ƥ��ͱ�׼��
	matchTemplate(src_img,dst_img,edge_img,g_nMatch_Method);
	normalize(edge_img, edge_img,0,1,NORM_MINMAX,-1,Mat());

	//ͨ������minMaxLoc��λ��ƥ���λ��
	double minValue;
	double MaxValue;
	Point minLocation;
	Point maxLoaction;
	Point matchLocation;
	minMaxLoc(edge_img,&minValue,&MaxValue,&minLocation,&maxLoaction,Mat());

	//���ڷ���SQDIFF��SQDIFF_NORMED,ԽС����ֵ���Ÿ��ߵ�ƥ����,������ķ���,
	//��ֵԽ��ƥ��Ч��Խ��;
	if (g_nMatch_Method == TM_SQDIFF || g_nMatch_Method == TM_SQDIFF_NORMED)
	{
		matchLocation = minLocation;
	}
	else
	{
		matchLocation = maxLoaction;
	}

	//���Ƴ�����,����ʾ���ս��
	rectangle(temp_img, matchLocation,Point(matchLocation.x+dst_img.cols,matchLocation.y+
	dst_img.rows),Scalar(0,0,255),2,8,0);

	rectangle(edge_img, matchLocation, Point(matchLocation.x + dst_img.cols, matchLocation.y +
		dst_img.rows), Scalar(0, 0, 255), 2, 8, 0);
	imshow("src_img",src_img);
	imshow("dst_img",dst_img);

}