#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void main() {
	Mat img1 = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat img2 = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dst;//�洢���
	imshow("img1", img1);
	imshow("img2", img2);
	cout << "img1  " << int(img1.at<Vec3b>(10, 10)[0]) << endl;//img1�����꣨10,10������ɫͨ����ֵ��ǿ��ת��int
	cout << "img2  " << int(img2.at<Vec3b>(10, 10)[0]) << endl;

	//dst=img1-img2;//����������Ч����ͬ    ��dst<0,��dst=0
	//subtract(img1,img2,dst);//ע�⣺Ҫ�󱻴���ͼƬ�ߴ�һ��

	absdiff(img1, img2, dst);//��dst<0,��dst=|dst|>=0    ���ڼ����������ͼ��Ĳ�ͬ�㣬Ч������������ּ�����

	cout << "dst  " << int(dst.at<Vec3b>(10, 10)[0]) << endl;
	imshow("dst", dst);
	waitKey(0);
}


//dst = 5 * img1;//�����ع�
//dst = img1 / 5;//�����ع�
//bitwise_and(img1, img2, dst);//�߼��룬�󽻼�
//bitwise_or(img1, img2, dst);//�߼����󲢼�
//bitwise_not(img1, dst);//�߼��ǣ��󲹼�
//bitwise_xor(img1, img2, dst);//�����ͬΪ0������Ϊ1