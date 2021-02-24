

/*
6.5.1��ˮ���Ķ���,
��ˮ��䷨��һ�����ض�����ɫ�����ͨ����ͨ�����ÿ���ͨ���ص��������Լ�
��ͨ��ʽ���ﵽ��ͬ�����Ч���ķ���;
��ˮ��侭����������ǻ����ͼ���һ����;
Ҳ��������������ͼ���ȡ���������������ٴ������,
����ֻ��������ָ�������ص�,�����Ľ������ĳ������������;
floodfill
�Զ�ѡ���˺����ӵ�����������,���Ž��������滻��ָ������ɫ;
���Һ����ӵ���ͨ����ɫ��ͬ�ĵ�;

int floodFill(InputArray src,
Point seedPoint,Scalar newVal,
CV_OUT Rect* rect=0,Scalar loDiff=Scalar(),Scalar upDiff=Scalar(),
int flags=4)

int floodFill(InputArray src,InputOutputArray mask,
Point seedPoint,Scalar newVal,
CV_OUT Rect* rect=0,Scalar loDiff=Scalar(),Scalar upDiff=Scalar(),
int flags=4)

InputOutputArray���͵�mask,��ʾ��������,��ͨ����8λ,���Ϳ��϶�������ͼ��
image���������ص�;��Ե������ӵ��������������Ϊ���룬��ֹ��䵽��Ե
,�ڶ�κ���������ʹ��ͬһ������,�Ա�֤�������򲻻��ص�;
����mask�����Ҫ����ͼ���,mask��������ͼ��(x,y)���ص�
���Ӧ������Ϊ(x+1,y+1)

����������:seedPoint����ˮ����㷨����ʼ��;
���ĸ�����:Scalar���͵�newVal,���ص㱻Ⱦɫ��ֵ,��
�ػ���������ص���ֵ;
���������:Rect*rect,��Ĭ��ֵΪ0,һ����ѡ�Ĳ���,��������
floodFill������Ҫ�ػ��������С�߽��������;
����������:Scalar���͵�upDiff,��Ĭ��ֵScalar(),��ʾ��ǰ
�۲�����ֵ���䲿����������ֵ�������ò�������������֮�������
����ɫ֮����(lower brightnesss/color difference)�����ֵ
�ڰ˸�����:int���͵�flags,������ʶ��,
�ڰ�λ(0-7):���ڿ����㷨����ͨ��,��ȡ4(Ĭ��ֵ)����8,
���Ϊ4:��ʾ����㷨ֻ���ǵ�ǰ����ˮƽ����ʹ�ֱ��������ڵ�;
�������Ϊ8,�����������ڵ��⣬��������Խ��߷�������ڵ�;
�߰�λ(16-32):����Ϊ0������������ѡ���ʶ�������,
FLOODFILL_FIXED_RANGE:�������Ϊ�����ʶ��,�ͻῼ�ǵ�ǰ������
��������֮��Ĳ�,����Ϳ��ǵ�ǰ���������������صĲ�,�����Χ��
������;
FLOODFOLL_MASK_ONLY:�������Ϊ�����ʶ��,��������ȥ���ı�ԭʼͼ��
(Ҳ���Ǻ��Ե���������newVal),����ȥ�������ͼ��(mask),�����ʶ��ֻ��
�ڶ����汾��floodfill����;
�м��λ��ֵ������ָ���������ͼ���ֵ;

*/
/*
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int main()
{

	Mat src_img, dst_img, gray_img, edge;

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	Rect ccomp;
	imshow("src_img",src_img);
	floodFill(src_img,Point(50,50),Scalar(155,255,55),&ccomp,Scalar(20,20,20),Scalar(20,20,20));

	imshow("floodFill_src_img",src_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img;

int g_nFillMode = 1;//��ˮ����ģʽ
int g_nLowDifference = 20;//�������ֵ
int g_nUpDifference = 20;//�������ֵ

int g_nConnectivity = 4;//��ʾfloodFill������ʶ���ڰ�λ����ֵͨ
int g_bIsColor = true;//�Ƿ�Ϊ��ɫͼ�ı�ʶ������ֵ
int g_bUseMask = false;//�Ƿ���ʾ���봰�ڵĲ���ֵ 
int g_nNewMaskVal = 255;//�µ����»��Ƶ�����ֵ

static void onMouse(int event, int x, int y, int, void*)
{
	//��������û�а���,�㷵��
	if (event!=EVENT_LBUTTONDOWN)
	{
		return;
	}
	//����floodFill����֮ǰ�Ĳ���׼������;
	Point seed = Point(x, y);
	//�շ�Χ����ˮ���,��ֵΪ0,��������Ϊȫ�ֵ�g_nLowDifference
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;
	//�շ�Χ����ˮ���,��ֵ����Ϊ0,��������Ϊȫ�ֵ�g_nUpDifference
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;
	//��ʶ����0-7λΪg_nConnectivity,8-15λΪg_nNewMaskVal����8λ��ֵ;
	//16-23λΪFLOODFILL_FIXED_RANGE����0;

	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

	//�������bgrֵ
	int b = (unsigned)theRNG() & 255;//�������һ��0-255֮���ֵ;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;//�����ػ��������С�߽��������
	//���ػ��������ص���ֵ,���ǲ�ɫͼģʽ,ȡScalar(b,g,r);
	//���ǻ�ɫͼģʽ,ȡScalar(r*0.299 + g*0.587 + r*0.114)
	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + r*0.114);//
	//Ŀ��ͼ�ĸ�ֵ
	Mat dst = g_bIsColor ? dst_img : gray_img;
	//
	int area;
	if (g_bUseMask)
	{
		threshold(mask_img,mask_img,1,128,THRESH_BINARY);
		area = floodFill(dst, mask_img,seed,newVal,&ccomp,Scalar(LowDifference,LowDifference,LowDifference)
		,Scalar(UpDifference,UpDifference,UpDifference),flags);
		imshow("mask",mask_img);

	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
		imshow("Ч��ͼ",dst);
		cout << area << "�����ر��ػ�\n";
	}
}
int main()
{

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//����ԭͼ��Ŀ��ͼ��
	src_img.copyTo(dst_img);
	//ת����ͨ����image���Ҷ�ͼ��
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
	//����image�ĳߴ�����ʼ������mask
	mask_img.create(src_img.rows+2,src_img.cols+2,CV_8UC1);
	
	namedWindow("Ч��ͼ",WINDOW_AUTOSIZE);
	//����Trackbar
	createTrackbar("��ֵ���ֵ","Ч��ͼ",&g_nLowDifference,255,0);
	createTrackbar("��ֵ���ֵ", "Ч��ͼ", &g_nUpDifference, 255, 0);

	//���ص�����
	setMouseCallback("Ч��ͼ",onMouse,0);
	//ѭ����ѯ����
	while (true)
	{
		imshow("Ч��ͼ", g_bIsColor ? dst_img : gray_img);
		//��ȡ���̰���
		int c = waitKey(0);
		//�ж�ESC�Ƿ���,���¾��˳�
		if ((c&255)==27)
		{
			cout << "�����˳�.....\n";
			break;
		}
		//���ݰ����Ĳ�ͬ,���и��ֲ���;
		switch ((char)c)
		{
			//���1�����£�Ч��ͼ�ڻ�ɫ����ɫͼ֮�以��
		case'1':
			//���ԭ��Ϊ��ɫ��ת��Ϊ�Ҷ�ͼ,���ҽ�����mask����Ԫ������Ϊ0
			if (g_bIsColor)
			{
				cout << "����1�����£��л���ɫ/��ɫģʽ,��ǰ����[��ɫģʽ]�л�Ϊ[�Ҷ�ģʽ]\n";
				cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
				//��mask����Ԫ������Ϊ0
				mask_img = Scalar::all(0);
				//����ʶ������Ϊfasle,��ʾ��ǰͼ��Ϊ��ɫ�����ǻҶ�
				g_bIsColor = false;
			}
			//ԭ��Ϊ�Ҷ�ͼ,��ԭ���Ĳ�ɫͼ�ٴθ��Ƹ�image,��������mask����Ԫ������Ϊ0
			else
			{
				cout << "����1������,[��ɫģʽ]�л���[��ɫģʽ]\n";
				src_img.copyTo(dst_img);
				mask_img = Scalar::all(0);
				g_bIsColor = true;
			}
			break;
		case'2':
			//���̰���2������,��ʾ/�������봰��
			if (g_bUseMask)
			{
				destroyWindow("mask");
				g_bUseMask = false;
			}
			else
			{
				namedWindow("mask",0);
				mask_img = Scalar::all(0);
				imshow("mask",mask_img);
				g_bUseMask = true; 
			}
			break; 
		case'3':
			cout << "����3������,�ָ�ԭʼͼ��\n";
			src_img.copyTo(dst_img);
			cvtColor(dst_img,gray_img,COLOR_BGR2GRAY);
			mask_img = Scalar::all(0);
			break;
		case'4':
			cout << "����4�����£�ʹ�ÿշ�Χ����ˮ���\n";
			g_nFillMode = 0;
			break;
		case'5':
			cout << "����5�����£�ʹ�ý���,�̶���Χ����ˮ���\n";
			g_nFillMode = 1;
			break;
		case'6':
			cout << "����6�����£�ʹ�ý���,������Χ����ˮ���\n";
			g_nFillMode =2;
			break;
		case'7':
			cout << "����7�����£�������ʶ���ĵڰ�λʹ��4λ������ģʽ\n";
			g_nConnectivity = 4;
			break;
		case'8':
			cout << "����8�����£�������ʶ���ĵڰ�λʹ��8λ������ģʽ\n";
			g_nConnectivity = 8;
			break;

		default:
			break;
		}
	}

	//imshow("src_img", src_img);
	//waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}

