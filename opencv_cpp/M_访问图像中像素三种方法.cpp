#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
//operationsOnArrays:LUT()<lut>
/*
//建立一个mat型用于查表
Mat lookUpTable(1,256,CV_8U);
uchar* p = lookUpTable.data;
for (size_t i = 0; i < 256; i++)
{
p[i] = lookUpTable[i];
}

//然后我们调用函数(I是输入，J是输出)
for (size_t i = 0; i < times; i++)
{
LUT(I,lookUpTable,J);
}

计时函数
getTickCount()和getTickFrequency()
getTickCount()函数返回CPU自某个事件(如启动电脑以来走过的时钟周期)
getTickFrequency()函数返回CPU一秒钟所走过的时钟周期数;
这样我们就可以轻松的以秒为单位对某运算计时了;

这两个函数组合起来使用的示例如下: 
double time_0=static_cast<double>(getTickCount());//记录起始时间
//进行图像处理操作....
time_0=((double)getTickCount()-time_0)/getTickFrequency();
cout<<"此方法运行时间为:"<<time_0<<"秒"<<endl;//输出运行时间


访问图像中像素的三类方法
方法1:指针访问:C操作符[];
方法2:迭代器iterator;
方法3:动态地址计算;

debug模式下差异明显，release模式下差异不太明显


*/
void colorReduce(Mat& inputImage,Mat& outputImage,int div);

//方法1:用指针访问像素
/*
用指针访问像素的这种法法利用的C语言中的操作符,
这种方法最快,但是略有点抽象,
*/
void colorReduce_C(Mat& inputImage, Mat& outputImage, int div)
{
	//参数准备
	outputImage = inputImage.clone();//复制实参到临时变量
	int row_num = outputImage.rows;//行数
	//列数x通道数=每一行元素的个数
	int col_num = outputImage.cols*outputImage.channels();
	//双重循环,遍历所有的像素值
	for (size_t i = 0; i < row_num; i++)
	{
		//获取第i行的首地址
		uchar* data = outputImage.ptr<uchar>(i);
		//列循环
		for (size_t j = 0; j < col_num; j++)
		{
			data[j] = data[j] / div*div + div / 2;//处理每个像素
			//*data++=*data/div*div+div/2;
		}
	}

}
//方法2:用迭代器操作像素
/*
用迭代器操作像素,这种方法与STL库的用法相似
在迭代法中,获取图像矩阵的begin和end,然后增加迭代直至begin和end;
将*操作符添加在迭代指针前,即可访问当前指向的内容
相比用指针直接访问可能出现越界问题,迭代器绝对是非常安全的方法
STL迭代器
*/
void colorReduce_iterator(Mat& inputImage, Mat& outputImage, int div)
{
	//参数准备
	outputImage = inputImage.clone();
	//获取迭代器
	Mat_<Vec3b>::iterator it_begin = outputImage.begin<Vec3b>();//初始位置的迭代器
	Mat_<Vec3b>::iterator it_end = outputImage.end<Vec3b>();//初始位置的迭代器

	//存取彩色图像像素
	for (; it_begin!=it_end; it_begin++)
	{
		(*it_begin)[0] = (*it_begin)[0] / div*div + div / 2;
		(*it_begin)[1] = (*it_begin)[1] / div*div + div / 2;
		(*it_begin)[2] = (*it_begin)[2] / div*div + div / 2;
	}

}
/*
方法3:动态地址计算
用动态地址计算来操作像素;
下面使用动态地址运算配置at的方法colorReduce函数的代码

Mat类中的cols和rows给出了图像的宽和高,而成员函数at(int y,int x)
可以用来存储图像元素,但是在编译期知道图像的数据类型,需要注意的是:
我们一定要确保指定的数据类型要和矩阵中的数据类型相符合,
因为at方法本身不会对任何数据类型进行转换

对于彩色图像,每个像素由三个部分构成:蓝色通道，绿色通道和红色通道(BGR)
对于一个包含彩色图像的Mat,会返回一个由三个8位数组成的向量
OpenCV将此类型的向量定义为Vec3b,即由三个unsigned char组成向量
存取彩色图像像素的代码如下形式:
img.at<Vec3b>(j,i)[channel]=value;索引值channel标明了颜色通道号

*/

void colorReduce_at(Mat& inputImage, Mat& outputImage, int div)
{
	//参数准备
	outputImage = inputImage.clone();
	int row_num = outputImage.rows;
	int col_num = outputImage.cols;

	//存取彩色图像像素
	for (size_t i = 0; i < row_num; i++)
	{
		for (int j = 0; j < col_num; j++)
		{
			//蓝色通道
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div*div + div / 2;
			//绿色通道
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div*div + div / 2;
			//红色通道
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div*div + div / 2;
		}
	}
}


//主程序调用colorReduce函数来完成减少颜色的工作,利用三种访问像素的三类方法,写出三个版本的colorRecuce函数;
int main()
{
	string imgpath4 = "1.jpg";
	Mat img = imread(imgpath4, 1);//读入图片数据
	if (img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	Mat dst_image;
	//按原始图的参数规格来创建效果图,效果图的大小,类型	
	dst_image.create(img.rows,img.cols,img.type());

	//记录起始时间
	double time_0 = static_cast<double>(getTickCount());

	//调用颜色空间缩减函数
	//colorReduce(img,dst_image,32);
	//colorReduce_C(img, dst_image, 32);//0.00674778s
	//colorReduce_iterator(img, dst_image, 32);//0.0110831--0.00992691s
	colorReduce_at(img, dst_image, 32);//0.00983608s

	//计算运行时间并输出
	time_0 = ((double)getTickCount() - time_0) / getTickFrequency();
	cout << "此方法运行时间" << time_0 << "秒" << endl;//输出运行时间

	imshow("效果图", dst_image);

	imshow("效果图1", img);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
