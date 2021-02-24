#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void main() {
	Mat img1 = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat img2 = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dst;//存储结果
	imshow("img1", img1);
	imshow("img2", img2);
	cout << "img1  " << int(img1.at<Vec3b>(10, 10)[0]) << endl;//img1在坐标（10,10）的蓝色通道的值，强制转成int
	cout << "img2  " << int(img2.at<Vec3b>(10, 10)[0]) << endl;

	//dst=img1-img2;//这两个减法效果相同    若dst<0,则dst=0
	//subtract(img1,img2,dst);//注意：要求被处理图片尺寸一致

	absdiff(img1, img2, dst);//若dst<0,则dst=|dst|>=0    用于检测两幅相似图像的不同点，效果比上面的两种减法好

	cout << "dst  " << int(dst.at<Vec3b>(10, 10)[0]) << endl;
	imshow("dst", dst);
	waitKey(0);
}


//dst = 5 * img1;//增加曝光
//dst = img1 / 5;//降低曝光
//bitwise_and(img1, img2, dst);//逻辑与，求交集
//bitwise_or(img1, img2, dst);//逻辑或，求并集
//bitwise_not(img1, dst);//逻辑非，求补集
//bitwise_xor(img1, img2, dst);//异或，相同为0，相异为1