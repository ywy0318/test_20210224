/*
离散傅里叶变换:是指傅里叶变换在时域和频域上都呈现离散的形式,
将时域信号的采样,变换为在离散时间傅里叶变换(DTFT)频域采样;
形式上,变换两端(时域和频域上)的序列是有限长的,而实际上这两组序列都应当
被认为是离散周期信号的主值序列;即使对有限长的离散信号做DFT,也应当对其
经过周期延拓成周期信号再进行变换;实际应用中,通常采用快速傅里叶变换来高效计算DFT;

变换之后得到实数图像加虚数图像或者幅度图像加相位图像;
实际图像处理仅仅使用了幅度图像,幅度图像包含了源图像的几乎所有我们需要的几何信息;

如果想要通过修改幅度图像或者相位图像的方法来简介修改原空间图像,需要使用逆傅里叶变换得到
修改后的空间图像;这样就必须同时保留幅度图像和相位图像了;

在频域里面,对于一幅图像,
高频部分代表了图像的细节，纹理信息;低频部分代表了图像的轮廓信息;
如果一副精致的图像使用低通滤波器,那么滤波后的结果就剩下轮廓了;

如果图像收到的噪声恰好位域某个特定的"频率"范围,则可以通过滤波器来
恢复原来的图像;

傅里叶变换在图像处理中可以做到图像增强与图像去噪,图像分割指边缘检测,
图像特征提取,图像压缩;

dft()函数详解
dft函数的作用是对一维或者二维浮点数数组进行正向或者反向离散傅里叶变换;
C++:void dft(InputArray src,OutputArray dst,int flags=0,int nonzerorows=0)

第一个参数:InputArray类型的src,输入矩阵，可以为实数，或者是虚数;
第二个参数:OutputArray类型的dst;函数调用后的运算结果,保存在这里,
其尺寸和类型取决于标识符,也就是第三个参数flags;
第三个参数，int类型的flags;转换的标识符,默认值为0,取值为下表:
DFT_INVERSE  用一维或者二维逆变换代替默认的正向变换
DFT_SCALE   缩放比例标识符,输出结果都会以1/N进行缩放,通常会结合
			DFT_INVERSE一起使用
DFT_ROWS	对输入矩阵的每行进行正向或者反向的变换,此标识符可以在处理多种矢量
			的时候用于减小资源开销,这些处理常常是三维或者高维变换等复杂操作;

DFT_COMPLEX_OUTPUT	进行一维或二维实数数组正变换,这样的结果虽然是复数阵列,
					但拥有复数的共轭对称性(CCS),所以可以被写成一个拥有同样尺寸的实数阵列;

DFT_REAL_OUTPUT     进行一维或者二维复数数组反变换;这样的结果通常是一个大小相同的复矩阵;
					如果输入的矩阵有复数的共轭对称性
					(比如是一个带有DFT_COMPLEX_OUTPUT标识符的正变换结果),便会输出实矩阵;



第四个参数:int类型的nonzeroRows,有默认值为0,当此参数设置为非0时,
			(最少是取值为想要处理的那一行的值,比如C.rows),函数会假设只有
			输入矩阵的第一个非零行包含非零元素(没有设置DFT_INVERSE标识符)
			或只有输出矩阵的第一个非零行包含非零元素(设置了DFT_INVERSE标识符)
			这样的话,函数就可对其他进行更高效的处理,以节省时间开销;
			在采用DFT计算矩阵卷积时非常有效;
*/


/*
void cvMulSpectrums( const CvArr* src1, const CvArr* src2, CvArr* dst, int flags );
src1
第一输入数组
src2
第二输入数组
dst
输出数组，和输入数组有相同的类型和大小。
flags
下面列举的值的组合:
CV_DXT_ROWS - 把数组的每一行视为一个单独的频谱 (参见 cvDFT 的参数讨论).
CV_DXT_MUL_CONJ - 在做乘法之前取第二个输入数组的共轭.
*/

/*
返回DFT最优尺寸大小:getOptimalDFTSize()函数
返回给定向量尺寸的傅里叶最优尺寸大小,为了调高离散傅里叶变换的运行速度,
需要扩充图像，具体扩充多少，由这个函数计算得到;
int getOptimalDFTSize(int vecsize)
参数为int类型的vecsize,向量尺寸,即图片的rows,cols;

*/

/*
扩充图像边界:copyMakeBorder()函数
copyMakeBorder函数的作用是扩充图像边界
void copyMakeBorder(InputArray src,OutputArray dst,int top,int bottom
,int left,int right,int borderType,const Scalar& value=Scalar())

第一个参数,InputArray类型的src,输入图像，源图像
第二个参数,OutputArray类型的dst,函数调用后的运算结果存在这里,即这个参数用于
			存放函数调用后的输出结果,需和源图片有一样的尺寸和类型,
			且size应为Size(src.cols+left+right,src.rows+top+bottom)

接下来的四个参数,分别为int类型的top,bottom,left,right，分别表示在
源图像的四个方向上扩充了多少像素,例如:top=2,bottom=2,left=2,right=2
这意味着在源图像的上下左右各扩充两个像素宽度的边界;

第七个参数,borderType类型的,边界类型,常见的取值为BORDER_CONSTANT,
			可以参考borderInterpolate()得到更多的细节

第八个参数,const Scalar&类型的value,默认值Scalar(),可以理解为默认为0;
			当borderType取值为BORDER_CONSTANT时，这个参数表示边界值

*/
/*
计算二维矢量的幅度:magnitude()函数
void magnitude(InputArray x,InputArray y,OutputArray magnitude)
x--表示矢量的浮点型X坐标值,实部
y--表示矢量的浮点型Y坐标值,虚部
OutputArray类型的magnitude,输出的幅值,它和第一个参数x有着同样的尺寸和类型

magnitude()函数原理:dst(I)=(X(I)^2+Y(I)^2)^(1/2)
*/

/*
计算自然对数:log()函数
log函数的功能是计算每个数组元素绝对值的自然对数;
第一个参数为输入图像,第二个参数为得到的对数值
dst(I)=
{
	log|src(I)|,if src(I)!=0
	C	otherwise
}

*/

/*
矩阵归一化:normalize()函数
void normalize(InputArray src,OutputArray,dst,double alpha=1,double beta=0,
int norm_type=NORM_L2,int dtype=-1,InputArray mask=noArray())

第一个参数:InputArray类型的src,
第二个参数:OutputArray类型的dst,函数调用后的运算结果都存在这里,和原图片有一样的尺寸和类型
第三个参数:double 类型的alpha,归一化后的最大值,默认为1
第四个参数:double类型的beta,归一化的最大值,默认为0----最小值
第五个参数:int类型的norm_type;归一化类型,有NORM_INT,NORM_L1,
			NORM_L2,NORM_MINMAX等参数可选,默认值NORM_L2;

第六个参数:int类型的dtype,默认值为-1，当此参数取负值,输出矩阵和src有同样的类型;
			否则，它和src有同样的通道数,且此时图像深度为CV_MAT_DEPTH(dtype)

第七个参数:InputArray类型的mask,可选的操作掩码,默认值noArray();

*/


#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
//使用dft函数计算两个二维实卷积矩阵的示例核心片段
/*
void convolveDFT(InputArray A, InputArray B, OutputArray C)
{
	//初始化输出矩阵
	C.create(abs(A.rows - B.rows) + 1,abs(A.cols-B.cols)+1,A.type());
	Size dft_size;

	//计算DFT变换的尺寸
	dft_size.width = getOptimalDFTSize(A.cols+B.cols-1);
	dft_size.height = getOptimalDFTSize(A.rows+B.rows-1);

	//分配临时缓冲区并初始化置零
	Mat temp_A(dft_size, A.type(), Scalar::all(0));
	Mat temp_B(dft_size, B.type(), Scalar::all(0));

	//分别复制A和B到temp_A和temp_B的左上角
	Mat roi_A(temp_A, Rect(0, 0, A.cols, A.rows));
	A.copyTo(roi_A);
	Mat roi_B(temp_B,Rect(0,0,B.cols,B.rows));
	B.copyTo(roi_B);


	//就地操作(in-place),进行快速傅里叶变换,并将nonzeroRows参数置为非零,
	//以进行更加快速的处理
	dft(temp_A, temp_A, 0, A.rows);
	dft(temp_B, temp_B, 0, B.rows);

	//将得到的频谱相乘,结果存放在temp_A---待续
	mulSpectrums(temp_A, temp_B, temp_A, DFT_COMPLEX_OUTPUT);

	//将结果变换为频域,尽管结果行(result rows)都为非零,只需要其中C.rows
	//的第一行,所以用nonzeroRows=C.rows
	dft(temp_A,temp_B,DFT_INVERSE+DFT_SCALE,C.rows);

	//将结果复制到C中
	temp_A(Rect(0, 0, C.cols, c.rows)).copyTo(C);
	//所有的临时缓冲区将被自动释放,无须收尾操作
}*/

int main()
{
	Mat src_img, des_img, gray_img, edge;

	src_img = imread("lena.jpg", 0);//读入图片数据,灰度模式
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);
	//ShowHelpText();没啥用，不是opencv自带的函数

	//将图像延扩到最佳的尺寸,边界用0补充
	//离散傅里叶变换的运行速度与图片的尺寸有很大关系;
	//当图像尺寸是2,3,5,的整数倍时,计算速度最快;
	//为了达到快速计算的目的,经常添凑新的边缘像素的方法,
	//获得最佳图像尺寸;
	int m = getOptimalDFTSize(src_img.rows);
	int n = getOptimalDFTSize(src_img.cols);

	//将添加的像素初始化为0
	Mat padded;
	copyMakeBorder(src_img, padded, 0, m - src_img.rows, 0, n - src_img.cols, BORDER_CONSTANT, Scalar::all(0));

	//为傅里叶变换的结果(实部和虚部)分配存储空间
	//将planes数组组合合并成一个多通道的数组complexI
	//傅里叶变换的结果是复数,这就是说对于每个原图像值,结果会有两个图像值,
	//此外,频域值范围远远超过空间值范围,因此至少要将频域存在float格式中,
	//所以我们将输入图像转换成浮点类型，并多加一个额外通道来储存复数部分;
	Mat planes[] = { Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F) };
	Mat complexI;
	merge(planes,2,complexI);

	//进行就地离散傅里叶变换(in-place,输入输出为同一图像)
	dft(complexI,complexI);

	//
	//将复数转换为幅值,即=>log(1+sqrt(Re(DFT(I))^2+Im(DFT(I))^2))
	split(complexI,planes);//将多通道数组complexI分离成几个单通道数组
						//planes[0] = Re(DFT(I),planes[1] = Im(DFT(I)));
	magnitude(planes[0],planes[1],planes[0]);//planes[0]=magnitude
	Mat magnitude_image = planes[0];

	//进行对数尺度缩放(logarithmic scale)
	//傅里叶变换的幅度值范围大到不适合在屏幕上显示,高值在屏幕上显示为
	//白点,地址为黑点,高地址的变换无法有效分辨,为了在屏幕上凸显高低变换的连续性
	//用对数尺度来替换线性尺度
	magnitude_image += Scalar::all(1);
	log(magnitude_image, magnitude_image);//求自然对数

	//剪切和重分布幅度图像限
	//若有技术航或者奇数列,进行频谱裁剪
	//第二部延扩了图像，现在将新添加的像素剔除掉，为了方便显示,
	//重新分布幅度图像限位置,(将第五步得到的幅度图从中间划开,)
	//得到4张1/4的子图像,将每张子图像,看做幅度图的一个象限，
	//重新分布，将四个焦点重叠到图片中心
	magnitude_image = magnitude_image(Rect(0, 0, magnitude_image.cols&-2, magnitude_image.rows&-2));

	//重新排列傅里叶图像中的象限,使得原点位于图像中心;
	int cx = magnitude_image.cols / 2;
	int cy = magnitude_image.rows / 2;
	Mat q0(magnitude_image,Rect(0,0,cx,cy));//ROI区域的左上角
	Mat q1(magnitude_image, Rect(cx, 0, cx, cy));//ROI区域的右上角
	Mat q2(magnitude_image, Rect(0, cy, cx, cy));//ROI区域的左下角
	Mat q3(magnitude_image, Rect(cx, cy, cx, cy));//ROI区域的右下角

	//交换象限(左上与右下进行交换)
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	//交换象限(右上与坐下进行交换)
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//归一化，用0到1之间的浮点值m将矩阵变换为可视的图像格式
	//为了显示,有了重分布后的幅度图,幅度图值仍然超过可
	//可显示范围[0,1]
	//opencv2
	//normalize(magnitude_image,magnitude_image,0,1,CV_MINMAX);
	//opencv3
	normalize(magnitude_image, magnitude_image, 0, 1, NORM_MINMAX);

	//显示效果图
	imshow("频谱幅值", magnitude_image);
	waitKey();

	cout << CV_MAJOR_VERSION << endl;
	waitKey(0);
	system("pause");
	return 0;
}
