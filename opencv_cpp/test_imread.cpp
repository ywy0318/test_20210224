#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;

/*
Imread flags.

Enumerator
IMREAD_UNCHANGED
If set, return the loaded image as is (with alpha channel, otherwise it gets cropped).

IMREAD_GRAYSCALE
If set, always convert image to the single channel grayscale image.

IMREAD_COLOR
If set, always convert image to the 3 channel BGR color image.

IMREAD_ANYDEPTH
If set, return 16-bit/32-bit image when the input has the corresponding depth, otherwise convert it to 8-bit.

IMREAD_ANYCOLOR
If set, the image is read in any possible color format.

IMREAD_LOAD_GDAL
If set, use the gdal driver for loading the image.

IMREAD_UNCHANGED ：不进行转化，比如保存为了16位的图片，读取出来仍然为16位。
IMREAD_GRAYSCALE ：进行转化为灰度图，比如保存为了16位的图片，读取出来为8位，类型为CV_8UC1。

IMREAD_COLOR ：进行转化为三通道图像。

IMREAD_ANYDEPTH ：如果图像深度为16位则读出为16位，32位则读出为32位，其余的转化为8位。

IMREAD_ANYCOLOR ：

IMREAD_LOAD_GDAL ：使用GDAL驱动读取文件，GDAL(Geospatial Data Abstraction Library)
是一个在X/MIT许可协议下的开源栅格空间数据转换库。
它利用抽象数据模型来表达所支持的各种文件格式。它还有一系列命令行工具来进行数据转换和处理。


IMREAD_UNCHANGED:已经废除，不再使用
IMREAD_GRAYSCALE=0:将加载的图像转换为单通道灰度图。
IMREAD_COLOR=1:函数默认值，将图像转化为三通道BGR彩色图像
IMREAD_ANYDEPTH=2:若载入图像深度为16位或32为就返回其对应深度，否则将图像转换为8位图像
IMREAD_ANYCOLOR=4:保持图像原格式，可以读取任意可能的彩色格式
IMREAD_LOAD_GDAL=8:使用文件格式驱动加载图像，在现阶段用处不多。
在使用flags时可能会同时使用多种flags，如果发生冲突，函数将自动采用较小数字值对应的加载方式。如：IMREAD_COLOR | IMREAD_ANYCOLOR，则imread()函数将自动载入IMREAD_COLOR所对应的3通道彩色图。如果要载入图像原本的彩色格式和深度，则可以使用: IMREAD_ANYCOLOR | IMREAD_ANYDEPTH。
也可以利用flags是int类型的变量输入其他值以达到加载特定图像格式的目的，但符合一下标准：
flags > 0:返回一个三通道的彩色图像
flags = 0: 返回灰度图像
flags < 0: 返回包含Alpha通道的图像。
图像在默认情况下不是从Alpha通道进来的，如果需要载入Alpha通道的话就取负值。


*/


/*
Mat imread(const String&filename,int flag =IMREAD_COLOR)
第一个参数是图片的绝对地址，第二个参数表示图片读入的方式
(flag可以缺省，缺省时为1)
flag>0表示以彩色方式读取图片
flag=0表示以灰度图方式读入图片
flag<0表示以图片本来的格式读入图片


/***********************************************************************************************************************************
文件说明:
1）OpenCv2.X系列，cv::Mat类源码解读
2）相似的数据类型：OpenCv1.x中的IplImage,CvMat
时间地点:
陕西师范大学 2017.4.13
作     者:
九月
************************************************************************************************************************************/

/*
class CV_EXPORTS Mat
{
public:
	/*****************************************************************************************************************************
	模块说明:
	基础图像容器类Mat类的----构造函数
	具体说明:
	1)我们可以通过图像矩阵容器类Mat的构造函数，在实例化Mat类的类对象的时候，初始化相关的图像属性
	2)可以显式的使用Mat类的构造函数创建Mat类的类对象
	******************************************************************************************************************************/
/*	Mat();                                      //【1】图像容器类Mat的默认构造函数
	Mat(int rows, int cols, int type);         //【2】有参构造函数,实例化一个二维的图像容器类，指定Mat的行数和列数，以及存储元素的数据
											   //类型和图像的通道数;具体的图像像素点数据元素类型和通道数有：CV_8UC1、CV_64FC3、CV_32SC
	Mat(Size size, int type);                   //【3】同上，只不过这个是通过Size类来指定图像的高度和宽度(rows*cols)
												//【4】构造一个指定大小(高*宽==rows*cols),指定类型(每一个像素点的数据类型和图像通道数)，
												//     并且使用指定数据初始化的图像矩阵
	Mat(int rows, int cols, int type, const Scalar& s);
	Mat(Size size, int type, const Scalar& s); //【5】同上
	Mat(int ndims, const int* sizes, int type);//【6】构造一个指定大小和指定类型的N维图像矩阵
											   //【7】构造一个指定大小，指定类型，并且对矩阵使用指定数值进行初始化的N维矩阵
	Mat(int ndims, const int* sizes, int type, const Scalar& s);
	Mat(const Mat& m);                          //【8】复制构造函数
												//【9】为用户使用的矩阵体构造一个矩阵头
	Mat(int rows, int cols, int type, void* data, size_t step = AUTO_STEP);
	//【10】构造矩阵头----create a matrix header
	Mat(Size size, int type, void* data, size_t step = AUTO_STEP);
	//【11】创建矩阵头
	Mat(int ndims, const int* sizes, int type, void* data, const size_t* steps = 0);
	//【12】为一个大矩阵体的一部分创建一个矩阵头
	Mat(const Mat& m, const Range& rowRange, const Range& colRange = Range::all());
	Mat(const Mat& m, const Rect& roi);
	Mat(const Mat& m, const Range* ranges);
	//【13】将旧式风格的矩阵CvMat*转换为一个新式的矩阵Mat，但是默认的并没有拷贝矩阵体
	Mat(const CvMat* m, bool copyData = false);
	//【14】将旧式风格的N维矩阵CvMatND*转换为新式矩阵Mat，矩阵体没有复制
	Mat(const CvMatND* m, bool copyData = false);
	//【15】将旧式风格的图像容器IplImage*转换为Mat类型,矩阵体没有被复制
	Mat(const IplImage* img, bool copyData = false);
	//【16】从std::vector构件矩阵，矩阵体被复制或者没有被复制
	template<typename _Tp> explicit Mat(const vector<_Tp>& vec, bool copyData = false);
	//【17】从cv::Vec构件矩阵，矩阵体被默认的一起复制过来
	template<typename _Tp, int n> explicit Mat(const Vec<_Tp, n>& vec, bool copyData = true);
	//【18】从cv::Matx构件矩阵，矩阵体被默认的一起复制过来
	template<typename _Tp, int m, int n> explicit Mat(const Matx<_Tp, m, n>& mtx, bool copyData = true);
	//【19】从二维点构建矩阵
	template<typename _Tp> explicit Mat(const Point_<_Tp>& pt, bool copyData = true);
	//【20】从三维点构建矩阵
	template<typename _Tp> explicit Mat(const Point3_<_Tp>& pt, bool copyData = true);
	//【21】builds matrix from comma initializer
	template<typename _Tp> explicit Mat(const MatCommaInitializer_<_Tp>& commaInitializer);
	//【22】从GpuMat下载数据
	explicit Mat(const gpu::GpuMat& m);
	//【23】图像容器类Mat的析构函数
	~Mat();
	Mat& operator = (const Mat& m);
	Mat& operator = (const MatExpr& expr);

	//! returns a new matrix header for the specified row
	Mat row(int y) const;
	//! returns a new matrix header for the specified column
	Mat col(int x) const;
	//! ... for the specified row span
	Mat rowRange(int startrow, int endrow) const;
	Mat rowRange(const Range& r) const;
	//! ... for the specified column span
	Mat colRange(int startcol, int endcol) const;
	Mat colRange(const Range& r) const;
	//! ... for the specified diagonal
	// (d=0 - the main diagonal,
	//  >0 - a diagonal from the lower half,
	//  <0 - a diagonal from the upper half)
	Mat diag(int d = 0) const;
	//! constructs a square diagonal matrix which main diagonal is vector "d"
	static Mat diag(const Mat& d);
	//【24】返回一个深复制的矩阵
	Mat clone() const;
	//【25】复制一个矩阵到m,调用之前先调用m.create(this->size(), this->type())
	void copyTo(OutputArray m) const;
	//【26】复制复制矩阵的元素到m,并且这些m矩阵的原始的元素被非零的掩膜元素标记
	void copyTo(OutputArray m, InputArray mask) const;
	//【27】将矩阵转换为另一种数据类型的矩阵(图像元素的数据类型可选)
	void convertTo(OutputArray m, int rtype, double alpha = 1, double beta = 0) const;
	void assignTo(Mat& m, int type = -1) const;
	//【28】将每一个矩阵的元素设置为s
	Mat& operator = (const Scalar& s);
	//! sets some of the matrix elements to s, according to the mask
	Mat& setTo(InputArray value, InputArray mask = noArray());
	//! creates alternative matrix header for the same data, with different
	// number of channels and/or different number of rows. see cvReshape.
	Mat reshape(int cn, int rows = 0) const;
	Mat reshape(int cn, int newndims, const int* newsz) const;

	//! matrix transposition by means of matrix expressions
	MatExpr t() const;
	//! matrix inversion by means of matrix expressions
	MatExpr inv(int method = DECOMP_LU) const;
	//! per-element matrix multiplication by means of matrix expressions
	MatExpr mul(InputArray m, double scale = 1) const;

	//! computes cross-product of 2 3D vectors
	Mat cross(InputArray m) const;
	//! computes dot-product
	double dot(InputArray m) const;
	/*****************************************************************************************************************************
	模块说明:
	Matlab风格，矩阵的初始化
	******************************************************************************************************************************/
/*	//【29】实例化一个指定大小，指定类型、初始值为0的矩阵对象
	static MatExpr zeros(int rows, int cols, int type);
	static MatExpr zeros(Size size, int type);
	static MatExpr zeros(int ndims, const int* sz, int type);
	//【30】实例化一个指定大小，指定类型、初始值为1的矩阵
	static MatExpr ones(int rows, int cols, int type);
	static MatExpr ones(Size size, int type);
	static MatExpr ones(int ndims, const int* sz, int type);
	//【31】实例化一个指定大小，指定类型的单位矩阵
	static MatExpr eye(int rows, int cols, int type);
	static MatExpr eye(Size size, int type);
	/*****************************************************************************************************************************
	模块说明:
	创建一个新的矩阵体
	******************************************************************************************************************************/
/*	void create(int rows, int cols, int type);
	void create(Size size, int type);
	void create(int ndims, const int* sizes, int type);

	//! increases the reference counter; use with care to avoid memleaks
	void addref();
	//! decreases reference counter;
	// deallocates the data when reference counter reaches 0.
	void release();

	//! deallocates the matrix data
	void deallocate();
	//! internal use function; properly re-allocates _size, _step arrays
	void copySize(const Mat& m);

	//! reserves enough space to fit sz hyper-planes
	void reserve(size_t sz);
	//! resizes matrix to the specified number of hyper-planes
	void resize(size_t sz);
	//! resizes matrix to the specified number of hyper-planes; initializes the newly added elements
	void resize(size_t sz, const Scalar& s);
	//! internal function
	void push_back_(const void* elem);
	//! adds element to the end of 1d matrix (or possibly multiple elements when _Tp=Mat)
	template<typename _Tp> void push_back(const _Tp& elem);
	template<typename _Tp> void push_back(const Mat_<_Tp>& elem);
	void push_back(const Mat& m);
	//! removes several hyper-planes from bottom of the matrix
	void pop_back(size_t nelems = 1);

	//! locates matrix header within a parent matrix. See below
	void locateROI(Size& wholeSize, Point& ofs) const;
	//! moves/resizes the current matrix ROI inside the parent matrix.
	Mat& adjustROI(int dtop, int dbottom, int dleft, int dright);
	//! extracts a rectangular sub-matrix
	// (this is a generalized form of row, rowRange etc.)
	Mat operator()(Range rowRange, Range colRange) const;
	Mat operator()(const Rect& roi) const;
	Mat operator()(const Range* ranges) const;

	//! converts header to CvMat; no data is copied
	//【32】将Mat的矩阵头转换为CvMat类型
	operator CvMat() const;
	operator CvMatND() const;
	//【33】将Mat的矩阵头转换为IplImage类型
	operator IplImage() const;

	template<typename _Tp> operator vector<_Tp>() const;
	template<typename _Tp, int n> operator Vec<_Tp, n>() const;
	template<typename _Tp, int m, int n> operator Matx<_Tp, m, n>() const;

	//! returns true iff the matrix data is continuous
	// (i.e. when there are no gaps between successive rows).
	// similar to CV_IS_MAT_CONT(cvmat->type)
	bool isContinuous() const;

	//! returns true if the matrix is a submatrix of another matrix
	bool isSubmatrix() const;
	/*****************************************一些属性****************************************************************************/
/*
	//! returns element size in bytes,
	// similar to CV_ELEM_SIZE(cvmat->type)
	//【34】返回图像中，每一个图像元素的大小(单位是字节，比如，int---4)
	size_t elemSize() const;
	//! returns the size of element channel in bytes.
	size_t elemSize1() const;
	//【35】返回元素的类型，类似CV_MAT_TYPE()
	int type() const;
	//【36】返回元素的深度，类似CV_MAT_DEPTH()
	int depth() const;
	//【37】返回元素的通道数，类此CV_MAT_CN()
	int channels() const;
	//【38】返回图像中每一行指针移动的个数step/elemSize1()
	size_t step1(int i = 0) const;
	//【39】判断矩阵是否为空，如果为空，则返回True
	bool empty() const;
	//【40】返回矩阵图像中，元素点的个数
	size_t total() const;

	//! returns N if the matrix is 1-channel (N x ptdim) or ptdim-channel (1 x N) or (N x 1); negative number otherwise
	int checkVector(int elemChannels, int depth = -1, bool requireContinuous = true) const;
	//【41】返回图像矩阵中，指定行的首地址
	uchar* ptr(int i0 = 0);
	const uchar* ptr(int i0 = 0) const;
	//【42】返回矩阵图像中，指定点的首地址
	uchar* ptr(int i0, int i1);
	const uchar* ptr(int i0, int i1) const;
	uchar* ptr(int i0, int i1, int i2);
	const uchar* ptr(int i0, int i1, int i2) const;

	//! returns pointer to the matrix element
	uchar* ptr(const int* idx);
	//! returns read-only pointer to the matrix element
	const uchar* ptr(const int* idx) const;

	template<int n> uchar* ptr(const Vec<int, n>& idx);
	template<int n> const uchar* ptr(const Vec<int, n>& idx) const;

	//! template version of the above method
	template<typename _Tp> _Tp* ptr(int i0 = 0);
	template<typename _Tp> const _Tp* ptr(int i0 = 0) const;

	template<typename _Tp> _Tp* ptr(int i0, int i1);
	template<typename _Tp> const _Tp* ptr(int i0, int i1) const;

	template<typename _Tp> _Tp* ptr(int i0, int i1, int i2);
	template<typename _Tp> const _Tp* ptr(int i0, int i1, int i2) const;

	template<typename _Tp> _Tp* ptr(const int* idx);
	template<typename _Tp> const _Tp* ptr(const int* idx) const;

	template<typename _Tp, int n> _Tp* ptr(const Vec<int, n>& idx);
	template<typename _Tp, int n> const _Tp* ptr(const Vec<int, n>& idx) const;

	/*****************************************************************************************************************************
	模块说明:
	返回图像矩阵中指定元素的地址(引用)
	******************************************************************************************************************************/
	/*template<typename _Tp> _Tp& at(int i0 = 0);
	template<typename _Tp> const _Tp& at(int i0 = 0) const;

	template<typename _Tp> _Tp& at(int i0, int i1);
	template<typename _Tp> const _Tp& at(int i0, int i1) const;

	template<typename _Tp> _Tp& at(int i0, int i1, int i2);
	template<typename _Tp> const _Tp& at(int i0, int i1, int i2) const;

	template<typename _Tp> _Tp& at(const int* idx);
	template<typename _Tp> const _Tp& at(const int* idx) const;

	template<typename _Tp, int n> _Tp& at(const Vec<int, n>& idx);
	template<typename _Tp, int n> const _Tp& at(const Vec<int, n>& idx) const;

	//! special versions for 2D arrays (especially convenient for referencing image pixels)
	template<typename _Tp> _Tp& at(Point pt);
	template<typename _Tp> const _Tp& at(Point pt) const;

	//! template methods for iteration over matrix elements.
	// the iterators take care of skipping gaps in the end of rows (if any)
	template<typename _Tp> MatIterator_<_Tp> begin();
	template<typename _Tp> MatIterator_<_Tp> end();
	template<typename _Tp> MatConstIterator_<_Tp> begin() const;
	template<typename _Tp> MatConstIterator_<_Tp> end() const;

	enum { MAGIC_VAL = 0x42FF0000, AUTO_STEP = 0, CONTINUOUS_FLAG = CV_MAT_CONT_FLAG, SUBMATRIX_FLAG = CV_SUBMAT_FLAG };
	/*****************************************************************************************************************************
	模块说明:
	图像矩阵的属性
	******************************************************************************************************************************/
/*	int flags;                                           //【43】图像矩阵是否连续
	int dims;                                            //【44】图像矩阵的维数dims>=2
	int rows, cols;                                      //【45】图像矩阵的行和列数
														 //【46】指向图像矩阵矩阵体的指针
	uchar* data;

	//! pointer to the reference counter;
	// when matrix points to user-allocated data, the pointer is NULL
	int* refcount;

	//! helper fields used in locateROI and adjustROI
	uchar* datastart;
	uchar* dataend;
	uchar* datalimit;

	//! custom allocator
	MatAllocator* allocator;
	*/
/*
	struct CV_EXPORTS MSize
	{
		MSize(int* _p);
		Size operator()() const;
		const int& operator[](int i) const;
		int& operator[](int i);
		operator const int*() const;
		bool operator == (const MSize& sz) const;
		bool operator != (const MSize& sz) const;

		int* p;
	};

	struct CV_EXPORTS MStep
	{
		MStep();
		MStep(size_t s);
		const size_t& operator[](int i) const;
		size_t& operator[](int i);
		operator size_t() const;
		MStep& operator = (size_t s);

		size_t* p;
		size_t buf[2];
	protected:
		MStep& operator = (const MStep&);
	};

	MSize size;
	MStep step;

protected:
	void initEmpty();
};

*/



int main(int argc, char* argv[])
{
	 Mat resimg;//mat是opencv基本的数据结构，定义一个图像矩阵类型
	//--1--双右斜线法
	string imgpath0="E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	//--2--双左斜线法
	string imgpath1="E://Visual Studio 2010//Projects//opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--3--单左斜线法
	string imgpath2 = "E:/Visual Studio 2010/Projects/opencv_2018_12_21/opencv_2018_12_21/1.jpg";
	//--4--以上三种混合
	string imgpath3 = "E:/Visual Studio 2010//Projects\\opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--5--相对路径法
	string imgpath4 = "1.jpg";
	//--6--命令行参数法
	//string imgpath5 = argv[1];
	
	Mat img = imread(imgpath4,1);//读入图片数据
	if (img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//cout<<img.
	cout << " open or find the img" << endl;
	cout <<"img.channels："<<img.channels() << endl;
	/*
		// similar to CV_ELEM_SIZE(cvmat->type)
	//【34】返回图像中，每一个图像元素的大小(单位是字节，比如，int---4)
	size_t elemSize() const;
	//! returns the size of element channel in bytes.
	size_t elemSize1() const;
	//【35】返回元素的类型，类似CV_MAT_TYPE()
	int type() const;
	//【36】返回元素的深度，类似CV_MAT_DEPTH()
	int depth() const;
	//【37】返回元素的通道数，类此CV_MAT_CN()
	int channels() const;
	//【38】返回图像中每一行指针移动的个数step/elemSize1()
	size_t step1(int i = 0) const;
	//【39】判断矩阵是否为空，如果为空，则返回True
	bool empty() const;
	//【40】返回矩阵图像中，元素点的个数
	size_t total() const;
	
	*/
	cout <<"img.elemSize:" << img.elemSize()<< endl;
	cout << "img.type:" << img.type() << endl;
	cout << "img.depth:" << img.depth() << endl;
	cout << "img.step1:" << img.step1() << endl;

	namedWindow("IMG",WINDOW_AUTOSIZE);//创建一个窗口
	imshow("IMG",img);
	/* 翻转模式，flipCode == 0垂直翻转（沿X轴翻转），
		flipCode>0水平翻转（沿Y轴翻转），
		flipCode<0水平垂直翻转（先沿X轴翻转，再沿Y轴翻转，等价于旋转180°） */
	flip(img,resimg,1);

	/*
	WINDOW_NORMAL:可以改变窗口大小（无限制），也可将一个满屏窗口转换成常用大小； 
WINDOW_AUTOSIZE：程序会根据呈现内容自动调整大小且不能手动更改窗口大小； 
WINDOW_OPENGL：创建支持OpenGL的窗口； 
WINDOW_FULLSCREEN：创建一个充满屏幕的窗口； 
WINDOW_FREETATIO：图像将尽可能展开; 
WINDOW_KEEPRATIO：图像比例受到约束。
	*/

	namedWindow("水平翻转",WINDOW_AUTOSIZE);
	imshow("水平翻转",resimg);

	flip(img,resimg,0);
	namedWindow("垂直翻转",WINDOW_AUTOSIZE);
	imshow("垂直翻转",resimg);

	flip(img,resimg,-1);
	namedWindow("水平垂直翻转",WINDOW_AUTOSIZE);
	imshow("水平垂直翻转",resimg);

	waitKey(0);
	system("pause");
	return 0;
}