#include<opencv2/opencv.hpp>
using namespace cv;

void main()
{
	//---���Ƶ㼯��͹��
	Mat img(400, 400, CV_8UC3, Scalar::all(0));  //�������ͼ��
	RNG rng;  //�������������
	while (1)
	{
		char key;
		int count = (unsigned int)rng % 100;  //�����ĸ���  
		vector<Point> points;  //����㼯
		for (int i = 0; i<count; i++)
		{
			Point pt;
			pt.x = rng.uniform(img.cols / 4, img.cols * 3 / 4);  //�趨���x��Χ
			pt.y = rng.uniform(img.rows / 4, img.rows * 3 / 4);  //�趨���y��Χ
			points.push_back(pt);
		}

		//���͹��
		vector<int> hull;
		convexHull(Mat(points), hull, true);

		img = Scalar::all(0);
		for (int i = 0; i < count; i++)
			circle(img, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), CV_FILLED, CV_AA);

		//׼������
		int hullcount = (int)hull.size(); //͹���ı���
		Point point0 = points[hull[hullcount - 1]]; //����͹���ߵ������

													//����͹���ı�
		for (int i = 0; i < hullcount; i++)
		{
			Point point = points[hull[i]];
			circle(img, point, 8, Scalar(0, 255, 0), 2, 8);
			line(img, point0, point, Scalar(255, 255, 255), 2, CV_AA);
			point0 = point;
		}

		//��ʾЧ��ͼ
		imshow("img", img);

		//����ESC,Q,����q�������˳�
		key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q')
			break;
	}
	
}