#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
//operationsOnArrays:LUT()<lut>
/*
//����һ��mat�����ڲ��
Mat lookUpTable(1,256,CV_8U);
uchar* p = lookUpTable.data;
for (size_t i = 0; i < 256; i++)
{
p[i] = lookUpTable[i];
}

//Ȼ�����ǵ��ú���(I�����룬J�����)
for (size_t i = 0; i < times; i++)
{
LUT(I,lookUpTable,J);
}

��ʱ����
getTickCount()��getTickFrequency()
getTickCount()��������CPU��ĳ���¼�(���������������߹���ʱ������)
getTickFrequency()��������CPUһ�������߹���ʱ��������;
�������ǾͿ������ɵ�����Ϊ��λ��ĳ�����ʱ��;

�����������������ʹ�õ�ʾ������: 
double time_0=static_cast<double>(getTickCount());//��¼��ʼʱ��
//����ͼ�������....
time_0=((double)getTickCount()-time_0)/getTickFrequency();
cout<<"�˷�������ʱ��Ϊ:"<<time_0<<"��"<<endl;//�������ʱ��


����ͼ�������ص����෽��
����1:ָ�����:C������[];
����2:������iterator;
����3:��̬��ַ����;

debugģʽ�²������ԣ�releaseģʽ�²��첻̫����


*/
void colorReduce(Mat& inputImage,Mat& outputImage,int div);

//����1:��ָ���������
/*
��ָ��������ص����ַ������õ�C�����еĲ�����,
���ַ������,�������е����,
*/
void colorReduce_C(Mat& inputImage, Mat& outputImage, int div)
{
	//����׼��
	outputImage = inputImage.clone();//����ʵ�ε���ʱ����
	int row_num = outputImage.rows;//����
	//����xͨ����=ÿһ��Ԫ�صĸ���
	int col_num = outputImage.cols*outputImage.channels();
	//˫��ѭ��,�������е�����ֵ
	for (size_t i = 0; i < row_num; i++)
	{
		//��ȡ��i�е��׵�ַ
		uchar* data = outputImage.ptr<uchar>(i);
		//��ѭ��
		for (size_t j = 0; j < col_num; j++)
		{
			data[j] = data[j] / div*div + div / 2;//����ÿ������
			//*data++=*data/div*div+div/2;
		}
	}

}
//����2:�õ�������������
/*
�õ�������������,���ַ�����STL����÷�����
�ڵ�������,��ȡͼ������begin��end,Ȼ�����ӵ���ֱ��begin��end;
��*����������ڵ���ָ��ǰ,���ɷ��ʵ�ǰָ�������
�����ָ��ֱ�ӷ��ʿ��ܳ���Խ������,�����������Ƿǳ���ȫ�ķ���
STL������
*/
void colorReduce_iterator(Mat& inputImage, Mat& outputImage, int div)
{
	//����׼��
	outputImage = inputImage.clone();
	//��ȡ������
	Mat_<Vec3b>::iterator it_begin = outputImage.begin<Vec3b>();//��ʼλ�õĵ�����
	Mat_<Vec3b>::iterator it_end = outputImage.end<Vec3b>();//��ʼλ�õĵ�����

	//��ȡ��ɫͼ������
	for (; it_begin!=it_end; it_begin++)
	{
		(*it_begin)[0] = (*it_begin)[0] / div*div + div / 2;
		(*it_begin)[1] = (*it_begin)[1] / div*div + div / 2;
		(*it_begin)[2] = (*it_begin)[2] / div*div + div / 2;
	}

}
/*
����3:��̬��ַ����
�ö�̬��ַ��������������;
����ʹ�ö�̬��ַ��������at�ķ���colorReduce�����Ĵ���

Mat���е�cols��rows������ͼ��Ŀ�͸�,����Ա����at(int y,int x)
���������洢ͼ��Ԫ��,�����ڱ�����֪��ͼ�����������,��Ҫע�����:
����һ��Ҫȷ��ָ������������Ҫ�;����е��������������,
��Ϊat������������κ��������ͽ���ת��

���ڲ�ɫͼ��,ÿ���������������ֹ���:��ɫͨ������ɫͨ���ͺ�ɫͨ��(BGR)
����һ��������ɫͼ���Mat,�᷵��һ��������8λ����ɵ�����
OpenCV�������͵���������ΪVec3b,��������unsigned char�������
��ȡ��ɫͼ�����صĴ���������ʽ:
img.at<Vec3b>(j,i)[channel]=value;����ֵchannel��������ɫͨ����

*/

void colorReduce_at(Mat& inputImage, Mat& outputImage, int div)
{
	//����׼��
	outputImage = inputImage.clone();
	int row_num = outputImage.rows;
	int col_num = outputImage.cols;

	//��ȡ��ɫͼ������
	for (size_t i = 0; i < row_num; i++)
	{
		for (int j = 0; j < col_num; j++)
		{
			//��ɫͨ��
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div*div + div / 2;
			//��ɫͨ��
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div*div + div / 2;
			//��ɫͨ��
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div*div + div / 2;
		}
	}
}


//���������colorReduce��������ɼ�����ɫ�Ĺ���,�������ַ������ص����෽��,д�������汾��colorRecuce����;
int main()
{
	string imgpath4 = "1.jpg";
	Mat img = imread(imgpath4, 1);//����ͼƬ����
	if (img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	Mat dst_image;
	//��ԭʼͼ�Ĳ������������Ч��ͼ,Ч��ͼ�Ĵ�С,����	
	dst_image.create(img.rows,img.cols,img.type());

	//��¼��ʼʱ��
	double time_0 = static_cast<double>(getTickCount());

	//������ɫ�ռ���������
	//colorReduce(img,dst_image,32);
	//colorReduce_C(img, dst_image, 32);//0.00674778s
	//colorReduce_iterator(img, dst_image, 32);//0.0110831--0.00992691s
	colorReduce_at(img, dst_image, 32);//0.00983608s

	//��������ʱ�䲢���
	time_0 = ((double)getTickCount() - time_0) / getTickFrequency();
	cout << "�˷�������ʱ��" << time_0 << "��" << endl;//�������ʱ��

	imshow("Ч��ͼ", dst_image);

	imshow("Ч��ͼ1", img);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
