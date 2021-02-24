#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void main() {
	VideoCapture cap;
	//cap.open("E:\\2.avi"); //打开视频,等价于   VideoCapture cap("E://2.avi");
	cap.open("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.mp4");//成功了
	if (!cap.isOpened())
		return;

	int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);  //帧宽度
	int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //帧高度
	int frameRate = cap.get(CV_CAP_PROP_FPS);  //帧率 x frames/s
	int totalFrames = cap.get(CV_CAP_PROP_FRAME_COUNT); //总帧数

	cout << "视频宽度=" << width << endl;
	cout << "视频高度=" << height << endl;
	cout << "视频总帧数=" << totalFrames << endl;
	cout << "帧率=" << frameRate << endl;//一个59 一个29

	Mat frame;
	while (1)
	{
		cap >> frame;//等价于cap.read(frame);
		if (frame.empty())
			break;
		imshow("video", frame);
		if (waitKey(20)>0)
			break;
	}
	cap.release();
}


//五、读取摄像头
//读取摄像头和读取视频大同小异，主要是这句代码有些许不同。
//VideoCapture cap;
//cap.open(0);
//读取视频时可以传入视频路径，而读取摄像头传入的是index索引号。
//
//注 :
//1)如果默认笔记本 / 台式机只有一个USB摄像头, Index = 0; 如果有2个，一般Index为0和1，根据具体情况区分，摄像头接入和断开会改变Index值
//2)如果接入2个以上，但只想用指定的一个，可以在设备管理器中禁用其他，同时Index设置为0
//
//3)因为开启摄像头后一直在进行读取，所以需要用waitKey()返回值判断退出预览
//imshow(“video”, frame);
//if (waitKey(30)>0)//无按键按下返回-1，按键按下时退出 
//break;
//也可以指定按键退出：
//if (waitKey(30) == 27) //Esc键退出，ESC的ASCLL码为27 
//break;