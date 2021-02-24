#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;

/*
ʹ��r����Ķ���,��Ҫע�����,����ͨ����randu()���������������ֵ��������,
��Ҫ����һ�����޺�һ��������ȷ�����ֵ�������ķ�Χ��;
*/



int main(int argc, char* argv[])
{
	Mat img, resimg;//mat��opencv���������ݽṹ������һ��ͼ���������
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

	Mat r = Mat(10, 3, CV_8UC3);
	randu(r,Scalar::all(0),Scalar::all(255));//�Ծ���ĳ�ʼ��
	//opencvĬ�Ϸ�����
	cout << "r(opencvĬ�Ϸ��)=" << r << ";" << endl << endl;

	//python3���������ʽ
	cout << "r(python)=" << format(r, Formatter::FMT_PYTHON) << ";" << endl << endl;

	//���ŷָ����(CSV)
	cout << "r=(���ŷָ����)=" << format(r, Formatter::FMT_CSV) << ";" << endl << endl;

	//numpy���
	cout << "r(numpy���)=" << format(r, Formatter::FMT_NUMPY) << endl << ";" << endl << endl;


	//C���Է��
	cout << "r(C���Է��)=" << format(r, Formatter::FMT_C) << ";" << endl << endl;

	while (true)
	{

	}

	img = imread(imgpath4, 1);//����ͼƬ����
	if (img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}




	//cout<<img.
	cout << " open or find the img" << endl;
	cout << "img.channels��" << img.channels() << endl;
	
	cout << "img.elemSize:" << img.elemSize() << endl;
	cout << "img.type:" << img.type() << endl;
	cout << "img.depth:" << img.depth() << endl;
	cout << "img.step1:" << img.step1() << endl;

	namedWindow("IMG", WINDOW_AUTOSIZE);//����һ������
	imshow("IMG", img);
	/* ��תģʽ��flipCode == 0��ֱ��ת����X�ᷭת����
	flipCode>0ˮƽ��ת����Y�ᷭת����
	flipCode<0ˮƽ��ֱ��ת������X�ᷭת������Y�ᷭת���ȼ�����ת180�㣩 */
	flip(img, resimg, 1);

	

	namedWindow("ˮƽ��ת", WINDOW_AUTOSIZE);
	imshow("ˮƽ��ת", resimg);

	flip(img, resimg, 0);
	namedWindow("��ֱ��ת", WINDOW_AUTOSIZE);
	imshow("��ֱ��ת", resimg);

	flip(img, resimg, -1);
	namedWindow("ˮƽ��ֱ��ת", WINDOW_AUTOSIZE);
	imshow("ˮƽ��ֱ��ת", resimg);

	waitKey(0);
	system("pause");
	return 0;
}