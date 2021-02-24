#include<iostream>
#include<opencv2\opencv.hpp>
#include "highgui.h"
#include"cvaux.h"
#include"cxcore.h"
#include"opencv2/imgproc.hpp"
#include<string>
using namespace std;
using namespace cv;

/*
学习把RGB（红绿蓝）空间的图像转化为其它空间的图像。

将RGB转化为HSV（色调（H），饱和度（S），明度（V））
将RGB转化为Lab（颜色模型 (Lab) 基于人对颜色的感觉，L表示明度（Luminosity），a表示从洋红色至绿色的范围，b表示从黄色至蓝色的范围） 
将RGB转化为YCrCb（其中“Y”表示明亮度（Luminance或Luma），也就是灰阶值；而“U”和“V” 表示的则是色度（Chrominance或Chroma），
作用是描述影像色彩及饱和度，用于指定像素的颜色）

*/

/*
void namedWindow(const string& winname,int flags=WINDOW_AUTOSIZE );
第一个参数，const string&型的name，即填被用作窗口的标识符的窗口名称。
第二个参数，int 类型的flags ，窗口的标识，可以填如下的值：
WINDOW_NORMAL设置了这个值，用户便可以改变窗口的大小（没有限制）
WINDOW_AUTOSIZE如果设置了这个值，窗口大小会自动调整以适应所显示的图像，并且不能手动改变窗口大小。
WINDOW_OPENGL 如果设置了这个值的话，窗口创建的时候便会支持OpenGL。
函数剖析：
首先需要注意的是，它有默认值WINDOW_AUTOSIZE，所以，一般情况下，这个函数我们填一个变量就行了。
namedWindow函数的作用是，通过指定的名字，创建一个可以作为图像和进度条的容器窗口。
如果具有相同名称的窗口已经存在，则函数不做任何事情。
我们可以调用destroyWindow()或者destroyAllWindows()函数来关闭窗口，并取消之前分配的与窗口相关的所有内存空间。
但话是这样说，其实对于代码量不大的简单小程序来说，
我们完全没有必要手动调用上述的destroyWindow()或者destroyAllWindows()函数，因为在退出时，
所有的资源和应用程序的窗口会被操作系统会自动关闭。
*/
/*
在指定的窗口中显示一幅图像。
void imshow(const string& winname, InputArray mat);
■ 第一个参数，const string&类型的winname，填需要显示的窗口标识名称。
■ 第二个参数，InputArray 类型的mat，填需要显示的图像。
imshow 函数详解：
imshow 函数用于在指定的窗口中显示图像。
如果窗口是用CV_WINDOW_AUTOSIZE（默认值）标志创建的，那么显示图像原始大小。
否则，将图像进行缩放以适合窗口。而imshow 函数缩放图像，取决于图像的深度：
如果载入的图像是8位无符号类型（8-bit unsigned），就显示图像本来的样子。
如果图像是16位无符号类型（16-bit unsigned）或32位整型（32-bit integer），便用像素值除以256。也就是说，值的范围是[0,255 x 256]映射到[0,255]。
如果图像是32位浮点型（32-bit floating-point），像素值便要乘以255。也就是说，该值的范围是[0,1]映射到[0,255]。
*/
/*
bool imwrite(const string& filename,InputArray img, const vector<int>& params=vector<int>() );
第一个参数，const string&类型的filename，填需要写入的文件名就行了，带上后缀，比如，“123.jpg”这样。
■ 第二个参数，InputArray类型的img，一般填一个Mat类型的图像数据就行了。
■ 第三个参数，const vector<int>&类型的params，表示为特定格式保存的参数编码，它有默认值vector<int>()，所以一般情况下不需要填写。

*/
int main()
{
	Mat src_img,des_img;
	string path = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	src_img = imread(path,IMREAD_COLOR);
	if (src_img.empty())
	{
		cout << "imread file failed"<< endl;
	}
	namedWindow("src_img", WINDOW_AUTOSIZE);
	imshow("src_img",src_img);
	//BGR->HSV
	cvtColor(src_img, des_img, CV_BGR2HSV);
	namedWindow("HSV_img", WINDOW_AUTOSIZE);
	imshow("HSV_img", des_img);

	//BGR->Lab
	cvtColor(src_img,des_img,CV_BGR2Lab);
	namedWindow("Lab_img", WINDOW_AUTOSIZE);
	imshow("Lab_img",des_img);
	//BGR->YCrCb
	cvtColor(src_img,des_img,CV_BGR2YCrCb);
	namedWindow("YCrCb_img",WINDOW_AUTOSIZE);
	imshow("YCrCb_img",des_img);
	waitKey(0);
	system("pause");
	return 0;
}