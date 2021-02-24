#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;

/*
Matx是个轻量级的Mat,必须在使用前规定好大小,如果一个2*3的float型的Matx,可以声明为Matx23f;
Vec是Matx的一个派生类,是一个一维的Matx,跟vactor很相似,
template<typename_Tp,int n> class Vec:public MatX<_TP,n,1>{...}

typedef Vec<uchar,2>Vec2b

Range类其实就是为了使opencv的作用更像MATLAB,比如Range::all(),


OpenCV中防止内存溢出的函数有alignPtr,alignSize,allocate,deallocate,
fastMalloc,fastFree

<math.h>里的一些函数使用起来很方便,有计算向量角度的函数fastAtan2,
计算立方根的函数cubeRoot,向上去整函数cvCeil,向下取整函数cvFloor,
四舍五入函数cvRound,cvIsInf判断自变量是否无穷大,cvIsNaN判断自变量是否不是一个数;

显示文字相关的函数有getTextSize,cvInitFont,putText
作图相关的函数:circle(绘制圆),clipLine,ellipse(椭圆),elipse2Poly,line(绘制直线),rectangle(绘制矩形),
polylines,类LineIterator;
填充相关的函数有fillConvexPoly,fillPoly(绘制填充的多边形);
OpenCV中RNG()函数的作用为初始化随机数状态的生成器

*/
int main()
{
	/*
	颜色空间转换:cvtColor()函数
	vtColor()函数是opencv里面的颜色空间转换函数,可以实现RGB颜色向HSV,HSI等颜色空间的转换,
	也可以转换为灰度图像;
	第一个参数为输入图像,第二个参数为输出图像,第三个参数为颜色空间转换的标识符,
	第四个参数为目标图像的通道数,如果该参数为0,表示目标图像取源图像的通道数
	C++:void cvtColor(InputArray src,OutputArray dst,int code,int dstCn=0)
	
	code 标识符;
	opencv2 的CV_2前缀的宏命名,被opencv3中的COLOR_式的宏命名前缀所取代;
	OPENCV图片的通道存储顺序是BGR,

	*/


	//颜色的表示:Scalar类
	/*
	Scalar()表示具有4个元素的数组，在opencv中被大量用于传递像素值,如RGB颜色值三个参数,
	对于Scalar函数来说，如果用不到第四个参数就不写出来;
	Scalar(a,b,c)//颜色参数表达式R=c,G=b,B=a
	Scalar类的源头为Scalar_类,Scalar_类是Vec4x的一个变种,
	Scalar起始就是Scalar_<double>,这就可以解释为什么很多函数的参数
	输入可以是Mat,也可以是Scalar
	*/
	//

	/*
	尺寸的表示:Size类
	Size类的源码:
	typedef Size_<int> Size2i;
	typedef Size2i Size;
	Size_是个类模板,Size_<int>表示其类内部的模板所代表的的类型为int;
	给已知的数据类型Size_<int>起个新名字,Size2i;
	又给已知的数据类型Size2i起个新名字,叫做Size;
	Size_<int> Size2i,Size这三个类型名等价

	Size_模板
	*/

	/*
	矩形的表示:Rect类
	Rect类的成员变量有x,y,width,height,分别为左上角点坐标,和矩形的宽高
	成员函数,Size()返回Size;area()返回矩形的面积;
	contains(Point)判断点是否在矩形内;inside(Rect)函数判断矩形是否在该矩形内;
	tl()返回左上角点坐标;br()返回右下角点坐标,
	如果求两个矩形的交集和并集;
	Rect rect=rect1&rect2;
	Rect rect=rect1|rect2;

	矩形进行平移操作和缩放操作
	Rect rectShift=rect+point;
	Rect rectScale=rect+size;
	
	*/

	//Point类数据结构表示了二维坐标系下的点,即由其图像坐标x和y指定的2D点
	Point point_1;
	point_1.x = 10;
	point_1.y = 8;
	Point point_2 = Point(11, 12);

	//typedef Point_<int> Point2i;
	//typedef Point2i Point;
	//typedef Point_<float> Point2f;
	//所以 Point_<int> Point2i,Point 互相等价;Point_<float>,Point2f互相等价;

	//二维点的定义和输出方法
	
	Point2f p(6, 2);
	//定义和输出三维点
	Point3f p_3f(8, 2, 0);

	//定义和输出基于Mat的std::vector
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
