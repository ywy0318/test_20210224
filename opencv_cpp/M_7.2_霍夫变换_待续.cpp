/*
7.2����任(Hough Transform)
��ͼ����ͼ�����Ӿ���,��δӵ�ǰ��ͼ������ȡ����Ҫ��������Ϣ
��ͼ��ʶ��Ĺؼ�����;�����Ӧ�ó�������Ҫ����׼ȷ�ļ���ֱ�߻�
Բ;����һ�ַǳ���Ч�Ľ������ķ������ǻ���(Hough)�任,��Ϊͼ������
��ͼ����ʶ�𼯺���״�Ļ�������֮һ,
Ҳ�кܶ�Ľ��㷨,������Ļ���任�ǴӺڰ�ͼ���м��ֱ��(�߶�);

����任��ͼ�����е�һ��������ȡ����,�ù�����һ�������ռ���ͨ��
�����ۼƽ���ľֲ����ֵ,�õ�һ�����ϸ��ض���״�ļ�����Ϊ����任���;

���ַ�����һ��ͻ���ŵ��Ƿָ�����Robustness,�������ݵĲ���ȫ������
���Ƿǳ�����;
����任������������ռ�֮��ı任����һ���ռ��о�����ͬ��״������
��ֱ��ӳ�䵽��һ������ռ��һ�������γɷ�ֵ,�Ӷ��Ѽ��������״������
ת��Ϊͳ�Ʒ�ֵ����;
�����߱任�ͻ���Բ�任;
�����߱任��һ������Ѱ��ֱ�ߵķ���,��ʹ�û����߱任֮ǰ,����Ҫ��ͼ����б�Ե
���Ĵ���,�������߱任��ֱ������ֻ���Ǳ�Ե��ֵͼ��;
Opencv֧�����ֲ�ͬ�Ļ����߱任,���Ƿֱ���:��׼����任(Standard Hough Transform,SHT),
��߶Ȼ���任(Multi-Scale Hough Transform MSHT),���ۼƸ��ʻ���任(Progressive Probabilistic Hough Transform,PPHT);
��߶Ȼ���任Ϊ�������任�ڶ�߶��µ�һ������;
���ۼƸ��ʻ���任�㷨�Ǳ�׼����任�㷨��һ���Ľ�;
����һ���ķ�Χ�ڽ��л���任�����㵥���߶εķ��򼰷�Χ,�Ӷ�����
������,���̼���ʱ��;
֮���Գ�PPHTΪ����,����Ϊ�������ۼ���ƽ���ڵ����п��ܵĵ��ۼ�,
��ֻ�ۼ�����һ����,���뷨�������ֵ�㹻��,ֻ��һ����ʱ��ȥѰ�����͹���,
���ղ���,����ʵ�ʵļ��ټ���ʱ��;

��OpenCV��,������HoughLines���������ñ�׼����任(SHT)�Ͷ�߶Ȼ���任(MSHT);
��HoughLinesP�������ڵ����ۼƸ��ʻ���任PPHT;�ۼƸ��ʻ���任ִ��Ч��
�ܸ�,���������HoughLines����,��������HoughLineP����;

��׼����任�Ͷ�߶Ȼ���任,��HoughLines��������;
�ۼƸ��ʻ���任��HoughLinesP��������;

��׼����任:HoughLines()����
�˺��������ҳ����ñ�׼����任�Ķ�ֵͼ������;
C++:void HoughLines(InputArray image,OutputArray lines,double rho,
double theta,int threshold,double,srn=0,double srn=0)
��һ������:��Ҫ��ͨ��������ͼ��,
�ڶ�������:��������HoughLines������洢�˻���任��⵽���������ʸ��;
ÿһ�����ɾ�������Ԫ�ص�ʸ��(p,q)��ʾ;
p��������ԭ��(0,0)Ҳ����ͼ�����Ͻǵľ���,q��ʾ����������ת�Ƕ�(0�ȱ�ʾ��ֱ��,PI/2��ʾˮƽ��)
����������:double���͵�rho,������Ϊ��λ�ľ��뾫��;��һ�ֱ�����ʽ��ֱ������ʱ�Ľ����ߴ�ĵ�λ�Ƕ�;
���ĸ�����:double���͵�theta,�Ի���Ϊ��λ�ĽǶȾ���;����һ�ֱ�����ʽ��ֱ������ʱ��
�����ߴ�ĵ�λ�Ƕ�;
���������:int���͵�threshold,�ۼ�ƽ�����ֵ����;��ʶ��ĳ����Ϊͼ�е�һ��ֱ��ʱ,
�����ۼ�ƽ�����ﵽ��ֵ;������ֵthreshold���߶βſ��Ա����ͨ�������ص������;
����������:double���͵�srn,��Ĭ��ֵ0,���ڶ�߶ȵĻ���任,���ǵ��������������ߴ�rho
�ĳ�������;���Ե��ۼ��������ߴ�ֱ���ǵ���������,��ȷ���ۼ��������ߴ�Ϊrho/sm;
���߸�����:double���͵�stn,��Ĭ��ֵΪ0;���ڶ�߶Ȼ���任,srn��ʾ���ĸ�����
�����ߴ�ĵ�λ�Ƕ�theta�ĳ�������;���srn��stnͬʱΪ0,�ͱ�ʾʹ�þ���Ļ���任,
����,����������Ӧ�ö���Ϊ����;


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

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//���б�Ե����ת��Ϊ�ָ�ͼ
	Canny(src_img, temp_img, 50, 200, 3);
	imshow("src_img", src_img);
	//imshow("temp_img", temp_img);
	//image.size().width==image.cols;        image.size().height==image.rows 
	cout << "src_img.dims:" << src_img.dims << endl;	
	//cout << "src_img.type():" << src_img.type() << endl;
	cout << "src_img.channels:" << src_img.channels() << endl;
	cout << "src_img.depth():" << src_img.depth() << endl;
	cout << "src_img.rows:" << src_img.rows << endl;
	cout << "src_img.cols:" << src_img.cols << endl;
	cout << "temp_img.channels():" << temp_img.channels() << endl;
	//waitKey(0);

	//ת����Ե�����ͼΪ�Ҷ�ͼ
	cvtColor(temp_img,gray_img,COLOR_BGR2GRAY);

	//���л����߱任
	vector<Vec2f>lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	HoughLines(temp_img,lines,1,CV_PI/180,150,0,0);

	//������ͼ�л��Ƴ�ÿ���߶�
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0+1000*(-b));
		pt1.y = cvRound(y0+1000*(a));
		pt2.x = cvRound(x0-1000*(-b));
		pt2.y = cvRound(y0-1000*(a));
		//����line(dst_img,pt1,pt2,Scalar(55,100,195),1,CV_AA);
		//�е�Scalar(55,100,195)����G,B,R��ɫֵ����ֵ,�õ�ͼ����Ҫ��������ɫ
		line(gray_img, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
	}

	imshow("temp_img", temp_img);
	imshow("gray_img", gray_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
