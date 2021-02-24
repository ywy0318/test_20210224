/*
!!!!!!!!!!!!����������
8.6ͼ���޲�
ͼ��������ʴ,���������ǻҳ�����ˮ�λ����Ǿ���Ƭ�Ļ���,����ͼ�����Ѿ���;
ͼ���޸�(Inpainting);
ͼ���޸�����������Щ�Ѿ����ƻ�����ı�Ե,��Ե����ɫ�ͽṹ,
��ֳ�ͻ�ϵ��𻵵�ͼ����,�Դﵽͼ���޲���Ŀ��;

ͼ���޲�:inpaint()����
������ɨ�����Ƭ����ɨ�ҳ��ͻ���,���ߴӾ�̬ͼ���
��Ƶ�г�ȥ����Ҫ������;
C++:void inpaint(InputArray src,InputArray inpaintMask,OutputArray dst,double inpaintRadius,
int flags)

��һ������:8λ��ͨ��������ͨ��ͼ��
�ڶ�������:InputArray���͵�inpaintMask,�޸�����,Ϊ8λ�ĵ�ͨ��ͼ��;
���еķ������ر�ʾҪ�޲�������
����������:��Դͼ��һ���ĳߴ������
���ĸ�����:double���͵�inpaintRadius,��Ҫ�޲���ÿ�����Բ������,
Ϊ�޸��㷨�Ĳο��뾶
���������:int���͵�flags,�޲������ı�ʶ��;

INPAINT_NS---����Navier-Stokes���̵ķ���
INPAINT_TELEA----Alexandru Telea����

*/
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;

Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
Point previousPoint(-1,-1);//ԭ���ĵ�����

static void on_Mouse(int event, int x, int y, int flags, void*)
{
	//������������Ϣ
	if (event==EVENT_LBUTTONUP||!(flags&EVENT_FLAG_LBUTTON))
	{
		previousPoint = Point(-1,-1);
	}
	//������������Ϣ
	else if (event==EVENT_LBUTTONDOWN)
	{
		previousPoint = Point(x,y);
	}
	//����ƶ����ҽ��л���
	else if(event==EVENT_MOUSEMOVE&&(flags&EVENT_FLAG_LBUTTON))
	{
		Point pt(x,y);
		if (previousPoint.x<0)
		{
			previousPoint = pt;			
		}
		line(mask_img, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		line(src_img, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		previousPoint = pt;
		imshow("src_img",src_img);
	}
}

int main()
{
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	temp_img = src_img.clone();
	mask_img = Mat::zeros(src_img.size(),src_img.type());
	namedWindow("src_img",WINDOW_AUTOSIZE);
	imshow("src_img", src_img);

	//�������ص���Ϣ
	setMouseCallback("src_img",on_Mouse,0);
	while (true)
	{
		char c = (char)waitKey();
		if (c == 27)
		{
			break;
		}
		if (c=='2')
		{
			edge_img = Scalar::all(0);
			src_img.copyTo(temp_img);
			imshow("src_img", src_img);
			//waitKey(0);
		}
		if (c=='1'||c==' ')
		{
			Mat inpainted_img;
			inpaint(temp_img, mask_img, inpainted_img,3,INPAINT_TELEA);
			
			namedWindow("inpainted_img", WINDOW_AUTOSIZE);
			imshow("inpainted_img", inpainted_img);
			//waitKey(0);
		}
		
	}
	return 0;
}