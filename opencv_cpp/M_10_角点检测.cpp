/*
!!!!!!!!!!����������
�ǵ���(Corner Detection)�Ǽ�����Ӿ�ϵͳ��������ȡͼ��������һ�ַ���;
�㷺Ӧ�����˶����,ͼ��ƥ��,�Ӿ�����,��ά��ģ��Ŀ��ʶ���������,
Ҳ��֮Ϊ��������

�ǵ�ͨ��������Ϊ�����ߵĽ���,�ǵ�ľֲ�����Ӧ�þ���������ͬ����Ĳ�ͬ����ı߽�;
ʵ��Ӧ����,�������ν�Ľǵ��ⷽ��������ӵ���ض���ͼ���,���������ǽǵ�;
��Щ��������ͼ�����о�������꣬���Ҿ���ĳЩ��ѧ����,��ֲ���������С�Ҷ�,
ĳЩ�ݶ�����;

��Ȥ��(interest points)Ҳ�������ؼ���(key points),������(feature points)
�����������ڽ������ʶ��,ͼ��ʶ��,ͼ��ƥ��,�Ӿ�����,��ά�ؽ�,��һϵ������;


ͼ���������Ϳ��Ա���Ϊ��������:
1.>��Ե
2.>�ǵ�(����Ȥ�ؼ���)
3.>�ߵ�(Blobs)(����Ȥ����)

���ĳһ�������ⷽ���һ��΢С�䶯��������ҶȺܴ�ı仯,��ô���ǰ�����֮Ϊ�ǵ�;
�ǵ���Ϊͼ���ϵ�������,��������Ҫ����Ϣ,��ͼ���ںϺ�Ŀ����ټ���ά�ؽ���
����Ҫ��Ӧ�ü�ֵ;

�ǵ�λ��������Ե�Ľ��㴦,������������Ե�仯�ķ����ϵĵ�,
�����ǿ��Ծ�ȷ��λ�Ķ�ά����,�����ﵽ�����صľ���; 
������ͼ���ݶ��кܸߵı仯,���ֱ仯�ǿ��������������ǵ��;
�ǵ���λ����ͬǿ�������ϵĵ㲻ͬ,�����������ϵĵ�Ҳ��ͬ,��Ϊ
��������������ͬ�����������Ͼ�ȷ��λ;

�ǵ��������һ�¼���:
һ�׵���(���Ҷȵ��ݶ�)�ľֲ��������Ӧ�ĵ����ص�;
�������������ϱ�Ե�Ľ���;
ͼ���е��ݶ�ֵ���ݶȷ���ı仯���ʶ��ܸߵĵ�;
�ǵ㴦��һ�׵������,���׵���Ϊ0,ָʾ�������Ե�仯�������ķ���;

10.1.2�ǵ���
���ڵĽǵ����㷨������ʮ�ֵĽ�׳;�ܶ෽����Ҫ���д�����ѵ����
��������������ֹ����ٴ��������ĳ���;
����,�ǵ��ⷽ����һ������Ҫ�����۱�׼����Զ��ͼ������ͬ
�����������ļ������,�����ܹ�Ӧ�ù��ձ仯,ͼ����ת��ͼ��仯;

�ڵ�ǰ��ͼ��������,�ǵ����㷨���Թ���Ϊ��������:
1.>���ڻҶ�ͼ��Ľǵ���
2.>���ڶ�ֵͼ��Ľǵ���
3.>�����������ߵĽǵ���


���ڻҶ�ͼ��Ľǵ����ֿɷ�Ϊ�����ݶ�,
����ģ��ͻ���ģ���ݶ�������෽��;

����ģ��ķ�����Ҫ�������������ĻҶȱ仯��ͼ������
�ı仯,�����ڵ����ȶԱ��㹻��ĵ㶨��Ϊ�ǵ�;
�����Ļ���ģ��Ľǵ�����㷨��:
Kitchen-Rosenfeld�ǵ����㷨,Harris�ǵ����㷨,
KLT�ǵ����㷨��SUSAN�ǵ����㷨;

10.1.3 harris�ǵ���
harris�ǵ�����һ��ֱ�ӻ��ڻҶ�ͼ��Ľǵ���ȡ�㷨,�ȶ��Ը�,
�����L�ͽǵ��⾫�ȸ�;�������ڲ����˸�˹�˲�,�����ٶ���Խ���,
�ǵ���Ϣ�ж�ʧ��λ��ƫ�Ƶ�����,���ҽǵ���ȡ�о۴�����;

10.1.4ʵ��Harris�ǵ���:cornerHarris()����
cornerHarris����������OpenCV������Harris�ǵ�������
�����нǵ���;
��cornerMineigenVal()�Լ�cornerEigenValsandVecs()����
����,cornerHarris��������ÿһ�����ص�(x,y)��blockSize*blockSize
������,����2*2�ݶȵ�Э�������M(x,y),��������������ʽ��:

dst(x,y)=detM(x,y)-k*(trM(x,y))^2;
�Ϳ����ҳ����ͼ�еľֲ����ֵ,���ҳ��˽ǵ�

C++:void cornerHarris(InputArray src,OutputArray dst,int blockSize,int ksize,double k,
int borderType=BORDER_DEFAULT)

��һ������:InputArray���͵�src,����ͼ��,��Դͼ��,��Mat��Ķ��󼴿�,����Ϊ��ͨ��8λ���߸�����ͼ��;
�ڶ�������:OutputArray���͵�dst,�������ú������������������,������������ڴ��harris�ǵ���
��������,��ԴͼƬ��һ���ĳߴ������;
����������:int���͵�blockSize,��ʾ����Ĵ�С,�������ϸ��Ϣ��cornerEigenValsAndVecs()���н�;
���ĸ�����:int���͵�ksize,��ʾSobel()���ӵĿ׾���С
���������:double���͵�k,Harris����
����������:int���͵�borderType,ͼ�����صı߽�ģʽ;ע������Ĭ��ֵBORDER_DEFAULT;

*/

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img,normalize_img,scaled_img;

int thresh = 30;
int thresh_max = 175;

void on_cornerHarris(int ,void*);

void cornerHarris_1()
{
	//����Harris�ǵ����ҳ��ǵ�
	Mat cornerStrength;
	cornerHarris(src_img,cornerStrength,2,3,0.01);
	//�ԻҶ�ͼ������ֵ����,�õ���ֵͼ����ʾ
	Mat harrisCorner;
	threshold(cornerStrength,harrisCorner,0.00001,255,THRESH_BINARY);
	imshow("src_img",src_img);
	imshow("harrisCorner", harrisCorner);
	waitKey(0);
}

void cornerHarris_2()
{
	imshow("src_img", src_img);
	temp_img = src_img.clone();
	//����һ�ŻҶ�ͼ
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
	
	createTrackbar("��ֵ:","on_cornerHarris",&thresh,thresh_max,on_cornerHarris);
	on_cornerHarris(0,0);
	//namedWindow("on_cornerHarris", WINDOW_AUTOSIZE);
	waitKey(0);
	return;
}
void on_cornerHarris(int, void*)
{
	dst_img = Mat::zeros(src_img.size(),CV_32FC1);
	edge_img = src_img.clone();

	//��ʽ���
	cornerHarris(gray_img,dst_img,2,3,0.04,BORDER_DEFAULT);
	//��һ����ת��
	normalize(dst_img, normalize_img,0,255,NORM_MINMAX,CV_32FC1,Mat());
	convertScaleAbs(normalize_img, scaled_img);

	//����⵽��,�ҷ�����ֵ�����Ľǵ���Ƴ���
	for (size_t j = 0; j < normalize_img.rows; j++)
	{
		for (int i = 0; i < normalize_img.cols; i++)
		{
			if ((int)normalize_img.at<float>(j,i)>thresh+80)
			{
				circle(temp_img, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(scaled_img, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
			}
		}
	}
	imshow("on_cornerHarris",temp_img);
	imshow("scaled_img",scaled_img);
}
int main()
{
	//src_img = imread("1.jpg", 0);//����ͼƬ����
	src_img = imread("lena.jpg", 0);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//cornerHarris_1();
	cornerHarris_2();
	//imshow("src_img", src_img);
	//waitKey(0);
	system("pause");
	return 0;
}