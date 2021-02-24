#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
/*
imwrite()������һ������д��ͼ���ļ���
Mat�������"<<"���������鿴ʵ��ֵ,����ֻ�Զ�ά������Ч;
Mat������һ���ǳ����õ�ͼ��������,Ҳ��һ��ͨ�õľ�����,���ǿ��������������Ͳ�����ά����;

���ڶ�ά��ͨ��ͼ��,����Ҫ������ߴ�,������������;Ȼ����Ҫָ���洢Ԫ�ص��������ͼ�
ÿ��������ͨ����

CV_[The number of bits per item][signed or Unsigned][Type Prefix][The channel number]
��:CV_[λ��][���������][����ǰ׺]C[ͨ����]
CV_8UC3��ʾʹ��8λ��unsigned char��,ÿ������������Ԫ�������ͨ��;
��Ԥ�ȶ����ͨ�������Զ��4��;
Scalar�Ǹ�short�͵������ܹ�ʹ��ָ���Ķ��ƻ�ֵ����ʼ������,���������ڱ�ʾ��ɫ


*/
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

	//��С����ʹ�ö��÷ָ�ʽ��ʼ������
	Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cout << "C=" << endl << "" << C << endl<<endl;

	//Ϊ�Ѵ��ڵĶ��󴴽�����Ϣͷ
	//ʹ�ó�Ա����clone()��copyTo()Ϊһ���Ѵ��ڵ�Mat���󴴽�һ���µ���Ϣͷ,
	Mat rowclone = C.row(1).clone();
	cout << "rowclone=" << endl << "" << rowclone << endl << endl;

	Mat E = Mat::eye(4, 4, CV_64F);
	cout << "E=" << "" << E << endl;

	Mat O = Mat::ones(2, 2, CV_32F);
	cout << "O=" << O << endl;

	Mat Z = Mat::zeros(3, 3, CV_8UC1);
	cout << "Z=" << Z << endl;

	Mat Ma;
	//����Mat���е�Create()��Ա��������Mat��ĳ�ʼ������
	//�˴�����������Ϊ�������ó�ʼֵ,ֻ���ڸı�ߴ�ʱ,����Ϊ�������ݿ����ڴ����
	Ma.create(4,4,CV_8UC(2));
	cout << "Ma=" << endl << "" << Ma << endl << endl;

	//Ϊ�Ѵ��ڵ�IplImageָ�봴����Ϣͷ
	IplImage* img_11 = cvLoadImage("1.jpg",1);

	//Mat mtx(img_11);//ת��IplImage*->Mat ---������

	int sz[3] = {2,2,2};
	Mat L(3,sz,CV_8UC3,Scalar::all(0));//<<���������ά��


	Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
	//cout << "M=" << M << endl;

	while (true)
	{

	}

	//mat��opencv���������ݽṹ������һ��ͼ���������
	Mat src_img, des_img;//******��������Ϣͷ����
	src_img = imread(imgpath4, 1);//����ͼƬ����--//����Ϊ���󿪱��ڴ�
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	Mat B(src_img);//ʹ�ÿ������캯��

	des_img = src_img;//��ֵ�����
	//��������Mat�������ն�ָ��ͬһ��Ҳ��Ψһһ�����ݾ�����Ȼ���ǵ���Ϣͷ��ͬ,
	//����ͨ���κ�һ�����������ĸı�Ҳ��Ӱ������,ʵ���ϲ�ͬ�Ķ���ֻ�Ƿ�����ͬ���ݵĲ�ͬ;������

	Mat D(src_img, Rect(10, 10, 100, 100));//ʹ�þ��ν綨
	//Mat E = D(Range:all(), Range(1, 3)); // ���к������綨----������
	//Mat E = src_img(Range:all(), Range(1, 3));// ���к������綨
	//����һ�£�����ֻ���ò������ݵ�ͷ��Ϣ��������Ҫ����һ������Ȥ����(ROI),
	//ֻ��Ҫ���������߽���Ϣ����Ϣͷ;

	//���ھ������ڶ��Mat����,��������Ҫ����ʱ��,���һ��ʹ�����Ķ������������ݾ���;
	//����ʵ����ͨ�����ü���������ʵ�ֵ�,������һ��Mat�������Ϣͷ��ʱ�򣬾ͻ����Ӿ�������ô���
	//��һ��ͷ���ͷ�֮��,���������������,��������ֵΪ0��ʱ��,����ᱻ����;

	//���ƾ�����(��ֻ����Ϣͷ�;���ָ��),ʹ�ú���clone()����copyTo()
	//F����G�Ͳ���Ӱ��Mat��Ϣͷ��ָ��ľ���
	Mat F = src_img.clone();
	Mat G;
	src_img.copyTo(G);

	system("pause");

	/**********/

	imshow("srcimg", src_img);
	//getStructuringElement�ķ���ֵ��ָ����״��ָ���ߴ���ں;���
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//erode(src_img, des_img, element);

	//���о�ֵ�˲�����
	blur(src_img, des_img, Size(15, 15));

	imshow("after blur", des_img);

	waitKey(0);
	system("pause");
	return 0;
}