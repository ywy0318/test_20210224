/*
ͼ��任
��һ��ͼ��ת��Ϊͼ�����ݵ���һ�ֱ�����ʽ;
��������Ӿ��Ǹ���Ҷ�任,��ͼ��ת��ΪԴͼ�����ݵ���һ��
������ʽ;��������Ľ����Ȼ������Opencvͼ��ṹ����ʽ,
��ͼ���ÿ���������ر�ʾԭʼ���ͼ���Ƶ�׷���,������ͨ�������ǵĿռ����;

��Ե����һ�㲽��:
��һ��:�˲�
��Ե�����㷨��Ҫ�ǻ���ͼ����ǿ��һ�׼����׵���,���ǵ���ͨ����
����������,��˱�������˲����������������йصı�Ե�����������;
�������˲�������Ҫ�и�˹�˲�,��������ɢ���ĸ�˹��������һ���һ����
��˹��,Ȼ����ڸ�˹�˺�����ͼ��ҶȾ����ÿһ����м�Ȩ���;

�ڶ���:��ǿ
��ǿ��Ե�Ļ�����ȷ��ͼ���������ǿ�ȵı仯ֵ;��ǿ�㷨���Խ�
�ض�ͼ�������ǿ��ֵ�������任�ĵ�͹�Գ���,�ھ���
���ʵ��ʱ,��ͨ�������ݶȸ�ֵ��ȷ��;

������:��ǿ
������ǿ��ͼ��,�����������кܶ����ݶ�ֵ�Ƚϴ�,�����ض���Ӧ����,
��Щ�㲢����Ҫ�ҵı�Ե��,����Ӧ�ò���ĳ�ַ�������Щ�����ȡ��,
ʵ�ʹ�����,���õķ�����ͨ����ֵ���ķ��������;

canny����:
canny��Ŀ�����ҵ�һ�����ŵı�Ե����㷨;
���ű�Ե����������Ҫ����Ŀ��:
�ʹ�����:��ʾ�������ܶ��ʵ�ʱ�Ե,ͬʱ�����ܵļ�����������
����;
�߶�λ��:��ʶ���ı�ԵҪ��ͼ���е�ʵ�ʱ�Ե�����ܽӽ�;
��С��Ӧ:ͼ���еı�Եֻ�ܱ�ʶһ��,���ҿ��ܴ��ڵ�ͼ��������Ӧ��ʶΪ
��Ե;
Ϊ��������ЩҪ��,Cannyʹ���˱�ַ�,����һ��Ѱ�������ض����ܵĺ����ķ���;
���ż����4��ָ��������ĺͱ�ʾ,�������ǳ��ӽ���˹������һ�׵���;

Canny��Ե���Ĳ���:
��һ��:��������;
һ������£�ʹ�ø�˹ƽ���˲����������;
�ڶ���:�����ݶȷ�ֵ�ͷ���
�ݶȷ���һ��ȡ4�����ܵĽǶ�֮һ:0��,45��,90��,135��;
������:�Ǽ���ֵ����
��һ���ų��Ǳ�Ե����,��������һЩϸ����(��ѡ��Ե);
���Ĳ�:
Cannyʹ�����ͺ���ֵ,�ͺ���ֵ��Ҫ������ֵ(����ֵ�����ֵ):
1.>��ĳһ����λ�õķ�ֵ��������ֵ,�����ر�����Ϊ��Ե����,
2.>��ĳһ����λ�õķ�ֵС�ڵ���ֵ,�����ر��ų�;
3.>��ĳһ����λ�õķ�ֵ��������ֵ֮��,�����ؽ��������ӵ�
һ�����ڸ���ֵ������ʱ������;

Canny��Ե���:Canny()����
c++:void Canny(InputArray src,OutputArray edges,double threshold1,
double threshold2,int apertureSize=3,bool L2gradient=false)
�ڶ�������:����ı�Եͼ,��ԴͼƬ��һ���ĳߴ������;
����������:double���͵�threshold1,��һ���ͺ�����ֵ;
���ĸ�����:double���͵�threshold2,�ڶ����ͺ�����ֵ;
���������:int���͵�apertureSize,��ʾӦ��Sobel���ӵ�
�׾���С,Ĭ��ֵΪ3;
����������,bool���͵�L2gradient,һ������ͼ���ݶȷ�ֵ�ı�ʶ,
Ĭ��ֵΪfalse;
��Ҫע�����,���������ֵ1����ֵ2�����н�С��ֵ���ڱ�Ե����,
���ϴ��ֵ��������ǿ��Ե�ĳ�ʼ��,�Ƽ��ĸߵ���ֵ�ı���2:1��3:1֮��;


*/
#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
//opencv����canny��Ե���
//����ͼ��,ת��Ϊ�Ҷ�ͼ,blur����ͼ��ģ�����룬Ȼ����canny���б�Ե��� 

//�߽׵�canny�÷�,ת�ɻҶ�ͼ,����,��canny,��󽫵õ��ı�Ե��Ϊ����,
//����ԭͼ�õ�Ч��ͼ��,�õ���ɫ�ı�Եͼ;

int main(int argc, char* argv[])
{

	//--1--˫��б�߷�
	string imgpath0 = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	//--2--˫��б�߷�
	string imgpath1 = "E://Visual Studio 2010//Projects//opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--3--����б�߷�
	string imgpath2 = "E:/Visual Studio 2010/Projects/opencv_2018_12_21/opencv_2018_12_21/1.jpg";
	//--4--�������ֻ��
	string imgpath3 = "E:/Visual Studio 2010//Projects\\opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--5--���·����
	string imgpath4 = "1.jpg";
	//--6--�����в�����
	//string imgpath5 = argv[1];
	//mat��opencv���������ݽṹ������һ��ͼ���������
	Mat src_img, dst_img, gray_img, edge_img,temp_img;

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	temp_img = src_img.clone();
	imshow("srcimg", temp_img);
	//������src_imgͬ���ͺʹ�С�ľ���
	dst_img.create(src_img.size(), src_img.type());


	//��ԭʼͼ��ת��Ϊ�Ҷ�ͼ��
	//opencv2�汾
	//cvtColor(src_img, gray_img, CV_BGR2GRAY);


	//opencv3�汾
	cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
	//ʹ��3x3�ں�������
	blur(gray_img, edge_img, Size(3, 3));

	//getStructuringElement�ķ���ֵ��ָ����״��ָ���ߴ���ں;���
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//erode(src_img, dst_img, element);

	//Canny����
	Canny(edge_img, edge_img, 3, 9, 3);

	dst_img = Scalar::all(0);
	//ʹ��Canny��������ı�Եͼg_cannyDetectedEdges��Ϊ����,
	//��ԭͼg_srcimage������Ŀ��ͼdst_img
	temp_img.copyTo(dst_img,edge_img);
	imshow("edge_img",edge_img);
	imshow("dst_img", dst_img);

	waitKey(0);
	system("pause");
	return 0;
}