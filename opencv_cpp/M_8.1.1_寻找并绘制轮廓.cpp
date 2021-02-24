/*
8图像轮廓与图像分割修复
canny之类的边缘检测算法可以根据像素之间的差异,检测出轮廓边界
的像素,并没有将轮廓作为一个整体;

一个轮廓一般对应一系列的点,图像中的一条曲线;
findContours()函数从二值图像中查找轮廓;

findContours()函数用于在二值图像中寻找轮廓
C++:void findContours(InputArray image,OutputArrayofArrays contours,OutputArray hierarchy
,int mode ,int mthod ,Point offset=Point())

第一个参数:InputArray 类型的image,输入图像,源图像,Mat类型的对象,8位单通道像素;
图像的非零像素被视为1,0像素值被保留为0;所以图像为二进制;
可以使用compare(),inrange(),threshold(),adaptivethreshold(),
canny()等函数由灰度图或彩色图创建二进制图像;
此函数会在提取图像的轮廓的同时修改图像的内容;

第二个参数:OutputArrayOfArrays类型的contours,检测到的轮廓,函数调用后的
运算结果存在这里,每个轮廓存储为一个点向量,即用Point类型的vector表示;

第三个参数:OutputArray类型的hierarchy,可选的输出向量,包含图像的拓扑信息;
作为轮廓数量的表示,包含了许多元素,每个轮廓contours[i]对应4个hierarchy
元素hierarchy[i][0]--hierarchy[i][3],分别表示后一个轮廓,前一个轮廓,
父轮廓,内嵌轮廓的索引编号,如果没有对应项,对应的hierarchy[i]值设置为
负数;
第四个参数:int类型的mode,轮廓检索模式;
标识符---含义
RETR--EXTERNAL---表示只检测最外侧轮廓,对所有轮廓,设置hierarchy[i][2]=hierarchy[i][3]=-1
RETR_LIST---提取所有轮廓,并且防止在list中,检测的轮廓不建立等级关系;
RETR_CCOMP---提取所有轮廓,并且将其组织为双层结构(two-level hierarchy:顶层为连通域
的外围边界,次层为孔的内层边界)
RETR_TREE--提取所有轮廓,并重新建立网状的轮廓结构; 

第五个参数:int method,为轮廓的近似办法;
CHAIN_APPROX_NONE :获取每个轮廓的每个像素,相邻的两个点的像素位置差不超过1,
即max(abs(x1-x2),abs(y2-y1))==1

CHAIN_APPROX_SIMPLE :压缩水平方向,垂直方向,对角线方向的元素,只保留该方向的
终点坐标,例如一个矩形轮廓只需4个点来保存轮廓信息;
 
CHAIN_APPROX_TC89_L1
CHAIN_APPROX_TC89_KCOS---使用Teh-Chinl链逼近算法中的一个;
第六个参数:Point类型的offset,每个轮廓点的可选偏移量,有默认值
Point();对ROI图像中找出的轮廓,并要在整个图像中进行分析时,整个参数
就可以派上用场;

findContours经常与drawContours配合使用--使用用findContours()函数来检测
到图像的轮廓后,就可以用draeContours等函数将检测到的轮廓绘制出来;
vector<vector<Point>> contours; 
findContours(img,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
//轮廓数组,//获取外轮廓,//获取每个轮廓的每个像素


绘制轮廓:drawContours()函数
drawContours()函数用于在图像中绘制外部或内部轮廓
C++:void drawContours(InputArray image,InputArrayOfarrays contours,
int contourIdx,const Scalar& color,int thickness=1,int linetype=8,
InputArray hierarchy=noArray(),
int maxLevel=INT_MAX,Point=offset=Point())

第二个参数:InputArrayOfArrays类型的contours,所有的输入轮廓;每个轮廓存储为
一个点向量,用point类型的vector表示
第三个参数:int类型的contourIdx,轮廓绘制的指示变量，如果其为负值,
则绘制所有轮廓;
第四个参数:const Scalar&类型的color,轮廓的颜色
第五个参数:int thickness,轮廓线条的粗细度,默认值1,如果为负值,
(thickness=CV_filled),便会绘制在轮廓的内部,可选的FILLED宏;
第六个参数:int类型的lineType,线条的类型,有默认值8;
8(默认值)--8连通线型;
4---4连通线型;
LINE_AA---抗锯齿线型;
第七个参数:InputArray类型的hierarchy,可选的层次结构信息;默认值
noArray();
第八个参数:int类型的maxLevel,表示用于绘制轮廓的最大等级,有默认值
INT_MAX;
第九个参数:Point类型的offset,可选的轮廓偏移参数,用指定的偏移量
offset=(dx,dy)绘制需要绘制的轮廓,有默认值Point();
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
	int index = 0;
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);

	//初始化结果图
	dst_img = Mat::zeros(src_img.rows,src_img.cols,CV_8UC3);

	//src_img去大于阈值119的那部分
	src_img = src_img > 119;
	imshow("src_img>119", src_img);
	//定义轮廓和层次结构
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	 
	//
	findContours(src_img, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	//遍历所有顶层的轮廓,以随机颜色绘制出每个链接组件的颜色
	
	for (; index>=0; index=hierarchy[index][0])
	{
		Scalar color(rand()&255,rand()&255,rand()&255);
		drawContours(dst_img,contours,index,color,FILLED,8,hierarchy);
	}
	imshow("dst_img",dst_img); 
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
