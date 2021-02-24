#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char* argv[])
{
	Mat src_img, des_img;//mat��opencv���������ݽṹ������һ��ͼ���������
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

	src_img = imread(imgpath4, 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("srcimg",src_img);
	//getStructuringElement�ķ���ֵ��ָ����״��ָ���ߴ���ں;���
	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	erode(src_img, des_img,element);

	imshow("after erode", des_img);

	waitKey(0);
	system("pause");
	return 0;
}