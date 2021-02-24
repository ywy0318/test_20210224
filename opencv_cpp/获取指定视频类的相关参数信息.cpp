#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void main() {
	VideoCapture cap;
	//cap.open("E:\\2.avi"); //����Ƶ,�ȼ���   VideoCapture cap("E://2.avi");
	cap.open("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.mp4");//�ɹ���
	if (!cap.isOpened())
		return;

	int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);  //֡���
	int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //֡�߶�
	int frameRate = cap.get(CV_CAP_PROP_FPS);  //֡�� x frames/s
	int totalFrames = cap.get(CV_CAP_PROP_FRAME_COUNT); //��֡��

	cout << "��Ƶ���=" << width << endl;
	cout << "��Ƶ�߶�=" << height << endl;
	cout << "��Ƶ��֡��=" << totalFrames << endl;
	cout << "֡��=" << frameRate << endl;//һ��59 һ��29

	Mat frame;
	while (1)
	{
		cap >> frame;//�ȼ���cap.read(frame);
		if (frame.empty())
			break;
		imshow("video", frame);
		if (waitKey(20)>0)
			break;
	}
	cap.release();
}


//�塢��ȡ����ͷ
//��ȡ����ͷ�Ͷ�ȡ��Ƶ��ͬС�죬��Ҫ����������Щ��ͬ��
//VideoCapture cap;
//cap.open(0);
//��ȡ��Ƶʱ���Դ�����Ƶ·��������ȡ����ͷ�������index�����š�
//
//ע :
//1)���Ĭ�ϱʼǱ� / ̨ʽ��ֻ��һ��USB����ͷ, Index = 0; �����2����һ��IndexΪ0��1�����ݾ���������֣�����ͷ����ͶϿ���ı�Indexֵ
//2)�������2�����ϣ���ֻ����ָ����һ�����������豸�������н���������ͬʱIndex����Ϊ0
//
//3)��Ϊ��������ͷ��һֱ�ڽ��ж�ȡ��������Ҫ��waitKey()����ֵ�ж��˳�Ԥ��
//imshow(��video��, frame);
//if (waitKey(30)>0)//�ް������·���-1����������ʱ�˳� 
//break;
//Ҳ����ָ�������˳���
//if (waitKey(30) == 27) //Esc���˳���ESC��ASCLL��Ϊ27 
//break;