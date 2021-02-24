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

IMREAD_UNCHANGED ��������ת�������籣��Ϊ��16λ��ͼƬ����ȡ������ȻΪ16λ��
IMREAD_GRAYSCALE ������ת��Ϊ�Ҷ�ͼ�����籣��Ϊ��16λ��ͼƬ����ȡ����Ϊ8λ������ΪCV_8UC1��

IMREAD_COLOR ������ת��Ϊ��ͨ��ͼ��

IMREAD_ANYDEPTH �����ͼ�����Ϊ16λ�����Ϊ16λ��32λ�����Ϊ32λ�������ת��Ϊ8λ��

IMREAD_ANYCOLOR ��

IMREAD_LOAD_GDAL ��ʹ��GDAL������ȡ�ļ���GDAL(Geospatial Data Abstraction Library)
��һ����X/MIT���Э���µĿ�Դդ��ռ�����ת���⡣
�����ó�������ģ���������֧�ֵĸ����ļ���ʽ��������һϵ�������й�������������ת���ʹ���


IMREAD_UNCHANGED:�Ѿ��ϳ�������ʹ��
IMREAD_GRAYSCALE=0:�����ص�ͼ��ת��Ϊ��ͨ���Ҷ�ͼ��
IMREAD_COLOR=1:����Ĭ��ֵ����ͼ��ת��Ϊ��ͨ��BGR��ɫͼ��
IMREAD_ANYDEPTH=2:������ͼ�����Ϊ16λ��32Ϊ�ͷ������Ӧ��ȣ�����ͼ��ת��Ϊ8λͼ��
IMREAD_ANYCOLOR=4:����ͼ��ԭ��ʽ�����Զ�ȡ������ܵĲ�ɫ��ʽ
IMREAD_LOAD_GDAL=8:ʹ���ļ���ʽ��������ͼ�����ֽ׶��ô����ࡣ
��ʹ��flagsʱ���ܻ�ͬʱʹ�ö���flags�����������ͻ���������Զ����ý�С����ֵ��Ӧ�ļ��ط�ʽ���磺IMREAD_COLOR | IMREAD_ANYCOLOR����imread()�������Զ�����IMREAD_COLOR����Ӧ��3ͨ����ɫͼ�����Ҫ����ͼ��ԭ���Ĳ�ɫ��ʽ����ȣ������ʹ��: IMREAD_ANYCOLOR | IMREAD_ANYDEPTH��
Ҳ��������flags��int���͵ı�����������ֵ�Դﵽ�����ض�ͼ���ʽ��Ŀ�ģ�������һ�±�׼��
flags > 0:����һ����ͨ���Ĳ�ɫͼ��
flags = 0: ���ػҶ�ͼ��
flags < 0: ���ذ���Alphaͨ����ͼ��
ͼ����Ĭ������²��Ǵ�Alphaͨ�������ģ������Ҫ����Alphaͨ���Ļ���ȡ��ֵ��


*/


/*
Mat imread(const String&filename,int flag =IMREAD_COLOR)
��һ��������ͼƬ�ľ��Ե�ַ���ڶ���������ʾͼƬ����ķ�ʽ
(flag����ȱʡ��ȱʡʱΪ1)
flag>0��ʾ�Բ�ɫ��ʽ��ȡͼƬ
flag=0��ʾ�ԻҶ�ͼ��ʽ����ͼƬ
flag<0��ʾ��ͼƬ�����ĸ�ʽ����ͼƬ


/***********************************************************************************************************************************
�ļ�˵��:
1��OpenCv2.Xϵ�У�cv::Mat��Դ����
2�����Ƶ��������ͣ�OpenCv1.x�е�IplImage,CvMat
ʱ��ص�:
����ʦ����ѧ 2017.4.13
��     ��:
����
************************************************************************************************************************************/

/*
class CV_EXPORTS Mat
{
public:
	/*****************************************************************************************************************************
	ģ��˵��:
	����ͼ��������Mat���----���캯��
	����˵��:
	1)���ǿ���ͨ��ͼ�����������Mat�Ĺ��캯������ʵ����Mat���������ʱ�򣬳�ʼ����ص�ͼ������
	2)������ʽ��ʹ��Mat��Ĺ��캯������Mat��������
	******************************************************************************************************************************/
/*	Mat();                                      //��1��ͼ��������Mat��Ĭ�Ϲ��캯��
	Mat(int rows, int cols, int type);         //��2���вι��캯��,ʵ����һ����ά��ͼ�������ָ࣬��Mat���������������Լ��洢Ԫ�ص�����
											   //���ͺ�ͼ���ͨ����;�����ͼ�����ص�����Ԫ�����ͺ�ͨ�����У�CV_8UC1��CV_64FC3��CV_32SC
	Mat(Size size, int type);                   //��3��ͬ�ϣ�ֻ���������ͨ��Size����ָ��ͼ��ĸ߶ȺͿ��(rows*cols)
												//��4������һ��ָ����С(��*��==rows*cols),ָ������(ÿһ�����ص���������ͺ�ͼ��ͨ����)��
												//     ����ʹ��ָ�����ݳ�ʼ����ͼ�����
	Mat(int rows, int cols, int type, const Scalar& s);
	Mat(Size size, int type, const Scalar& s); //��5��ͬ��
	Mat(int ndims, const int* sizes, int type);//��6������һ��ָ����С��ָ�����͵�Nάͼ�����
											   //��7������һ��ָ����С��ָ�����ͣ����ҶԾ���ʹ��ָ����ֵ���г�ʼ����Nά����
	Mat(int ndims, const int* sizes, int type, const Scalar& s);
	Mat(const Mat& m);                          //��8�����ƹ��캯��
												//��9��Ϊ�û�ʹ�õľ����幹��һ������ͷ
	Mat(int rows, int cols, int type, void* data, size_t step = AUTO_STEP);
	//��10���������ͷ----create a matrix header
	Mat(Size size, int type, void* data, size_t step = AUTO_STEP);
	//��11����������ͷ
	Mat(int ndims, const int* sizes, int type, void* data, const size_t* steps = 0);
	//��12��Ϊһ����������һ���ִ���һ������ͷ
	Mat(const Mat& m, const Range& rowRange, const Range& colRange = Range::all());
	Mat(const Mat& m, const Rect& roi);
	Mat(const Mat& m, const Range* ranges);
	//��13������ʽ���ľ���CvMat*ת��Ϊһ����ʽ�ľ���Mat������Ĭ�ϵĲ�û�п���������
	Mat(const CvMat* m, bool copyData = false);
	//��14������ʽ����Nά����CvMatND*ת��Ϊ��ʽ����Mat��������û�и���
	Mat(const CvMatND* m, bool copyData = false);
	//��15������ʽ����ͼ������IplImage*ת��ΪMat����,������û�б�����
	Mat(const IplImage* img, bool copyData = false);
	//��16����std::vector�������󣬾����屻���ƻ���û�б�����
	template<typename _Tp> explicit Mat(const vector<_Tp>& vec, bool copyData = false);
	//��17����cv::Vec�������󣬾����屻Ĭ�ϵ�һ���ƹ���
	template<typename _Tp, int n> explicit Mat(const Vec<_Tp, n>& vec, bool copyData = true);
	//��18����cv::Matx�������󣬾����屻Ĭ�ϵ�һ���ƹ���
	template<typename _Tp, int m, int n> explicit Mat(const Matx<_Tp, m, n>& mtx, bool copyData = true);
	//��19���Ӷ�ά�㹹������
	template<typename _Tp> explicit Mat(const Point_<_Tp>& pt, bool copyData = true);
	//��20������ά�㹹������
	template<typename _Tp> explicit Mat(const Point3_<_Tp>& pt, bool copyData = true);
	//��21��builds matrix from comma initializer
	template<typename _Tp> explicit Mat(const MatCommaInitializer_<_Tp>& commaInitializer);
	//��22����GpuMat��������
	explicit Mat(const gpu::GpuMat& m);
	//��23��ͼ��������Mat����������
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
	//��24������һ����Ƶľ���
	Mat clone() const;
	//��25������һ������m,����֮ǰ�ȵ���m.create(this->size(), this->type())
	void copyTo(OutputArray m) const;
	//��26�����Ƹ��ƾ����Ԫ�ص�m,������Щm�����ԭʼ��Ԫ�ر��������ĤԪ�ر��
	void copyTo(OutputArray m, InputArray mask) const;
	//��27��������ת��Ϊ��һ���������͵ľ���(ͼ��Ԫ�ص��������Ϳ�ѡ)
	void convertTo(OutputArray m, int rtype, double alpha = 1, double beta = 0) const;
	void assignTo(Mat& m, int type = -1) const;
	//��28����ÿһ�������Ԫ������Ϊs
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
	ģ��˵��:
	Matlab��񣬾���ĳ�ʼ��
	******************************************************************************************************************************/
/*	//��29��ʵ����һ��ָ����С��ָ�����͡���ʼֵΪ0�ľ������
	static MatExpr zeros(int rows, int cols, int type);
	static MatExpr zeros(Size size, int type);
	static MatExpr zeros(int ndims, const int* sz, int type);
	//��30��ʵ����һ��ָ����С��ָ�����͡���ʼֵΪ1�ľ���
	static MatExpr ones(int rows, int cols, int type);
	static MatExpr ones(Size size, int type);
	static MatExpr ones(int ndims, const int* sz, int type);
	//��31��ʵ����һ��ָ����С��ָ�����͵ĵ�λ����
	static MatExpr eye(int rows, int cols, int type);
	static MatExpr eye(Size size, int type);
	/*****************************************************************************************************************************
	ģ��˵��:
	����һ���µľ�����
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
	//��32����Mat�ľ���ͷת��ΪCvMat����
	operator CvMat() const;
	operator CvMatND() const;
	//��33����Mat�ľ���ͷת��ΪIplImage����
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
	/*****************************************һЩ����****************************************************************************/
/*
	//! returns element size in bytes,
	// similar to CV_ELEM_SIZE(cvmat->type)
	//��34������ͼ���У�ÿһ��ͼ��Ԫ�صĴ�С(��λ���ֽڣ����磬int---4)
	size_t elemSize() const;
	//! returns the size of element channel in bytes.
	size_t elemSize1() const;
	//��35������Ԫ�ص����ͣ�����CV_MAT_TYPE()
	int type() const;
	//��36������Ԫ�ص���ȣ�����CV_MAT_DEPTH()
	int depth() const;
	//��37������Ԫ�ص�ͨ���������CV_MAT_CN()
	int channels() const;
	//��38������ͼ����ÿһ��ָ���ƶ��ĸ���step/elemSize1()
	size_t step1(int i = 0) const;
	//��39���жϾ����Ƿ�Ϊ�գ����Ϊ�գ��򷵻�True
	bool empty() const;
	//��40�����ؾ���ͼ���У�Ԫ�ص�ĸ���
	size_t total() const;

	//! returns N if the matrix is 1-channel (N x ptdim) or ptdim-channel (1 x N) or (N x 1); negative number otherwise
	int checkVector(int elemChannels, int depth = -1, bool requireContinuous = true) const;
	//��41������ͼ������У�ָ���е��׵�ַ
	uchar* ptr(int i0 = 0);
	const uchar* ptr(int i0 = 0) const;
	//��42�����ؾ���ͼ���У�ָ������׵�ַ
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
	ģ��˵��:
	����ͼ�������ָ��Ԫ�صĵ�ַ(����)
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
	ģ��˵��:
	ͼ����������
	******************************************************************************************************************************/
/*	int flags;                                           //��43��ͼ������Ƿ�����
	int dims;                                            //��44��ͼ������ά��dims>=2
	int rows, cols;                                      //��45��ͼ�������к�����
														 //��46��ָ��ͼ�����������ָ��
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
	 Mat resimg;//mat��opencv���������ݽṹ������һ��ͼ���������
	//--1--˫��б�߷�
	string imgpath0="E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	//--2--˫��б�߷�
	string imgpath1="E://Visual Studio 2010//Projects//opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--3--����б�߷�
	string imgpath2 = "E:/Visual Studio 2010/Projects/opencv_2018_12_21/opencv_2018_12_21/1.jpg";
	//--4--�������ֻ��
	string imgpath3 = "E:/Visual Studio 2010//Projects\\opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--5--���·����
	string imgpath4 = "1.jpg";
	//--6--�����в�����
	//string imgpath5 = argv[1];
	
	Mat img = imread(imgpath4,1);//����ͼƬ����
	if (img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//cout<<img.
	cout << " open or find the img" << endl;
	cout <<"img.channels��"<<img.channels() << endl;
	/*
		// similar to CV_ELEM_SIZE(cvmat->type)
	//��34������ͼ���У�ÿһ��ͼ��Ԫ�صĴ�С(��λ���ֽڣ����磬int---4)
	size_t elemSize() const;
	//! returns the size of element channel in bytes.
	size_t elemSize1() const;
	//��35������Ԫ�ص����ͣ�����CV_MAT_TYPE()
	int type() const;
	//��36������Ԫ�ص���ȣ�����CV_MAT_DEPTH()
	int depth() const;
	//��37������Ԫ�ص�ͨ���������CV_MAT_CN()
	int channels() const;
	//��38������ͼ����ÿһ��ָ���ƶ��ĸ���step/elemSize1()
	size_t step1(int i = 0) const;
	//��39���жϾ����Ƿ�Ϊ�գ����Ϊ�գ��򷵻�True
	bool empty() const;
	//��40�����ؾ���ͼ���У�Ԫ�ص�ĸ���
	size_t total() const;
	
	*/
	cout <<"img.elemSize:" << img.elemSize()<< endl;
	cout << "img.type:" << img.type() << endl;
	cout << "img.depth:" << img.depth() << endl;
	cout << "img.step1:" << img.step1() << endl;

	namedWindow("IMG",WINDOW_AUTOSIZE);//����һ������
	imshow("IMG",img);
	/* ��תģʽ��flipCode == 0��ֱ��ת����X�ᷭת����
		flipCode>0ˮƽ��ת����Y�ᷭת����
		flipCode<0ˮƽ��ֱ��ת������X�ᷭת������Y�ᷭת���ȼ�����ת180�㣩 */
	flip(img,resimg,1);

	/*
	WINDOW_NORMAL:���Ըı䴰�ڴ�С�������ƣ���Ҳ�ɽ�һ����������ת���ɳ��ô�С�� 
WINDOW_AUTOSIZE���������ݳ��������Զ�������С�Ҳ����ֶ����Ĵ��ڴ�С�� 
WINDOW_OPENGL������֧��OpenGL�Ĵ��ڣ� 
WINDOW_FULLSCREEN������һ��������Ļ�Ĵ��ڣ� 
WINDOW_FREETATIO��ͼ�񽫾�����չ��; 
WINDOW_KEEPRATIO��ͼ������ܵ�Լ����
	*/

	namedWindow("ˮƽ��ת",WINDOW_AUTOSIZE);
	imshow("ˮƽ��ת",resimg);

	flip(img,resimg,0);
	namedWindow("��ֱ��ת",WINDOW_AUTOSIZE);
	imshow("��ֱ��ת",resimg);

	flip(img,resimg,-1);
	namedWindow("ˮƽ��ֱ��ת",WINDOW_AUTOSIZE);
	imshow("ˮƽ��ֱ��ת",resimg);

	waitKey(0);
	system("pause");
	return 0;
}