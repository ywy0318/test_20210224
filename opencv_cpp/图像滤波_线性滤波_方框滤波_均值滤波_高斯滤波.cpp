#include<opencv2/opencv.hpp>
using namespace cv;
//û����ɶЧ����

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dst;
	//�����˲�����-1����ԭͼ����ȣ�size�ں˴�С��true��Ȩ����ӣ���ʱ���ھ�ֵ�˲�����false��ԭ������ӣ����Ժܶ����ص㶼������255������ͼ��ʾ��
//	boxFilter(src, dst, -1, Size(3, 3), Point(-1, -1), true);
//	blur(src,dst,Size(5,5));//��ֵ�˲�
	//GaussianBlur(src,dst, Size(5, 5),1);//��˹�˲�
//	 medianBlur(src, dst, 5);//��ֵ�˲�
  	bilateralFilter(src, dst, 5, 10.0, 2.0);//˫���˲�
	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
}