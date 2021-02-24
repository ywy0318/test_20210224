/*
6.4��̬ѧ�˲�(2):�����㣬�����㣬��̬ѧ�ݶȣ���ñ,��ñ,
���ͺ͸�ʴ�����������̬ѧ����������ʵ�ָ��߼�����̬ѧ�任;
�߼�����̬ѧ���ǽ����ڸ�ʴ�����ͻ����ϵ�;

������(Opening Operation),��ʵ�����ȸ�ʴ�����͵Ĺ���;
dst=open(src,element)=dilate(erode(src,element))
���������������С���壬����ϸ�㴦�������壬������ƽ���ϴ������
�߽��ͬʱ���ı������

������:�����ͺ�ʴ�Ĺ��̳�Ϊ������(Closing Operation);
dst=clese(src,element)=erode(dilate(src,element));
�������ܹ��ų�С�ͺڶ�(��ɫ����);

��̬ѧ�ݶ�(Morphological Gradient)������ͼ�븯ʴͼ֮��,
dst=morph-grad(src,element)=dilate(src,element)-erode(src,element);
�Զ�ֵͼ�������һ���������Խ��ſ�(blob)�ı�Եͻ������������̬ѧ�ݶ�����������
�ı�Ե����;

��ñ����(Top Hat)�ֱ���Ϊ"��ñ"����,
��ñ����:��ԭͼ���뿪���صĽ��ͼ֮��,
dst=tophat(src,element)=src-open(src,element)
����������Ľ���ǷŴ����ѷ���߾ֲ������ȵ�����,
��ˣ���ԭͼ�м�ȥ��������ͼ���õ���Ч��ͼͻ���˱�ԭͼ
������Χ�������������������һ�β�����ѡ��ĺ˵Ĵ�С���;

��ñ������������������ٽ�����һЩ�İߵ�,��һ��ͼ�����
����ı�������΢С��Ʒ�Ƚ��й��ɵ�����£�����ʹ��
��ñ������б�����ȡ;

��ñ(Black Hat)�����Ǳ�����Ľ��ͼ��ԭͼ��֮��,
dst=blackhat(src,element)=close(src,element)-src
��ñ������Ч��ͼͻ���˱�ԭͼ������Χ���������������
��һ������ѡ��ĺ˵Ĵ�С���;

morphologyEx�������û��������ͺ͸�ʴ��������ִ�и��Ӹ߼���̬ѧ�任;
��Щ�������Խ��о͵ز���(in-place)���������ڶ�ͨ��ͼ��ÿһ��ͨ����
�������в���;
morphologyEx:������ʵ�ָ�ʴ�����Ͳ���;
C++:void morphologyEx(
InputArray src,
OutputArray dst,
int op,
InputArray kernel,
Point anchor=Point(-1,-1),
intiterations=1,
intborderType=BORDER_CONSTANT,
const Scalar& borderValue=morphologyDefaultBorderValue());

����������:int���͵�op,��ʾ��̬ѧ���������,
MORPH_OPEN  ������
MORPH_CLOSE ������
MORPH_GRADIENT ��̬ѧ�ݶ�
MORPH_TOPHAT ��ñ
MORPH_BLACKHAT ��ñ
MORPH_ERODE    ��ʴ
MORPH_DILATE   ����
���ĸ�����:InputArray���͵�kernel,��̬ѧ������ں�,��ΪNULL,
��ʾ����ʹ�òο���λ������3X3�ĺ�,һ��ʹ�ú���
getStructuringElement������������ʹ��
����������:int���͵�iterations,����ʹ�ú����Ĵ�����Ĭ��ֵΪ1;
*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, edge; 
int g_nElementShape = MORPH_RECT;//Ԫ�ؽṹ����״

//����TrcakBarλ�ò���
int g_nMaxIterationNum = 10;

int g_nOpenCloseNum = 10;
int g_nErodeDilateNum = 10;
int g_nTopBlackHatNum = 10;

void on_OpenClose(int, void*);//�ص�����
void on_ErodeDilate(int ,void*);
void on_TopBlackHat(int,void*);

int main()
{
	
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img",1);
	imshow("src_img",src_img);

	namedWindow("�����������", 1);
	namedWindow("��ʴ����", 1);
	namedWindow("��ñ��ñ", 1);

	//�ֱ�Ϊ�������ڴ���������
	createTrackbar("����ֵ", "�����������", &g_nOpenCloseNum, g_nMaxIterationNum * 2 + 1, on_OpenClose);
	createTrackbar("����ֵ", "��ʴ����", &g_nErodeDilateNum, g_nMaxIterationNum * 2 + 1, on_ErodeDilate);
	createTrackbar("����ֵ", "��ñ��ñ", &g_nTopBlackHatNum, g_nMaxIterationNum * 2 + 1, on_TopBlackHat);
	
	while (true)
	{
		int c;
		on_OpenClose(g_nOpenCloseNum,0);
		on_ErodeDilate(g_nErodeDilateNum,0);
		on_TopBlackHat(g_nTopBlackHatNum,0);
		//��ȡ����
		c = waitKey(0);
		//����Q������ECS,�����˳�
		if ((char)c=='q'||(char)c==27)
		{
			break;
		}
		//���¼���1��ʹ����Բ(Elliptic)�ṹԪ��MORPH_ELLIPSE
		if ((char)c==49)
		{
			g_nElementShape = MORPH_ELLIPSE;
		}
		//50���� ����2
		else if((char)c == 50)
		{
			g_nElementShape = MORPH_RECT;
		}
		//51���� ����3
		else if ((char)c == 51)
		{
			g_nElementShape = MORPH_CROSS;
		}
		//�ո��,�ھ���,��Բ��ʮ������ѭ��
		else if ((char)c == ' ')
		{
			g_nElementShape = (g_nElementShape+1)%3;
		}

	}
	//�����
	//Mat element = getStructuringElement(MORPH_RECT,Size(15,15));

	//������̬ѧ����--���Ҫѡȡ������̬ѧ�Ĳ�����ֻ��Ҫ�ı����������
	//--MORPH_OPEN--MORPH_CLOSE--MORPH_GRADIENT--MORPH_TOPHAT--MORPH_BLACKHAT--MORPH_ERODE--MORPH_DILATE
	//morphologyEx(src_img,dst_img, MORPH_DILATE,element);
	//imshow("dst_img", dst_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}

void on_OpenClose(int, void*)
{
	//ƫ�����Ķ���
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;

	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));

	if (offset<0)
	{
		morphologyEx(src_img,dst_img,MORPH_OPEN,element);
	}
	else
	{
		morphologyEx(src_img, dst_img, MORPH_CLOSE, element);
	}
	imshow("�����������",dst_img);
}

void on_ErodeDilate(int, void*)
{
	//ƫ�����Ķ���
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;

	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));

	if (offset<0)
	{
		//morphologyEx(src_img, dst_img, MORPH_TOPHAT, element);
		erode(src_img,dst_img,element);
	}
	else
	{
		//morphologyEx(src_img, dst_img, MORPH_BLACKHAT, element);
		dilate(src_img,dst_img,element);
	}
	imshow("��ʴ����", dst_img);
}

void on_TopBlackHat(int, void*)
{
	//ƫ�����Ķ���
	int offset = g_nTopBlackHatNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;

	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));

	if (offset<0)
	{
		morphologyEx(src_img, dst_img, MORPH_TOPHAT, element);
	}
	else
	{
		morphologyEx(src_img, dst_img, MORPH_BLACKHAT, element);
	}
	imshow("��ñ��ñ", dst_img);
}