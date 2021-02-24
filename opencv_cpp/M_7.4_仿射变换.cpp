/*7.4仿射变换
表示的就是两幅图片之间的一种联系;

仿射变换(Affine Map),又称为放射映射,是指在几何中,一个向量空间进行一次
线性变换并接上一个平移,变换为另一个向量空间的过程;
它保持了二维图像的"平直性"(直线经过变换之后依然是直线),和"平行性"
(二维图像之间的相对位置关系保持不变,平行线依然是平行线,且直线上
点的位置顺序不变);
一个任意的放射变换都能表示为乘以一个矩阵(线性变换)再接着加上一个
向量(平移)的形式;

旋转:rotation(线性变换)
平移,translation(向量加)
缩放,scale(线性变换)

OpenCV仿射变换相关的函数一般涉及到wapAffine和getRotationMatrix2D
这两个函数;
wrapAffine来实现一些简单的重映射
getRotationMatrix2D来获得旋转矩阵

wrapAffine函数的作用是依据一下公式,对图像做仿射变换
dst(x,y)=src(M11x+M12y+M13,M21x+M22y+M23)
C++:void wrapAffine(InputArray src,OutputArray dst,InputArray M,
Size dsize,int flag=INTER_LINEAR,int borderMode=BORDER_CONSTANT,
const Scalar&borderValue=Scalar());

第二个参数:OutputArray类型的dst,函数调用后的运算结果存在这里,
需要和源图片有一样的尺寸和类型;
第三个参数:InputArray类型的M,2*3的变换矩阵;
第四个参数:Size类型的dsize,表示输出图像的尺寸;
第五个参数:int类型的flags,插值方法的标识符;此参数有默认值
INTER_LINEAR(线性插值);
INTER_NEAREST--最近邻插值
INTER_AREA---区域插值
INTER_CUBIC--三次样条插值
INTER_LANCZOS4---Lanczos插值
CV_WRAP_FILL_OUTLINES--填充所有输出图像的像素,如果
部分像素落在输入图像的边界外,那么他们的值 设置为fillval
CV_WRAP_INTERSE_MAP--表示M为输出图像到输入图像的反变换;
因此可以直接用来做像素插值;否则,wrapAffine函数从M矩阵得到
反变换;

第六个参数,int类型的borderMode,边界像素模式,默认值为BORDER_CONSTANT;
第七个参数,const Scalar&类型的borderValue,在恒定的边界情况下
取的值,默认值为Scalar(),即为0;

warpAffine函数与一个叫做cvGetQuardrangleSubPix()的函数类似,
但是不完全相同;WrapAffine要求输入和输出图像具有同样的数据类型,
有更大的资源开销(因此对小图像不太合适)而且输出图像的部分可以
保留不变;
而cvGetQuadrangleSubPix可以精确地从8位图像中提取四边形到
浮点数缓冲区中,具有比较小的系统开销,而且总是全部改变输出图像的内容; 

计算二维旋转变换矩阵:getRotationMatrix2D()
getRotationMatrix2D()函数用于计算二维旋转变换矩阵;变换会将
旋转中心映射到它自身;
C++:Mat getRotationMatrix2D(Point2f center,double angle,double scale );
第一个参数:Point2f类型的center,表示源图像的旋转中心;
第二个参数:double类型的angle,旋转角度,角度为正值表示向逆时针旋转(坐标原点是左上角); 
第三个参数:double类型的scale,缩放系数;

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
	//参数准备
	//定义两组点,代表两个三角形
	Point2f src_Triangle[3];
	Point2f dst_Triangle[3];

	Mat rotMat(2,3,CV_32FC1);
	Mat wrapMat(2,3,CV_32FC1);

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}

	dst_img = Mat::zeros(src_img.rows,src_img.cols,src_img.type());

	//设置源图像和目标图像上的三组点以计算仿射变换
	src_Triangle[0] = Point2f(0,0);
	src_Triangle[1] = Point2f(static_cast<float>(src_img.cols - 1), 0);
	src_Triangle[2] = Point2f(0, static_cast<float>(src_img.rows - 1));

	dst_Triangle[0] = Point2f(static_cast<float>(src_img.cols*0.0), static_cast<float>(src_img.rows *0.33));
	dst_Triangle[1] = Point2f(static_cast<float>(src_img.cols*0.65), static_cast<float>(src_img.rows *0.35));
	dst_Triangle[2] = Point2f(static_cast<float>(src_img.cols*0.15), static_cast<float>(src_img.rows *0.6));

	//求得仿射变换
	wrapMat = getAffineTransform(src_Triangle,dst_Triangle);
	//对源图像应用刚刚求得的仿射变换
	warpAffine(src_img,dst_img,wrapMat,dst_img.size());

	//对图像进行缩放后再旋转
	//计算绕图像中心店顺时针转50度缩放因子为0.6的旋转矩阵
	Point center = Point(dst_img.cols/2,dst_img.rows/2);
	double angle = -30.0;
	double scale = 0.8;
	//通过上面的旋转细节信息求得旋转矩阵
	rotMat = getRotationMatrix2D(center, angle, scale);
	//旋转已缩放后的图像
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
