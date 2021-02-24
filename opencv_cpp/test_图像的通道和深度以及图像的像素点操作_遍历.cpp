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
ͼ�����Ⱥ�ͨ��
ͼ�������ص�ռ��bitλ��������ͼ������;
����:
��ֵͼ��ͼ������ص㲻��0����1(ͼ���Ǻ�ɫ���ǰ�ɫ),ͼ�����ص�ռ��λ������1λ��ͼ�����Ⱦ���1��Ҳ����λͼ;
�Ҷ�ͼ��:ͼ������ص�λ��0-255֮�䣬(0:ȫ�ڣ�255����ȫ�ף���0-255֮�������256���ȼ��ĻҶȣ�),
2^8=256��ͼ�����Ⱦ���8
�Դ����ƣ����ǰѼ�����д洢�������ص����õ�bitλ��Ϊͼ������;
ͼ���ͨ��
����ͼ����ȵĸ������֪�������24λ��ͼ����������ص����ɫȡֵ��Χ��:0-2^24,�����Χ�ر��
�������֪����ĳ�������ֵ��ô�ж����ص����ɫ�أ�
BGR�ǻ�������ԭɫ�����������8λ����һ����ɫ��ÿ����ɫ�����255������ÿ�����ص����ɫֵ�ķ�Χ����
(0-255,0-255,0-255)����ͼ���ͨ������3;
�Ҷ�ͼ��ͼ��洢ģ��
�Ҷ�ͼ�����ص�Ĵ洢���Ƕ�Ӧ��ԭͼ�����ң����ϵ��£���������,ÿ�����ֵ�������ص��ֵ��
ÿ����ĵ�ַ�����������ص�ĵ�ַ��
RGBͼ��ͼ��洢ģ��
RGB��ɫͼ��ͻ�ɫͼ��ȣ�ÿ�����ص㶼��3��ͨ����ÿ��ͨ��ռ���ڴ�ռ�8λ�����ڴ���RGBͼ��Ĵ洢���Զ�ά�������ʽ;

ͼ�������ص�ı���
ע��:���Ƕ�ͼ�����صı�����ʵ��ÿ�����ص���ͨ���ı������Ժ����Ƕ��������Լ�ͨ����ز���

ʲô����ɫ�ռ����ɫ
����3ͨ���������8��RGBͼ��һ��������255^3����ɫ������Ӵ����ɫ�����ǵĴ���ܲ����㣬���Զ�ͼ������ؽ���������
��Сͼ�����ɫ���࣬ͬ��Ҳ���Դﵽͬ����Ч�����������ǰ�ͼ������ؼ���8������ÿ��ͨ����ֻ����256/8=32����ɫ��
�����Ļ���Բ��ͼ��0-7���ص��Ӧ�������0����������ʵ�ֶ�ͼ���ѹ��;
����C/C++��int������"/"���㣬�����Ļ�(0-7)/8=0,ͬ�����ο��Եõ�ѹ��������ֵ;

(1)���û������к��и���ʵ�����ر���;
ͼ��Ĵ洢���Զ�ά�������ʽ��ȡ��ά�����е�Ԫ�أ���ȷ���У���ȷ���У��������ܰ�Ԫ����ȡ������
opencv��Mat���ж����ָ�룬���Ի�ȡĳһ�еĵ�ַ��Ȼ��ȷ�������Ϳ��Ի�ȡ����Ҫ�ĵ�ַ;
Mat������:Mat.ptr<uchar>(int i=0)��ȡ���ؾ����ָ�룬i�Ǵӵ�0�п�ʼ�ģ�����е����ά���ݵĴ洢������
��ά������Ե��������ɸ�һάָ�룬���֪����ÿ���еĵ�һ��Ԫ�ؾ��ܱ�����������


*/
//(1)���û������к��и���ʵ�����ر���;
//srcImage:����ͼ��,desImage:���ͼ��,n���ٱ���
void colorReduce(Mat&srcImage, Mat&desImage, int n)
{
	desImage = srcImage.clone();
	int channels = desImage.channels();
	int rows = desImage.rows;
	int cols = desImage.cols;//���������������ص���������ͨ����,�����RGBͼ��Ĵ洢
	//˫��ѭ������ѭ��������ͼƬ������
	for (int i = 0; i < rows; i++)
	{
		uchar *pt = desImage.ptr<uchar>(i);//��ȡ��i�е�ͼ�����ָ��;
		for (int j = 0; j < cols; j++)//˫��ѭ������ѭ��,����ͼ�������(����ÿ��ͨ����)
		{
			pt[j] = (pt[j] / n)*n + n / 2;//ͨ�����ǻ��ں������n/2;
			//�ڲ�ѭ��������ָ��ʵ���ƶ�����һ��
			//*pt++ = (*pt / n)*n + n / 2;
		}
	}
}
//(2)���ö�̬��ַ�������ص�
/*
Mat���еĳ�Ա����at(int x,int y)������������ͼ��Ԫ��,�����ڱ����ڼ䣬֪��ͼ����������ͣ�
����һ����ȷ��ָ�����������ͺ;������������ͷ���,��Ϊat����������κ��������ͽ���ת��;
���ڲ�ɫͼ��ÿ����������������ɣ�ͨ��(RGB),��ˣ�����ÿһ��������ɫͼ���Mat,�᷵��һ����
8λ������ɵ�����,opencv����������������Ϊ:Vec3b;�洢��ɫͼ�����ش������д��:
image.at<Vec3b>(i,j)[channal]=value;
����,(i,j)�������ص�λ�ã�channel����ͨ��;

*/
void colorReduce2(Mat&src, Mat&des, int n = 8)
{
	des = src.clone();
	int cols = src.cols;
	int rows = src.rows;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			des.at<Vec3b>(i, j)[0] = (src.at<Vec3b>(i, j)[0] / n)*n + n / 2;
			des.at<Vec3b>(i, j)[1] = (src.at<Vec3b>(i, j)[1] / n)*n + n / 2;
			des.at<Vec3b>(i, j)[2] = (src.at<Vec3b>(i, j)[2] / n)*n + n / 2;
		}
	}
}
//(3)��������������
//��������C++��STL�ĸ���
void colorReduce3(Mat&src, Mat&des, int n = 8)
{
	des = src.clone();
	Mat_<Vec3b>::iterator it = des.begin<Vec3b>();//��ʼλ�õ�����
	Mat_<Vec3b>::iterator itend = des.end<Vec3b>();//��ʼλ�õ�����
	for (;it!=itend; it++)
	{
		(*it)[0] = ((*it)[0] / n)*n + n / 2;
		(*it)[1] = ((*it)[1] / n)*n + n / 2;
		(*it)[2] = ((*it)[2] / n)*n + n / 2;
	}
}
//��ͨ������
void fore_each_signal(Mat &src)
{
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			uchar *data = src.ptr<uchar>(i);
			int pixel = data[j];
			printf("gray_pixel=%d\n",pixel);
		}
	}
}
//RGBͼ��
void fore_each_RGB(Mat&src)
{
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			uchar *data = src.ptr<uchar>(i);
			int b = data[3 * j];
			int g = data[3 * j + 1];
			int r = data[3 * j + 2];
			printf("blue_pixel=%d-green_pixel=%d-red_pixel=%d\n",b,g,r);
		}
	}
}

/*
�������ش洢�ṹ

*/
/*
opencv������ģ��Vec,���Ա�ʾһ������;opencv��ʹ��Vec��Ԥ������
һЩС����,�������ھ���Ԫ�صı��;

typedef Vec<uchar, 2> Vec2b;
typedef Vec<uchar, 3> Vec3b;
typedef Vec<uchar, 4> Vec4b;

typedef Vec<short, 2> Vec2s;
typedef Vec<short, 3> Vec3s;
typedef Vec<short, 4> Vec4s;

typedef Vec<int, 2> Vec2i;
typedef Vec<int, 3> Vec3i;
typedef Vec<int, 4> Vec4i;

typedef Vec<float, 2> Vec2f;
typedef Vec<float, 3> Vec3f;
typedef Vec<float, 4> Vec4f;
typedef Vec<float, 6> Vec6f;

typedef Vec<double, 2> Vec2d;
typedef Vec<double, 3> Vec3d;
typedef Vec<double, 4> Vec4d;
typedef Vec<double, 6> Vec6d;

����8U���͵�RGB��ɫͼ��Ҳ����ʹ��Vec3B,
3ͨ��float���͵ľ������ʹ��Vec3f,
����Vec�������ʹ��[]����������һ������Ԫ��
���ж�д����
��:
Vec3b color;//��color��������һ��RGB��ɫ
color[0]=255;//B����
color[1]=0;//G����
color[2]=0;//R����
*/
/*
3������ֵ�Ķ�д
�ڶ�ͼ����д���ʱ����Ҫ��ȡĳ������ֵ��������ĳ������ֵ;
�ڸ����ʱ����Ҫ��ͼ�����������ؽ��б���

*/

void test_01()
{
	//2D Point
	Point2f p(5, 1);
	cout << endl << "Point(2D)=" << p << endl << endl;
	//3D Point
	Point3f p3f(2, 5, 7);
	cout << endl << "Point(3f)=" << p3f << endl << endl;
	//std::vector via cv::Mat
	vector<float> v;
	v.push_back((float)CV_PI);//��pi��ֵ��float���ʹ���v,push_back��c++��������һ�ֲ���
	v.push_back(2);
	v.push_back(3.01f);
	cout << "vector of floats via Mat=" << endl << Mat(v) << endl << endl;

	//std::vector of points 
	vector<Point2f> vPoints(20);
	for (size_t i = 0; i < vPoints.size(); ++i)
	{
		vPoints[i] = Point2f((float)i * 5, (float)(i % 7));
	}
	cout << "vector of 2D points=" << endl << vPoints << endl << endl;
}
//3.1 at()����
/*
�����ú���at()��ʵ�ֶԾ�����ĳ������ֵ���ж�ȡ����и�ֵ����,
����ǰ��Ҫ֪������������λ��,
�÷�����:
uchar value =img.at<uchar>(i,j);//��ȡ��i�е�j������ֵ
img.at<uchar>(i,j)=128;//����i�е�j������ֵ����Ϊ128
*/
//�����Ҫ��ͼ�����ؽ��б��������Ƽ�ʹ��at()��������Ϊʹ�����������Ч�ʲ��ߣ�������ɶ��ԽϺá�
void fore_each_at()
{
	double timeConsume = static_cast<double>(getTickCount());
	Mat grayImage(400,600,CV_8UC1);//����һ����СΪ600*800�ĵ�ͨ���Ҷ�ͼ
	Mat colorImage(400,600,CV_8UC3);//����һ����СΪ400*600����ͨ����ɫͼ
	//�����������ز���������ֵ
	for (int i = 0; i < grayImage.rows; i++)//������
	{
		for (int j = 0; j < grayImage.cols; j++)//������
		{
			grayImage.at<uchar>(i, j) = (i + j) % 255;
		}
	}
	//�����������ز���������ֵ
	for (int i = 0; i < colorImage.rows; i++)//������
	{
		for (int j = 0; j < colorImage.cols; j++)//������
		{
			Vec3b pixel;//������ͨ������ֵ����
			pixel[0] = i % 255;//blue
			pixel[1] = j % 255;//green
			pixel[2] = 0;//red
			colorImage.at<Vec3b>(i, j) = pixel;
		}
	}
	//��ʾ����ͼ��Ľ��
	namedWindow("grayimage",WINDOW_AUTOSIZE);
	imshow("grayimage",grayImage);

	namedWindow("colorimage", WINDOW_AUTOSIZE);
	imshow("colorimage", colorImage);

	timeConsume = ((double)getTickCount() - timeConsume) / getTickFrequency();
	cout << "�����ʱ:" << timeConsume << endl;


}

/*
ʹ�õ�����iterator
ʹ�õ��������Ժܷ���ı�������Ԫ��;Mat��֧�ֵ������ķ�ʽ�Ծ���Ԫ�ؽ��б���;
����ʹ�õ������Ͳ���Ҫ��ʹ�����������в���;
*/
/*
ʹ�õ������������ر�������Ϊ��һ�ָ���ȫ�ķ�ʽ,ʹ�õ�����ֻ��Ҫ�������Ŀ�ͷ�;���ĩβ��
������ʹ��forѭ�����е�����֪��"it==end",
������"colorit=colorimage.begin(),colorend=colorimage.end()";
�����������ʼλ�úͽ���λ��;
*/
void fore_each_iterator()
{
	double timeConsume = static_cast<double>(getTickCount());
	Mat grayImage(400,600,CV_8UC1);
	Mat colorImage(400, 600, CV_8UC3);
	//�����������ز�����������ֵ
	MatIterator_<uchar>grayit, grayend;
	for (grayit = grayImage.begin<uchar>(), grayend = grayImage.end<uchar>(); grayit != grayend; grayit++)
	{
		*grayit = rand() % 255;
	}
	//�����������ز���������ֵ
	MatIterator_<Vec3b> colorit, colorend;
	for (colorit = colorImage.begin<Vec3b>(), colorend = colorImage.end<Vec3b>(); colorit != colorend; colorit++)
	{
		(*colorit)[0] = rand() % 255;//blue
		(*colorit)[1] = rand() % 255;//green
		(*colorit)[2] = rand() % 255;//red
	}
	namedWindow("color",WINDOW_AUTOSIZE);
	imshow("color",colorImage);//

	namedWindow("gray",WINDOW_AUTOSIZE);
	imshow("gray",grayImage);
	timeConsume = ((double)getTickCount() - timeConsume) / getTickFrequency();
	cout <<"�����ʱ:" <<timeConsume<< endl;
	waitKey(0);
}

/*
3.3ʹ��ָ����з���
��ǰ���Ѿ��ᵽ��ָ����з���,��Ȼʹ��ָ���ٶ���죬����ָ���������������
�Լ�Խ���飬�����ڳ���д�ñ���û�����⣬�������о��п��ܳ���;
��Ȼ�ٶȲ���ָ�룬����������߱Ƚ�����ʵ��,�ɶ��ԱȽϺ�,

*/
void fore_each_point()
{
	double timeConsume = static_cast<double>(getTickCount());
	Mat grayImage(400,600,CV_8UC1);
	Mat colorImage(400, 600, CV_8UC3);
	//����
	for (int i = 0; i < grayImage.rows; i++)
	{
		uchar *p = grayImage.ptr<uchar>(i);//��ȡ��i�е�һ�����ص�ָ��
		for (int j = 0; j < grayImage.cols; j++)
		{
			p[j] = (i + j) % 255;//��ÿ��i�е��������ؽ��и�ֵ����
		}
	}
	//�����������ز�����������ֵ
	for (int i = 0; i < colorImage.rows; i++)
	{
		Vec3b *p = colorImage.ptr<Vec3b>(i);
		for (int j = 0; j < colorImage.cols; j++)
		{
			p[j][0] = i % 255;
			p[j][1] = j % 255;
			p[j][2] = 0;
		}
	}
	namedWindow("grayimage",WINDOW_AUTOSIZE);
	imshow("grayimage",grayImage);
	namedWindow("color",WINDOW_AUTOSIZE);
	imshow("color",colorImage);
	timeConsume=((double)getTickCount() - timeConsume) / getTickFrequency();
	cout <<"�����ʱ:"<< timeConsume<< endl;
	waitKey(0);
}

int main()
{
	//test_01();
	//fore_each_at();
	//fore_each_iterator();
	fore_each_point();
	system("pause");
	return 0;
}