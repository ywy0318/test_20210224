/*
5.3.1ͨ������:split()����
split�������ڽ�һ����ͨ���������ɼ�����ͨ������,
C++�汾�ĺ���ԭ��
void split(const Mat&src,Mat*mvbegin);
void split(InputArray m,OutputArrayOfArray  mv);
��һ������:InputArray���͵�m����const Mat&���͵�src,
��������Ҫ���з���Ķ�ͨ������
�ڶ�������:OutputArrayOfArrays���͵�mv,������������
���������vector����;
split�����ָ��ͨ������ת���ɶ����ĵ�ͨ������
mv[c](I)=src(I)c;
5.3.2ͨ���ϲ�:merge()����
merge()������split()�������������---���������ϲ���һ����ͨ��������;
��ͨ�����һЩ�����ĵ�ͨ������,����Щ�����ĵ�ͨ������ϲ���һ����ͨ����
����,�Ӷ�������һ���ɶ�ͨ��������ɵĶ�ͨ������;

void merge(const Mat*mv,size_t count,OutputArray dst)
void merge(InputArrayOfArrays mv,OutputArray dst)
��һ������:mv;����Ҫ���ϲ�����������vector����������;
���mv���������е����б�������һ���ĳߴ�����;
�ڶ�������,count;��mvΪһ���հ�C����ʱ,�����������ĸ���,���������Ȼ����1;
����������,dst;���������;��mv[0]ӵ��һ���ĳߴ�����,����ͨ��������
�Ǿ���������ͨ��������;
merge�����Ĺ����ǽ�һЩ����ϲ���һ����ͨ��������;
��������е�ÿһ��Ԫ�ض����������Ĵ���;
��i�����������Ԫ��mv[i],
Cһ�������е�Mat::at()��������ĳ��ͨ�����д�ȡ;
channels.at(0);
Mat::at()��������һ�����õ�ָ��������Ԫ��;
�൱�����ߵȼ�;
�����Ҫ�Ӷ�ͨ����������ȡ�ض��ĵ�ͨ������,����Ҫʵ��һЩ���ӵ�ͨ�����,
����ʹ��mixChannels()����

*/



#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
//opencv����canny��Ե���
//����ͼ��,ת��Ϊ�Ҷ�ͼ,blur����ͼ��ģ�����룬Ȼ����canny���б�Ե���

int main(int argc, char* argv[])
{

	//--1--˫��б�߷�
	string imgpath0 = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	//--2--˫��б�߷�
	string imgpath1 = "E://Visual Studio 2010//Projects//opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--3--����б�߷�
	string imgpath2 = "E:/Visual Studio 2010/Projects/opencv_2018_12_21/opencv_2018_12_21/1.jpg";
	//--4--�������ֻ��
	string imgpath3 = "E:/Visual Studio 2010//Projects\\opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--5--���·����
	string imgpath4 = "1.jpg";
	string imgpath5 = "lena.jpg";
	//--6--�����в�����
	//string imgpath5 = argv[1];
	//mat��opencv���������ݽṹ������һ��ͼ���������
	Mat src_img, des_img, gray_img, edge,src_img_1;
	vector<Mat> channels;
	vector<Mat> channels_1;
	vector<Mat> channels_2;
	Mat image_blue_channel;
	Mat image_green_channel;
	Mat image_red_channel;
	
	src_img = imread(imgpath5, 1);//����ͼƬ����
	des_img = imread(imgpath5, 1);//����ͼƬ����
	gray_img = imread(imgpath5, 1);//����ͼƬ����
	edge = imread(imgpath5, 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	src_img_1 = imread("2.jpg", 0);//����ͼƬ����,flag=0;��ʾ����Ҷ�ͼ��
	if (src_img_1.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}

	//��һ����ͨ��ͼ��ת����3����ͨ��ͼ��
	split(src_img, channels);//����ɫ��ͨ��
	split(src_img, channels_1);//����ɫ��ͨ��
	split(src_img, channels_2);//����ɫ��ͨ��
	 image_blue_channel= channels.at(0);
	 image_green_channel = channels_1.at(1);
	 image_red_channel = channels_2.at(2);

	 addWeighted(image_blue_channel(Rect(0,0, src_img.cols,src_img.rows)),1.0, src_img_1,0.5,0.0,
		 image_blue_channel(Rect(0, 0, src_img.cols, src_img.rows)));

	 merge(channels, src_img);

	 addWeighted(image_green_channel(Rect(0, 0, src_img.cols, src_img.rows)), 1.0, src_img_1, 0.5, 0.0,
		 image_green_channel(Rect(0, 0, src_img.cols, src_img.rows)));

	 merge(channels_1, des_img);

	 addWeighted(image_red_channel(Rect(0, 0, src_img.cols, src_img.rows)), 1.0, src_img_1, 0.5, 0.0,
		 image_red_channel(Rect(0, 0, src_img.cols, src_img.rows)));
	 merge(channels_2, gray_img);

	 imshow("src_img_blue", src_img);
	 imshow("src_img_green", des_img);
	 imshow("src_img_red", gray_img);
	 //imshow("image_blue_channel", image_blue_channel);

	 imshow("src", imread(imgpath5, 1));
	 
	 //gray_img(Rect(0,0,src_img.cols/2,src_img.rows/2)));
	//des_img = channels.at(2);
	//imshow("des_img before addWeighted", des_img);
	//addWeighted(des_img(Rect(0,0, src_img.cols,src_img.rows)),1.0, src_img,0.5,0.0,gray_img);
		//gray_img(Rect(0,0,src_img.cols/2,src_img.rows/2)));
	//merge(channels, edge);
	//namedWindow("sample");
	
	//imshow("des_img(Rect", des_img(Rect(0, 0, src_img.cols/2, src_img.rows/2 )));
	//imshow("des_img", edge);
	//imshow("srcimg", src_img);
	//imshow("srcimg", gray_img);
	//������src_imgͬ���ͺʹ�С�ľ���
	//des_img.create(src_img.size(), src_img.type());


	//��ԭʼͼ��ת��Ϊ�Ҷ�ͼ��
	//opencv2�汾
	//cvtColor(src_img, gray_img, CV_BGR2GRAY);


	//opencv3�汾
	//cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
	//ʹ��3x3�ں�������
	//blur(gray_img, edge, Size(3, 3));

	//getStructuringElement�ķ���ֵ��ָ����״��ָ���ߴ���ں;���
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//erode(src_img, des_img, element);

	//Canny����
	//Canny(edge, edge, 3, 9, 3);

	//imshow("after erode", edge);

	waitKey(0);
	system("pause");
	return 0;
}