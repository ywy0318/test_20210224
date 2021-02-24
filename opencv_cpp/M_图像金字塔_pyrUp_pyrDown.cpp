#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img,temp_img;
int main()
{
	int key = 0;
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	temp_img = src_img;
	dst_img = src_img;
	
	namedWindow("src_img",1); 
	imshow("src_img",src_img);

	while (true)
	{
		key = waitKey(9);//读取键值到key变量中
		switch (key)
		{
		case 27://按下ESC
			return 0;
			break;
		case 'q'://按下ESC
			return 0;
			break;
		case'a':
			pyrUp(temp_img,dst_img,Size(temp_img.cols*2,temp_img.rows*2));
			cout << "a按下,开始基于pyrUp函数的图片放大,图片尺寸*2\n";
			break;
		case'1'://按键1按下,resize函数
			resize(temp_img,dst_img,Size(temp_img.cols*2,temp_img.rows*2));
			cout << "1被按下,开始进行resize函数的图片放大,图片尺寸*2\n";
			break;
		case'3':
			pyrUp(temp_img,dst_img,Size(temp_img.cols*2,temp_img.rows*2));
			cout << "3被按下,开始进行pyrUp函数的图片放大:图片尺寸*2\n";
			break; 
		case 'd':
			pyrDown(temp_img,dst_img,Size(temp_img.cols/2,temp_img.rows/2));
			cout << "d被按下,开始进行pyrDown函数的图片缩小,图片尺寸/2\n";
			break;
		case's':
			resize(temp_img,dst_img,Size(temp_img.cols/2,temp_img.rows/2));
			cout << "s被按下,开始进行resize函数的图片缩小:图片尺寸/2\n";
			break;
		case '4':
			pyrDown(temp_img,dst_img,Size(temp_img.cols/2,temp_img.rows/2));
			cout << "4被按下,开始进行pyrDown函数的图片缩小:图片尺寸/2\n";
			break;
		default:
			break;
		}
		namedWindow("dst_img",1);
		imshow("dst_img",dst_img);
		temp_img = dst_img;
	}

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
