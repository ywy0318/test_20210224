/*
6.1.1ƽ������
ƽ������(smoothing)Ҳ��Ϊģ������(bluring),��һ�ּ���ʹ��Ƶ��
�ܸߵ�ͼ������;
ƽ����������������ͼ���ϵ���㣬����ʧ��;����ͼ��ֱ���;

ͼ���˲����˲���
ͼ���˲���ָ�ھ�������ͼ��ϸ�������������¶�Ŀ��ͼ���������������,
��ͼ�����в���ȱ�ٵĲ���,�䴦��Ч���ĺû���ֱ��Ӱ�쵽����ͼ����
�ͷ�������Ч�ԺͿɿ���;

����ͼ���е������ɷֽ���ͼ���ƽ�������˲�����;
�źŻ�ͼ��������󲿷ּ����ڷ����׵ĵ�Ƶ����Ƶ��,
���ڽϸ�Ƶ�Σ����õ���Ϣ������������û;
���һ���ܽ��͸�Ƶ�ɷַ��ȵ��˲������ܼ���������Ӱ��;

�˲���Ŀ��������:һ���ǳ�������������Ϊͼ��ʶ�������ģʽ;
��һ����Ϊ��Ӧͼ�����Ҫ��,����ͼ�����ֻ�ʱ�����������;

ͼ���˲������Ҫ��������:һ�ǲ�����ͼ�����������Ե����Ҫ��Ϣ;
����ʹͼ�������Ӿ�Ч����;

ƽ���˲��ǵ�Ƶ��ǿ�Ŀռ����˲�����;Ŀ��������:һ����ģ��,��һ������������;


�ռ����ƽ���˲�һ����ü�ƽ��������,�������ٽ���Ԫ���ƽ������;
����Ĵ�С��ƽ����Ч��ֱ�����,����Խ��ƽ����Ч��Խ��,�����������
ƽ��Ҳ��ʹ��������Ϣ��ʧ��Խ��,�Ӷ�ʹ�����ͼ���ø�ģ��,
��������ѡ������Ĵ�С;

�����˲���:һ������ı�����:���԰��˲��������һ����Ȩϵ���Ĵ���,
��ʹ������˲���ƽ������ͼ��ʱ,�Ͱ�������ڷŵ�ͼ��֮��,͸���������
�������ǵõ���ͼ��;

�˲����������кܶ�,5�ֳ��õ�ͼ��ƽ������Ĳ����취:

�����˲�---BoxBlur����(�����˲�)
��ֵ�˲�(����ƽ���˲�)---Blur����(�����˲�)
��˹�˲�---GaussianBlur����(�����˲�)

��ֵ�˲�---medianBlur����(�������˲�)
˫���˲�---bilateralFilter����(�������˲�)


�����˲���:
��ͨ�˲���:�����Ƶ��ͨ��;
��ͨ�˲���:�����Ƶ��ͨ��;
��ͨ�˲���:����һ����Χ�˲�ͨ��;
�����˲���:��ֹһ����ΧƵ��ͨ����������Ƶ��ͨ��;
ȫͨ�˲�������������Ƶ��ͨ��,�����ı���λ��ϵ;
�ݲ��˲���(Band-Stop Filter):��ֹһ����խƵ�ʷ�Χͨ��,
��һ������Ĵ����˲���;

�˲��ǽ��ź����ض�����Ƶ���˳��Ĳ���,�����ƺͷ�ֹ���ŵ�һ����Ҫ��ʩ;

�˲���Ϊ��ͨ�͵�ͨ����,��˹�˲���ָ�ø�˹������Ϊ�˲��������˲�����,
�����ǲ���ģ����Ҫ���Ǹ�˹��ͨ���Ǹ�˹��ͨ����ͨ��ģ������ͨ����;

��˹�˲���ָ��˹������Ϊ�˲��������˲�����;
��˹ģ����ָ��˹��ͨ�˲�;


�������������������˲�
��������(�ֲ�����)�����ø���������Χ������ֵ�ľ���������
���������ֵ��һ������;�����������˲�����һ�ֳ��õ���������;
���ص����ֵȡ�����������صļ�Ȩ��;

�������ӳ����ھֲ�ɫ���������⣬����������ͼ���˲�,��ʵ��ͼ���
ƽ�����񻯣�ͼ���Ե��ǿ��ͼ��������ȥ��;


�����˲�(box Filter)
�����˲�(box Filter)����װ��һ����Ϊboxblur�ĺ�����,
boxblur�������÷����˲�����ģ��һ��ͼƬ(��ͨ);

C++:void boxFilter(InputerArray src,OutputArray dst ,int ddepth,
Size ksize,Point anchor=Point(-1,-1),boolnormalize=true,int borderType=BORDER_DEFAULT)
��һ������:�������ͼƬ���Ӧ��ΪCV_8U,CV_16U,CV_16S,CV_32F�Լ�CV_64F
�ڶ�������:Ŀ��ͼ��,��Ҫ��ԴͼƬ��һ���ĳߴ������;
����������:int���͵�ddepth,�����ͼ������,-1����ʹ��ԭͼ���,
src.depth();
���ĸ�����:Size���͵�ksize,�ں˵Ĵ�С;һ���õ�Size(w,h)����ʾ�ں˵Ĵ�С,
����wΪ���ؿ��,hΪ���ظ߶�;Size(3,3)��ʾ3*3�ĺ˴�С;
���������:Point�����͵�anchor,��ʾê��(����ƽ�����Ǹ���),ע��,����Ĭ��ֵ
Point(-1,-1);�������������Ǹ�ֵ�Ļ�,��ʾȡ������Ϊê��,����
Ĭ��ֵPoint(-1,-1)��ʾ���ê���ں˵�����;
����������:bool���͵�normalize,Ĭ��ֵΪtrue,һ����ʶ��,��ʾ
�ں��Ƿ����������һ��(normalized)��;
���߸�����:int ���͵�borderType,�����ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ,
��Ĭ��ֵBORDER_DEFAULT;

������������,normalize=true��ʱ��,�����˲��ͱ���˾�ֵ�˲�,
Ҳ����˵,��ֵ�˲��Ƿ����˲��Ĺ�һ��(normalized)����������;
��һ�����ǰ�Ҫ����������ŵ�һ����Χ(����(0,1)),�Ա�
ͳһ�����ֱ������;
�ǹ�һ��(Unnormalized)�ķ����˲����ڼ���ÿ�����������ڵĻ�������,
�����ܼ������㷨���õ���ͼ��ĵ�����Э�������;
�������Ҫ�ڿɱ�Ĵ����м��������ۺ�,ʹ��integral()����;

6.17��ֵ�˲�
��ֵ�˲�,����򵥵�һ���˲�����,���ͼ���ÿһ�������Ǻ˴���
������ͼ���Ӧ���ص�ƽ��ֵ(�������ؼ�Ȩϵ�����),
��һ����ķ����˲�,

��ֵ�˲���ȱ��:���ܺܺõı���ͼ��ϸ��,��ͼ��ȥ���ͬʱҲ�ƻ���
ͼ���ϸ�ڲ���,�Ӷ�ʹͼ����ģ��,���ܺܺõ�ȥ��������;

C++:void blur(InputArray src OutputArray dst,Size ksize,Point anchor=Point(-1,-1),
int borderType=BORDER_DEFAULT)

6.18��˹�˲�
��˹�˲���һ������ƽ���˲�,����������˹����,�㷺Ӧ����ͼ����ļ������;
��˹�˲��ľ������:��һ��ģ��(���,����)ɨ��ͼ���е�ÿһ������,��ģ��ȷ��
�����������صļ�Ȩƽ���Ҷ�ֵȥ����ģ���������ص��ֵ;

��˹ƽ��,��˹ģ���Ĺ��̾���ͼ������̬�ֲ������,��̫�ֲ�Ҳ������˹�ֲ�,
����Ҳ������˹ģ��;
��˹�����ĸ���Ҷ�任������һ����˹����,��˹ģ����ͼ����˵��һ����ͨ
�˲�����;
C++:void GaussianBlur(InputArray src,OutputArray dst,Size ksize,double sigmaX,
double sigmaY=0,intborderType=BORDER_DEFAULT)
֧�־͵ع���(In-placefiltering)

sigmaX ��ʾ��˹�˺�����X����ı�׼ƫ��;
sigmaY ��ʾ��˹�˺�����Y����ı�׼ƫ�
���sigmaYΪ0,������ΪsigmaX;
���sigmaX��sigmaY����0;
��ô����ksize.width��ksize.height
Size,sigmaX��sigmaYҪȫ��ָ����;

*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img_1, dst_img_2, dst_img_3, dst_img_4, dst_img_5, gray_img, edge;

int g_nBoxfilter_Value = 3;//�����˲�����ֵ;
int g_nMeanBlur_Value = 3;//��ֵ�˲�����ֵ
int g_nGaussianBlur_Value = 3;//��˹�˲�����ֵ
int g_nMedianBlur_Value = 10;//��ֵ�˲�����ֵ
int g_nBilateralFilter_Value = 10;//˫���˲�����ֵ

//�����˲�
void on_BoxFilter(int a, void*)
{
	boxFilter(src_img,dst_img_1,-1,Size(g_nBoxfilter_Value+1, g_nBoxfilter_Value+1));
	imshow("on_BoxFilter", dst_img_1);
}
//��ֵ�˲�
void on_MeanBlur(int a, void*)
{
	blur(src_img, dst_img_2, Size(g_nMeanBlur_Value + 1, g_nMeanBlur_Value + 1),Point(-1,-1));
	imshow("on_MeanBlur", dst_img_2);
}
//��˹�˲�
void on_GaussianBlur(int a,void*)
{
	GaussianBlur(src_img, dst_img_3, Size(41, 41), 0, 0);//----------------------����������
	//GaussianBlur(src_img, dst_img_3, Size(g_nGaussianBlur_Value + 1, g_nGaussianBlur_Value + 1), 0, 0);
	//GaussianBlur(src_img, dst_img_3, Size(a + 1, a + 1), 0, 0);
	imshow("on_GaussianBlur",dst_img_3);
}

void on_medianBlur(int, void*)
{
	medianBlur(src_img,dst_img_4,g_nMedianBlur_Value*2+1);
	imshow("��ֵ�˲�",dst_img_4);
}

void on_BilateralFilter(int, void*)
{
	bilateralFilter(src_img, dst_img_5, g_nBilateralFilter_Value, g_nBilateralFilter_Value * 2,
		g_nBilateralFilter_Value / 2);
	imshow("˫���˲�",dst_img_5);
}

int main()
{

	//Mat src_img, dst_img, gray_img, edge;

	system("color5E");

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}

	dst_img_1 = src_img.clone();
	dst_img_2 = src_img.clone();
	dst_img_3 = src_img.clone();

	namedWindow("src");
	imshow("src",src_img);
	//namedWindow("after_filter");

	namedWindow("on_BoxFilter",1);
	createTrackbar("�ں�ֵ","on_BoxFilter",&g_nBoxfilter_Value,40, on_BoxFilter);
	on_BoxFilter(g_nBoxfilter_Value,0);


	namedWindow("on_MeanBlur", 1);

	createTrackbar("�ں�ֵ","on_MeanBlur", &g_nMeanBlur_Value,40,on_MeanBlur);
	on_MeanBlur(g_nMeanBlur_Value,0);

	namedWindow("on_GaussianBlur", 1);
	createTrackbar("�ں�ֵ","on_GaussianBlur",&g_nGaussianBlur_Value,40,on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlur_Value,0);



	namedWindow("��ֵ�˲�",1);
	createTrackbar("����ֵ","��ֵ�˲�",&g_nMedianBlur_Value,50,on_medianBlur);
	on_medianBlur(g_nMedianBlur_Value,0);


	namedWindow("˫���˲�",1);
	createTrackbar("�ں�ֵ","˫���˲�",&g_nBilateralFilter_Value,100,on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilter_Value,0);

	//�����˲�����
	//boxFilter(src_img, dst_img,-1,Size(5,5));

	//��ֵ�˲�����
	//blur(src_img,dst_img,Size(7,7));

	//��˹�˲�����
	//GaussianBlur(src_img, dst_img, Size(3, 3), 0, 0);

	//imshow("after_filter", dst_img);
	waitKey(0);

	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
