/*
OpenCV����vector vector
������Χ���ƾ��ο�
vector<vector<Point>>,vector<Vec4i>,vector<Rect>,
vector<RotatedRect>


vector<vector<Point>>;vector�����������һ��vector����,����������ŵ�;
vector<Vec4i>:����4άint����
vector<Rect>:����width*height fromλ��(x,y)
vector<RotatedRect>:��ͼ������Ա
angle:0 center:[0,0] size:[0*0]
angle:-88.4926 center:[119.147,237.399] size:[115.697*43.9322]

*/
/*
opencv��Mat ����������data,size,depth,channels,elesize,rows,
cols�������ں�

data:uchar���͵�ָ��,ָ��Mat���ݾ�����׵�ַ
dims:Mat�����ά��,��Mat��һ����ά����,��dims=2
��ά��dims=3,���������´���Ķ��Ƕ�ά����,��һ��ƽ����
�ľ���
rows:Mat���������
cols:Mat���������
size():����size��һ���ṹ��,������Mat���;��������ݵķֲ���ʽ,
��ֵ���й�ϵʽ:
image.size().width=image.cols;image.size().height=image.rows;
channels():
Mat����Ԫ��ӵ�е�ͨ����;����:������RGB��ɫͼ��,channels==3,��
�Ҷ�ͼ��ֻ��һ���Ҷȷ�����Ϣ,channels=1;
��ʾ����һ�������е�ÿ��Ԫ�طֱ��м���ֵ,����һ��4*3�ľ���,��12��
Ԫ��,ÿ��Ԫ�����������ֵ,��˾���������ͨ��,ÿ��Ԫ�����ĸ�ֵ,��
�˾������ĸ�ͨ��;
depth:
��������ÿһ��������ÿһ��ͨ���ľ���,����������ͼ���ͨ�����޹�;depth
��ֵԽ��,����Խ��,��Opencv��Mat.depth()�õ�����һ��0-6������,
�ֱ����ͬ��λ��;
enum{CV_8U=0,CV_8S=1,CV_16U=2,CV_16S=3,CV_32S=4,CV_32F=5,CV_64F=6}
����U��unsigned����˼,S��ʾ signed,Ҳ�����з��ź��޷�����;

eleSize:
��ʾ������ÿһ��Ԫ�ص����ݴ�С,
���Mat�е�����������CV_8UC1,��ôelemSize=1;
�����CV_8UC3����CV_8SC3,��ôelemSize=3;
���CV_16UC3����CV_16SC3,��ôelemSize==6;
��elemSize����8λ(һ���ֽ�)Ϊһ����λ,����ͨ����
��8λ��������;
elemSize1:
1������Ϊ��Ԫ����һ��ͨ������˼,�����������ϲ�ֺ�ͺ����׽���
���������;��ʾMat������ÿһ��Ԫ�ص���ͨ�������ݴ�С,���ֽ�Ϊ
һ����λ,����eleSize1=elemSize/channels;
step:
Mat������ÿһ�е�"����",���ֽ�Ϊ������λ,ÿһ��������Ԫ�ص��ֽ�����,
�ۼ���һ��������Ԫ��,����ͨ��,����ͨ����elemSize1֮���ֵ;
step1():
���ֽ�Ϊ������λ,Mat������ÿһ�����صĴ�С,�ۼ�������ͨ��,
����ͨ����elemSize1֮���ֵ,������
step1=step/elemSize1;

type:
Mat���������,�����о�����Ԫ�ص������Լ�ͨ������Ϣ,type������
��ʽΪCV_(λ��)+(��������)+(ͨ����),����ȡֵ����:
CV_8UC1,   
CV_8SC1,
CV_16UC1,
CV_16SC1,
CV_32SC1,
CV_32FC1,
CV_64FC1,

CV_8UC2,
CV_8SC2,
CV_16UC2,
CV_16SC2,
CV_32SC2,
CV_32FC2,
CV_64FC2,

CV_8UC3,
CV_8SC3,
CV_16UC3,
CV_16SC3,
CV_32SC3,
CV_32FC3,
CV_64FC3,

CV_8UC4,
CV_8SC4,
CV_16UC4,
CV_16SC4,
CV_32SC4,
CV_32FC4,
CV_64FC4,

���ֻ�ͼƬ�ĺ���,�޸ĺ���ֵ�ĳ���
*/


#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img,bin_out_img;

int test_vector()
{
	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img",CV_WINDOW_AUTOSIZE);
	namedWindow("dst_img", CV_WINDOW_AUTOSIZE);
	imshow("src_img", src_img);

	cvtColor(src_img,gray_img,CV_BGR2GRAY);
	blur(gray_img,gray_img,Size(10,10),Point(-1,-1),BORDER_DEFAULT);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	threshold(gray_img,bin_out_img,144,255,0);
	findContours(bin_out_img,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

	vector<vector<Point>> contour_poly(contours.size());
	vector<Rect> poly_rects(contours.size());
	vector<RotatedRect> minRect(contours.size());
	//ȡ��
	for (size_t i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]),contour_poly[i],3,true);//������������
		poly_rects[i] = boundingRect(contour_poly[i]);//��ȡ���ƾ�������
		if (contour_poly[i].size()>5)
		{
			minRect[i] = minAreaRect(contour_poly[i]);//��ȡ��֮��ת��������
		}
	}
	//��ʼ����
	src_img.copyTo(dst_img);
	Point2f pst[4];//�洢������ת���ε��ĸ���
	cout << "-----Point2f pst[4]" << endl;

	for (size_t i = 0; i < contours.size(); i++)
	{
		rectangle(dst_img,poly_rects[i],Scalar(255,0,0),2,8);//���ƾ��ο�
		minRect[i].points(pst);//���߶λ�����,��RotatedRect����ת��Ϊ4���� 
		for (size_t u = 0; u < 4; u++)
		{
			line(dst_img, pst[u], pst[(u + 1) % 4], Scalar(0, 255, 0), 2, 8);
			cout << pst[u];//��ʾpst������
		}
		cout << endl;
		Rect brect = minRect[i].boundingRect();//���ذ�����ת���ε���С����
		rectangle(dst_img,brect,Scalar(0,0,255));
	}
	cout << endl;
	
	cout << "-----vector<vector<Point>>cotours_poly----" << endl;
	for (size_t i = 0; i < contour_poly.size(); i++)
	{
		cout << "��" << i << "��:";
		for (size_t j = 0; j < contour_poly[i].size(); j++)
		{
			cout << contour_poly[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << "---vector<Vec4i>-hierarchy---" << endl;
	for (size_t i = 0; i < hierarchy.size(); i++)
	{
		cout << hierarchy[i] << endl;
	}
	cout << endl;

	cout << "---vector<Rect> poly_rects---" << endl;
	for (size_t i = 0; i < poly_rects.size(); i++)
	{
		cout << poly_rects[i] << endl;
	}
	cout << endl;
	cout << "---vector <rotatedRect>- minRect---" << endl;
	for (size_t i = 0; i < minRect.size(); i++)
	{
		cout << "angle:" << minRect[i].angle << "center:" << minRect[i].center
			<< "size:" << minRect[i].size << endl;
	}
	cout << endl;
	imshow("dst_img", dst_img);
	waitKey(0);
	return 0;
}
int main()
{
	test_vector();
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}