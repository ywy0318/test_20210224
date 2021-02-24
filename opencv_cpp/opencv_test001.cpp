#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
 
 
using namespace cv;
 

//Mat imread(const String& filename, int flags = IMREAD_COLOR);
//
//返回Mat对象；
//
//参数filename : 待打开图片的绝对地址，需要注意的是，并不是所有文件都可以用它打开，它支持的文件如下；函数识别不是依靠文件的后缀名，而是依靠内容的编码格式；
//
//	需要注意的是imread读取数据时会重新排列数据。
//
//	Windows bitmaps - *.bmp, *.dib(always supported)
//	JPEG files - *.jpeg, *.jpg, *.jpe(see the Notes section)
//	JPEG 2000 files - *.jp2(see the Notes section)
//	Portable Network Graphics - *.png(see the Notes section)
//	WebP - *.webp(see the Notes section)
//	Portable image format - *.pbm, *.pgm, *.ppm *.pxm, *.pnm(always supported)
//	Sun rasters - *.sr, *.ras(always supported)
//	TIFF files - *.tiff, *.tif(see the Notes section)
//	OpenEXR Image files - *.exr(see the Notes section)
//	Radiance HDR - *.hdr, *.pic(always supported)
//	Raster and Vector geospatial data supported by Gdal(see the Notes section)
//	参数flags：打开的参数，这个非常重要，因为如果设置不合适的话，很容易出现预想之外的效果。它可以指导将原图读取时进行一定的转换。默认值是IMREAD_LOAD_GDAL。因此，如果是想直接处理原图，应该设置为IMREAD_UNCHANED。
//
//	IMREAD_UNCHANGED 
//
//	If set, return the loaded image as is(with alpha channel, otherwise it gets cropped).
//
//	IMREAD_GRAYSCALE 
//
//	If set, always convert image to the single channel grayscale image.
//
//	IMREAD_COLOR 
//
//	If set, always convert image to the 3 channel BGR color image.
//
//	IMREAD_ANYDEPTH 
//
//	If set, return 16 - bit / 32 - bit image when the input has the corresponding depth, otherwise convert it to 8 - bit.
//
//	IMREAD_ANYCOLOR 
//
//	If set, the image is read in any possible color format.
//
//	IMREAD_LOAD_GDAL 
//
//	If set, use the gdal driver for loading the image.
//
//	IMREAD_REDUCED_GRAYSCALE_2 
//
//	If set, always convert image to the single channel grayscale image and the image size reduced 1 / 2.
//
//	IMREAD_REDUCED_COLOR_2 
//
//	If set, always convert image to the 3 channel BGR color image and the image size reduced 1 / 2.
//
//	IMREAD_REDUCED_GRAYSCALE_4 
//
//	If set, always convert image to the single channel grayscale image and the image size reduced 1 / 4.
//
//	IMREAD_REDUCED_COLOR_4 
//
//	If set, always convert image to the 3 channel BGR color image and the image size reduced 1 / 4.
//
//	IMREAD_REDUCED_GRAYSCALE_8 
//
//	If set, always convert image to the single channel grayscale image and the image size reduced 1 / 8.
//
//	IMREAD_REDUCED_COLOR_8 
//
//	If set, always convert image to the 3 channel BGR color image and the image size reduced 1 / 8.
//
//	1 通道编码顺序
//	通道，与像素深度深度有关。灰度图通常是8比特的像素深度，则通道数为1。如果是彩色图，且为RGB编码，那么一般为24比特的像素深度，通道数为3。而有的彩色图的像素深度是16或者32比特。16比特可能有多种情况：一是压缩的RGB格式，二是YUV的输出。无论何种，都是只有2通道，需要手动解析分离。32比特（windows *.bmp）的像素深度对应的彩色图，则表示的是4通道，RGBA，多出的A表示的是透明度的索引。
//
//	另外读取时需要注意内部像素的编码顺序，这也依赖于imread的flags选项的取值，如果取值决定转成RGB，那么正常的顺序是BGR，排列顺序如下图所示。如果最后imread输出是四通道，多了Alpha通道，那么顺序是RGBA。
//
//
//
//	2 图像像素通道数据访问
//	这部分可以借鉴网上资料，可以分为三种类型。
//
//	2.1 动态访问at<typename>(i, j)
//	Imread返回的mat类，提供了at模板函数。Image.at<uchar>(i, j)；取出i行j列的数据，uchar可以理解为imread返回之后图像的编码类型（如1所述的通道）。如果是三通道，则可以是Vec3b，四通道则是Vec4b。
//
//	//CV_LOAD_IMAGE_UNCHANGED如果要取A分量那么flag最好设置成这个值
//
//	Mat image = imread("1_firstlai.png", CV_LOAD_IMAGE_UNCHANGED);
//
//for (int i = 0; i<image.rows; i++)
//
//{
//
//	for (int j = 0; j<image.cols; j++)
//
//	{
//
//		image.at<Vec3b>(i, j)[0]; //B
//
//		image.at<Vec3b>(i, j)[1]; //G
//
//		image.at<Vec3b>(i, j)[2]; //R
//
//
//
//		image.at<Vec4b>(i, j)[0]; //B
//
//		image.at<Vec4b>(i, j)[1]; //G
//
//		image.at<Vec4b>(i, j)[2]; //R
//
//		image.at<Vec4b>(i, j)[3]; //A
//
//	}
//
//}
//
//
//
//2.2 指针 - 更加高效
//imgage.ptr<uchar>(i)。
//
//int nr = image.rows;
//
//// 将3通道转换为1通道
//
//int nl = image.cols*image.channels();
//
//for (int k = 0; k<nr; k++)
//
//{
//
//	// 每一行图像的指针
//
//	const uchar* inData = image.ptr<uchar>(k);
//
//	for (int i = 0; i<nl; i++)
//
//	{
//
//		inData[i];
//
//	}
//
//}
//
//本质就是将每行的3 / 4通道数据转换为1通道数据访问，因为OpenCV内部存储每一行像素数据以及像素内部通道数据都是连续存储的。但是行与行的数据并不一定是连续存储的，所以不能应用在行与行之间。
//
//2.3 结合isContinuous的指针
//2.2中已经说明了，OpenCV中行与行之间不一定连续存储，也就是有可能连续存储，而且提供了对应的API支持判断是否连续这一现象，也可基于此，再提高访问速度。
//
//int nr = image.rows;
//
//int nc = image.cols*image.channels();
//
//if (image.isContinuous()) {
//
//	nc = nc*nr;
//
//	nr = 1;
//
//}
//
//for (int i = 0; i<nr; i++) {
//
//	// 每一行图像的指针
//
//	const uchar* inData = image.ptr<uchar>(i);
//
//	for (int j = 0; j<nc; j++) {
//
//		inData[j];
//
//	}
//
//}
//
//2.4 安全但低效的迭代器
//2.1 - 2.3的方法虽然效率高，但是如果操作不小心，容易造成数组越界的Bug。所以opencv提供了一种更安全的访问方法 - 迭代器。
//
//MatIterator_<Vec3b> it_im, itEnd_im;
//
//it_im    = im.begin<Vec3b>();
//
//itEnd_im = im.end<Vec3b>();
//
//for (; it_im != itEnd_im; it_im++, it_om++) {
//
//	(*it_im)[0]; //B
//
//	(*it_im)[1]; //G
//
//	(*it_im)[2]; //R 
//
//}
//-------------------- -
//作者：时行居正
//来源：CSDN
//原文：https ://blog.csdn.net/firstlai/article/details/70882240 
//版权声明：本文为博主原创文章，转载请附上博文链接！
 

//会创建一个命名为“camera”的窗口。 但是默认的创建窗口的namedWindow参数为WINDOW_AUTOSIZE。
//窗口大小会自动调整以适应所显示的图像，但是不能更改大小。
//创建窗口时候改变下参数就可以鼠标随意拖动窗口改变大小啦~
//cv::namedWindow("camera", CV_WINDOW_NORMAL);
//cv::imshow("camera", frame);
//WINDOW_NORMAL设置了这个值，用户便可以改变窗口的大小（没有限制)
//INDOW_AUTOSIZE如果设置了这个值，窗口大小会自动调整以适应所显示的图像，并且不能手动改变窗口大小.
//WINDOW_OPENGL 如果设置了这个值的话，窗口创建的时候便会支持OpenGL
//还有 Qt backend supports additional flags :
//
//
//CV_WINDOW_NORMAL or CV_WINDOW_AUTOSIZE : CV_WINDOW_NORMAL enables you to resize the window, whereasCV_WINDOW_AUTOSIZE adjusts automatically the window size to fit the displayed image(seeimshow()), and you cannot change the window size manually.可以改变窗口大小 vs 自适应不能改变窗口大小。
//CV_WINDOW_FREERATIO or CV_WINDOW_KEEPRATIO : CV_WINDOW_FREERATIO adjusts the image with no respect to its ratio, whereasCV_WINDOW_KEEPRATIO keeps the image ratio.调整图像不管比例 vs 保持原图比例。
//CV_GUI_NORMAL or CV_GUI_EXPANDED : CV_GUI_NORMAL is the old way to draw the window without statusbar and toolbar, whereasCV_GUI_EXPANDED is a new enhanced GUI.无状态栏和工具栏的普通版GUI 和 增强版GUI
//默认的flags == CV_WINDOW_AUTOSIZE | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED
//-------------------- -
//作者：wuyoy520
//来源：CSDN
//原文：https ://blog.csdn.net/wuyoy520/article/details/47111295 
//版权声明：本文为博主原创文章，转载请附上博文链接！


//语法：imshow(f, G)
//imshow(f, [low high])
//imshow(f, [])
//说明：G是显示该图像的灰度级数；
//小于或等于low的值都显示为黑色，大于或等于high的值都显示为白色。
//[]自动将变量low设置为f的最小值，将high设置为f的最大值。
//-------------------- -
//作者：在云端821
//来源：CSDN
//原文：https ://blog.csdn.net/slj821/article/details/80743417 
//版权声明：本文为博主原创文章，转载请附上博文链接！

//解决：使用imshow(A, [])，即可把图像矩阵A显示为正常的灰度图像。
//
//原理：imshow(A, [])是将A的最大值（max(A)）和最小值（min(A)）分别作为纯白(255)和纯黑(0)，中间的K值相应地映射为0到255之间的标准灰度值，这样就可以正常显示了。。。，相当于将double型的矩阵A拉伸成为了0 - 255的uint8型的矩阵，因此就可以正常显示
//-------------------- -
//作者：1024Michael
//来源：CSDN
//原文：https ://blog.csdn.net/michael__corleone/article/details/68483407 
//版权声明：本文为博主原创文章，转载请附上博文链接！


int main()
{
	// 读入一张图片（游戏原画）
	Mat img=imread("cat2.jpg");//Mat imread(const String& filename,int flags = IMREAD_COLOR);
	// 创建一个名为 "游戏原画"窗口
	namedWindow("游戏原画", CV_WINDOW_NORMAL);
	// 在窗口中显示游戏原画
	imshow("游戏原画",img);
	// 等待6000 ms后窗口自动关闭
	waitKey(6000*2);
}
