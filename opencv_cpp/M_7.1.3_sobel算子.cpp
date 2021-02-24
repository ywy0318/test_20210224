/*
sobel���ӵĻ�������
sobel������һ����Ҫ���ڱ�Ե������ɢ΢������;
������˸�˹ƽ����΢����,��������ͼ��ҶȺ����Ľ����ݶ�;
��ͼ����κ�һ��ʹ�ô�����,����������Ӧ���ݶ�ʸ�����䷨ʸ��
1.>�ֱ���x��y����������;
2.>��ͼ���ÿһ��,����������������������ݶ�
Sobel����ʹ����չ��Sobel,������һ��,���ף����׻���ͼ����;
C++:void sobel(InputArray src,OutputArray dst,int ddepth,int dx,int dy,
int ksize=3,double scale=1,double delta=0,int borderType=BORDER_DEFAULT);

����������:int ���͵�ddepth,���ͼ������,src.depth()��ddepth�����;
	��src.depth()=CV_8U,ȡddepth=-1/CV_16S/CV_32F/CV_64F
	��src.depth()=CV_16U/CV_16S,ȡddepth=-1/CV_32F/CV_64F
	��src.depth()=CV_32U,ȡddepth=-1CV_32F/CV_64F
	��src.depth()=CV_64U,ȡddepth=-1/CV_64F

����������:ksize,Ĭ��ֵΪ3,��ʾSobel�˵Ĵ�С,����ȡ1��3��5��7
���߸�����:double���͵�scale,���㵼��ֵʱ��ѡ����������,Ĭ��ֵ��1,
��ʾĬ���������û��Ӧ�����ŵ�;
�ڰ˸�����:double���͵�delta,��ʾ�ڽ������Ŀ��ͼ(�ڶ�������dst)
֮ǰ��ѡ��delta ֵ,��Ĭ��ֵ0;
�ھŸ�����:int���͵�borderType,�߽�ģʽ,Ĭ��ֵΪBORDER_DEFAULT;
һ�������,������ksize*ksize�����㵼����,��ksize=1ʱ,
������ʹ��3*1����1*3,�����������,û�н��и�˹ƽ������;

���ں˴�СΪ3ʱ,Sobel�ں˿��ܲ����Ƚ����Ե����,
(�Ͼ�Sobel����ֻ����ȡ�����Ľ���ֵ����,);
Scharr����,���ú����������ڴ�СΪ3���ں�,�ú����������Sobel����һ����;
���ǽ�����Ӿ�ȷ;
��ΪSobel���ӽ���˸�˹ƽ���ͷֻ�,��˽������и���Ŀ�����;
����������,ʹ��sobel����ʱ,xorder=1,yorder=0,ksize=3������ͼ��X����ĵ���;
xorder=0,yorder=1,ksize=3;������ͼ��y����ĵ���;

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
	Mat abs_grad_x, abs_grad_y, dst;
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img",src_img);
	//��x�����ݶ�
	Sobel(src_img, grad_x,CV_16S,1,0,3,1,1,BORDER_DEFAULT);
	convertScaleAbs(grad_x,abs_grad_x);
	imshow("x_sobel",abs_grad_x);

	//��y�����ݶ�
	Sobel(src_img, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("y_sobel", abs_grad_y);
	//�ϲ��ݶ�
	addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,dst);
	imshow("dst",dst);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
