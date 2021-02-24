#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void main() {
	VideoCapture cap;
	cap.open("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.mp4");//�ɹ���
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
		writer << frame;//��ͬ��writer.write(frame);
		imshow("video", frame);
		if (waitKey(10)>0)
			break;
	}
	cout << "write end!";
	cap.release();
	destroyAllWindows();
}

//��VideoWriter�� OpenCV�ṩVideoWriter��д��Ƶ�ļ�����Ĺ��캯������ָ���ļ���������֡�ʡ�֡�ߴ硢�Ƿ񴴽���ɫ��Ƶ��
//
//������д��֡������
//1 ) writer.write(frame);
//2��writer >> frame(����ļ�ͷ����Ӧ���෴����֪��Ϊʲô��ͷ�������);
//��ע�����
//1)д����Ƶǰ�谲װ��Ӧ�ı������
//2)������Ƶ�Ƿ�֧�ֲ�ɫӦ�빹�캯������һ��
//3)������Ƶ�ߴ������ȡ��Ƶ�ߴ�һ��