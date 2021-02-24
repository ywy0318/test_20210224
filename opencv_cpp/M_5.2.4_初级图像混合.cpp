/*
�趨����Ȥ����ROI��ʹ��addweighted��������ͼ�����Ի�ϵĻ�����,
�����߽������,��ָ��ROI,��ʹ��addWeighted������ָ����ROI�����ͼ��
���л�ϲ���,�����װ��ROI_LiearBlending

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

	//����һ��Mat���Ͳ������趨ROI����
	Mat image_ROI;
	//����һ:
	//image_ROI = src_img(Rect(200,250,src_img_1.cols/2,src_img_1.rows/2));

	//������:
	image_ROI = src_img(Range(250, 250 + src_img_1.rows/2), Range(200, 200 + src_img_1.cols/2));

	//0.0=gamma
	addWeighted(src_img, alpha_value, src_img_1, beta_value, 0.0, image_ROI);

	namedWindow("src_img", 1);
	imshow("src_img", src_img);

	//namedWindow("des_img--LinearBlending",1);
	imshow("image_ROI", image_ROI);
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
