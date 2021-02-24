#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void main() {
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat element2 = getStructuringElement(MORPH_CROSS, Size(5, 5));
	Mat element3 = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	cout << endl << element << endl;
	cout << endl << element2 << endl;
	cout << endl << element3 << endl;
	system("pause");
}