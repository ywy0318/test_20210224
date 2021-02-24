#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, edge;
int g_nTrackbarNumber = 0;//0表示腐蚀erode,1表示膨胀dilate
int g_nStructElementSize = 3;//结构元素(内核矩阵)的尺寸


void Process();//膨胀和腐蚀的处理函数
void on_TrackNumChange(int ,void*);//回调函数
void on_ElementSizeChange(int ,void*);//回调函数

int main()
{

	system("color5E");
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img");
	imshow("src_img",src_img);
	namedWindow("dst_img");
	Mat element = getStructuringElement(MORPH_RECT,Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1));
	erode(src_img,dst_img,element);
	imshow("dst_img",dst_img);

	//创建轨迹条
	createTrackbar("腐蚀/膨胀","dst_img",&g_nTrackbarNumber,1, on_TrackNumChange);
	createTrackbar("内核尺寸","dst_img",&g_nStructElementSize,21, on_ElementSizeChange);


	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}

void Process()
{
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1));
	//进行腐蚀与膨胀操作
	if (g_nTrackbarNumber==0)
	{
		erode(src_img,dst_img,element);
	}
	else
	{
		dilate(src_img,dst_img,element);
	}
	imshow("dst_img",dst_img);
}

//腐蚀和膨胀之间切换开关的回调函数
void on_TrackNumChange(int, void*)
{
	//腐蚀和膨胀之间效果已经切换，回调函数体内需要调用一次Process函数,
	//使改变后的效果立即生效并显示出来
	Process();
}
//腐蚀和膨胀操作内核改变时的回调函数
void on_ElementSizeChange(int, void*)
{
	//内核尺寸已改变,回调函数体内需要调用一次Process函数,
	//使改变后的效果立即生效并显示出来
	Process();
}
