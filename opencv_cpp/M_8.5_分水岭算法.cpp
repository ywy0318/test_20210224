/*
!!!!!!!!!!!!!!!!!!!!!!!还有问题
8.5分水岭算法
watershed algorithm
分割图像,但是无法从背景图像中获得有用信息;
分水岭算法(watershed algorithm)在这方面往往有非常有效的;
此算法可以将图像中的边缘转化成"山脉",将均匀区域转化成为"山谷";
有助于分割目标;

watershed函数实现的分水岭算法是基于标记的分割算法中的一种;
在把图像传给函数之前,需要大致勾画标记出图像中的期望进行分割的
区域,他们被标记为正指数;所以每一个区域都会被标记为像素值1,2,3;
表示成为一个或者多个连接组件;这些标记的值可以使用findcontours()函数
和drawcontours()函数,由二进制的掩码检索出来;不难理解,这些标记
就是即将绘制出来的分割区域的"种子",而没有标记清除的区域,被置为0;
在函数输出中,每一个标记中的像素被设置为"种子"的值,而区域间的值被
设置为-1;
C++:void watershed(In putArray image,InputArray markets);
第一个参数:输入图像,8位三通道的彩色图像;
第二个参数:InputArray类型的markets,函数调用后的运算结果存在这里,
输入/输出32为单通道图像的标记结果;这个参数用于存放函数调用后的
输出结果,需和源图片有一样的尺寸和类型;
*/
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
Point prevPt(-1, -1);

static void on_Mouse(int event,int x,int y,int flag,void*);

int main()
{

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);
	src_img.copyTo(temp_img);

	cvtColor(src_img,mask_img,COLOR_BGR2GRAY);
	cvtColor(mask_img,gray_img,COLOR_GRAY2RGB);
	mask_img = Scalar::all(0);

	//设置鼠标回调函数
	setMouseCallback("src_img",on_Mouse,0);
	while (true)
	{
		int c = waitKey(0);
		if ((char)c==27)
		{
			break;
		}
		if ((char)c=='2')
		{
			mask_img = Scalar::all(0);
			temp_img.copyTo(src_img);
			imshow("src_img",src_img);
		}
		if (((char)c=='1')||((char)c==' '))
		{
			int i, j, compCount = 0;
			vector<vector<Point>> contours;
			vector<Vec4i> hierarchy;
			printf("1\n");
			//寻找轮廓
			findContours(mask_img, contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_NONE);
			if (contours.empty())
			{
				continue;
			}
			//复制掩模
			Mat maskImage(mask_img.size(),CV_32S);
			maskImage = Scalar::all(0);
			//循环绘制出轮廓
			for (size_t i = 0; i >=0; i=hierarchy[i][0],compCount++)
			{
				drawContours(maskImage,contours,i,Scalar::all(compCount+1),-1,8,hierarchy,INT_MAX);				
			}
			//compCount为0时的处理
			if (compCount==0)
			{
				continue;
			}
			//生成随机颜色
			vector<Vec3b> colorTab;
			for (size_t i = 0; i < compCount; i++)
			{
				int b = theRNG().uniform(0,255);
				int g = theRNG().uniform(0, 255);
				int r = theRNG().uniform(0, 255);

				colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
			}
			printf("colorTab.push_back\n");

			//计算处理时间并输出到窗口中
			double dTime = (double)getTickCount();
			watershed(src_img,maskImage);
			dTime = (double)getTickCount() - dTime;
			printf("\t处理时间=%gms\n",dTime*1000/getTickFrequency());

			//双层循环,将分水岭图像遍历存入watershedImage中
			Mat watershedImage(maskImage.size(),CV_8UC3); 
			for (size_t i = 0; i < maskImage.rows ; i++)
			{
				for (int j = 0; j < maskImage.cols; j++)
				{
					int index = maskImage.at<int>(i,j);
					if (index == -1)
					{
						watershedImage.at<Vec3b>(i, j) = Vec3b(255,255,255);
					}
					else if (index <= 0 || index > compCount)
					{
						watershedImage.at<Vec3b>(i, j) = Vec3b(0,0,0);
					}
					else
					{
						watershedImage.at<Vec3b>(i, j) = colorTab[index-1];
					}
				}
				//混合灰度图和分水岭效果图并显示最终的窗口
				watershedImage = watershedImage*0.5 + gray_img*0.5;
				imshow("watershed transform", watershedImage);
			}
		}
	}
	
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
static void on_Mouse(int event, int x, int y, int flag, void*)
{
	//处理鼠标不在窗口中的情况
	if (x < 0 || x >= src_img.cols || y < 0 || y >= src_img.rows)
	{
		return;
	}
	//处理鼠标左键相关消息
	if (event == EVENT_LBUTTONUP || !(flag&EVENT_FLAG_LBUTTON))
	{
		prevPt = Point(-1,-1);
	}
	else if(event==EVENT_LBUTTONDOWN)
	{
		prevPt = Point(x,y);
	}
	//鼠标左键按下并移动,绘制出白色线条
	else if(event==EVENT_MOUSEMOVE&&(flag&EVENT_FLAG_LBUTTON))
	{
		Point pt(x,y);
		if (prevPt.x<0)
		{
			prevPt = pt;
		}
		line(mask_img, prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(src_img, prevPt, pt, Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		imshow("src_img",src_img);
	}
}