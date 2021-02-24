#include<iostream>
#include<opencv2\opencv.hpp>
#include "highgui.h"
#include"cvaux.h"
#include"cxcore.h"
#include"opencv2/imgproc.hpp"
#include<string>
using namespace std;
using namespace cv;

/*
ѧϰ��RGB�����������ռ��ͼ��ת��Ϊ�����ռ��ͼ��

��RGBת��ΪHSV��ɫ����H�������Ͷȣ�S�������ȣ�V����
��RGBת��ΪLab����ɫģ�� (Lab) �����˶���ɫ�ĸо���L��ʾ���ȣ�Luminosity����a��ʾ�����ɫ����ɫ�ķ�Χ��b��ʾ�ӻ�ɫ����ɫ�ķ�Χ�� 
��RGBת��ΪYCrCb�����С�Y����ʾ�����ȣ�Luminance��Luma����Ҳ���ǻҽ�ֵ������U���͡�V�� ��ʾ������ɫ�ȣ�Chrominance��Chroma����
����������Ӱ��ɫ�ʼ����Ͷȣ�����ָ�����ص���ɫ��

*/

/*
void namedWindow(const string& winname,int flags=WINDOW_AUTOSIZE );
��һ��������const string&�͵�name������������ڵı�ʶ���Ĵ������ơ�
�ڶ���������int ���͵�flags �����ڵı�ʶ�����������µ�ֵ��
WINDOW_NORMAL���������ֵ���û�����Ըı䴰�ڵĴ�С��û�����ƣ�
WINDOW_AUTOSIZE������������ֵ�����ڴ�С���Զ���������Ӧ����ʾ��ͼ�񣬲��Ҳ����ֶ��ı䴰�ڴ�С��
WINDOW_OPENGL ������������ֵ�Ļ������ڴ�����ʱ����֧��OpenGL��
����������
������Ҫע����ǣ�����Ĭ��ֵWINDOW_AUTOSIZE�����ԣ�һ������£��������������һ�����������ˡ�
namedWindow�����������ǣ�ͨ��ָ�������֣�����һ��������Ϊͼ��ͽ��������������ڡ�
���������ͬ���ƵĴ����Ѿ����ڣ����������κ����顣
���ǿ��Ե���destroyWindow()����destroyAllWindows()�������رմ��ڣ���ȡ��֮ǰ������봰����ص������ڴ�ռ䡣
����������˵����ʵ���ڴ���������ļ�С������˵��
������ȫû�б�Ҫ�ֶ�����������destroyWindow()����destroyAllWindows()��������Ϊ���˳�ʱ��
���е���Դ��Ӧ�ó���Ĵ��ڻᱻ����ϵͳ���Զ��رա�
*/
/*
��ָ���Ĵ�������ʾһ��ͼ��
void imshow(const string& winname, InputArray mat);
�� ��һ��������const string&���͵�winname������Ҫ��ʾ�Ĵ��ڱ�ʶ���ơ�
�� �ڶ���������InputArray ���͵�mat������Ҫ��ʾ��ͼ��
imshow ������⣺
imshow ����������ָ���Ĵ�������ʾͼ��
�����������CV_WINDOW_AUTOSIZE��Ĭ��ֵ����־�����ģ���ô��ʾͼ��ԭʼ��С��
���򣬽�ͼ������������ʺϴ��ڡ���imshow ��������ͼ��ȡ����ͼ�����ȣ�
��������ͼ����8λ�޷������ͣ�8-bit unsigned��������ʾͼ���������ӡ�
���ͼ����16λ�޷������ͣ�16-bit unsigned����32λ���ͣ�32-bit integer������������ֵ����256��Ҳ����˵��ֵ�ķ�Χ��[0,255 x 256]ӳ�䵽[0,255]��
���ͼ����32λ�����ͣ�32-bit floating-point��������ֵ��Ҫ����255��Ҳ����˵����ֵ�ķ�Χ��[0,1]ӳ�䵽[0,255]��
*/
/*
bool imwrite(const string& filename,InputArray img, const vector<int>& params=vector<int>() );
��һ��������const string&���͵�filename������Ҫд����ļ��������ˣ����Ϻ�׺�����磬��123.jpg��������
�� �ڶ���������InputArray���͵�img��һ����һ��Mat���͵�ͼ�����ݾ����ˡ�
�� ������������const vector<int>&���͵�params����ʾΪ�ض���ʽ����Ĳ������룬����Ĭ��ֵvector<int>()������һ������²���Ҫ��д��

*/
int main()
{
	Mat src_img,des_img;
	string path = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	src_img = imread(path,IMREAD_COLOR);
	if (src_img.empty())
	{
		cout << "imread file failed"<< endl;
	}
	namedWindow("src_img", WINDOW_AUTOSIZE);
	imshow("src_img",src_img);
	//BGR->HSV
	cvtColor(src_img, des_img, CV_BGR2HSV);
	namedWindow("HSV_img", WINDOW_AUTOSIZE);
	imshow("HSV_img", des_img);

	//BGR->Lab
	cvtColor(src_img,des_img,CV_BGR2Lab);
	namedWindow("Lab_img", WINDOW_AUTOSIZE);
	imshow("Lab_img",des_img);
	//BGR->YCrCb
	cvtColor(src_img,des_img,CV_BGR2YCrCb);
	namedWindow("YCrCb_img",WINDOW_AUTOSIZE);
	imshow("YCrCb_img",des_img);
	waitKey(0);
	system("pause");
	return 0;
}