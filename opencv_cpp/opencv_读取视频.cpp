#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	VideoCapture cap; //warning: Error opening file(.. / .. / modules / highgui / src / cap_ffmpeg_impl.hpp:545)������������Ƶ�ļ���·�����ˣ�����
	//Ӧ������ E:\\Codes\\student5.mp4	\\ �����ָ�
	//cap.open("E://2.avi"); //����Ƶ,��������ȼ���VideoCapture cap("E://2.avi");
	//cap.open("E://1.avi");
	cap.open("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.mp4");//�ɹ���
	//E:\Visual Studio 2010\Projects\opencv\opencv
						   //cap.open("http://www.laganiere.name/bike.avi");//Ҳ����ֱ�Ӵ���ҳ�л�ȡͼƬ��ǰ������ҳ����Ƶ���Լ����ٹ���
	if (!cap.isOpened())//�����Ƶ�����������򷵻�
	{
		printf("error\n");
		system("pause");
		return;
	}
	Mat frame;
	while (1)
	{
		cap >> frame;//�ȼ���cap.read(frame);
		if (frame.empty())//���ĳ֡Ϊ�����˳�ѭ��
			break;
		imshow("video", frame);
		waitKey(20);//ÿ֡��ʱ20����
	}
	cap.release();//�ͷ���Դ
}
//
//��Ƶ��ȡ�����Ͼ��Ƕ�ȡͼ����Ϊ��Ƶ����һ֡һ֡ͼ����ɵġ�1��24֡�������������Ķ�ȡ��Ƶ�ˡ�
//�ٶ�ȡ��Ƶ�����ַ�����
//A.VideoCapture cap;
//cap.open(��1.avi��);
//B.VideoCapture cap(��1.avi��);
//
//��ѭ����ʾÿһ֡��
//while (1)
//{
//	Mat frame; //����Mat�����������洢ÿһ֡ 
//	cap >> frame; //��ȡ��ǰ֡����һ 
//				  //cap.read(frame); //��ȡ��ǰ֡������ 
//	imshow(����Ƶ��ʾ��, frame); //��ʾһ֡���� 
//	waitKey(30); //��ʱ30ms 
//}



//������ȡ��Ƶ˵��
//�򿪵���Ƶ�����Ǳ�����Ƶ�� :
//VideoCapture cap(��1.avi��);
//Ҳ������������Ƶ�磺
//VideoCapture cap(��http://www.laganiere.name/bike.avi��);
//��ȡ��Ƶһ��Ҫ���쳣�ж�
//A.����Ƶʧ��(����ԭ��)
//B.ȡ֡ʧ���쳣(�����β�ж�)
//ex1 :
//	if (!cap.isOpened()) //�����Ƿ�ɹ� 
//		return;
//ex2:
//cap >> frame;
//if (!frame.empty()) //�жϵ�ǰ ֡�Ƿ�Ϊ�� 
//{
//	imshow(��video��, frame);
//	waitKey(30);
//}
//else break;

