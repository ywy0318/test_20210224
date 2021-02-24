/*
9.3ֱ��ͼ�Ա�
ʹ��ĳЩ����ı�׼���Ƚ�����ֱ��ͼ�����ƶ�;
ѡ��һ������ֱ��ͼ���ƶȵĶԱȱ�׼;
compareHist()�������Ա�����ֱ��ͼ�����ƶ�,
�κ�������ֵ��d(H1,H2);
compareHist()�������ڶ�����ֱ��ͼ���бȽ�,
C++:double compareHist(InputArray H1,InputArray H2,int method)
C++:double compareHist(const SparseMat&H1,const SparseMat&H2,int method)
ǰ������������Ҫ�ȽϵĴ�С��ͬ��ֱ��ͼ,��������������ѡ��ı�׼����;

���ֱȽϷ���:
1,���,Correlation(method=CV_COMP_CORREL)
2,����,Chi-Square(method=CV_COMP_CHISQR)
3,ֱ��ͼ�ཻ,Intersection(method=CV_COMP_INTERSECT)
4,����,Bhattacharyya (method=CV_COMP_BHATTACHARYYA)
*/
//�����е�MatND�������ڴ洢ֱ��ͼ��һ�����ݽṹ;

/*
�����н���׼ͼ���������������ͼ����жԱ�;
����׼ͼ��ֱ��ͼ����������жԱ�ʱ,�����������ƥ��;
������Դ��ͬһ���ı��������İ�����ͼ�Ա�ʱ,Ӧ�û��бȽϸߵ����ƶ�;
�������Բ�ͬ���ȹ����������������Ų���ͼ��Ա�ʱ,ƥ���Ӧ�ò��Ǻܺ�;

Correlation��Intersection��׼,ֵԽ���ʾ���ƶ�Խ��;


*/


#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
//���������׼ͼ����������ŶԱ�ͼ��ľ���(RGB��HSV)
Mat src_img_base, HSV_img_base;
Mat src_img_test_1, HSV_img_test_1;
Mat src_img_test_2, HSV_img_test_2;
Mat HSV_img_halfDown;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int main()
{
	//�����׼ͼ��(src_img_base)�����Ų���ͼ��(src_img_test_1,src_img_test_2),������ʾ
	src_img_base = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img_base.empty())
	{
		cout << "can not open or find the src_img_base" << endl;
		system("pause");
		return -1;
	}
	src_img_test_1 = imread("lena_2.jpg", 1);//����ͼƬ����
	if (src_img_test_1.empty())
	{
		cout << "can not open or find the src_img_test_1" << endl;
		system("pause");
		return -1;
	}
	src_img_test_2 = imread("lena_3.jpg", 1);//����ͼƬ����
	if (src_img_test_2.empty())
	{
		cout << "can not open or find the src_img_test_2" << endl;
		system("pause");
		return -1;
	}
	imshow("src_img_base", src_img_base);
	imshow("src_img_test_1", src_img_test_1);
	imshow("src_img_test_2", src_img_test_2);

	//��ͼ����BGRɫ�ʿռ�ת����HSVɫ�ʿռ�
	cvtColor(src_img_base, HSV_img_base,COLOR_BGR2HSV);
	cvtColor(src_img_test_1, HSV_img_test_1, COLOR_BGR2HSV);
	cvtColor(src_img_test_2, HSV_img_test_2, COLOR_BGR2HSV);
	//����������׼ͼ���°벿�ֵİ���ͼ��(HSV��ʽ)
	HSV_img_halfDown = HSV_img_base(Range(HSV_img_base.rows/2,HSV_img_base.rows-1),Range(0,HSV_img_base.cols-1));
	//��ʼ������ֱ��ͼ��Ҫ��ʵ��
	//��hueͨ��ʹ��30��bin,��saturationͨ��ʹ��32��bin
	int h_bins = 50;
	int s_bins = 60;
	int histSize[] = { h_bins ,s_bins };
	//hue��ȡֵ��Χ��0-256,saturationȡֵ��Χ��0��180
	float h_ranges[] = { 0,256 };
	float s_ranges[] = { 0,180 };
	const float* ranges[] = { h_ranges,s_ranges };
	//ʹ�õ�0ͨ���͵�1ͨ��
	int channels[] = { 0,1 };

	//��������ֱ��ͼ��MatND���ʵ��
	MatND baseHist;
	MatND halfDownHist;
	MatND testHist1;
	MatND testHist2;

	//�����׼ͼ��,���Ų���ͼ��,�����׼ͼ���HSVֱ��ͼ
	calcHist(&HSV_img_base,1,channels,Mat(),baseHist,2, histSize,ranges,true,false);
	normalize(baseHist, baseHist, 0,1, NORM_MINMAX, -1, Mat());

	calcHist(&HSV_img_halfDown, 1, channels, Mat(), halfDownHist, 2, histSize, ranges, true, false);
	normalize(halfDownHist, halfDownHist, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&HSV_img_test_1, 1, channels, Mat(), testHist1, 2, histSize, ranges, true, false);
	normalize(testHist1, testHist1, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&HSV_img_test_2, 1, channels, Mat(), testHist2, 2, histSize, ranges, true, false);
	normalize(testHist2, testHist2, 0, 1, NORM_MINMAX, -1, Mat());
	
	//��˳��ʹ��4�жԱȱ�׼����׼ͼ���ֱ��ͼ�������ֱ��ͼ���жԱ�
	for (size_t i = 0; i < 4; i++)
	{
		int compare_method = i;
		double base_base = compareHist(baseHist,baseHist,compare_method);
		double base_half = compareHist(baseHist, halfDownHist, compare_method);
		double base_test1 = compareHist(baseHist, testHist1, compare_method);
		double base_test2 = compareHist(baseHist, testHist2, compare_method);
		//������
		//printf("����[%d]��ƥ��������:\n",i);
		//printf("[��׼ͼ - ��׼ͼ]:%f, [��׼ͼ - ����ͼ] : %f",base_base,base_half);
		//printf("[��׼ͼ - ����ͼ1]:%f, [��׼ͼ - ����ͼ2] : %f\n",base_test1,base_test2);
		cout << "����[" << i << "]��ƥ��������:" << endl;
		cout << "[��׼ͼ - ��׼ͼ0]:" << base_base << "[��׼ͼ - ����ͼ0] : " << base_half << endl;
		cout << "[��׼ͼ - ����ͼ1]:" << base_test1 << "[��׼ͼ - ����ͼ2] :" << base_test2 << endl;
		cout << endl;
	}
	cout << "���Խ���" << endl;
	//printf("���Խ���\n");
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}