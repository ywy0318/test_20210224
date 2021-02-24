/*7.4����任
��ʾ�ľ�������ͼƬ֮���һ����ϵ;

����任(Affine Map),�ֳ�Ϊ����ӳ��,��ָ�ڼ�����,һ�������ռ����һ��
���Ա任������һ��ƽ��,�任Ϊ��һ�������ռ�Ĺ���;
�������˶�άͼ���"ƽֱ��"(ֱ�߾����任֮����Ȼ��ֱ��),��"ƽ����"
(��άͼ��֮������λ�ù�ϵ���ֲ���,ƽ������Ȼ��ƽ����,��ֱ����
���λ��˳�򲻱�);
һ������ķ���任���ܱ�ʾΪ����һ������(���Ա任)�ٽ��ż���һ��
����(ƽ��)����ʽ;

��ת:rotation(���Ա任)
ƽ��,translation(������)
����,scale(���Ա任)

OpenCV����任��صĺ���һ���漰��wapAffine��getRotationMatrix2D
����������;
wrapAffine��ʵ��һЩ�򵥵���ӳ��
getRotationMatrix2D�������ת����

wrapAffine����������������һ�¹�ʽ,��ͼ��������任
dst(x,y)=src(M11x+M12y+M13,M21x+M22y+M23)
C++:void wrapAffine(InputArray src,OutputArray dst,InputArray M,
Size dsize,int flag=INTER_LINEAR,int borderMode=BORDER_CONSTANT,
const Scalar&borderValue=Scalar());

�ڶ�������:OutputArray���͵�dst,�������ú����������������,
��Ҫ��ԴͼƬ��һ���ĳߴ������;
����������:InputArray���͵�M,2*3�ı任����;
���ĸ�����:Size���͵�dsize,��ʾ���ͼ��ĳߴ�;
���������:int���͵�flags,��ֵ�����ı�ʶ��;�˲�����Ĭ��ֵ
INTER_LINEAR(���Բ�ֵ);
INTER_NEAREST--����ڲ�ֵ
INTER_AREA---�����ֵ
INTER_CUBIC--����������ֵ
INTER_LANCZOS4---Lanczos��ֵ
CV_WRAP_FILL_OUTLINES--����������ͼ�������,���
����������������ͼ��ı߽���,��ô���ǵ�ֵ ����Ϊfillval
CV_WRAP_INTERSE_MAP--��ʾMΪ���ͼ������ͼ��ķ��任;
��˿���ֱ�����������ز�ֵ;����,wrapAffine������M����õ�
���任;

����������,int���͵�borderMode,�߽�����ģʽ,Ĭ��ֵΪBORDER_CONSTANT;
���߸�����,const Scalar&���͵�borderValue,�ں㶨�ı߽������
ȡ��ֵ,Ĭ��ֵΪScalar(),��Ϊ0;

warpAffine������һ������cvGetQuardrangleSubPix()�ĺ�������,
���ǲ���ȫ��ͬ;WrapAffineҪ����������ͼ�����ͬ������������,
�и������Դ����(��˶�Сͼ��̫����)�������ͼ��Ĳ��ֿ���
��������;
��cvGetQuadrangleSubPix���Ծ�ȷ�ش�8λͼ������ȡ�ı��ε�
��������������,���бȽ�С��ϵͳ����,��������ȫ���ı����ͼ�������; 

�����ά��ת�任����:getRotationMatrix2D()
getRotationMatrix2D()�������ڼ����ά��ת�任����;�任�Ὣ
��ת����ӳ�䵽������;
C++:Mat getRotationMatrix2D(Point2f center,double angle,double scale );
��һ������:Point2f���͵�center,��ʾԴͼ�����ת����;
�ڶ�������:double���͵�angle,��ת�Ƕ�,�Ƕ�Ϊ��ֵ��ʾ����ʱ����ת(����ԭ�������Ͻ�); 
����������:double���͵�scale,����ϵ��;

a*b*(1-a)*center.x-b*center.y
-b*a*b*center.x+(1-a)*center.y

a=scale.cos(angle),
b=scale.sin(angle)
*/

#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int main()
{
	//����׼��
	//���������,��������������
	Point2f src_Triangle[3];
	Point2f dst_Triangle[3];

	Mat rotMat(2,3,CV_32FC1);
	Mat wrapMat(2,3,CV_32FC1);

	src_img = imread("lena.jpg", 1);//����ͼƬ����
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}

	dst_img = Mat::zeros(src_img.rows,src_img.cols,src_img.type());

	//����Դͼ���Ŀ��ͼ���ϵ�������Լ������任
	src_Triangle[0] = Point2f(0,0);
	src_Triangle[1] = Point2f(static_cast<float>(src_img.cols - 1), 0);
	src_Triangle[2] = Point2f(0, static_cast<float>(src_img.rows - 1));

	dst_Triangle[0] = Point2f(static_cast<float>(src_img.cols*0.0), static_cast<float>(src_img.rows *0.33));
	dst_Triangle[1] = Point2f(static_cast<float>(src_img.cols*0.65), static_cast<float>(src_img.rows *0.35));
	dst_Triangle[2] = Point2f(static_cast<float>(src_img.cols*0.15), static_cast<float>(src_img.rows *0.6));

	//��÷���任
	wrapMat = getAffineTransform(src_Triangle,dst_Triangle);
	//��Դͼ��Ӧ�øո���õķ���任
	warpAffine(src_img,dst_img,wrapMat,dst_img.size());

	//��ͼ��������ź�����ת
	//������ͼ�����ĵ�˳ʱ��ת50����������Ϊ0.6����ת����
	Point center = Point(dst_img.cols/2,dst_img.rows/2);
	double angle = -30.0;
	double scale = 0.8;
	//ͨ���������תϸ����Ϣ�����ת����
	rotMat = getRotationMatrix2D(center, angle, scale);
	//��ת�����ź��ͼ��
	warpAffine(dst_img, gray_img, rotMat, dst_img.size());
	imshow("src_img",src_img);
	imshow("dst_img",dst_img);
	imshow("gray_img",gray_img);

	imshow("src_img", src_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
