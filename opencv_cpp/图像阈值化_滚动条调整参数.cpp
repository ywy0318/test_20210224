#include<opencv2/opencv.hpp>
using namespace cv;

Mat src, dst, dst2;
int thres_value = 21, block_size = 5, c = 5;

void onThreshold(int, void*) {
	threshold(src, dst, thres_value, 255, CV_THRESH_BINARY);
	imshow("�̶���ֵ", dst);
}
void onAdaptiveThreshold(int, void *) {
	if (block_size % 2 == 0)    block_size++;//���block_size��ż��
	adaptiveThreshold(src, dst2, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, block_size, c);
	imshow("����Ӧ��ֵ", dst2);
}

void main() {
	src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg", 0);//�ԻҶ�ģʽ����    
	namedWindow("�̶���ֵ", CV_WINDOW_AUTOSIZE);
	namedWindow("����Ӧ��ֵ", CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "�̶���ֵ", &thres_value, 255, onThreshold, 0);
	createTrackbar("Block_size", "����Ӧ��ֵ", &block_size, 255, onAdaptiveThreshold, 0);
	createTrackbar("C", "����Ӧ��ֵ", &c, 255, onAdaptiveThreshold, 0);

	onThreshold(thres_value, 0); //�ص�������ʼ��
	onAdaptiveThreshold(block_size, 0);
	onAdaptiveThreshold(c, 0);

	imshow("src", src);
	waitKey(0);
}