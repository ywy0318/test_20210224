/*
7.3��ӳ��
��ӳ��ĸ���:
��ӳ��,���ǰ�һ��ͼ����ĳλ�õ����ط��õ�����һ��ͼƬ
ָ��λ�õĹ���;Ϊ�������ӳ��,��Ҫ���һЩ��ֵΪ������
���ص�����,��ΪԴͼ����Ŀ��ͼ����������겻��һһ��Ӧ��,
ʵ����ӳ��:remap()����
remap()���������ָ����ӳ����ʽ,��Դͼ�������ӳ��
���α任,�������µĹ�ʽ:
dst(x,y)=src(mapx(x,y),mapy(x,y))
�˺�����֧�־͵ز���,
C++:void remap(InpuArray src,OutputArray dst,InputArray,map1,InputArray map2,
int interpolation,inteborderMode=BORDER_CONSTANT,const Scalar&borderValue=Scalar())

����������:InputArray���͵�map1,�������ֿ��ܵı�ʾ����;
��ʾ��(x,y)�ĵ�һ��ӳ��
��ʾCV_16SC2,CV_32FC1,CV_32FC2���͵�Xֵ;

���ĸ�����:InputArray���͵�map2,��Ҳ�����ֿ��ܵı�ʾ����;
����map1��ȷ����ʾ���ֶ���
map1��ʾ��(x,y)ʱ,��������������κ�ֵ;
��ʾCV_16UC1,CV_32FC1���͵�Yֵ(�ڶ���ֵ);
���������,int���͵�interpolation,��ֵ��ʽ,֮ǰ��resize()����
���н���;
INTER_NEAREST--����ڲ�ֵ
INTER_LINEAR--˫���Բ�ֵ(Ĭ��ֵ)
INTER_CUBIC--˫����������ֵ(��4X4���������ڵ�˫���β�ֵ)
INTER_LANCZOS4--Lanczos��ֵ(��8X8���������Lanczos��ֵ)
����������:int���͵�border,�߽�ģʽ
���߸�����:const Scalar&���͵�borderValue,���г����߽�ʱʹ�õ�ֵ,
Ĭ��ֵScalar().Ĭ��ֵΪ0;


*/

#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int main()
{
	Mat map_x, map_y;
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);
	//������ԭʼͼһ����Ч��ͼ,x��ӳ��ͼ,y��ӳ��ͼ
	dst_img.create(src_img.size(),src_img.type());
	map_x.create(src_img.size(),CV_32FC1);
	map_y.create(src_img.size(), CV_32FC1);
	//˫��ѭ��,����ÿһ�����ص�,�ı�map_x,map_y��ֵ
	for (size_t i = 0; i < src_img.rows; i++)
	{
		for (size_t j = 0; j < src_img.cols; j++)
		{
			//�ı�map_x,map_y��ֵ
			map_x.at<float>(j, i) = static_cast<float>(i);
			map_y.at<float>(j, i) = static_cast<float>(src_img.rows - j);
		}
	}
	//������ӳ�����
	remap(src_img, dst_img, map_x, map_y, INTER_LINEAR,BORDER_DEFAULT,Scalar(0,0,0));
	imshow("dst_img",dst_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
