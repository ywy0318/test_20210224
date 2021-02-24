/*
����ͼ�����Ƶ��Ϣ�����Ĺ���,��ֱ��ͼ��ʾ����,�õ��Ƚ�ֱ�۵����ݸй�չʾ;
ֱ��ͼ���������������ֲ�ͬ�Ĳ���������,����:�����ɫ�ʷֲ�,�����Ե�ݶ�ģ��,
�Լ���ʾĿ��λ�õĵ�ǰ����ĸ��ʷֲ�;

ֱ��ͼ�㷺�����ڼ�����Ӿ���,ͨ�����֡��֮֡�������ı�Ե����ɫ
��ͳ�Ʊ仯,�������Ƶ�г����ı仯;��ÿ����Ȥ������һ��������������
ֱ��ͼ�����ɵ�"��ǩ",����ȷ��ͼ���е���Ȥ��;��Ե,ɫ��,�Ƕȵ�ֱ��ͼ
�����˿��Ա����ݸ�Ŀ��ʶ���������һ��ͨ����������;ɫ�ʺͱ�Ե��ֱ��ͼ����
��������ʶ��������Ƶ�Ƿ񱻸���;

ֱ��ͼ���Ƕ����ݽ���ͳ�Ƶ�һ�ַ���,���ҽ�ͳ��ֵ��֯��һϵ��ʵ�ֶ���õ�bin����;
binΪֱ��ͼ�о����õ���һ������,����Ϊ:"ֱ��"����"���",��ֵ�ʹ������м��������
����ͳ����,��Щ���ݿ����������ݶ�,����,ɫ�ʻ��κ���������;ֱ��ͼ���
�������ݷֲ���ͳ��ͼ;ͨ��ֱ��ͼ��ά��Ҫ����ԭʼ����;ֱ��ͼ�Ǽ�����Ӿ������Ĺ���֮һ;

��ͳ��ѧ��,ֱ��ͼ(Histogram)��һ�ֶ����ݷֲ������ͼ�α�ʾ,��һ�ֶ�άͳ��ͼ��,������������
�ֱ���ͳ�������͸�������Ӧ��ĳ�����ԵĶ���;

ֱ��ͼ�ľ��⻯,��ͨ����������ǿ�ȷֲ���Χ����ǿͼ��Աȶȵ�һ�ַ���;

ͼ��ֱ��ͼ(image Histogram)�����Ա�ʾ����ͼ�������ȷֲ���ֱ��ͼ,
�����ͼ����ÿ������ֵ��������,���Խ����۲��ֱ��ͼ�˽���Ҫ��ε������ȷֲ�;

����ֱ��ͼ,����������Ϊ����,�ϰ�������,���Ҳ�Ϊ����,���׵�����;
���,һ�Žϰ�ͼƬ��ͼ��ֱ��ͼ�е����ݶ༯���������м䲿��,����������,
ֻ��������Ӱ��ͼ���෴;

ֱ��ͼ������:
ֱ��ͼ��ͼ��������ǿ�ȷֲ���ͼ�α�﷽ʽ;
��ͳ����ÿһ��ǿ��ֵ�����е����ظ���;

ֱ��ͼ�Ƕ����ݵ�ͳ�Ƽ���,����ͳ�ƽ���ֲ���һϵ��Ԥ�����bins��;
��������ݲ�����ָ���ǻҶ�ֵ,��ͳ�����ݿ������κ�����Ч����ͼ�������;

ֱ��ͼ����������ͳ����ɫ�Ҷ�,���ǿ���ͳ���κ�ͼ������,���ݶ�,����;
dims:��Ҫͳ�Ƶ���������Ŀ;dims=1��Ϊ��ͳ���˻Ҷ�ֵ(�Ҷ�ͼ��)
bins:ÿ�������ռ������ε���Ŀ,���Է����"ֱ��","���";
range:ÿ�������ռ��ȡֵ��Χ;range=[0,255]


9.2ֱ��ͼ�ļ��������

C++:void calcHist(const Mat* image,int nimage,const int* channels,InputArray mask,
OutputArray hist ,int dims,const,int* histSize,const float **range,bool uniform=true
,bool accumulate=false)

��һ������:const Mat*���͵�image,���������(�������ݼ�),��ҪΪ��ͬ�����(CV_8U����CV_32F)����ͬ�ĳߴ�;
�ڶ�������:int���͵�nimage,��������ĸ���,��һ�������д���˶�����"ͼ��",�м���ԭ����;
����������:const int*���͵�channels,��Ҫͳ�Ƶ�ͨ��(dim)����;��һ������ͨ����0��images[0].channels()-1,
			�ڶ�������ͨ����images[0].channels()���㵽images[0].channels()+images[1].channels()-1;
���ĸ�����:InputArray���͵�mask,��ѡ�Ĳ�������,��������벻Ϊ��,��ô��������8λ��,������
images[i]��ͬ����С�ĳߴ�;����ķ�������Ԫ�����ڱ�Ǵ�ͳ��ֱ��ͼ������Ԫ������;
���������:OutputArray���͵�hist,�����Ŀ��ֱ��ͼ,һ����ά����;
����������,int���͵�dims,��Ҫ�����ֱ��ͼ��ά��,����������,�Ҳ�����CV_MAX_DIMS(�ڵ�ǰ�汾��Opencv�е���32);
���߸�����:const int*���͵�histSize,���ÿ��ά�ȵ�ֱ��ͼ�ߴ������;
�ڰ˸�����:const float**���͵�ranges,��ʾһ��ά������(����������dims)��ÿһά�ı߽�����;
�������Ϊÿһά�����ȡֵ��Χ;

�ھŸ�����:bool���͵�uniform,ָʾֱ��ͼ�Ƿ���ȵı�ʶ��,Ĭ��Ϊtrue;

��ʮ������:bool���͵�accumulate,�ۼƱ�ʶ��,Ĭ��ֵfalse;����Ϊtrue,ֱ��ͼ�����ý׶�
���ᱻ����;�˹�����Ҫ�������������м��㵥��ֱ��ͼ,�����������ض���ʱ�����ֱ��ͼ;
------------------
��Ѱ��ֵ:minMaxLoc()����
minMaxLoc()���������������������ҵ�ȫ����Сֵ�����ֵ,�������汾
C++:void minMaxLoc(InputArray src,double* minVal,double *maxVal=0,Point*minLoc=0,
Point *=maxLoc=0,InputArray mask=noArray())

��һ������:InputArray���͵�src,����ĵ�ͨ������
�ڶ�������:double*���͵�minVal,������Сֵ��ָ��,�����뷵�أ���ֵ��ΪNULL;
����������:double*���͵�maxVal,���ص����ֵ��ָ��,�����뷵�أ���ֵ��ΪNULL;
���ĸ�����:Point*���͵�minLoc,������Сλ�õ�ָ��(��ά�����),�����뷵��,
��ֵ��ΪNULL;
���������:Point*���͵�maxLoc,�������λ�õ�ָ��(��ά�����),�����뷵��,
��ֵ��ΪNULL;
����������:InputArray���͵�mask,����ѡ�������еĿ�ѡ����;

*/
//�����ɫͼ���ɫ��,���Ͷȶ�άֱ��ͼ
//ɫ��(Hue),���Ͷ�(Saturation);����H-Sֱ��ͼ,����ɫ��--���Ͷ�ֱ��ͼ;

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int main()
{
	src_img = imread("1.jpg", 1);//����ͼƬ����
	//src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	cvtColor(src_img,dst_img,COLOR_BGR2HSV);
	//����׼��
	//��ɫ������Ϊ30���ȼ�,�����Ͷ�����Ϊ32���ȼ�;
	int hueBinNum = 30;//ɫ����ֱ��ͼֱ������
	int saturationBinNum = 32;//���Ͷȵ�ֱ��ͼֱ������
	int histSize[] = { hueBinNum ,saturationBinNum };
	//����ɫ���ı仯��ΧΪ0-179
	float hueRanges[] = { 0,180 };
	//���履�Ͷȵı仯��ΧΪ0(�ڰ׻�)��255(��������ɫ)
	float saturationRanges[] = {0,256};
	const float*ranges[] = { hueRanges ,saturationRanges };
	MatND dstHist;
	//����׼��,calcHist�����н������0ͨ���͵�1ͨ����ֱ��ͼ
	int channels[] = {0,1};
	//��ʽ����calcHist,����ֱ��ͼ����
	calcHist(&dst_img,//���������
		1,//�������Ϊ1
		channels,//ͨ������
		Mat(),//��ʹ������
		dstHist,//�����Ŀ��ֱ��ͼ
		2,//��Ҫ�����ֱ��ͼ��ά��Ϊ2
		histSize,//���ÿ��ά�ȵ�ֱ��ͼ�ߴ������
		ranges,//ÿһά�����ȡֵ��Χ����
		true,//ָʾֱ��ͼ�Ƿ���ı�ʶ��,true��ʾ���ȵ�ֱ��ͼ
		false//�ۼƱ�ʶ��,false��ʾֱ��ͼ�����ý׶λᱻ����
	);
	//Ϊ����ֱ��ͼ׼������
	double maxValue = 0;//���ֵ
	minMaxLoc(dstHist,0,&maxValue,0,0);//����������������ȫ����Сֵ�����ֵ����maxValue��
	int scale = 10;
	Mat histImg = Mat::zeros(saturationBinNum*scale,hueBinNum*10,CV_8UC3);
	//˫��ѭ��,����ֱ��ͼ����
	for (size_t i = 0; i < hueBinNum; i++)
	{
		for (int saturation = 0; saturation < saturationBinNum; saturation++)
		{
			float binValue = dstHist.at<float>(i,saturation);//ֱ��ͼֱ����ֵ
			int intensity = cvRound(binValue*255/maxValue);//ǿ��
			//��ʽ���л���
			rectangle(histImg,Point(i*scale,saturation*scale),
				Point((i+1)*scale-1,(saturation+1)*scale-1),Scalar::all(intensity),FILLED);
		}
		//��ʾЧ��ͼ
		imshow("src_img",src_img);
		imshow("h-s_img", histImg);
		waitKey();
	}
}