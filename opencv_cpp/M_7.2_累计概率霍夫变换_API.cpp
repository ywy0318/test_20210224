/*
�ۼƸ��ʻ���任:HoughLineP()����
HoughLineP()����,���������Ҷ�ֵͼ���ֱ��
C++:void HoughLineP(InputArray image,OutputArray lines,double rho,
double theta,int threshold,double minLineLength=0,double maxLineGap=0)
��һ������ ����Ҫ8λ�ĵ�ͨ��������ͼ��,���Խ������Դͼ�������������
�����޸ĳɴ˸�ʽ���������;
�ڶ�������:InputArray ���͵�lines,��������HoughLineP������洢�˼�⵽������
�����ʸ��,ÿһ���ɾ���4��Ԫ�ص�ʸ��(x_1,y_1,x_2,y_2)��ʾ,����
(x_1,y_1)��(x_2,y_2)��ÿ����ⰾ���߶εĽ�����;
����������:double���͵�rho,������Ϊ��λ�ľ��뾫��;��һ�ֱ�����ʽ��ֱ������ʱ
�Ľ����ߴ�ĵ�λ�뾶
���ĸ�����:double���͵�theta,�Ի���Ϊ��λ�ĽǶȾ���;��һ�ֱ�ʾ��ʽ��ֱ������ʱ
�Ľ����ߴ�ĵ�λ�Ƕ�;
���������:int���͵�threshold,�ۼ�ƽ�����ֵ����,��ʶ��ĳ����Ϊͼ�е�һ��ֱ��ʱ,
�����ۼ�ƽ���б���ﵽ��ֵ;������ֵthreshold���߶βſ��Ա����ͨ������
���ص������;
����������:double���͵�minLineLength,��Ĭ��ֵΪ0,��ʾ����߶εĳ���,������趨����
�̵��߶ξͲ��ܱ����ֳ���;
���߸�����:double���͵�maxLineGap,��Ĭ��ֵΪ0,����ͬһ�е����֮���������������ľ���

*/

#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int main()
{

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//���б�Ե����ת��Ϊ�Ҷ�ͼ
	Canny(src_img,temp_img,50,200,3);
	cvtColor(temp_img,dst_img,COLOR_GRAY2BGR);
	//���л����߱任
	vector<Vec4i> lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	HoughLinesP(temp_img,lines,CV_PI/180,80,50,10);


	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dst_img,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(186,88,255),1,LINE_AA);
	}

	imshow("src_img", src_img);
	imshow("dst_img",dst_img);
	imshow("temp_img",temp_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
