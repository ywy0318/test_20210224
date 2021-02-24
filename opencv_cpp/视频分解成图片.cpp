#include<opencv2/opencv.hpp>

using namespace cv;
//需要提前在E盘创建pic文件夹
void main()
{
	Mat frame;
	char outfile[50];
	//VideoCapture cap("E:\\2.avi");
	VideoCapture cap("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.mp4");
	//cap.open("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.mp4");//成功了
	if (!cap.isOpened())//打开失败
		return;
	int totalFrame = cap.get(CV_CAP_PROP_FRAME_COUNT);//获取视频总帧数
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