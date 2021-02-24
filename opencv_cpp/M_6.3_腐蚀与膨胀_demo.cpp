#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, edge;
int g_nTrackbarNumber = 0;//0��ʾ��ʴerode,1��ʾ����dilate
int g_nStructElementSize = 3;//�ṹԪ��(�ں˾���)�ĳߴ�


void Process();//���ͺ͸�ʴ�Ĵ�����
void on_TrackNumChange(int ,void*);//�ص�����
void on_ElementSizeChange(int ,void*);//�ص�����

int main()
{

	system("color5E");
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img");
	imshow("src_img",src_img);
	namedWindow("dst_img");
	Mat element = getStructuringElement(MORPH_RECT,Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1));
	erode(src_img,dst_img,element);
	imshow("dst_img",dst_img);

	//�����켣��
	createTrackbar("��ʴ/����","dst_img",&g_nTrackbarNumber,1, on_TrackNumChange);
	createTrackbar("�ں˳ߴ�","dst_img",&g_nStructElementSize,21, on_ElementSizeChange);


	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}

void Process()
{
	//��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1));
	//���и�ʴ�����Ͳ���
	if (g_nTrackbarNumber==0)
	{
		erode(src_img,dst_img,element);
	}
	else
	{
		dilate(src_img,dst_img,element);
	}
	imshow("dst_img",dst_img);
}

//��ʴ������֮���л����صĻص�����
void on_TrackNumChange(int, void*)
{
	//��ʴ������֮��Ч���Ѿ��л����ص�����������Ҫ����һ��Process����,
	//ʹ�ı���Ч��������Ч����ʾ����
	Process();
}
//��ʴ�����Ͳ����ں˸ı�ʱ�Ļص�����
void on_ElementSizeChange(int, void*)
{
	//�ں˳ߴ��Ѹı�,�ص�����������Ҫ����һ��Process����,
	//ʹ�ı���Ч��������Ч����ʾ����
	Process();
}
