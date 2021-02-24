/*
7.5ֱ��ͼ���⻯
����ͼ��Ķ�̬��Χ,ֱ��ͼ���⻯;
ֱ��ͼ���⻯�ǻҶȱ任��һ��Ӧ��;
ͼ������ػҶȱ任�������,ֱ��ͼ��ͼ�θߵͲ���,
ֱ��ͼ���⻯������һ�����㷨ʹֱ��ͼ����ƽ��;

ֱ��ͼ���⻯��ͨ����������ǿ�ȷֲ���Χ����ǿ�Աȶȵ�һ�ַ���;
���⻯������ͼ��ֻ�ܽ��ƾ���ֲ�;���⻯ͼ��Ķ�̬��Χ������, 
�䱾�����������������,���������𷴶�������;
ԭ���ҶȲ�ͬ��ͼ�񾭴����,���ܱ����ͬ;�γ���һƬ��ͬ�Ҷȵ�����;
������֮�������Եı߽�,�Ӷ�������α����;

��ԭʼͼ��Աȶȱ����ͺܸߵ������,����پ��⻯��Ҷȵ���,�ԱȶȻ�
����;�ڷ��׻��͵�ͼ����,���⻯��ϲ�һЩ���ػҶ�,�Ӷ����ӶԱȶ�;
���⻯��ͼƬ����ٶ�����⻯,��ͼ�񲻻����κα仯;

ʵ��ֱ��ͼ���⻯:equalizeHist()����
C++:void equalizeHist(InputArray src ,OutputArray dst)
����ͼ��Ϊ8λ��ͨ����ͼ��,���ͼ���Դͼ����һ���ĳߴ������;

����ֱ��ͼ��һ��,ֱ��ͼ�����ĺ�Ϊ255;
����ֱ��ͼ����;
�Ի�����Ϊ��ѯ�����ͼ��任;
equalizeHist()����ʵ�ֵĻҶ�ֱ��ͼ���⻯�㷨,���ǰ�ֱ��ͼ��
ÿ���Ҷȼ����й�һ������,��ÿ�ֻҶȵ��ۻ��ֲ�,�õ�һ��ӳ���
�Ҷ�ӳ���,Ȼ�������Ӧ�ĻҶ�ֵ������ԭͼ�е�ÿ������;

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

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);
	//תΪ�Ҷ�ͼ������ʾ����
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
	imshow("gray_img",gray_img);
	equalizeHist(gray_img,dst_img);
	imshow("dst_img",dst_img);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
