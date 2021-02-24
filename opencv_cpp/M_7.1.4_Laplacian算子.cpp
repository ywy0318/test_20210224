/*
Laplacian������nάŷ����¿ռ��е�һ������΢������,
����ͼ�����ԭ���֪�����׵��������������м���Ե,
��Ϊͼ����"��ά��",��Ҫ�����������Ͻ�����,
ʹ��Laplacian���ӽ���ʹ�󵼹��̱�ü�;
����Laplacian����ʹ����ͼ���ݶ�,���ڲ��Ĵ�����ʵ�ǵ�����
Sobel����;
��һ��ͼ���ȥ����Laplacian���ӿ�����ǿ�Աȶ�;
Laplacian()�������Լ����ͼ�񾭹�������˹�任��Ľ��;
C++:void Laplacian(InputArray src,OutputArray dst,int ddepth,
int ksize=1,double=scale=1,double delta=0,intborderType=BORDER_DEFAULT);
ddepth,Ŀ��ͼ������
double���͵�scale,����������˹ֵ��ʱ���ѡ�ı�������,Ĭ��ֵΪ1;
����������:double���͵�delta,��ʾ�ڽ������Ŀ��ͼ(�ڶ�������dst)
֮ǰ��ѡ��deltaֵ,Ĭ��ֵΪ0;

*/#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);
	//ʹ�ø�˹�˲���������
	GaussianBlur(src_img,src_img,Size(3,3),0,0,BORDER_DEFAULT);
	//ת��Ϊ�Ҷ�ͼ
	cvtColor(src_img,gray_img,COLOR_RGB2BGRA);
	//ʹ��Laplacian����
	Laplacian(gray_img,dst_img,CV_16S,3,1,0,BORDER_DEFAULT);
	//�������ֵ,�������ת����8λ
	convertScaleAbs(dst_img, temp_img);
	imshow("dst_img",temp_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
