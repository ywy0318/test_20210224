/*
�ۺ�ʵ��:��Ե���
�ֱ���ʾ��canny��Ե��⣬sobel��Ե��⣬scharr�˲���

*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;

Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
//Canny��Ե�����ر���
Mat g_cannyDetectededges;
int g_cannyLowThreshold = 1;//TrackBarλ�ò���

//Sobel��Ե�����ر���
Mat g_sobelGradient_x, g_sobelGradient_y;
Mat g_sobelAbsGradient_x, g_sobelAbsGradient_y;
int g_sobelKernelSize = 1;//TrackBarλ�ò���

//Scharr�˲�����ر���
Mat g_scharrGradient_x, g_scharrGradient_y;
Mat g_scharrAbsGradient_x, g_scharrAbsGradient_y;

static void on_Canny(int ,void*);//Canny��Ե��ⴰ�ڹ������Ļص�����
static void on_Sobel(int, void*);//Sobel��Ե��ⴰ�ڹ������Ļص�����
void on_Scharr();//��װ�˱�Ե�����ش���ĺ���


int main()
{
	//�ı�console������ɫ
	system("color 2F");
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img",WINDOW_AUTOSIZE);
	imshow("src_img", src_img);

	//������srcͬ���ͺʹ�С�ľ���(dst)
	dst_img.create(src_img.size(),src_img.type());
	//��Դͼ��ת��Ϊ�Ҷ�ͼ��
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);

	namedWindow("Canny",WINDOW_AUTOSIZE);
	namedWindow("Sobel", WINDOW_AUTOSIZE);
	namedWindow("Scharr", WINDOW_AUTOSIZE);

	createTrackbar("����ֵ:","Canny",&g_cannyLowThreshold,120,on_Canny);
	createTrackbar("����ֵ","Sobel",&g_sobelKernelSize,3,on_Sobel);

	//���ûص�����
	on_Canny(0,0);
	on_Sobel(0,0);
	//���÷�װ��Scharr��Ե������ĺ��� 
	on_Scharr();
	waitKey(0);
	while (true)
	{

	}

	
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
void on_Canny(int ,void*)
{
	//��ʹ��3*3�ں�������
	blur(gray_img,g_cannyDetectededges,Size(3,3));
	//�������ǵ�Canny����
	Canny(g_cannyDetectededges,g_cannyDetectededges,g_cannyLowThreshold,g_cannyLowThreshold*3,3);
	
	//�Ƚ�dst_img�ڵ�����Ԫ������Ϊ0
	dst_img = Scalar::all(0);
	//ʹ��Canny��������ı�Եͼg_cannyDetechedEgdes��Ϊ����,����ԭͼg_src_img,����
	//Ŀ��ͼg_dstimg��
	src_img.copyTo(dst_img,g_cannyDetectededges);
	imshow("Canny",dst_img);
	waitKey(0);
}
void on_Sobel(int, void*)
{
	//��x�����ݶ�
	Sobel(src_img, g_sobelGradient_x,CV_16S,1,0,(2*g_sobelKernelSize+1),1,1,BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_x,g_sobelAbsGradient_x);

	//��Y�����ݶ�
	Sobel(src_img, g_sobelGradient_y, CV_16S, 0, 1, (2 * g_sobelKernelSize + 1), 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_y,g_sobelAbsGradient_y);

	//�ϲ��ݶ�
	addWeighted(g_sobelAbsGradient_x,0.5, g_sobelAbsGradient_y,0.5,0,dst_img);
	imshow("Sobel",dst_img);
	waitKey(0);
}

void on_Scharr( )
{
	//��x�����ݶ�
	Sobel(src_img, g_scharrGradient_x, CV_16S, 1, 0, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_x, g_scharrAbsGradient_x);

	//��Y�����ݶ�
	Sobel(src_img, g_scharrGradient_y, CV_16S, 0, 1, (2 * g_sobelKernelSize + 1), 1, BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_y, g_scharrAbsGradient_y);

	//�ϲ��ݶ�
	addWeighted(g_scharrAbsGradient_x, 0.5, g_scharrAbsGradient_y, 0.5, 0, dst_img);
	imshow("Scharr", dst_img);
	waitKey(0);
}
