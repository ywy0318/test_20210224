/*
8ͼ��������ͼ��ָ��޸�
canny֮��ı�Ե����㷨���Ը�������֮��Ĳ���,���������߽�
������,��û�н�������Ϊһ������;

һ������һ���Ӧһϵ�еĵ�,ͼ���е�һ������;
findContours()�����Ӷ�ֵͼ���в�������;

findContours()���������ڶ�ֵͼ����Ѱ������
C++:void findContours(InputArray image,OutputArrayofArrays contours,OutputArray hierarchy
,int mode ,int mthod ,Point offset=Point())

��һ������:InputArray ���͵�image,����ͼ��,Դͼ��,Mat���͵Ķ���,8λ��ͨ������;
ͼ��ķ������ر���Ϊ1,0����ֵ������Ϊ0;����ͼ��Ϊ������;
����ʹ��compare(),inrange(),threshold(),adaptivethreshold(),
canny()�Ⱥ����ɻҶ�ͼ���ɫͼ����������ͼ��;
�˺���������ȡͼ���������ͬʱ�޸�ͼ�������;

�ڶ�������:OutputArrayOfArrays���͵�contours,��⵽������,�������ú��
��������������,ÿ�������洢Ϊһ��������,����Point���͵�vector��ʾ;

����������:OutputArray���͵�hierarchy,��ѡ���������,����ͼ���������Ϣ;
��Ϊ���������ı�ʾ,���������Ԫ��,ÿ������contours[i]��Ӧ4��hierarchy
Ԫ��hierarchy[i][0]--hierarchy[i][3],�ֱ��ʾ��һ������,ǰһ������,
������,��Ƕ�������������,���û�ж�Ӧ��,��Ӧ��hierarchy[i]ֵ����Ϊ
����;
���ĸ�����:int���͵�mode,��������ģʽ;
��ʶ��---����
RETR--EXTERNAL---��ʾֻ������������,����������,����hierarchy[i][2]=hierarchy[i][3]=-1
RETR_LIST---��ȡ��������,���ҷ�ֹ��list��,���������������ȼ���ϵ;
RETR_CCOMP---��ȡ��������,���ҽ�����֯Ϊ˫��ṹ(two-level hierarchy:����Ϊ��ͨ��
����Χ�߽�,�β�Ϊ�׵��ڲ�߽�)
RETR_TREE--��ȡ��������,�����½�����״�������ṹ; 

���������:int method,Ϊ�����Ľ��ư취;
CHAIN_APPROX_NONE :��ȡÿ��������ÿ������,���ڵ������������λ�ò����1,
��max(abs(x1-x2),abs(y2-y1))==1

CHAIN_APPROX_SIMPLE :ѹ��ˮƽ����,��ֱ����,�Խ��߷����Ԫ��,ֻ�����÷����
�յ�����,����һ����������ֻ��4����������������Ϣ;
 
CHAIN_APPROX_TC89_L1
CHAIN_APPROX_TC89_KCOS---ʹ��Teh-Chinl���ƽ��㷨�е�һ��;
����������:Point���͵�offset,ÿ��������Ŀ�ѡƫ����,��Ĭ��ֵ
Point();��ROIͼ�����ҳ�������,��Ҫ������ͼ���н��з���ʱ,��������
�Ϳ��������ó�;

findContours������drawContours���ʹ��--ʹ����findContours()���������
��ͼ���������,�Ϳ�����draeContours�Ⱥ�������⵽���������Ƴ���;
vector<vector<Point>> contours; 
findContours(img,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
//��������,//��ȡ������,//��ȡÿ��������ÿ������


��������:drawContours()����
drawContours()����������ͼ���л����ⲿ���ڲ�����
C++:void drawContours(InputArray image,InputArrayOfarrays contours,
int contourIdx,const Scalar& color,int thickness=1,int linetype=8,
InputArray hierarchy=noArray(),
int maxLevel=INT_MAX,Point=offset=Point())

�ڶ�������:InputArrayOfArrays���͵�contours,���е���������;ÿ�������洢Ϊ
һ��������,��point���͵�vector��ʾ
����������:int���͵�contourIdx,�������Ƶ�ָʾ�����������Ϊ��ֵ,
�������������;
���ĸ�����:const Scalar&���͵�color,��������ɫ
���������:int thickness,���������Ĵ�ϸ��,Ĭ��ֵ1,���Ϊ��ֵ,
(thickness=CV_filled),���������������ڲ�,��ѡ��FILLED��;
����������:int���͵�lineType,����������,��Ĭ��ֵ8;
8(Ĭ��ֵ)--8��ͨ����;
4---4��ͨ����;
LINE_AA---���������;
���߸�����:InputArray���͵�hierarchy,��ѡ�Ĳ�νṹ��Ϣ;Ĭ��ֵ
noArray();
�ڰ˸�����:int���͵�maxLevel,��ʾ���ڻ������������ȼ�,��Ĭ��ֵ
INT_MAX;
�ھŸ�����:Point���͵�offset,��ѡ������ƫ�Ʋ���,��ָ����ƫ����
offset=(dx,dy)������Ҫ���Ƶ�����,��Ĭ��ֵPoint();
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
	int index = 0;
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);

	//��ʼ�����ͼ
	dst_img = Mat::zeros(src_img.rows,src_img.cols,CV_8UC3);

	//src_imgȥ������ֵ119���ǲ���
	src_img = src_img > 119;
	imshow("src_img>119", src_img);
	//���������Ͳ�νṹ
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	 
	//
	findContours(src_img, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	//�������ж��������,�������ɫ���Ƴ�ÿ�������������ɫ
	
	for (; index>=0; index=hierarchy[index][0])
	{
		Scalar color(rand()&255,rand()&255,rand()&255);
		drawContours(dst_img,contours,index,color,FILLED,8,hierarchy);
	}
	imshow("dst_img",dst_img); 
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
