#include<iostream>
#include<opencv2\opencv.hpp>
#include "highgui.h"
#include"cvaux.h"
#include"cxcore.h"
#include"opencv2/imgproc.hpp"
#include<string>
using namespace std;
using namespace cv;

/*
����ͨ����ģ����(ͨ�������к�)��ͼ���ÿ��ͼ������ֵ���¼���;
�����Ĥ���ܹ������ٽ����ذ�����ǰ���ض������ص�Ӱ��̶�;
����ѧ�Ƕ������������������ֵ�Ե�ǰ��ֵ����һ����Ȩƽ���Ĳ���,
�ٸ�����,����һ��ͼ��Աȶ���ǿ�ķ���������������Ҫ������Ĺ�ʽ
Ӧ�õ�ÿ��������;
��һ����ʽ������ѧ��ʽ���ڶ�������һ����Ĥ��;����Ĥ�����ķŵ�����
����������ϣ�������ֵ�ۼӲ���������Ӿ���ֵ��ˣ����ڽϴ��
������������һ�ֱ�﷽ʽ���������;
*/
//������
void sharpen(const Mat&myimage, Mat &result)
{
	CV_Assert(myimage.depth()==CV_8U);
	const uchar* precious = NULL;
	const uchar* current = NULL;
	const uchar* next = NULL;
	uchar* output = NULL;
	const int nchannels = myimage.channels();
	for (int i = 0; i < myimage.rows; i++)
	{
		precious = myimage.ptr<uchar>(i - 1);//��ǰ������һ��ָ��;
		current = myimage.ptr<uchar>(i);//��ǰ������ָ��
		next = myimage.ptr<uchar>(i + 1);//��ǰ������һ��ָ��
		output = result.ptr<uchar>(i);
	}
	//���ù�ʽ�����������ĸ����ضԵ�ǰ����ֵ���д���
	for (int j = nchannels; j < nchannels*(myimage.cols-1); ++j)
	{
		*output++ = saturate_cast<uchar>(5 * current[j] - current[j - nchannels]
			- current[j + nchannels] - precious[j] - next[j]);
	}
	result.row(0).setTo(Scalar(0));//���õ�һ������Ԫ��ֵΪ0;
	result.row(result.rows-1).setTo(Scalar(0));//�������һ������Ԫ��ֵΪ0;
	result.col(0).setTo(Scalar(0));//���õ�һ������Ԫ��ֵΪ0;
	result.col(result.cols-1).setTo(Scalar(0));//���õ�һ��һ������Ԫ��ֵΪ0;
}
int main()
{
	Mat img,des;
	string imgpath0 = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	img = imread(imgpath0, 1);//����ͼƬ����
	if (img.empty())
	{
		cout << "can not open or find the img" << endl;
		system("pause");
		return -1;
	}
	cout << "ͼƬ��ȡ�ɹ�" << endl;

	namedWindow("srcimgae",WINDOW_AUTOSIZE);
	imshow("srcimage",img);

	des.create(img.size(),img.type());
	sharpen(img,des);
	namedWindow("desimage",WINDOW_AUTOSIZE);
	imshow("desimage",des);
	waitKey(0);
	

	system("pause");
	return 0;
}