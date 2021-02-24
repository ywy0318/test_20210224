#include<opencv2/opencv.hpp>
using namespace cv;

//���ı�ͼ���С
Mat imgTranslate(Mat &src, int x_off, int y_off) {//x����ƫ��,y����ƫ��
	int rows = src.rows;//��
	int cols = src.cols;//��
	Mat dst = Mat::zeros(src.size(), src.type());//����һ��ȫ��ͼ��
	for (int i = 0; i < rows; i++)//������
	{
		for (int j = 0; j < cols; j++)//������
		{

			int x = j + x_off;//������+x����ƫ��=��ǰx����
			int y = i + y_off;
			if (x >= 0 && y >= 0 && x<cols&&y<rows) {
				dst.at<Vec3b>(y, x) = src.at<Vec3b>(i, j);//��ֵ����y,x����Ӧ(i,j)�����������ͼʾ
			}
		}
	}
	return dst;
}
//�ı�ͼ���С
Mat imgTranslate2(Mat &src, int x_off, int y_off) {
	int rows = src.rows + y_off;
	int cols = src.cols + x_off;
	Mat dst = Mat::zeros(rows, cols, src.type());//ע��������Ĳ����������ѡֵ
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{

			int x = j + x_off;
			int y = i + y_off;
			if (x >= 0 && y >= 0 && x<cols&&y<rows) {
				dst.at<Vec3b>(y, x) = src.at<Vec3b>(i, j);
			}
		}
	}
	return dst;
}

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dst=imgTranslate(src,20,30);
	//Mat dst = imgTranslate2(src, -20, -30);
	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
}