#include "opencv2/opencv.hpp"
using namespace cv;

Mat src, dst;
int min_thres = 30, max_thres = 100;//����ֱ������Ϊmin��max����׼��std����min��max����

void onCanny(int, void*) {
	Canny(src, dst, min_thres, max_thres);
	imshow("src", src);
	imshow("Canny", dst);
}
//ע�⣺canny��Ե����ͼ��Ϊ�Ҷ�ͼ��
//��⹤���Ƿ�ƽ������Ⲽ���Ƿ�ƽ��
void main()
{
	src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\7.jpg", 0);
	namedWindow("Canny", CV_WINDOW_AUTOSIZE);
	createTrackbar("min_thres", "Canny", &min_thres, 255, onCanny, 0);
	createTrackbar("max_thres", "Canny", &max_thres, 255, onCanny, 0);

	onCanny(min_thres, 0);//�ص�������ʼ��
	onCanny(max_thres, 0);

	waitKey(0);
	destroyAllWindows();
}