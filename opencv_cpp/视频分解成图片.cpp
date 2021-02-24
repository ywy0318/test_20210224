#include<opencv2/opencv.hpp>

using namespace cv;
//��Ҫ��ǰ��E�̴���pic�ļ���
void main()
{
	Mat frame;
	char outfile[50];
	//VideoCapture cap("E:\\2.avi");
	VideoCapture cap("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.mp4");
	//cap.open("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.mp4");//�ɹ���
	if (!cap.isOpened())//��ʧ��
		return;
	int totalFrame = cap.get(CV_CAP_PROP_FRAME_COUNT);//��ȡ��Ƶ��֡��
	for (int i = 1; i <= totalFrame; i++)
	{
		cap >> frame;
		if (frame.empty())
			break;
		sprintf(outfile, "E:\\pic\\%d.bmp", i);
		imwrite(outfile, frame);
		imshow("video", frame);
		waitKey(15);
	}
	cap.release();
	destroyAllWindows();
}