#include<opencv2/opencv.hpp>

using namespace cv;

void main()
{
	//������ȡͼƬ������
	char filename[50];
	char winName[50];
	Mat srcImg;
	for (int i = 1; i < 100; i++)
	{
		sprintf(filename, "%d.bmp", i);
		sprintf(winName, "NO--%d", i);
		srcImg = imread(filename);
		if (srcImg.empty())
			break;
		imshow(winName, srcImg);
	}
	waitKey(0);
	destroyAllWindows();
}