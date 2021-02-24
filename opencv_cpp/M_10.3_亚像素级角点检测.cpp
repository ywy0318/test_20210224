/*
10.3�����ؼ��ǵ���
������ͼ�����Ŀ�Ĳ�����ȡ����ʶ�����������ǽ��м��β���,
ͨ����Ҫ���ߵľ���,������goodFeatureTotrack()ֻ���ṩ�򵥵����ص�
����ֵ,Ҳ����,��ʱ�����Ҫʵ������ֵ��������������ֵ;

�����ؽǵ����λ����������궨,���ٲ��ؽ�������켣,�����ؽ�
������Ŀ�����ά�ṹʱ,��һ�������Ĳ���ֵ;

Ѱ�������ؽǵ�:cornerSubPix()����

cornerSubPix��������Ѱ�������ص�λ��(�����������͵�λ��,���Ǹ���ȷ�ĸ�������λ��)
C++:void cornerSubPix(InputArray image,InputOutputArray corners,Size winSize,
size zeroZone,TermCriteria criteria)

��һ������:InputArray ���͵�image,����ͼ��,��Դͼ��
�ڶ�������:InputOutputArray���͵�corners,�ṩ����ǵ�ĳ�ʼ����;�ȷ���������;
����������:Size���͵�winSize,�������ڵ�һ��ߴ�;��winSize=Size(5,5),��ô�ͱ�ʾ
ʹ��(5*2+1)*(5*2+1)=11*11��С����������
���ĸ�����:Size���͵�zeroZone,��ʾ������һ��ߴ�;������Ϊ����������������λ����
������������,������������ؾ�����ֵ�ĳЩ���ܵ�������,ֵΪ(-1,-1)��ʾû������;
���������:TermCriteria���͵�Criteria,��ǵ�ĵ������̵���ֹ����;
���ǵ�λ�õ�ȷ��,Ҫô������Ŀ����ĳ���趨ֵ,�����Ǿ�ȷ�ȴﵽĳ���趨ֵ;
criteria��������������Ŀ,�������趨�ľ�ȷ��,Ҳ���������ǵ����;


10.3.3�ۺ�ʾ��:�����ؼ��ǵ���
*/

/*
�Լ������ǵ���ĺ���,��Ҫ�õ�cornerMinEigenVal������minMaxLoc����;
����������ѡȡ,�ж�����Ҫ�����Լ�������༭��
�����������,�ǵ�ľ���Ҫ�����,������cornerSubPix�������ǵ㶨λ��������;

*/

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int g_maxCornerNumber = 33;
int g_maxTrackBarNumber = 500;
RNG g_rng(12345);
void on_good_feature_to_track(int, void*);
int main()
{

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
	namedWindow("Shi_Tomasi", WINDOW_AUTOSIZE);
	createTrackbar("���ǵ���:", "Shi_Tomasi", &g_maxCornerNumber, g_maxTrackBarNumber, on_good_feature_to_track);
	on_good_feature_to_track(0, 0);
	imshow("Shi_Tomasi", src_img);
	waitKey(0);
	return 0;
}
void on_good_feature_to_track(int, void*)
{
	//�Ա���С�ڵ���1ʱ�Ĵ���
	if (g_maxCornerNumber <= 1)
	{
		g_maxCornerNumber = 1;
	}
	//Shi-Tomasi�㷨(goodFeatureTotrack����)�Ĳ���׼��
	vector<Point2f> corners;
	double qualityLevel = 0.01;//�ǵ���ɽ��ܵ���С����ֵ
	double minDistance = 10;//�ǵ�֮�����С����
	int blockSize = 3;//���㵼������ؾ���ʱָ��������Χ
	double k = 0.04;//Ȩ��ϵ��
	Mat copy = src_img.clone();//����Դͼ��һ����ʱ������,��Ϊ����Ȥ����
							   //Shi-Tomasi�ǵ���
							   //��⵽�Ľǵ���������
							   //�ǵ���������
							   //�ǵ���ɽ��ܵ���С����ֵ
							   //�ǵ�֮����С�ľ���
							   //����Ȥ����
							   //���㵼������ؾ���ʱ������Χ
							   //��ʹ��harrsi�ǵ���
	goodFeaturesToTrack(gray_img, corners, g_maxCornerNumber, qualityLevel, minDistance, Mat(), blockSize, false, k);

	//���������Ϣ
	cout << ">�˴μ�⵽�Ľǵ�����Ϊ:" << corners.size() << endl;
	//���Ƽ�⵽�Ľǵ�
	int r = 4;
	for (size_t i = 0; i < corners.size(); i++)
	{
		//���������ɫ���Ƴ��ǵ�
		circle(copy, corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)), -1, 8, 0);
	}
	//��ʾ����
	imshow("Shi_Tomasi", copy);

	//�����ؽǵ���Ĳ�������
	Size winSize = Size(5,5);
	Size zeroZone = Size(-1, -1);
	//opencv2
	//TermCriteria criteria=TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,40,0.001);

	//opencv3
	TermCriteria criteria=TermCriteria(TermCriteria::EPS+TermCriteria::MAX_ITER,40,0.001);
	//����������ؽǵ�λ��
	cornerSubPix(gray_img,corners,winSize,zeroZone,criteria);
	//����ǵ���Ϣ
	for (size_t i = 0; i < corners.size(); i++)
	{
		cout << "\t>>��ȷ�ǵ�����:[" << i << "](" << corners[i].x << "," << corners[i].y << ")" << endl;
	}
}