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

#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	VideoCapture cap;
	cap.open(0); //������ͷ

	if (!cap.isOpened())
		return;

	Mat frame;
	while (1)
	{
		cap >> frame;//�ȼ���cap.read(frame);
		//Canny(frame, frame, 30, 100);//canny��Ե��⣬ȥ����һ�о��Ǵ���Ķ�ȡ����ͷ��
		//cvtColor(frame, frame, CV_BGR2HSV)�������ã����ǳ�����Ч����̫�ѿ�
	    //cvtColor(frame, frame, CV_BGR2HSV);//BGR�ռ�תΪHSV��ɫ�ռ䣬ע�⣬���߲���ͬʱ��ͬһ��ͼƬ���ڴ�Ϊframe�����д������򱨴�
		if (frame.empty())
			break;
		imshow("video", frame);
		if (waitKey(20)>0)//����������˳�����ͷ��������Ի������죬�еĵ��Կ��ܻ����һ�����������
			break;
	}
	cap.release();
	destroyAllWindows();//�ر����д���
}

//��Ե�20�д��룺�ʼ�������õ�opencv2.x�汾���������������ͷû�����⣻����ʹ��opencv3.x�汾�����±�����contrib������������ͷ�򿪺�һ��������
//
//ԭ���� waitkey() �����������ʱ���Ƿ��� oxff��oxff�޷���ʱ��255���з���ʱ�� - 1��windows vs �Ļ���Ĭ�������Ϊ�Ƿ����� ��255����opencv����Щ���û������� - 1��
//
//�����������ԭʼ������ѭ����ȡ֡��
//
//if (waitKey(20) >= 0)����break;
//
//��Ϊ
//
//if (waitKey(20) != 255)����break;
//
//���߰�waitkey�ķ���ֵ���з�����ȥ��ȡ��
//
//uchar c = waitkey(20);����if (c != 255)  break;