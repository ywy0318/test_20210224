/*
8.2Ѱ�������͹��
͹��(Convex Hull)��һ�����㼸��(ͼ��ѧ)����,������άƽ��
�ϵĵ㼯,͹�����ǽ������ĵ������������ɵ�͹�����,����
�ܰ����㼯�����е��;���������״��������һ�ֱȽ����õķ���
�Ǽ���һ�������͹��,Ȼ�������͹ȱ��(convexity defeects);
�ܶิ������������ܹ��ܺõı�����ȱ�ݱ��ֳ���;

Ѱ��͹��:convexHull()��������Ѱ��ͼ�����е�͹��,
C++:void convexHull(InputArray points,OutputArray hull,
bool clockwise=false,bool returnPoints=true)
��һ������:InputArray���͵�points,����Ķ�ά�㼯,
������Mat���ͻ���std:vector
�ڶ�������:OutputArray���͵�hull,�������,�������ú�
�ҵ���͹��;
����������:bool���͵�clockwise,���������ʶ��,���˱�ʶ��
Ϊ��ʱ,�����͹��Ϊ˳ʱ�뷽��,�����Ϊ��ʱ�뷽��,����
�ٶ�����ϵ��x��ָ����,y��ָ���Ϸ�;
���ĸ�����:bool���͵�returnPoints,������ʶ��,Ĭ��Ϊtrue;
����ʶ��Ϊ��ʱ,�������ظ�͹���ĸ�����;����,������͹��
�����ָ��,�����������std::vectorʱ,�˱�־������;
*/

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;

int main()
{
	//��ʼ�����������ֵ
	Mat image(1000,1000, CV_8UC3);
	RNG& rng = theRNG();

	while (true)
	{
		//
		char key;
		//int count = (unsigned)rng % 100 + 3;//������ɵ������
		int count = 500;
		vector<Point> points;
		for (size_t i = 0; i < count; i++)
		{
			Point point_1;
			point_1.x = rng.uniform(image.cols/4,image.cols*3/4);
			point_1.y = rng.uniform(image.rows/4,image.rows*3/4);
			points.push_back(point_1);
		}
		//���͹��
		vector<int> hull;
		convexHull(Mat(points), hull, true);
		//���Ƴ������ɫ�ĵ�
		image = Scalar::all(0);
		for (size_t i = 0; i < count; i++)
		{
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);

		}
		//׼������
		int hullcount = (int)hull.size();//͹���ı���
		Point point_0 = points[hull[hullcount - 1]];//����͹���ߵ������

		//����͹���ı�
		for (size_t i = 0; i < hullcount; i++)
		{
			Point point_2 = points[hull[i]];
			line(image,point_0, point_2,Scalar(255,255,255),2,LINE_AA);
			point_0 = point_2;

		}
		imshow("͹�����ʾ��",image);
		key = (char)waitKey();
		if ((key == 27) || (key == 'q') || (key == 'Q'))
		{
			break;
		}
		return 0;
	}

}