/*
5.4ͼ��Աȶ�,����ֵ����
��������
���ӵĸ���:һ���ͼ�������Ӷ���һ������,������һ�����߶������ͼ��
���쳤���ͼ��;���������ӵ�һ����ʽ;
g(x)=h(f(x))����g(x)=h(f0(x)-----fn(x))
ͼ�����ȺͶԱȶȵĵ�������,��ʵ����ͼ����任�бȽ�
�򵥵�һ��---�����(pointoperators);
�������һ���ص�:����������������ֵ(��ʱ�ɼ���ĳЩȫ����Ϣ���߲���),
��������Ӧ���������ֵ,�������Ӱ�������(brightness)�ͶԱȶ� (contrast)����,
��ɫУ��(colorcorrection)�ͱ任(transformations);
������õĵ����(����˵������)�ǳ���һ������(��Ӧ�Աȶȵĵ���)
�Լ�����һ������(��Ӧ����ֵ�ĵ���)
g(x)=a*f(x)+b
f(x)��ʾԴͼ������
g(x)��ʾ���ͼ������;
a(��Ҫ����a>0)����Ϊ����(gain),��������������ͼ��ĶԱȶ�;
bͨ������Ϊƫ��(bias),��������������ͼ�������;
g(i,j)=a*f(i,j)+b
i,j��ʾ����λ�ڵ�i�к͵�j��,���ʽ����opencv
�п���ͼ������ȺͶԱȶȵ����۹�ʽ;


//���������ܻᳬ������ȡֵ��Χ(���),�������Ƿ�����(����Ǹ������Ļ�),
����Ҫ�� saturate_cast �Խ������ת��,��ȷ����Ϊ��Чֵ;
{
����ԭ��:
	if(data<0)
        data=0;
else if(data>255)
	data=255;

}
for(int y=0;y<image.rows;y++)
{
	for(int x=0;x<image.cols;x++)
	{
		for(int c=0;c<3;c++)
		{
		new_image.at<Vec3b>(y,x)[c]=saturate_cast<uchar>((g_nConstrastValue*0.01)*(iamge.at<Vec3b>(y,x)+g_nBrightValue)
		}
	}
}

*/

#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int g_nContrastValue = 80;//�Աȶ�ֵ
int g_nBrightValue = 80;//����ֵ
Mat src_img, dst_img, gray_img, edge;

void on_ContrastAndBright(int ,void*)
{
	namedWindow("ԭʼͼ����",1);
	for (size_t y = 0; y < src_img.cols; y++)
	{
		for (int x=0;x<src_img.rows;x++)
		{
			for (size_t c = 0; c < 3; c++)
			{
				dst_img.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(
					(g_nContrastValue)*0.01*(src_img.at<Vec3b>(y, x)[c]) + g_nBrightValue);
			}
		}
	}
	imshow("ԭʼͼ����",src_img);
	imshow("Ч��ͼ����",dst_img);
}
int main()
{
	
	
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	dst_img = Mat::zeros(src_img.size(),src_img.type());


	namedWindow("Ч��ͼ����",1);
	createTrackbar("�Աȶ�:","Ч��ͼ����",&g_nContrastValue,300,on_ContrastAndBright);
	createTrackbar("�� ��:", "Ч��ͼ����", &g_nBrightValue, 300,on_ContrastAndBright);

	on_ContrastAndBright(g_nContrastValue,0);
	on_ContrastAndBright(g_nBrightValue, 0);
	waitKey(0);
	while (true)
	{

	}
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
