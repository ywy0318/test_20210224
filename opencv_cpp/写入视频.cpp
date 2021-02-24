#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void main() {
	VideoCapture cap;
	cap.open("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.mp4");//成功了
	//cap.open("E://2.avi");
	Size size0 = Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	VideoWriter writer("E://out.avi", -1, cap.get(CV_CAP_PROP_FPS), size0, false);

	if (!cap.isOpened())
		return;

	Mat frame;
	while (1)
	{
		cap >> frame;
		Canny(frame, frame, 30, 100);
		if (frame.empty())
			break;
		writer << frame;//等同于writer.write(frame);
		imshow("video", frame);
		if (waitKey(10)>0)
			break;
	}
	cout << "write end!";
	cap.release();
	destroyAllWindows();
}

//①VideoWriter： OpenCV提供VideoWriter类写视频文件，类的构造函数可以指定文件名、播放帧率、帧尺寸、是否创建彩色视频。
//
//②两种写入帧方法：
//1 ) writer.write(frame);
//2）writer >> frame(这里的箭头方向应该相反，不知道为什么箭头不能向←);
//③注意事项：
//1)写入视频前需安装对应的编解码器
//2)生成视频是否支持彩色应与构造函数设置一致
//3)生成视频尺寸需与读取视频尺寸一致