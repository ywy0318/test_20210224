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

#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	VideoCapture cap;
	cap.open(0); //打开摄像头

	if (!cap.isOpened())
		return;

	Mat frame;
	while (1)
	{
		cap >> frame;//等价于cap.read(frame);
		//Canny(frame, frame, 30, 100);//canny边缘检测，去掉这一行就是纯粹的读取摄像头了
		//cvtColor(frame, frame, CV_BGR2HSV)这句可以用，就是出来的效果，太难看
	    //cvtColor(frame, frame, CV_BGR2HSV);//BGR空间转为HSV颜色空间，注意，两者不能同时对同一张图片（在此为frame）进行处理，否则报错
		if (frame.empty())
			break;
		imshow("video", frame);
		if (waitKey(20)>0)//按下任意键退出摄像头　　因电脑环境而异，有的电脑可能会出现一闪而过的情况
			break;
	}
	cap.release();
	destroyAllWindows();//关闭所有窗口
}

//针对第20行代码：最开始电脑配置的opencv2.x版本，上述代码打开摄像头没有问题；后来使用opencv3.x版本，重新编译了contrib包，发现摄像头打开后一闪而过。
//
//原因是 waitkey() 如果不按键的时候是返回 oxff，oxff无符号时是255，有符号时是 - 1。windows vs 的环境默认了这个为非符号数 即255，而opencv的有些配置环境中是 - 1。
//
//解决方案：把原始代码中循环读取帧的
//
//if (waitKey(20) >= 0)　　break;
//
//改为
//
//if (waitKey(20) != 255)　　break;
//
//或者把waitkey的返回值用有符号数去读取。
//
//uchar c = waitkey(20);　　if (c != 255)  break;