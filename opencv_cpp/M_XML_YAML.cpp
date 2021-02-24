/*
XML��YAML�ļ����
XML:eXtensible Markup Language ���������Ϊ"����չ��ʶ����"
XML��һ��Ԫ�������,��ν"Ԫ���",���ǿ����߸���������Ҫ�����Լ���
���,������Զ�����<book><name>;
�κ�����XML������������ƶ����Ա��,�����ͬ��Ӧ�ó�����˴���
XML,��һ�����壬�ṹ������,�������ĵ��Ľṹ������;
*******
YAML:��������������Ϊ����,���������ñ�����Ϊ�ص�,���÷�豴ʽ���
��������,YAML��һ�ֿɶ��Ը�,��������������еĸ�ʽ,
�ο��˶�������,XML,C,Python,Perl,�����ʼ���ʽRFC2822

.yml��.yamlͬΪYAML��ʽ�ĺ�׺��
YAML��ͼ��һ�ֱ�XML�����ݵķ�ʽ,�����XML����ɵ�����;

FileStorage������ļ���ʹ������
XML��YAML��ʹ�÷ǳ��㷺���ļ���ʽ,��������XML����YAML
��ʽ���ļ��洢�ͻ�ԭ��ʽ���������ݽṹ,�����Դ洢����������
���ӵ����ݽṹ,����opencv����ܱ���ص����ݽṹ,�Լ�����ԭʼ��������
��:�����͸������ֺ��ı��ַ���

д����߶�ȡ��XML����YAML�ļ��еĹ���
1.>ʵ����һ��FileStorage��Ķ���,��Ĭ�ϴ������Ĺ��캯����ɳ�ʼ��
������FileStorage::open()��Ա����������ʼ��;
2.>ʹ����������<<�����ļ�д�����,����ʹ��>>����
�ļ���ȡ����,����C++�е��ļ����������;
3.>ʹ��FileStorage::release()����������FileStorage
�����,ͬʱ�ر��ļ�;

*/
#include"opencv2/opencv.hpp"
#include<time.h>
using namespace cv;
using namespace std;

void test_XML_YAML_write()
{
	//��ʼ��
	FileStorage fs("test.yaml",FileStorage::WRITE);
	
	//��ʼ�ļ�д��
	fs << "frameCount" << 5;
	time_t rawtime;
	time(&rawtime);
	fs << "calibrationDate" << asctime(localtime(&rawtime));
	Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
	Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0, 001, 0, 0);
	fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
	fs << "features" << "[";
	for (size_t i = 0; i < 3; i++)
	{
		int x = rand() % 640;
		int y = rand() % 480;
		uchar lbp = rand() % 256;
		fs << "{:" << "x" << x << "y" << y << "lbp" << lbp;
		for (size_t j = 0; j < 8; j++)
		{
			fs << ((lbp >> j) & 1);
			fs << "]" << "}";
		}
		fs << "]";
		fs.release();

		print("�ļ���д��ϣ����ڹ���Ŀ¼�²鿴���ɵ��ļ�");
		system("pause");
		return ;
	}
}

void test_XML_YAML_read()
{
	//�ı�console������ɫ
	system("color 6F");
	//��ʼ��
	FileStorage fs_2("test.yaml",FileStorage::READ);
	//��һ�ַ���:��FileNode����
	int frameCount = (int)fs_2["frameCount"];
	std::string date;
	//�ڶ��ַ���,ʹ��FileNode�����>>
	fs_2["calibrateDate"] >> date;
	Mat cameraMatrix2, distCoeffs2;
	fs_2["cameraMatrix2"] >> cameraMatrix2;
	fs_2["distCoeffs2"] >> distCoeffs2;

	cout << "frameCount:" << frameCount << endl;
	cout << "calibrateDate" << date << endl;
	cout << "cameraMatrix2" << cameraMatrix2 << endl;
	cout << "distCoeffs2" << distCoeffs2 << endl;

	FileNode features = fs_2["features"];
	FileNodeIterator it = features.begin(), it_end = features.end();
	int idx = 0;
	std::vector<uchar> lbqval;

	//ʹ��FileNodeIterator��������
	for (; it !=it_end; it++,idx++)
	{
		cout << "features #" << idx << ":";
		cout << "x=" << (int)(*it)["x"] << ",y=" << (int)(*it)["y"]
			<< ",lbp:(";
		//������ʹ��filenode>>std::vector�������������׵Ķ���ֵ����
		(*it)["lbp"] >> lbqval;
		for (size_t i = 0; i < (int)lbqval.size(); i++)
		{
			cout << "" << (int)lbqval[i];
			cout << ")" << endl;

		}
	}
	
	fs_2.release();
	printf("\n�ļ���ȡ���,�������������������");
	system("pause");
	return;
}

//............����
int main()
{
	test_XML_YAML_write();
	test_XML_YAML_read();
}