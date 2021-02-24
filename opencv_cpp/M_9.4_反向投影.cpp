/*
9.4����ͶӰ
һ��ͼ�����������ʾ����һ�ֽṹ�������
һ�����ص�����,��ô��������ֱ��ͼ���Կ���һ�����ʺ���,
�������ʽ��ĳ���������ڸ����������ĸ���;

����ͶӰ(back projection)����һ�ּ�¼����ͼ���е����ص�
�����Ӧֱ��ͼģ�����طֲ���ʽ��һ�ַ���;

����ͶӰ�������ȼ���ĳһ������ֱ��ͼģ��,Ȼ��ʹ��ģ��ȥ
Ѱ��ͼ���д��ڵĸ������ķ���;

ʹ��ģ��ֱ��ͼ(�������Ƶ�Ƥ��ɫ��)��������ͼ�е�Ƥ������;
��ⲽ������:
1.>�Բ���ͼ���е�ÿ������(p(i,j)),��ȡɫ�����ݲ��ҵ���ɫ��(Hij,sij)
��ֱ��ͼ�е�bin��λ��;
2.>��ѯģ��ֱ��ͼ�ж�Ӧbin����ֵ;
3.>������ֵ�洢���µķ���ͶӰͼ����;Ҳ�����ȹ�һ��ֱ��ͼ��ֵ��0-255��
��������ֱ����ʾ����ͶӰͼ��(��ͨ��ͼ��);
4.>ͨ���Բ���ͼ���е�ÿ�����ز�ȡ���ϲ���,�õ����յķ���ͶӰͼ��;
5.>ʹ��ͳ��ѧ�����Խ��з���;����ͶӰ�д������ֵ�����˲���ͼ����
����������Ƥ������ĸ���;
�����������Ƥ������ĸ��ʸ���,�������������ʾƤ���ĸ��ʸ���;
�����ڲ��ͱ�Ե����ӰӰ���˼��ľ���;

9.4.3����ͶӰ������
����ͶӰ����������ͼ��(ͨ���ϴ�)�в������ض�ͼ��(ͨ����С����
��һ������,���³�Ϊģ��ͼ��)��ƥ��ĵ��������,Ҳ���Ƕ�λģ��
ͼ�����������ͼ���λ��;
9.4.4����ͶӰ�Ľ��
����ͶӰ�Ľ����������ÿ������ͼ�����ص�λ����ֱ��ͼ�ԱȽ��;
���԰���������һ����ά�ĸ���������,��ά����,���ߵ�ͨ���ĸ�����ͼ��;


���㷴��ͶӰ:calcBackProject()����
calcBackProject()�������ڼ���ֱ��ͼ�ķ���ͶӰ

C++:void calcBackProject(
const Mat*images,
int nimages,
const int*channels,
InputArray hist,
OutputArray backProject,
const float**ranges,
double scale=1,
bool uniform=true
)
��һ������:���������������鼯,���鼯Ҫ����ͬ����Ⱥͳߴ�,ͨ����������;
�ڶ�������:int���͵�nimages,��������ĸ���,Ҳ���ǵ�һ�������з��˶�����"ͼ��",
�м���ԭ����;
����������:const int*���͵�channels,��Ҫͳ�Ƶ�ͨ��(dim)����;��һ������ͨ����
0��images[0].channels()-1,���ڶ�������ͨ����images[0].channels()���㵽
images[0].channels()+images[1].channels()-1;
���ĸ�����:InputArray���͵�hist,�����ֱ��ͼ;
���������:OutputArray���͵�backProject,Ŀ�귴��ͶӰ����,��ҪΪ��ͨ��,
���Һ�imags[0]����ͬ�Ĵ�С�����;
����������:const float**���͵�ranges,��ʾÿһ��ά������(����������dims)��ÿһά
�ı߽�����,�������Ϊÿһά��ֵ��ȡֵ��Χ;
���߸�����:double scale,Ĭ��ֵΪ1,����ķ���ͶӰ��ѡ����������,Ĭ��Ϊ1;
�ڰ˸�����:bool���͵�uniform,ָʾֱ��ͼ�Ƿ���ȵı�ʶ��,Ĭ��ֵΪtrue;

---------------
ͨ������:
mixChannels()����
�˺����������������ĳͨ������������ض���ͨ����;

C++:void mixChannels(const Mat*src,size_t nsrcs,Mat* dst,size_t ndsts,const int*fromTo);
��һ������:���������,����ͬ�ĳߴ�����;
�ڶ�������:src����ľ�����
����������:���������,���о�����뱻��ʼ��,�Ҵ�С����ȱ�����src[0]��ͬ
���ĸ�����:����������dst����ľ�����
�������������ָ����ͨ�����и�ֵ����������
����������:fromTo��������


C++:void minChannels(const vector<Mat>&src,vector<Mat>&dst,const int* fromTo,size_t npairs)

��һ������:����ľ�������,���еľ����������ͬ�ĳߴ�����
�ڶ�������:����ľ�������,���о�����Ҫ����ʼ��,�Ҵ�С���������src[0]��ͬ
����������:��ָ����ͨ�����и��Ƶ���������
���ĸ�����:fromTo��������

�˺���Ϊ����ͼ��ͨ���ṩ�˱Ƚ��Ƚ��Ļ���;֮ǰ�Ӵ�����
split()��merge(),�Լ�cvtColor()��ĳЩ��ʽ,����mixChannels()��һ����;
*/

/*
��4ͨ����RGBAͼ��ת��Ϊ��ͨ��BGR(Rͨ����Bͨ������),��һ��������Alphaͨ����ͼ��;
Mat rgba(100,100,CV_8UC4,Scalar(1,2,3,4));
Mat bgr(rgba.rows,rgba.cols,CV_8UC3);
Mat alpha(rgba.rows,rgba.cols,CV_8UC1);

//���������������в���
Mat out[]={bgr,alpha};
//˵��:rgba[0]->bgr[2],rgba[1]->bgr[1]
//˵��:rgna[2]->bgr[0],rgba[3]->alpha[0]
int from_to[]={0,2,1,1,2,0,3,3};
mixChannels(&rgba,1,out,2,from_to,4);
*/
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int g_bins = 30;//ֱ��ͼ���
void on_BinChange(int, void*);
int main()
{

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	cvtColor(src_img,temp_img,COLOR_BGR2HSV);
	//����hueɫ��ͨ��
	edge_img.create(temp_img.size(),temp_img.depth());
	int ch[] = {0,0};
	mixChannels(&temp_img, 1, &edge_img, 1, ch, 1);

	//����Trackbar������bin����Ŀ
	namedWindow("src_img",WINDOW_AUTOSIZE);
	createTrackbar("ɫ�����","src_img",&g_bins,180,on_BinChange);
	on_BinChange(0,0);
	imshow("src_img",src_img);
	waitKey(0);
	return 0;
}
void on_BinChange(int, void*)
{
	//����׼��
	MatND hist;
	int histSize = MAX(g_bins,2);
	float hue_range[] = { 0,180 };
	const float*range = { hue_range };
	//����ֱ��ͼ����һ��
	calcHist(&edge_img,1,0,Mat(),hist,1,&histSize,&range,true,false);
	normalize(hist,hist,0,255,NORM_MINMAX,-1,Mat());
	//���㷴��ͶӰ
	MatND backproj;
	calcBackProject(&edge_img,1,0,hist,backproj,&range,1,true);
	//��ʾ����ͶӰ
	imshow("����ͶӰͼ",backproj);
	//����ֱ��ͼ�Ĳ���׼��
	int w = 400;
	int h = 400;
	int bin_w = cvRound((double)w/histSize);
	Mat histImg = Mat::zeros(w,h,CV_8UC3);
	//����ֱ��ͼ
	for (size_t i = 0; i < g_bins; i++)
	{
		{
			rectangle(histImg,Point(i*bin_w,h),Point((i+1)*bin_w,h-cvRound(hist.at<float>(i)*h/255.0)),
				Scalar(100,123,255),-1);
		}
	}
	//��ʾֱ��ͼ����
	imshow("ֱ��ͼ", histImg);
}