#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
Mat map_x, map_y; 
int update_map(int key);
int main()
{
	system("color 2F");
	printf("system()\n");
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img",CV_WINDOW_AUTOSIZE);
	imshow("src_img", src_img);

	//������ԭʼͼһ����Ч��ͼ,x��ӳ��ͼ,y��ӳ��ͼ
	dst_img.create(dst_img.size(),src_img.type());
	map_x.create(src_img.size(),CV_32FC1);
	map_y.create(src_img.size(),CV_32FC1);

	//��ѵ����,����map_x,map_y��ֵ,������ӳ���������ʾЧ��ͼ
	while (true)
	{
		//��ȡ���̰���
		int key = waitKey(0);
		//�ж�esc�Ƿ���,�����±��˳�
		if ((key & 255) == 27)
		{
			cout << "�����˳�....\n";
			break;
		}
		//���ݰ��µļ��̰���������map_x&map_y��ֵ,Ȼ�����remap()������ӳ��
		update_map(key);
		remap(src_img, dst_img, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
		imshow("dst_img",dst_img);
	}

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
int update_map(int key)
{
	//˫��ѭ��,����ÿһ�����ص�
	for (size_t i = 0; i < src_img.rows; i++)
	{
		for (int j = 0; j < src_img.cols; j++)
		{
			switch (key)
			{
			case'1'://����1����,���е�һ����ӳ�����
				if ((i>src_img.cols*0.25)&&(i<src_img.cols*0.75)
					&&(j<src_img.rows*0.75)&&(j>src_img.rows*0.25))
				{
					map_x.at<float>(j, i) = static_cast<float>(2 * (i - src_img.cols*0.25) + 0.5);
					map_y.at<float>(j, i) = static_cast<float>(2 * (j - src_img.rows*0.25) + 0.5);
				}
				else
				{
					map_x.at<float>(j, i) = 0;
					map_y.at<float>(j, i) = 0;
				}
				break;
			case'2':
				map_x.at<float>(j, i) = static_cast<float>(i);
				map_y.at<float>(j, i) = static_cast<float>(src_img.rows - j);
				break;
			case'3':
				map_x.at<float>(j,i)=static_cast<float>(src_img.cols-i);
				map_y.at<float>(j, i) = static_cast<float>(j);
				break;
			case'4':
				map_x.at<float>(j, i) = static_cast<float>(src_img.cols - i);
				map_y.at<float>(j, i) = static_cast<float>(src_img.rows - j);
				break;
			default:
				break;
			}
		}
	}
	return 1;
}