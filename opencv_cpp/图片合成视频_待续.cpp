#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
//������ϳɵ���Ƶû������
void main()
{
	VideoWriter writer("E:\\out.avi", CV_FOURCC('X', 'V', 'I', 'D'), 20, Size(320, 240), true);//SizeҪ��ͼƬ�ߴ籣��һ��
	char filename[50];
	Mat frame;
	for (int i = 1; i < 1118; i++)
	{
		sprintf(filename, "E:\\pic\\%d.bmp", i);
		frame = imread(filename);
		if (frame.empty())   break;
		writer << frame;
		cout << i << endl;
	}
	cout << "write end!" << endl;
	system("pause");
	destroyAllWindows();
}