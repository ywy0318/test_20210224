#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
Mat map_x, map_y; 
int update_map(int key);
int main()
{
	system("color 2F");
	printf("system()\n");
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img",CV_WINDOW_AUTOSIZE);
	imshow("src_img", src_img);

	//创建和原始图一样的效果图,x重映射图,y重映射图
	dst_img.create(dst_img.size(),src_img.type());
	map_x.create(src_img.size(),CV_32FC1);
	map_y.create(src_img.size(),CV_32FC1);

	//轮训按键,更新map_x,map_y的值,进行重映射操作并显示效果图
	while (true)
	{
		//获取键盘按键
		int key = waitKey(0);
		//判断esc是否按下,若按下便退出
		if ((key & 255) == 27)
		{
			cout << "程序退出....\n";
			break;
		}
		//根据按下的键盘按键来更新map_x&map_y的值,然后调用remap()进行重映射
		update_map(key);
		remap(src_img, dst_img, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
		imshow("dst_img",dst_img);
	}

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
int update_map(int key)
{
	//双层循环,遍历每一个像素点
	for (size_t i = 0; i < src_img.rows; i++)
	{
		for (int j = 0; j < src_img.cols; j++)
		{
			switch (key)
			{
			case'1'://键盘1按下,进行第一种重映射操作
				if ((i>src_img.cols*0.25)&&(i<src_img.cols*0.75)
					&&(j<src_img.rows*0.75)&&(j>src_img.rows*0.25))
				{
					map_x.at<float>(j, i) = static_cast<float>(2 * (i - src_img.cols*0.25) + 0.5);
					map_y.at<float>(j, i) = static_cast<float>(2 * (j - src_img.rows*0.25) + 0.5);
				}
				else
				{
					map_x.at<float>(j, i) = 0;
					map_y.at<float>(j, i) = 0;
				}
				break;
			case'2':
				map_x.at<float>(j, i) = static_cast<float>(i);
				map_y.at<float>(j, i) = static_cast<float>(src_img.rows - j);
				break;
			case'3':
				map_x.at<float>(j,i)=static_cast<float>(src_img.cols-i);
				map_y.at<float>(j, i) = static_cast<float>(j);
				break;
			case'4':
				map_x.at<float>(j, i) = static_cast<float>(src_img.cols - i);
				map_y.at<float>(j, i) = static_cast<float>(src_img.rows - j);
				break;
			default:
				break;
			}
		}
	}
	return 1;
}