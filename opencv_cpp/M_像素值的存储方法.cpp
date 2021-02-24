#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;

/*

��ֵ����ֻ�кںͰף��ҶȾ����в�ͬ��ȵĻ�ɫ�ͺڰ���ɫ����ɫ���ǲ�ɫ����
������ǿ��Ա��ֵĶ�������ֵֻ�ܱ���������ɫ���Ҷȿ��Ա��ֲ�ͬ��ȵĻ�ɫ���������裬
��ɫ�Ϳ��Ա��ִ󲿷ֶ����ˡ�ռ�ÿռ��ֵ��С���Ҷ���Σ���ɫ��ࡣ

��δ洢����ֵ:
�洢����ֵ��Ҫָ����ɫ�ռ����������;
��ɫ�ռ���ָ���һ����������ɫ,��������ɫԪ���Զ������,
��򵥵���ɫ�ռ䣬Ҫ���ڻҶȼ��ռ䣬ֻ�����ɫ�Ͱ�ɫ,�����ǽ�����ϾͿ��Բ�����ͬ�̶ȵĻ�ɫ;

��ɫ��ʽ���и����������ɫ�ռ�,�������ַ�ʽ,���ǰ���ɫ�ֳ�����Ԫ�ػ����ĸ�Ԫ��,
ͨ����ϻ���Ԫ�ؾͿ��Բ������е���ɫ;
RGB��ɫ�ռ�����õ�һ����ɫ�ռ�,��Ҳ�������ڲ�������ɫ��,
��ʱ��Ϊ�˱�ʾ͸����ɫҲ�������ĸ�Ԫ��alpha(A);

RGB�������,�����۲������ƵĹ�������,����ʾ�豸������
HSV��HLS����ɫ�ֽ��ɫ��,���ͶȺ�����/����,������ɫ����Ȼ��������ʽ
�������ͨ���������һ��Ԫ��,ʹ�㷨������ͼ��Ĺ�������������

YCrCb��JPEGͼ���ʽ�й㷺ʹ��
CIE L*a*b��һ���ڸ�֪�Ͼ��ȵ���ɫ�ռ�,���ʺ���������������ɫ֮��ľ���
ÿ�����Ԫ�ض������Լ��Ķ�����,��������ȡ��������������,��δ洢һ��Ԫ�ؾ�����
�������䶨�������ܹ����Ƶľ���;
����Ԫ�صĳߴ�Ҳ������ͼ����ռ���ڴ�ռ�

*/
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

	Mat src_img, des_img;//mat��opencv���������ݽṹ������һ��ͼ���������

	src_img = imread(imgpath4, 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("srcimg", src_img);
	//getStructuringElement�ķ���ֵ��ָ����״��ָ���ߴ���ں;���
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//erode(src_img, des_img, element);

	//���о�ֵ�˲�����
	blur(src_img, des_img, Size(15, 15));

	imshow("after blur", des_img);

	waitKey(0);
	system("pause");
	return 0;
}