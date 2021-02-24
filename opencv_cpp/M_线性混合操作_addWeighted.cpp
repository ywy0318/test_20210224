/*
���Ի�ϲ���
���Ի�ϲ���ʱһ�ֵ��͵Ķ�Ԫ(��������)�����ز���
g(x)=(1-a)*f1(x)+a*f2(x)
ͨ����Χ0-1֮��ı�aֵ,��������ͼ��(f1(x)��f2(x))��������Ƶ
ͬ��Ϊ(f0(x)��f1(x))����ʱ���ϵĻ��������(cross-dissolve)
Ч��,����õ�Ƭ��ӳ�͵�Ӱ�����е�����,Ҳ�����ڻõ�Ƭ��ҳʱ���õ�
ǰ��ҳ�������ɵ���Ч��,�Լ���Ӱ��ڹ���ʱ���ֵĻ�����ӵ�Ч��
OpenCV������addWeighted����;
���������Ȩ��:addWeighted()����---������������(ͼ������)�ļ�Ȩ��
(InputArray scr_1,double alpha,InputArray src_2,double beta,double gamma,OutputArray dst,int dtype=-1)
��һ������:InputArray���͵�src_1,��ʾ��Ҫ��Ȩ�ĵ�һ������,������һ��Mat;
�ڶ�������:alpha,��һ�������Ȩ��
����������:InputArray--src_2,�ڶ������飬����Ҫ�͵�һ������ӵ����ͬ�ĳߴ��ͨ����;
���ĸ�����:beta,��ʾ��һ�������Ȩ��ֵ;
���������:gamma,һ���ӵ�Ȩ���ܺ��ϵı���ֵ,
����������,OutputArray���͵�dst,��������飬�����������������ӵ����ͬ�ĳߴ��ͨ����
���߸�����:int ���͵�dtype,������еĿ�ѡ���,��Ĭ��ֵ-1,�������������������ͬ�����,
�����������Ϊ-1,��ͬ��src_1.depth();
ͼ�������ָ�洢ÿ���������õ�λ����Ҳ��������ͼ���ɫ�ʷֱ��ʡ�
��ѧ���ʽ:
dst=src_1[I]*alpha+src_2*beta+gamma;
I,�Ƕ�ά����Ԫ�ص�����ֵ,��������ͨ�������ʱ��,ÿ��ͨ������Ҫ�������д���;
�������������ΪCV_32S��ʱ��,�������������,
�ͻ��ڴ��������������Ľ������;

*/

#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
//opencv����canny��Ե���
//����ͼ��,ת��Ϊ�Ҷ�ͼ,blur����ͼ��ģ�����룬Ȼ����canny���б�Ե���

int main(int argc, char* argv[])
{
	
	//--1--˫��б�߷�
	string imgpath0 = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	//--2--˫��б�߷�
	string imgpath1 = "E://Visual Studio 2010//Projects//opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--3--����б�߷�
	string imgpath2 = "E:/Visual Studio 2010/Projects/opencv_2018_12_21/opencv_2018_12_21/1.jpg";
	//--4--�������ֻ��
	string imgpath3 = "E:/Visual Studio 2010//Projects\\opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--5--���·����
	string imgpath4 = "1.jpg";
	//--6--�����в�����
	//string imgpath5 = argv[1];
	//mat��opencv���������ݽṹ������һ��ͼ���������
	Mat src_img, src_img_1, des_img, gray_img, edge;
	double alpha_value = 0.5;
	double beta_value = (1.0 - alpha_value);
	src_img = imread(imgpath4);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	src_img_1 = imread("1_1.jpg");//����ͼƬ����
	if (src_img_1.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//0.0=gamma
	addWeighted(src_img, alpha_value, src_img_1, beta_value,0.0, des_img);

	namedWindow("src_img_1", 1);
	imshow("src_img_1", src_img_1);

	//namedWindow("des_img--LinearBlending",1);
	imshow("LinearBlending", des_img);
	//imshow("srcimg", src_img);
	//������src_imgͬ���ͺʹ�С�ľ���
	//des_img.create(src_img.size(), src_img.type());


	//��ԭʼͼ��ת��Ϊ�Ҷ�ͼ��
	//opencv2�汾
	//cvtColor(src_img, gray_img, CV_BGR2GRAY);


	//opencv3�汾
	//cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
	//ʹ��3x3�ں�������
	//blur(gray_img, edge, Size(3, 3));

	//getStructuringElement�ķ���ֵ��ָ����״��ָ���ߴ���ں;���
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//erode(src_img, des_img, element);

	//Canny����
	//Canny(edge, edge, 3, 9, 3);

	

	waitKey(0);
	system("pause");
	return 0;
}