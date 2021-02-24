/*
8.4ͼ��ľ�
�غ�����ͼ����������Ź㷺��Ӧ��;��ģʽʶ��,
Ŀ�����,Ŀ��ʶ���뷽λ����,ͼ��������ع�;

һ����һ������ͼ���м�������ľؼ�,ͨ��������
��ͼ����״��ȫ������;���ṩ�˴����Ĺ��ڸ�ͼ��Ĳ�ͬ���͵�
����������Ϣ,�����С,λ��,������״;

ͼ��ص��������������������㷺��Ӧ���ڸ���ͼ����,
������Ӿ��ͻ����˼��������Ŀ��ʶ���뷽λ������;
һ�׾�����״�й�;
���׾���ʾ����Χ��ֱ��ƽ��ֵ����չ�̶�;
���׾����ǹ���ƽ��ֵ�ĶԳ��ԵĲ���;

���׾غ����׾ؿ��Ե���һ�鹲7�������;
���������ͼ���ͳ������,����ƽ��,��������ת������
�Ĳ�������ͼ��ʶ������õ��㷺��Ӧ��;

һ����moments,contourArea,arcLength�������������ȡ;
ʹ��moments����ͼ�����еľ�(��ߵ�����);
ʹ��contourArea�������������;
ʹ��arcLength���������������߳���;


�صļ���:moments()����
moments()�������ڼ������κ͹�դ��״����ߴ����׵����о�;
������������״������,���,�����������״����;��7Hu��������;
C++:Moments moments(InputArray array,bool binaryImage=false)
��һ������:�����ǹ�դͼ��(��ͨ��,8λ�򸡵�Ķ�ά����)���ά����(1N��N1);
�ڶ�������:bool���͵�binaryImage,��Ĭ��ֵfalse,���˲���ȡtrue,
�򷵻����з�������Ϊ1,�˲�������ͼ��ʹ��; 
�˺����ķ���ֵ�������к�Ľ��

�����������:contourArea()����
contourArea()�������ڼ������������򲿷����������
C++:double contourArea(InputArray contour,bool oriented=false)
��һ������:InputArray ���͵�contour,����ı���,��ά��(������),
����Ϊstd::vector��Mat����
�ڶ�������:bool���͵�oriented,���������ʶ��;����Ϊtrue,�ú�������һ��������
�����ֵ,������ȡ���������ķ���(˳ʱ�뻹����ʱ��);
��������������ǿ��Ը�������ķ�����ȷ��������λ��,��Ҫע�����,
���������Ĭ��ֵfalse,��ʾ�Ծ���ֵ����,��������;

vector<Point> contour;
contour.push_back(Point2f(0,0));
contour.push_back(Point2f(10,0));
contour.push_back(Point2f(10,10));
contour.push_back(Point2f(5,4));

double area_0=contourArea(contour); 

vector<Point> approx;
approxPolyDP(contour,approx,5,true);
double area_1=contourArea(approx);

cout<<"area_0="<<area_0<<endl<<
	"area_1="<<area_1<<endl<<
	"approx poly vertices"<<approx.size()<<endl;

������������:arcLength()����
arcLength()�������ڼ������������ܳ������ߵĳ���
C++:double arcLength(InputArray curve,bool closed);
�ڶ�������:bool���͵�closed,һ������ָʾ�����Ƿ��յı�ʶ��,
��Ĭ��ֵclosed,��ʾ���߷��;
 
*/

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;

int g_nThresh = 100;
int g_nthresh_max = 255;
RNG g_rng(12345);

vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;
void on_ThreshChange(int,void*);

int main()
{

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
	blur(gray_img,gray_img,Size(3,3));
	namedWindow("src_img",CV_WINDOW_AUTOSIZE);
	imshow("src_img", src_img);
	//���������������г�ʼ��
	createTrackbar("��ֵ:","src_img",&g_nThresh,g_nthresh_max,on_ThreshChange);
	on_ThreshChange(0,0);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
void on_ThreshChange(int,void*)
{
	//ʹ��Canny����Ե
	Canny(gray_img,edge_img,g_nThresh,g_nThresh*2,3);
	//�ҵ�����
	findContours(edge_img,g_vContours,g_vHierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));
	//�����
	vector<Moments> mu(g_vContours.size());
	for (size_t i = 0; i < g_vContours.size(); i++)
	{
		mu[i] = moments(g_vContours[i],false);
	}
	//�������ľ�
	vector<Point2f> mc(g_vContours.size());
	for (size_t i = 0; i < g_vContours.size(); i++)
	{
		mc[i] = Point2f(static_cast<float>(mu[i].m10/mu[i].m00),static_cast<float>(mu[i].m01 / mu[i].m00));
	}
	//��������
	Mat draw_img = Mat::zeros(edge_img.size(), CV_8UC3);
	for (size_t i = 0; i < g_vContours.size(); i++)
	{
		//���������ɫֵ
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		//���������ڲ�����
		drawContours(draw_img, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
		//����Բ
		circle(draw_img,mc[i],4,color,-1,8,0);
	}
	namedWindow("draw_img",CV_WINDOW_AUTOSIZE);
	imshow("draw_img", draw_img);

	printf("\t�������:�������������\n");
	for (size_t i = 0; i < g_vContours.size(); i++)
	{
		printf(">ͨ��m00���������[%d]�����:(M_00)=%.2f\nOPENCV����������������=%.2f,����:%.2f\n\n",i,mu[i].m00
		,contourArea(g_vContours[i]),arcLength(g_vContours[i],true));
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255),g_rng.uniform(0, 255));
		drawContours(draw_img,g_vContours,i,color,2,8,g_vHierarchy,0,Point() );
		circle(draw_img, mc[i], 4, color, -1, 8, 0);
	}
}