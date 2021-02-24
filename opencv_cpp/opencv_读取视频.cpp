#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	VideoCapture cap; //warning: Error opening file(.. / .. / modules / highgui / src / cap_ffmpeg_impl.hpp:545)这个问题就是视频文件的路径错了！！！
	//应该这样 E:\\Codes\\student5.mp4	\\ 这样分隔
	//cap.open("E://2.avi"); //打开视频,以上两句等价于VideoCapture cap("E://2.avi");
	//cap.open("E://1.avi");
	cap.open("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.mp4");//成功了
	//E:\Visual Studio 2010\Projects\opencv\opencv
						   //cap.open("http://www.laganiere.name/bike.avi");//也可以直接从网页中获取图片，前提是网页有视频，以及网速够快
	if (!cap.isOpened())//如果视频不能正常打开则返回
	{
		printf("error\n");
		system("pause");
		return;
	}
	Mat frame;
	while (1)
	{
		cap >> frame;//等价于cap.read(frame);
		if (frame.empty())//如果某帧为空则退出循环
			break;
		imshow("video", frame);
		waitKey(20);//每帧延时20毫秒
	}
	cap.release();//释放资源
}
//
//视频读取本质上就是读取图像，因为视频是由一帧一帧图像组成的。1秒24帧基本就能流畅的读取视频了。
//①读取视频有两种方法：
//A.VideoCapture cap;
//cap.open(“1.avi”);
//B.VideoCapture cap(“1.avi”);
//
//②循环显示每一帧：
//while (1)
//{
//	Mat frame; //定义Mat变量，用来存储每一帧 
//	cap >> frame; //读取当前帧方法一 
//				  //cap.read(frame); //读取当前帧方法二 
//	imshow(“视频显示”, frame); //显示一帧画面 
//	waitKey(30); //延时30ms 
//}



//三、读取视频说明
//打开的视频可以是本地视频如 :
//VideoCapture cap(“1.avi”);
//也可以是网络视频如：
//VideoCapture cap(“http://www.laganiere.name/bike.avi“);
//读取视频一定要加异常判断
//A.打开视频失败(各种原因)
//B.取帧失败异常(程序结尾判断)
//ex1 :
//	if (!cap.isOpened()) //检查打开是否成功 
//		return;
//ex2:
//cap >> frame;
//if (!frame.empty()) //判断当前 帧是否为空 
//{
//	imshow(“video”, frame);
//	waitKey(30);
//}
//else break;

