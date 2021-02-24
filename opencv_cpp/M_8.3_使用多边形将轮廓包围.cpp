/*
8.3ʹ�ö���ν�������Χ

�����ⲿ���б߽�:boundingRect()���� 
�˺������㲢����ָ���㼯������(up-right)�ľ��α߽�
C++:Rect boundingRect(InputArray points);
��Ψһ��һ������Ϊ����Ķ�ά�㼯,������std:vector��Mat����

Ѱ����С��Χ����:minAreaRect()����
�˺������ڶԸ�����2D�㼯,Ѱ�ҿ���ת����С����İ�Χ����
C++:RotatedRect minAreaRect(Inputarray points)
��Ψһ��һ������Ϊ����Ķ�ά�㼯,������std::vector<>��Mat����

Ѱ����С��ΧԲ��:minEnclosingCircle()����
minEnclosingCircle�����Ĺ���������һ�ֵ����㷨,�������2D�㼯,
ȥѰ�������С�Ŀɰ�Χ���ǵ�Բ��;
C++:void minEnclosingCircle(InputArray points,Point2f& center,float& redius)
�ڶ�������:Point2f&���͵�center,Բ�����Բ��
����������:float&���͵�radius,Բ������뾶;

����Բ��϶�ά�㼯:fitEllipse()����
����Բ��϶�ά�㼯
C++:RotatedRect fitEllipse(InputArray points)


�ƽ����������:approxPolyDP()����
approxPolyDP()��������������ָ�����ȱƽ����������;
C++:void approxPolyDp(InputArray curve,OutputArray approxCurve,double epsilon,
bool closed)

��һ������:�����ά�㼯
�ڶ�������:����αƽ��Ľ��
����������:double���͵�epsilon,�ƽ��ľ���,Ϊԭʼ���ߺͼ���������
������ֵ;
���ĸ�����:bool���͵�closed,���Ϊ��,����Ƶ�����Ϊ�������,
(��һ����������һ����������),����,���Ƶ��������߲����;

*/


#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int g_nThresh = 50;
int g_nThresh_max = 255;
RNG g_rng(12345);//�����������

void on_minAreaRect()
{
	Mat image(1000, 1000, CV_8UC3);
	RNG &rng = theRNG();
	while (true)
	{
		int count = rng.uniform(3,106);
		//int count = 3;
		vector<Point> points;
		for (size_t i = 0; i < count; i++)
		{
			Point point_1;
			point_1.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point_1.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
			points.push_back(point_1);
		}
		//������2D�㼯,Ѱ����С����İ�Χ����
		RotatedRect box = minAreaRect(Mat(points));
		Point2f vertex[4];
		box.points(vertex);
		//���Ƴ������ɫ�ĵ�
		image = Scalar::all(0);
		for (size_t i = 0; i < count; i++)
		{
			circle(image,points[i],3,Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)),FILLED,LINE_AA);
		}
		//���Ƴ���С����İ�Χ����
		for (size_t i = 0; i < count; i++)
		{
			line(image,vertex[i],vertex[(i+1)%4],Scalar(100,200,211),2,LINE_AA);
		}
		imshow("minAreaRect",image);
		char key = (char)waitKey();
		if ((key == 27) || (key == 'q') || (key == 'Q'))
		{
			break;
		}
	}
	//return 0;
}

void on_minEnclosingCircle()
{
	Mat image(1000, 1000, CV_8UC3);
	RNG &rng = theRNG();
	while (true)
	{
		//int count = rng.uniform(3, 1036);
		int count = 5;
		vector<Point> points;
		for (size_t i = 0; i < count; i++)
		{
			Point point_1;
			point_1.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point_1.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
			points.push_back(point_1);
		}
		////������2D�㼯,Ѱ����С����İ�Χ����
		//RotatedRect box = minAreaRect(Mat(points));
		//Point2f vertex[4];
		//box.points(vertex);
		//���ڸ�����2D�㼯,Ѱ����С����İ�Χͼ
		Point2f center;
		float radius = 0;
		minEnclosingCircle(Mat(points),center,radius);
		//���Ƴ������ɫ�ĵ�
		image = Scalar::all(0);
		for (size_t i = 0; i < count; i++)
		{
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);
		}
		//���Ƴ���С����İ�Χ����
	/*	for (size_t i = 0; i < count; i++)
		{
			line(image, vertex[i], vertex[(i + 1) % 4], Scalar(100, 200, 211), 2, LINE_AA);
		}*/

		circle(image,center,cvRound(radius),Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)), 2, LINE_AA);

		imshow("minAreaRect", image);
		char key = (char)waitKey();
		if ((key == 27) || (key == 'q') || (key == 'Q'))
		{
			break;
		}
	}
}

void on_ContoursChange(int, void*)
{
	Mat threshold_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//ʹ��Threshold����Ե
	threshold(gray_img, threshold_output, g_nThresh, 255, THRESH_BINARY);
	findContours(threshold_output,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

	//����αƽ�����,��ȡ���κ�Բ�α߽��
	vector<vector<Point>> contourse_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());


	//һ��ѭ�����������в���,
	for (size_t i = 0; i < contours.size(); i++)
	{
		//��ָ�����ȱƽ����������
		approxPolyDP(Mat(contours[i]), contourse_poly[i],3,true);
		//����㼯��������(up-right)���α߽�
		boundRect[i] = boundingRect(Mat(contourse_poly[i]));
		//�Ը�����2D�㼯,Ѱ����С����İ�ΧԲ��
		minEnclosingCircle(contourse_poly[i],center[i],radius[i]);
	}
	//���ƶ��������+��Χ�ľ��ο�+Բ�ο�
	Mat draw_img = Mat::zeros(threshold_output.size(),CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		//���������ɫ
		Scalar color = Scalar(g_rng.uniform(0,255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		//��������
		drawContours(draw_img,contourse_poly,i,color,1,8,vector<Vec4i>(),0,Point());
		//���ƾ���
		rectangle(draw_img,boundRect[i].tl(), boundRect[i].br(),color,2,8,0);
		//����Բ��
		circle(draw_img,center[i],(int)radius[i],color,2,8,0);
	}
	namedWindow("draw_img",CV_WINDOW_AUTOSIZE);
	imshow("draw_img", draw_img);
}
int on_contoursChange_test()
{
	system("color 1A");
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
	blur(gray_img,gray_img,Size(3,3));
	namedWindow("src_img",CV_WINDOW_AUTOSIZE);
	imshow("src_img", src_img);

	createTrackbar("��ֵ:","src_img",&g_nThresh,g_nThresh_max,on_ContoursChange);
	on_ContoursChange(0,0);
	waitKey(0);
	return 0;
}

int main()
{
	int flag = 0;
	if (flag)
	{
		//on_minAreaRect();
		//on_minEnclosingCircle();
	}
	else
	{
		on_contoursChange_test();
	}
	
	system("pause");
	return 0;
}
