/*7.1.5scharr�˲���
scharr�˲���,��opencv����Ҫ�����Sobel���ӵ���������ڵ�;
1.>����ͼ����:Scharr()����
ʹ��Scharr�˲������������x��y�����ͼ����;��ʵ����
����������Sobel��������һ����,����û��ksize�˵Ĵ�С;
C++:void Scharr(InputArray src,OutputArray dst,int ddepth,
int dx,int dy,double scale=1(��������),double delta=0,int boederType=BORDER_DEFAULT)

Scharr(src,dst,ddepth,dx,dy,scale,delta,borderType)
Sobel(src,dst,ddepth,dx,dy,CV_SCHARR,scale,delta,borderType)
*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);
	//x�����ݶ�
	Scharr(src_img,grad_x,CV_16S,1,0,1,0,BORDER_DEFAULT);
	convertScaleAbs(grad_x,abs_grad_x);
	imshow("abs_grad_x",abs_grad_x);

	//y�����ݶ�
	Scharr(src_img,grad_y,CV_16S,0,1,1,0,BORDER_DEFAULT);
	convertScaleAbs(grad_y,abs_grad_y);
	imshow("abs_grad_y",abs_grad_y);
	
	//�ϲ��ݶ�(����)
	addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,dst_img);
	imshow("addWeighted",dst_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
