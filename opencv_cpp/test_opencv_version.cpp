#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img,gray_img,mask_img,edge_img,temp_img;	
int main()
{	
	
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	
	imshow("src_img",src_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION<< endl;
	system("pause");
	return 0;
}
