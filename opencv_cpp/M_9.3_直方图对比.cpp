/*
9.3直方图对比
使用某些具体的标准来比较两个直方图的相似度;
选择一个衡量直方图相似度的对比标准;
compareHist()函数来对比两个直方图的相似度,
次函数返回值是d(H1,H2);
compareHist()函数用于对两幅直方图进行比较,
C++:double compareHist(InputArray H1,InputArray H2,int method)
C++:double compareHist(const SparseMat&H1,const SparseMat&H2,int method)
前面两个参数是要比较的大小相同的直方图,第三个变量是所选择的标准距离;

四种比较方法:
1,相关,Correlation(method=CV_COMP_CORREL)
2,卡方,Chi-Square(method=CV_COMP_CHISQR)
3,直方图相交,Intersection(method=CV_COMP_INTERSECT)
4,距离,Bhattacharyya (method=CV_COMP_BHATTACHARYYA)
*/
//代码中的MatND类是用于存储直方图的一种数据结构;

/*
代码中将基准图像与它自身及其半身图像进行对比;
当基准图像直方图及其自身进行对比时,会产生完美的匹配;
当与来源与同一样的背景环境的半自身图对比时,应该会有比较高的相似度;
当与来自不同亮度光照条件的其余两张测试图像对比时,匹配度应该不是很好;

Correlation和Intersection标准,值越大表示相似度越高;


*/


#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
//声明储存基准图像和另外两张对比图像的矩阵(RGB和HSV)
Mat src_img_base, HSV_img_base;
Mat src_img_test_1, HSV_img_test_1;
Mat src_img_test_2, HSV_img_test_2;
Mat HSV_img_halfDown;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int main()
{
	//载入基准图像(src_img_base)和两张测试图像(src_img_test_1,src_img_test_2),并且显示
	src_img_base = imread("lena.jpg", 1);//读入图片数据
	if (src_img_base.empty())
	{
		cout << "can not open or find the src_img_base" << endl;
		system("pause");
		return -1;
	}
	src_img_test_1 = imread("lena_2.jpg", 1);//读入图片数据
	if (src_img_test_1.empty())
	{
		cout << "can not open or find the src_img_test_1" << endl;
		system("pause");
		return -1;
	}
	src_img_test_2 = imread("lena_3.jpg", 1);//读入图片数据
	if (src_img_test_2.empty())
	{
		cout << "can not open or find the src_img_test_2" << endl;
		system("pause");
		return -1;
	}
	imshow("src_img_base", src_img_base);
	imshow("src_img_test_1", src_img_test_1);
	imshow("src_img_test_2", src_img_test_2);

	//将图像由BGR色彩空间转换到HSV色彩空间
	cvtColor(src_img_base, HSV_img_base,COLOR_BGR2HSV);
	cvtColor(src_img_test_1, HSV_img_test_1, COLOR_BGR2HSV);
	cvtColor(src_img_test_2, HSV_img_test_2, COLOR_BGR2HSV);
	//创建包含基准图像下半部分的半身图像(HSV格式)
	HSV_img_halfDown = HSV_img_base(Range(HSV_img_base.rows/2,HSV_img_base.rows-1),Range(0,HSV_img_base.cols-1));
	//初始化计算直方图需要的实参
	//对hue通道使用30个bin,对saturation通道使用32个bin
	int h_bins = 50;
	int s_bins = 60;
	int histSize[] = { h_bins ,s_bins };
	//hue的取值范围从0-256,saturation取值范围从0到180
	float h_ranges[] = { 0,256 };
	float s_ranges[] = { 0,180 };
	const float* ranges[] = { h_ranges,s_ranges };
	//使用第0通道和第1通道
	int channels[] = { 0,1 };

	//创建储存直方图的MatND类的实例
	MatND baseHist;
	MatND halfDownHist;
	MatND testHist1;
	MatND testHist2;

	//计算基准图像,两张测试图像,半身基准图像的HSV直方图
	calcHist(&HSV_img_base,1,channels,Mat(),baseHist,2, histSize,ranges,true,false);
	normalize(baseHist, baseHist, 0,1, NORM_MINMAX, -1, Mat());

	calcHist(&HSV_img_halfDown, 1, channels, Mat(), halfDownHist, 2, histSize, ranges, true, false);
	normalize(halfDownHist, halfDownHist, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&HSV_img_test_1, 1, channels, Mat(), testHist1, 2, histSize, ranges, true, false);
	normalize(testHist1, testHist1, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&HSV_img_test_2, 1, channels, Mat(), testHist2, 2, histSize, ranges, true, false);
	normalize(testHist2, testHist2, 0, 1, NORM_MINMAX, -1, Mat());
	
	//按顺序使用4中对比标准将基准图像的直方图与其余各直方图进行对比
	for (size_t i = 0; i < 4; i++)
	{
		int compare_method = i;
		double base_base = compareHist(baseHist,baseHist,compare_method);
		double base_half = compareHist(baseHist, halfDownHist, compare_method);
		double base_test1 = compareHist(baseHist, testHist1, compare_method);
		double base_test2 = compareHist(baseHist, testHist2, compare_method);
		//输出结果
		//printf("方法[%d]的匹配结果如下:\n",i);
		//printf("[基准图 - 基准图]:%f, [基准图 - 半身图] : %f",base_base,base_half);
		//printf("[基准图 - 测试图1]:%f, [基准图 - 测试图2] : %f\n",base_test1,base_test2);
		cout << "方法[" << i << "]的匹配结果如下:" << endl;
		cout << "[基准图 - 基准图0]:" << base_base << "[基准图 - 半身图0] : " << base_half << endl;
		cout << "[基准图 - 测试图1]:" << base_test1 << "[基准图 - 测试图2] :" << base_test2 << endl;
		cout << endl;
	}
	cout << "测试结束" << endl;
	//printf("测试结束\n");
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}