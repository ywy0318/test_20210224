#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;

/*
Matx�Ǹ���������Mat,������ʹ��ǰ�涨�ô�С,���һ��2*3��float�͵�Matx,��������ΪMatx23f;
Vec��Matx��һ��������,��һ��һά��Matx,��vactor������,
template<typename_Tp,int n> class Vec:public MatX<_TP,n,1>{...}

typedef Vec<uchar,2>Vec2b

Range����ʵ����Ϊ��ʹopencv�����ø���MATLAB,����Range::all(),


OpenCV�з�ֹ�ڴ�����ĺ�����alignPtr,alignSize,allocate,deallocate,
fastMalloc,fastFree

<math.h>���һЩ����ʹ�������ܷ���,�м��������Ƕȵĺ���fastAtan2,
�����������ĺ���cubeRoot,����ȥ������cvCeil,����ȡ������cvFloor,
�������뺯��cvRound,cvIsInf�ж��Ա����Ƿ������,cvIsNaN�ж��Ա����Ƿ���һ����;

��ʾ������صĺ�����getTextSize,cvInitFont,putText
��ͼ��صĺ���:circle(����Բ),clipLine,ellipse(��Բ),elipse2Poly,line(����ֱ��),rectangle(���ƾ���),
polylines,��LineIterator;
�����صĺ�����fillConvexPoly,fillPoly(�������Ķ����);
OpenCV��RNG()����������Ϊ��ʼ�������״̬��������

*/
int main()
{
	/*
	��ɫ�ռ�ת��:cvtColor()����
	vtColor()������opencv�������ɫ�ռ�ת������,����ʵ��RGB��ɫ��HSV,HSI����ɫ�ռ��ת��,
	Ҳ����ת��Ϊ�Ҷ�ͼ��;
	��һ������Ϊ����ͼ��,�ڶ�������Ϊ���ͼ��,����������Ϊ��ɫ�ռ�ת���ı�ʶ��,
	���ĸ�����ΪĿ��ͼ���ͨ����,����ò���Ϊ0,��ʾĿ��ͼ��ȡԴͼ���ͨ����
	C++:void cvtColor(InputArray src,OutputArray dst,int code,int dstCn=0)
	
	code ��ʶ��;
	opencv2 ��CV_2ǰ׺�ĺ�����,��opencv3�е�COLOR_ʽ�ĺ�����ǰ׺��ȡ��;
	OPENCVͼƬ��ͨ���洢˳����BGR,

	*/


	//��ɫ�ı�ʾ:Scalar��
	/*
	Scalar()��ʾ����4��Ԫ�ص����飬��opencv�б��������ڴ�������ֵ,��RGB��ɫֵ��������,
	����Scalar������˵������ò������ĸ������Ͳ�д����;
	Scalar(a,b,c)//��ɫ�������ʽR=c,G=b,B=a
	Scalar���ԴͷΪScalar_��,Scalar_����Vec4x��һ������,
	Scalar��ʼ����Scalar_<double>,��Ϳ��Խ���Ϊʲô�ܶຯ���Ĳ���
	���������Mat,Ҳ������Scalar
	*/
	//

	/*
	�ߴ�ı�ʾ:Size��
	Size���Դ��:
	typedef Size_<int> Size2i;
	typedef Size2i Size;
	Size_�Ǹ���ģ��,Size_<int>��ʾ�����ڲ���ģ��������ĵ�����Ϊint;
	����֪����������Size_<int>���������,Size2i;
	�ָ���֪����������Size2i���������,����Size;
	Size_<int> Size2i,Size�������������ȼ�

	Size_ģ��
	*/

	/*
	���εı�ʾ:Rect��
	Rect��ĳ�Ա������x,y,width,height,�ֱ�Ϊ���Ͻǵ�����,�;��εĿ��
	��Ա����,Size()����Size;area()���ؾ��ε����;
	contains(Point)�жϵ��Ƿ��ھ�����;inside(Rect)�����жϾ����Ƿ��ڸþ�����;
	tl()�������Ͻǵ�����;br()�������½ǵ�����,
	������������εĽ����Ͳ���;
	Rect rect=rect1&rect2;
	Rect rect=rect1|rect2;

	���ν���ƽ�Ʋ��������Ų���
	Rect rectShift=rect+point;
	Rect rectScale=rect+size;
	
	*/

	//Point�����ݽṹ��ʾ�˶�ά����ϵ�µĵ�,������ͼ������x��yָ����2D��
	Point point_1;
	point_1.x = 10;
	point_1.y = 8;
	Point point_2 = Point(11, 12);

	//typedef Point_<int> Point2i;
	//typedef Point2i Point;
	//typedef Point_<float> Point2f;
	//���� Point_<int> Point2i,Point ����ȼ�;Point_<float>,Point2f����ȼ�;

	//��ά��Ķ�����������
	
	Point2f p(6, 2);
	//����������ά��
	Point3f p_3f(8, 2, 0);

	//������������Mat��std::vector
	vector<float>v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);

	vector<Point2f> points(20);
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i] = Point2f((float)(i * 5), (float)(i % 7));
	}

	cout << "Point3f=" << p_3f << ";\n" << endl;
	cout << "Point2f=" << p << ";\n" << endl;

	cout << "vector<float> v=" << Mat(v) << ";\n" << endl;
	cout << "vector<Point2f> points(20)=" << points << ";\n";

	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
