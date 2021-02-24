

/*
6.5.1漫水填充的定义,
漫水填充法是一种用特定的颜色填充连通区域，通过设置可连通像素的上下限以及
连通方式来达到不同的填充效果的方法;
漫水填充经常被用来标记或分离图像的一部分;
也可以用来从输入图像获取掩码区域，掩码会加速处理过程,
或者只处理掩码指定的像素点,操作的结果总是某个连续的区域;
floodfill
自动选中了和种子点相连的区域,接着将该区域替换成指定的颜色;
查找和种子点连通的颜色相同的点;

int floodFill(InputArray src,
Point seedPoint,Scalar newVal,
CV_OUT Rect* rect=0,Scalar loDiff=Scalar(),Scalar upDiff=Scalar(),
int flags=4)

int floodFill(InputArray src,InputOutputArray mask,
Point seedPoint,Scalar newVal,
CV_OUT Rect* rect=0,Scalar loDiff=Scalar(),Scalar upDiff=Scalar(),
int flags=4)

InputOutputArray类型的mask,表示操作掩码,单通道，8位,长和宽上都比输入图像
image大两个像素点;边缘检测算子的输出可以用来作为掩码，防止填充到边缘
,在多次函数调用中使用同一个掩码,以保证填充的区域不会重叠;
掩码mask会比需要填充的图像大,mask中与输入图像(x,y)像素点
相对应的坐标为(x+1,y+1)

第三个参数:seedPoint，漫水填充算法的起始点;
第四个参数:Scalar类型的newVal,像素点被染色的值,在
重绘区域的像素的新值;
第五个参数:Rect*rect,有默认值为0,一个可选的参数,用于设置
floodFill函数将要重绘区域的最小边界矩形区域;
第六个参数:Scalar类型的upDiff,有默认值Scalar(),表示当前
观察像素值与其部件邻域像素值或待加入该部件的种子像素之间的亮度
或颜色之正差(lower brightnesss/color difference)的最大值
第八个参数:int类型的flags,操作标识符,
第八位(0-7):用于控制算法的连通性,可取4(默认值)或者8,
如果为4:表示填充算法只考虑当前像素水平方向和垂直方向的相邻点;
如果设置为8,除了上述相邻点外，还会包含对角线方向的相邻点;
高八位(16-32):可以为0或者如下两种选项标识符的组合,
FLOODFILL_FIXED_RANGE:如果设置为这个标识符,就会考虑当前像素与
种子像素之间的差,否则就考虑当前像素与其相邻像素的差,这个范围是
浮动的;
FLOODFOLL_MASK_ONLY:如果设置为这个标识符,函数不会去填充改变原始图像
(也就是忽略第三个参数newVal),而是去填充掩码图像(mask),这个标识符只对
第二个版本的floodfill有用;
中间八位的值是用于指定填充掩码图像的值;

*/
/*
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int main()
{

	Mat src_img, dst_img, gray_img, edge;

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	Rect ccomp;
	imshow("src_img",src_img);
	floodFill(src_img,Point(50,50),Scalar(155,255,55),&ccomp,Scalar(20,20,20),Scalar(20,20,20));

	imshow("floodFill_src_img",src_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img;

int g_nFillMode = 1;//漫水填充的模式
int g_nLowDifference = 20;//负差最大值
int g_nUpDifference = 20;//正差最大值

int g_nConnectivity = 4;//表示floodFill函数标识符第八位的连通值
int g_bIsColor = true;//是否为彩色图的标识符布尔值
int g_bUseMask = false;//是否显示掩码窗口的布尔值 
int g_nNewMaskVal = 255;//新的重新绘制的像素值

static void onMouse(int event, int x, int y, int, void*)
{
	//若鼠标左键没有按下,便返回
	if (event!=EVENT_LBUTTONDOWN)
	{
		return;
	}
	//调用floodFill函数之前的参数准备部分;
	Point seed = Point(x, y);
	//空范围的漫水填充,此值为0,否则设置为全局的g_nLowDifference
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;
	//空范围的漫水填充,此值设置为0,否则设置为全局的g_nUpDifference
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;
	//标识符的0-7位为g_nConnectivity,8-15位为g_nNewMaskVal左移8位的值;
	//16-23位为FLOODFILL_FIXED_RANGE或者0;

	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

	//随机生成bgr值
	int b = (unsigned)theRNG() & 255;//随机返回一个0-255之间的值;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;//定义重绘区域的最小边界矩形区域
	//在重绘区域像素的新值,若是彩色图模式,取Scalar(b,g,r);
	//若是灰色图模式,取Scalar(r*0.299 + g*0.587 + r*0.114)
	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + r*0.114);//
	//目标图的赋值
	Mat dst = g_bIsColor ? dst_img : gray_img;
	//
	int area;
	if (g_bUseMask)
	{
		threshold(mask_img,mask_img,1,128,THRESH_BINARY);
		area = floodFill(dst, mask_img,seed,newVal,&ccomp,Scalar(LowDifference,LowDifference,LowDifference)
		,Scalar(UpDifference,UpDifference,UpDifference),flags);
		imshow("mask",mask_img);

	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
		imshow("效果图",dst);
		cout << area << "个像素被重绘\n";
	}
}
int main()
{

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//复制原图像到目标图像
	src_img.copyTo(dst_img);
	//转换三通道的image到灰度图像
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
	//利用image的尺寸来初始化掩码mask
	mask_img.create(src_img.rows+2,src_img.cols+2,CV_8UC1);
	
	namedWindow("效果图",WINDOW_AUTOSIZE);
	//创建Trackbar
	createTrackbar("负值最大值","效果图",&g_nLowDifference,255,0);
	createTrackbar("正值最大值", "效果图", &g_nUpDifference, 255, 0);

	//鼠标回调函数
	setMouseCallback("效果图",onMouse,0);
	//循环轮询按键
	while (true)
	{
		imshow("效果图", g_bIsColor ? dst_img : gray_img);
		//获取键盘按键
		int c = waitKey(0);
		//判断ESC是否按下,按下就退出
		if ((c&255)==27)
		{
			cout << "程序退出.....\n";
			break;
		}
		//根据按键的不同,进行各种操作;
		switch ((char)c)
		{
			//如果1被按下，效果图在灰色，彩色图之间互换
		case'1':
			//如果原来为彩色，转换为灰度图,并且将掩码mask所有元素设置为0
			if (g_bIsColor)
			{
				cout << "键盘1被按下，切换彩色/灰色模式,当前操作[彩色模式]切换为[灰度模式]\n";
				cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
				//将mask所有元素设置为0
				mask_img = Scalar::all(0);
				//将标识符设置为fasle,表示当前图像不为彩色，而是灰度
				g_bIsColor = false;
			}
			//原来为灰度图,将原来的彩色图再次复制给image,并将掩码mask所有元素设置为0
			else
			{
				cout << "键盘1被按下,[彩色模式]切换成[灰色模式]\n";
				src_img.copyTo(dst_img);
				mask_img = Scalar::all(0);
				g_bIsColor = true;
			}
			break;
		case'2':
			//键盘按键2被按下,显示/隐藏掩码窗口
			if (g_bUseMask)
			{
				destroyWindow("mask");
				g_bUseMask = false;
			}
			else
			{
				namedWindow("mask",0);
				mask_img = Scalar::all(0);
				imshow("mask",mask_img);
				g_bUseMask = true; 
			}
			break; 
		case'3':
			cout << "按键3被按下,恢复原始图像\n";
			src_img.copyTo(dst_img);
			cvtColor(dst_img,gray_img,COLOR_BGR2GRAY);
			mask_img = Scalar::all(0);
			break;
		case'4':
			cout << "按键4被按下，使用空范围的漫水填充\n";
			g_nFillMode = 0;
			break;
		case'5':
			cout << "按键5被按下，使用渐变,固定范围的漫水填充\n";
			g_nFillMode = 1;
			break;
		case'6':
			cout << "按键6被按下，使用渐变,浮动范围的漫水填充\n";
			g_nFillMode =2;
			break;
		case'7':
			cout << "按键7被按下，操作标识符的第八位使用4位的连接模式\n";
			g_nConnectivity = 4;
			break;
		case'8':
			cout << "按键8被按下，操作标识符的第八位使用8位的连接模式\n";
			g_nConnectivity = 8;
			break;

		default:
			break;
		}
	}

	//imshow("src_img", src_img);
	//waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}

