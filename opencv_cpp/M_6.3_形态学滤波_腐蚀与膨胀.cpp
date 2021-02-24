/*
//6.3��̬ѧ�˲�,��ʴ������
��ѧ��̬ѧ:��һ�Ž����ڸ���������ѧ����֮�ϵ�ͼ�����ѧ��,
����ѧ��̬ѧͼ����Ļ�������,��������������:��ֵ��ʴ������,
��ֵ��������,�Ǽܳ�ȡ�����޸�ʴ,���л����б任,��̬ѧ�ݶ�,
Top-hat�任,��������,����任,��ֵ��ʴ������,��ֵ��������,��ֵ��̬ѧ�ݶ�

��̬ѧ�������ǻ�����״��һϵ��ͼ���������,�ֱ�������(dilate)�͸�ʴ(erode)

�����븯ʴ��ʵ�ֶ��ֶ����Ĺ���:
��������;
�ָ�(isolate)��������ͼ��Ԫ��,��ͼ��������(join)���ڵ�Ԫ��;
Ѱ��ͼ���е����Եļ���ֵ������߼�Сֵ����
���ͼ����ݶ�;

��ʴ�������Ƕ԰�ɫ(��������)����,���Ǻ�ɫ���֣�
������ͼ���еĸ������ֽ�������,������"��������",
Ч��ͼӵ�б�ԭͼ����ĸ�������;
��ʴ��ԭͼ�еĸ������ֱ���ʴ,������"���򱻲�ʳ"
Ч��ͼӵ�б�ԭͼ��С�ĸ�������;

���ͻ�ʴ�����ǽ�ͼ��(ͼ���һ��������,)��˽��о��;

�˿������κ���״�ʹ�С,ӵ��һ��������������Ĳο���,��֮Ϊê��(anchorpoint),
��������£�����һ��С�ģ��м���вο�����ʵ�������λ�Բ�̣���ʵ���԰Ѻ���Ϊ
ģ���������;

����(dilate)����ֲ����ֵ�Ĳ���;
ͼ����˽��о��,����˸��ǵ���������ص�����ֵ,����������ֵ
��ֵ���ο���ָ��������;������ʹͼ���еĸ�������������,

��ʴ(erode)���෴��һ�Բ���,���Ծ�����ֲ���Сֵ�Ĳ���;


//����:dilate����
dilate����ʹ�����������ڵľֲ����������������һ��ͼƬ,��src����,
��dst���,֧�־͵�(in-place)����

void dilate(InputArray src,OutputArray dst,InputArray kernel,Point anchor=Point(-1,-1),
int iterations=1,
int borderType=BORDER_CONSTRANT,const Scalar& borderValue=morphologyDefaultBorderValue());
��һ������:ͼ�����ӦΪCV_8U,CV_16U,CV_16S,CV_32F��CV_64F
�ڶ�������:�ߴ������Ӧ�ú�Ŀ��ͼ��һ��,
����������:���Ͳ����ĺ�,��ΪNULLʱ����ʾʹ�òο���λ������3X3�ĺ�

һ��ʹ�ú��� getStructuringElement����������ʹ��;
getStructuringElement�����᷵��ָ����״�ͳߴ�ĽṹԪ��(�ں˾���),
getStructuringElement�����ĵ�һ��������ʾ�ں˵���״,
��������״����ѡ��:
����:MORPH_RECT;
������:MORPH_CROSS;
��Բ��:MORPH_ELLIPSE;
�ڶ��������͵����������ֱ����ں˵ĳߴ缰ê���λ��;
һ���ڵ���erode��dilate����֮ǰ���ȶ�һ��Mat���͵ı��������
getStructuringElement�����ķ���ֵ;��Ӧê���λ��,Ĭ��ֵPoint(-1,-1),
��ʾê����������,������Ҫע�����,ʮ���ε�element��״Ψһ������ê���λ��,
�������������,ê��ֻ��Ӱ������̬ѧ��������ƫ��;

getStructuringElement������صĵ���ʾ������
int g_nStructElementSize=3;//�ṹԪ��(�ں˾���)�ĳߴ�
//��ȡ�Զ����
Mat element=getStructuringElement(MORPH_RECT,Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1)
,Point(2*g_nStructElementSize+1,2*g_nStructElementSize+1));

����֮�󣬿����ڽ���������erode��dilate���� ʱ,�ڵ��������������
getStructuringElement����ֵ��Mat���ͱ���;
���ĸ�����:Point���͵�anchor,ê���λ��,Ĭ��ֵ(-1,-1),��ʾê��λ������;
���������:int ���͵�iterations,����ʹ��erode()�����Ĵ���,Ĭ��ֵΪ1��
����������:int���͵�borderType,�����ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ;
Ĭ��ֵΪBORDER_DEFAULT
���߸�����:const Scalar&���͵�borderValue,���߽�Ϊ����ʱ�ı߽�ֵ,
��Ĭ��ֵmorphologyDefaultBorderValue(),һ�㲻��ȥ����,
��Ҫʱȥ�鿴�ٷ��ĵ���createMorphologyFilter()����,


��ʴ:erode����
erode����ʹ�����������ڵľֲ���С���������ʴһ��ͼƬ,֧�־͵�(in-place)
����
C++:void erode(InputArray src,OutputArray dst,InputArray kernel,Point anchor=Point(-1,-1),
int iterations=1,int borderType=BORDER_CONSTRANT,
const Scalar& borderValue=morphologyDefaultBorderValue());
*/

#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;



int main()
{
	Mat src_img, dst_img, gray_img, edge;

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img");
	namedWindow("erode");
	imshow("src_img",src_img);

	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	//��ʴ����
	//erode(src_img,dst_img,element);

	imshow("erode", dst_img);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
