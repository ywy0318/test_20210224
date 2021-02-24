#include "opencv2/opencv.hpp"
#include<iostream>
using namespace cv;
using namespace std;

void main()
{
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg", 0);  //�ԻҶȷ�ʽ�򿪣��Ҷ�ͼ�Ͳ�ɫͼֱ��ͼ�����ͬ
	imshow("src", img);

	Mat dstHist;  //����洢ֱ��ͼ����
	int dims = 1;  //��Ҫͳ�Ƶ�������Ŀ(ֻͳ�ƻҶ�ֵ)
	float hranges[] = { 0, 256 };  //��Χ[0,256),ע�������ֵ��1
	const float* ranges[] = { hranges };
	int bins = 256;//��ࣺ�����Ϊֱ��ͼ��Ϊ��������
	int channels = 0;
	//����ֱ��ͼ
	calcHist(&img, 1, &channels, Mat(), dstHist, dims, &bins, ranges);

	int scale = 1;
	Mat dstImg(bins * scale, bins * 1, CV_8UC3, Scalar(0));  //����ֱ��ͼ���ͼ��,������
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue);//ͳ��ֱ��ͼdstHist����С���ֵ,�����ظ�ֵλ��
	int hpt = saturate_cast<int>(0.9*bins);  //�������ֵ����ֹ���
	int j = 0;
	//����ֱ��ͼ
	for (int i = 0; i<256; i++)
	{
		float binValue = dstHist.at<float>(i);
		//if(i>250)
		cout << "i=" << i << "---Value=" << binValue << endl;
		int realValue = saturate_cast<int>(binValue*hpt / maxValue);  //��һ������
																	  //cout<<"i="<<i<<"---Value="<<realValue<<endl;
		line(dstImg, Point(i*scale, bins - 1), Point(i*scale, bins - realValue), Scalar(0, 255, 0), 1, 8);
		//�ڶ���������line()�޸�ֱ��ͼ�ܶȵ������

		//���ϽǺ����½����꣬����ϵ����ͼ��ʾ
		//rectangle(dstImg, Point(i*scale, bins-1), Point(i*scale+1, bins-realValue), Scalar(0, 255, 0), 1);
		//rectangle(dstImg, Point(j*scale, bins-1), Point(j*scale+1, bins-realValue), Scalar(rand()%255, rand()%255, rand()%255), -1);
		//rectangle(dstImg, Point(j*scale, bins-1), Point(j*scale+1, bins-realValue), Scalar(rand()%255, rand()%255, rand()%255), -1);
		//j=j+3;


	}
	imshow("Histogram", dstImg);
	waitKey(0);
	destroyAllWindows();
}