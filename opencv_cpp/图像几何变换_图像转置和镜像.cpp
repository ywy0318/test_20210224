#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dst;
//	transpose(src,dst);//�����ҷ�ת��Ȼ������ʱ����ת90��
//	flip(src,dst,0);//��x�ᷭת
//	flip(src,dst,1);//����0����y�ᷭת
	flip(src, dst, -1);//С��0����ԭ�㷭ת

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
}