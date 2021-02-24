/*
!!!!!!!!!!!!!!!!!!!!!!!��������
8.5��ˮ���㷨
watershed algorithm
�ָ�ͼ��,�����޷��ӱ���ͼ���л��������Ϣ;
��ˮ���㷨(watershed algorithm)���ⷽ�������зǳ���Ч��;
���㷨���Խ�ͼ���еı�Եת����"ɽ��",����������ת����Ϊ"ɽ��";
�����ڷָ�Ŀ��;

watershed����ʵ�ֵķ�ˮ���㷨�ǻ��ڱ�ǵķָ��㷨�е�һ��;
�ڰ�ͼ�񴫸�����֮ǰ,��Ҫ���¹�����ǳ�ͼ���е��������зָ��
����,���Ǳ����Ϊ��ָ��;����ÿһ�����򶼻ᱻ���Ϊ����ֵ1,2,3;
��ʾ��Ϊһ�����߶���������;��Щ��ǵ�ֵ����ʹ��findcontours()����
��drawcontours()����,�ɶ����Ƶ������������;�������,��Щ���
���Ǽ������Ƴ����ķָ������"����",��û�б�����������,����Ϊ0;
�ں��������,ÿһ������е����ر�����Ϊ"����"��ֵ,��������ֵ��
����Ϊ-1;
C++:void watershed(In putArray image,InputArray markets);
��һ������:����ͼ��,8λ��ͨ���Ĳ�ɫͼ��;
�ڶ�������:InputArray���͵�markets,�������ú����������������,
����/���32Ϊ��ͨ��ͼ��ı�ǽ��;����������ڴ�ź������ú��
������,���ԴͼƬ��һ���ĳߴ������;
*/
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
Point prevPt(-1, -1);

static void on_Mouse(int event,int x,int y,int flag,void*);

int main()
{

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);
	src_img.copyTo(temp_img);

	cvtColor(src_img,mask_img,COLOR_BGR2GRAY);
	cvtColor(mask_img,gray_img,COLOR_GRAY2RGB);
	mask_img = Scalar::all(0);

	//�������ص�����
	setMouseCallback("src_img",on_Mouse,0);
	while (true)
	{
		int c = waitKey(0);
		if ((char)c==27)
		{
			break;
		}
		if ((char)c=='2')
		{
			mask_img = Scalar::all(0);
			temp_img.copyTo(src_img);
			imshow("src_img",src_img);
		}
		if (((char)c=='1')||((char)c==' '))
		{
			int i, j, compCount = 0;
			vector<vector<Point>> contours;
			vector<Vec4i> hierarchy;
			printf("1\n");
			//Ѱ������
			findContours(mask_img, contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_NONE);
			if (contours.empty())
			{
				continue;
			}
			//������ģ
			Mat maskImage(mask_img.size(),CV_32S);
			maskImage = Scalar::all(0);
			//ѭ�����Ƴ�����
			for (size_t i = 0; i >=0; i=hierarchy[i][0],compCount++)
			{
				drawContours(maskImage,contours,i,Scalar::all(compCount+1),-1,8,hierarchy,INT_MAX);				
			}
			//compCountΪ0ʱ�Ĵ���
			if (compCount==0)
			{
				continue;
			}
			//���������ɫ
			vector<Vec3b> colorTab;
			for (size_t i = 0; i < compCount; i++)
			{
				int b = theRNG().uniform(0,255);
				int g = theRNG().uniform(0, 255);
				int r = theRNG().uniform(0, 255);

				colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
			}
			printf("colorTab.push_back\n");

			//���㴦��ʱ�䲢�����������
			double dTime = (double)getTickCount();
			watershed(src_img,maskImage);
			dTime = (double)getTickCount() - dTime;
			printf("\t����ʱ��=%gms\n",dTime*1000/getTickFrequency());

			//˫��ѭ��,����ˮ��ͼ���������watershedImage��
			Mat watershedImage(maskImage.size(),CV_8UC3); 
			for (size_t i = 0; i < maskImage.rows ; i++)
			{
				for (int j = 0; j < maskImage.cols; j++)
				{
					int index = maskImage.at<int>(i,j);
					if (index == -1)
					{
						watershedImage.at<Vec3b>(i, j) = Vec3b(255,255,255);
					}
					else if (index <= 0 || index > compCount)
					{
						watershedImage.at<Vec3b>(i, j) = Vec3b(0,0,0);
					}
					else
					{
						watershedImage.at<Vec3b>(i, j) = colorTab[index-1];
					}
				}
				//��ϻҶ�ͼ�ͷ�ˮ��Ч��ͼ����ʾ���յĴ���
				watershedImage = watershedImage*0.5 + gray_img*0.5;
				imshow("watershed transform", watershedImage);
			}
		}
	}
	
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
static void on_Mouse(int event, int x, int y, int flag, void*)
{
	//������겻�ڴ����е����
	if (x < 0 || x >= src_img.cols || y < 0 || y >= src_img.rows)
	{
		return;
	}
	//���������������Ϣ
	if (event == EVENT_LBUTTONUP || !(flag&EVENT_FLAG_LBUTTON))
	{
		prevPt = Point(-1,-1);
	}
	else if(event==EVENT_LBUTTONDOWN)
	{
		prevPt = Point(x,y);
	}
	//���������²��ƶ�,���Ƴ���ɫ����
	else if(event==EVENT_MOUSEMOVE&&(flag&EVENT_FLAG_LBUTTON))
	{
		Point pt(x,y);
		if (prevPt.x<0)
		{
			prevPt = pt;
		}
		line(mask_img, prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(src_img, prevPt, pt, Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		imshow("src_img",src_img);
	}
}