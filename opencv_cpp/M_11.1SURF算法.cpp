/*
SURF,Ӣ��ȫ��:SpeededUp Robust Features,���ٰ�ľ���³���Ե������㷨;
SURF�ǳߴ粻�������任�㷨(SIFT)�ļ��ٰ�;
һ����˵,��׼SURF���ӱ�SIFT���ӿ�ü���,�����ڶ��ͼƬ�¾���
���õ��ȶ���;SURF�����������ڲ�����harr�����Լ�����ͼ��ĸ���,
����ӿ��˳��������ʱ��;
SURF����Ӧ���ڼ�����Ӿ�������ʶ��3D�ع���;

11.1.2SURF�㷨ԭ��


11.1.4���ƹؼ���:drawKeyPoints()����
C++:void drawKeyPoints(const Mat&image,const vector<KeyPoint>&keypoints,
Mat&outImage,const Scalar& color=Scalar::all(-1),int flags=DrawMatchesFlags::DEFAULT)

��һ������:const Mat&���͵�src,����ͼ��
�ڶ�������:const vector<KeyPoint>&���͵�keypoints,����Դͼ��õ���������,����һ���������;
����������:Mat&���͵�outImage,���ͼ��,������ȡ���ڵ����������ʶ��flags;
���ĸ�����:const Scalar&���͵�color,�ؼ������ɫ,Ĭ��ֵScalar::all(-1);
���������:int���͵�flags,���ƹؼ����������ʶ��,Ĭ��ֵDrawMatchesFlags::DEFAULT;

struct DrawMatchesFlags
{
	enum
	{
		DEFAULT=0;//�������ͼ�����(ʹ��Mat::create);//ʹ���ִ�����ͼ�����
		ƥ��Ժ�������;�Ҷ�ÿһ���ؼ���,ֻ�����м��;
		DRAW_OVER_OUTIMG=1;//���������ͼ�����,���������ͼ���ϻ���ƥ���
		NOT_DRAW_SINGLE_POINTS=2;//���������㲻������
		DRAW_RICH_KEYPOINTS=4;//��ÿһ���ؼ���,���ƴ���С�ͷ���Ĺؼ���ԲȦ;
	};
};

KeyPoint��
KeyPoint����һ��Ϊ����������������ݽṹ,���ڱ�ʾ������;
class KeyPoint
{
	Point2f pt;//����
	float size;//����������ֱ��
	float angle;//������ķ���,ֵΪ[0,360],��ֵ��ʾ��ʹ��
	float response;
	int octave;//���������ڵ�ͼ�����������;
	int class_id;//���ھ����id;
}


*/

/*
ʾ������:SURF��������
1.>ʹ��FeatureDetector�ӿ������ָ���Ȥ��;
2.>ʹ��SurfFeatureDetector�Լ��亯��detector��ʵ�ּ�����;
3.>ʹ�ú���drawKeypoints���Ƽ�⵽�Ĺؼ���;
D:\opencv\opencv_2413\opencv\build\include\opencv2\nonfree
*/
#include<iostream>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/nonfree/>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int main()
{
	system("color 2F");
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	temp_img = imread("lena_2.jpg", 1);//����ͼƬ����
	if (temp_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("temp_img", temp_img);
	//������Ҫ�õ��ı�������
	int minHessian = 400;//����SURF��hessian��ֵ������������
	SurfFea

}