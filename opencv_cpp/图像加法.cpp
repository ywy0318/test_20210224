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
	cout << "img1  " << int(img1.at<Vec3b>(100, 100)[0]) << endl;//img1�����꣨100,100������ɫͨ����ֵ��ǿ��ת��int
	cout << "img2  " << int(img2.at<Vec3b>(100, 100)[0]) << endl;

	dst = img1 + img2;//�������ӷ�Ч����ͬ
					  //add(img1,img2,dst);//ע�⣺�������ӷ�Ҫ�󱻼ӵ�ͼƬ�ߴ����һ��
					  //addWeighted(img1,0.5,img2,0.5,0,dst);//��Ȩ����ӣ���һ��dst�������Ϊ����������һ��
	cout << "dst  " << int(dst.at<Vec3b>(100, 100)[0]) << endl;
	imshow("dst", dst);
	waitKey(0);
}