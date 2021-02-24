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
	Mat src_img, dst_img, gray_img, edge_img,temp_img;

	src_img = imread(imgpath4, 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//imshow("srcimg", src_img);
	//������src_imgͬ���ͺʹ�С�ľ���
	dst_img.create(src_img.size(), src_img.type());


	//��ԭʼͼ��ת��Ϊ�Ҷ�ͼ��
	//opencv2�汾
	//cvtColor(src_img, gray_img, CV_BGR2GRAY);


	//opencv3�汾
	cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
	//ʹ��3x3�ں�������
	blur(gray_img, edge, Size(3, 3));

	//getStructuringElement�ķ���ֵ��ָ����״��ָ���ߴ���ں;���
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//erode(src_img, dst_img, element);

	//Canny����
	Canny(edge, edge, 3, 9, 3);

	imshow("after erode", edge);

	waitKey(0);
	system("pause");
	return 0;
}