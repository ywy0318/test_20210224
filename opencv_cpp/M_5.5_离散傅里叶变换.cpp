/*
��ɢ����Ҷ�任:��ָ����Ҷ�任��ʱ���Ƶ���϶�������ɢ����ʽ,
��ʱ���źŵĲ���,�任Ϊ����ɢʱ�丵��Ҷ�任(DTFT)Ƶ�����;
��ʽ��,�任����(ʱ���Ƶ����)�����������޳���,��ʵ�������������ж�Ӧ��
����Ϊ����ɢ�����źŵ���ֵ����;��ʹ�����޳�����ɢ�ź���DFT,ҲӦ������
�����������س������ź��ٽ��б任;ʵ��Ӧ����,ͨ�����ÿ��ٸ���Ҷ�任����Ч����DFT;

�任֮��õ�ʵ��ͼ�������ͼ����߷���ͼ�����λͼ��;
ʵ��ͼ�������ʹ���˷���ͼ��,����ͼ�������Դͼ��ļ�������������Ҫ�ļ�����Ϣ;

�����Ҫͨ���޸ķ���ͼ�������λͼ��ķ���������޸�ԭ�ռ�ͼ��,��Ҫʹ���渵��Ҷ�任�õ�
�޸ĺ�Ŀռ�ͼ��;�����ͱ���ͬʱ��������ͼ�����λͼ����;

��Ƶ������,����һ��ͼ��,
��Ƶ���ִ�����ͼ���ϸ�ڣ�������Ϣ;��Ƶ���ִ�����ͼ���������Ϣ;
���һ�����µ�ͼ��ʹ�õ�ͨ�˲���,��ô�˲���Ľ����ʣ��������;

���ͼ���յ�������ǡ��λ��ĳ���ض���"Ƶ��"��Χ,�����ͨ���˲�����
�ָ�ԭ����ͼ��;

����Ҷ�任��ͼ�����п�������ͼ����ǿ��ͼ��ȥ��,ͼ��ָ�ָ��Ե���,
ͼ��������ȡ,ͼ��ѹ��;

dft()�������
dft�����������Ƕ�һά���߶�ά�������������������߷�����ɢ����Ҷ�任;
C++:void dft(InputArray src,OutputArray dst,int flags=0,int nonzerorows=0)

��һ������:InputArray���͵�src,������󣬿���Ϊʵ��������������;
�ڶ�������:OutputArray���͵�dst;�������ú��������,����������,
��ߴ������ȡ���ڱ�ʶ��,Ҳ���ǵ���������flags;
������������int���͵�flags;ת���ı�ʶ��,Ĭ��ֵΪ0,ȡֵΪ�±�:
DFT_INVERSE  ��һά���߶�ά��任����Ĭ�ϵ�����任
DFT_SCALE   ���ű�����ʶ��,������������1/N��������,ͨ������
			DFT_INVERSEһ��ʹ��
DFT_ROWS	����������ÿ�н���������߷���ı任,�˱�ʶ�������ڴ������ʸ��
			��ʱ�����ڼ�С��Դ����,��Щ����������ά���߸�ά�任�ȸ��Ӳ���;

DFT_COMPLEX_OUTPUT	����һά���άʵ���������任,�����Ľ����Ȼ�Ǹ�������,
					��ӵ�и����Ĺ���Գ���(CCS),���Կ��Ա�д��һ��ӵ��ͬ���ߴ��ʵ������;

DFT_REAL_OUTPUT     ����һά���߶�ά�������鷴�任;�����Ľ��ͨ����һ����С��ͬ�ĸ�����;
					�������ľ����и����Ĺ���Գ���
					(������һ������DFT_COMPLEX_OUTPUT��ʶ�������任���),������ʵ����;



���ĸ�����:int���͵�nonzeroRows,��Ĭ��ֵΪ0,���˲�������Ϊ��0ʱ,
			(������ȡֵΪ��Ҫ�������һ�е�ֵ,����C.rows),���������ֻ��
			�������ĵ�һ�������а�������Ԫ��(û������DFT_INVERSE��ʶ��)
			��ֻ���������ĵ�һ�������а�������Ԫ��(������DFT_INVERSE��ʶ��)
			�����Ļ�,�����Ϳɶ��������и���Ч�Ĵ���,�Խ�ʡʱ�俪��;
			�ڲ���DFT���������ʱ�ǳ���Ч;
*/


/*
void cvMulSpectrums( const CvArr* src1, const CvArr* src2, CvArr* dst, int flags );
src1
��һ��������
src2
�ڶ���������
dst
������飬��������������ͬ�����ͺʹ�С��
flags
�����оٵ�ֵ�����:
CV_DXT_ROWS - �������ÿһ����Ϊһ��������Ƶ�� (�μ� cvDFT �Ĳ�������).
CV_DXT_MUL_CONJ - �����˷�֮ǰȡ�ڶ�����������Ĺ���.
*/

/*
����DFT���ųߴ��С:getOptimalDFTSize()����
���ظ��������ߴ�ĸ���Ҷ���ųߴ��С,Ϊ�˵�����ɢ����Ҷ�任�������ٶ�,
��Ҫ����ͼ�񣬾���������٣��������������õ�;
int getOptimalDFTSize(int vecsize)
����Ϊint���͵�vecsize,�����ߴ�,��ͼƬ��rows,cols;

*/

/*
����ͼ��߽�:copyMakeBorder()����
copyMakeBorder����������������ͼ��߽�
void copyMakeBorder(InputArray src,OutputArray dst,int top,int bottom
,int left,int right,int borderType,const Scalar& value=Scalar())

��һ������,InputArray���͵�src,����ͼ��Դͼ��
�ڶ�������,OutputArray���͵�dst,�������ú����������������,�������������
			��ź������ú��������,���ԴͼƬ��һ���ĳߴ������,
			��sizeӦΪSize(src.cols+left+right,src.rows+top+bottom)

���������ĸ�����,�ֱ�Ϊint���͵�top,bottom,left,right���ֱ��ʾ��
Դͼ����ĸ������������˶�������,����:top=2,bottom=2,left=2,right=2
����ζ����Դͼ����������Ҹ������������ؿ�ȵı߽�;

���߸�����,borderType���͵�,�߽�����,������ȡֵΪBORDER_CONSTANT,
			���Բο�borderInterpolate()�õ������ϸ��

�ڰ˸�����,const Scalar&���͵�value,Ĭ��ֵScalar(),�������ΪĬ��Ϊ0;
			��borderTypeȡֵΪBORDER_CONSTANTʱ�����������ʾ�߽�ֵ

*/
/*
�����άʸ���ķ���:magnitude()����
void magnitude(InputArray x,InputArray y,OutputArray magnitude)
x--��ʾʸ���ĸ�����X����ֵ,ʵ��
y--��ʾʸ���ĸ�����Y����ֵ,�鲿
OutputArray���͵�magnitude,����ķ�ֵ,���͵�һ������x����ͬ���ĳߴ������

magnitude()����ԭ��:dst(I)=(X(I)^2+Y(I)^2)^(1/2)
*/

/*
������Ȼ����:log()����
log�����Ĺ����Ǽ���ÿ������Ԫ�ؾ���ֵ����Ȼ����;
��һ������Ϊ����ͼ��,�ڶ�������Ϊ�õ��Ķ���ֵ
dst(I)=
{
	log|src(I)|,if src(I)!=0
	C	otherwise
}

*/

/*
�����һ��:normalize()����
void normalize(InputArray src,OutputArray,dst,double alpha=1,double beta=0,
int norm_type=NORM_L2,int dtype=-1,InputArray mask=noArray())

��һ������:InputArray���͵�src,
�ڶ�������:OutputArray���͵�dst,�������ú������������������,��ԭͼƬ��һ���ĳߴ������
����������:double ���͵�alpha,��һ��������ֵ,Ĭ��Ϊ1
���ĸ�����:double���͵�beta,��һ�������ֵ,Ĭ��Ϊ0----��Сֵ
���������:int���͵�norm_type;��һ������,��NORM_INT,NORM_L1,
			NORM_L2,NORM_MINMAX�Ȳ�����ѡ,Ĭ��ֵNORM_L2;

����������:int���͵�dtype,Ĭ��ֵΪ-1�����˲���ȡ��ֵ,��������src��ͬ��������;
			��������src��ͬ����ͨ����,�Ҵ�ʱͼ�����ΪCV_MAT_DEPTH(dtype)

���߸�����:InputArray���͵�mask,��ѡ�Ĳ�������,Ĭ��ֵnoArray();

*/


#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
//ʹ��dft��������������άʵ��������ʾ������Ƭ��
/*
void convolveDFT(InputArray A, InputArray B, OutputArray C)
{
	//��ʼ���������
	C.create(abs(A.rows - B.rows) + 1,abs(A.cols-B.cols)+1,A.type());
	Size dft_size;

	//����DFT�任�ĳߴ�
	dft_size.width = getOptimalDFTSize(A.cols+B.cols-1);
	dft_size.height = getOptimalDFTSize(A.rows+B.rows-1);

	//������ʱ����������ʼ������
	Mat temp_A(dft_size, A.type(), Scalar::all(0));
	Mat temp_B(dft_size, B.type(), Scalar::all(0));

	//�ֱ���A��B��temp_A��temp_B�����Ͻ�
	Mat roi_A(temp_A, Rect(0, 0, A.cols, A.rows));
	A.copyTo(roi_A);
	Mat roi_B(temp_B,Rect(0,0,B.cols,B.rows));
	B.copyTo(roi_B);


	//�͵ز���(in-place),���п��ٸ���Ҷ�任,����nonzeroRows������Ϊ����,
	//�Խ��и��ӿ��ٵĴ���
	dft(temp_A, temp_A, 0, A.rows);
	dft(temp_B, temp_B, 0, B.rows);

	//���õ���Ƶ�����,��������temp_A---����
	mulSpectrums(temp_A, temp_B, temp_A, DFT_COMPLEX_OUTPUT);

	//������任ΪƵ��,���ܽ����(result rows)��Ϊ����,ֻ��Ҫ����C.rows
	//�ĵ�һ��,������nonzeroRows=C.rows
	dft(temp_A,temp_B,DFT_INVERSE+DFT_SCALE,C.rows);

	//��������Ƶ�C��
	temp_A(Rect(0, 0, C.cols, c.rows)).copyTo(C);
	//���е���ʱ�����������Զ��ͷ�,������β����
}*/

int main()
{
	Mat src_img, des_img, gray_img, edge;

	src_img = imread("lena.jpg", 0);//����ͼƬ����,�Ҷ�ģʽ
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);
	//ShowHelpText();ûɶ�ã�����opencv�Դ��ĺ���

	//��ͼ����������ѵĳߴ�,�߽���0����
	//��ɢ����Ҷ�任�������ٶ���ͼƬ�ĳߴ��кܴ��ϵ;
	//��ͼ��ߴ���2,3,5,��������ʱ,�����ٶ����;
	//Ϊ�˴ﵽ���ټ����Ŀ��,��������µı�Ե���صķ���,
	//������ͼ��ߴ�;
	int m = getOptimalDFTSize(src_img.rows);
	int n = getOptimalDFTSize(src_img.cols);

	//����ӵ����س�ʼ��Ϊ0
	Mat padded;
	copyMakeBorder(src_img, padded, 0, m - src_img.rows, 0, n - src_img.cols, BORDER_CONSTANT, Scalar::all(0));

	//Ϊ����Ҷ�任�Ľ��(ʵ�����鲿)����洢�ռ�
	//��planes������Ϻϲ���һ����ͨ��������complexI
	//����Ҷ�任�Ľ���Ǹ���,�����˵����ÿ��ԭͼ��ֵ,�����������ͼ��ֵ,
	//����,Ƶ��ֵ��ΧԶԶ�����ռ�ֵ��Χ,�������Ҫ��Ƶ�����float��ʽ��,
	//�������ǽ�����ͼ��ת���ɸ������ͣ������һ������ͨ�������渴������;
	Mat planes[] = { Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F) };
	Mat complexI;
	merge(planes,2,complexI);

	//���о͵���ɢ����Ҷ�任(in-place,�������Ϊͬһͼ��)
	dft(complexI,complexI);

	//
	//������ת��Ϊ��ֵ,��=>log(1+sqrt(Re(DFT(I))^2+Im(DFT(I))^2))
	split(complexI,planes);//����ͨ������complexI����ɼ�����ͨ������
						//planes[0] = Re(DFT(I),planes[1] = Im(DFT(I)));
	magnitude(planes[0],planes[1],planes[0]);//planes[0]=magnitude
	Mat magnitude_image = planes[0];

	//���ж����߶�����(logarithmic scale)
	//����Ҷ�任�ķ���ֵ��Χ�󵽲��ʺ�����Ļ����ʾ,��ֵ����Ļ����ʾΪ
	//�׵�,��ַΪ�ڵ�,�ߵ�ַ�ı任�޷���Ч�ֱ�,Ϊ������Ļ��͹�Ըߵͱ任��������
	//�ö����߶����滻���Գ߶�
	magnitude_image += Scalar::all(1);
	log(magnitude_image, magnitude_image);//����Ȼ����

	//���к��طֲ�����ͼ����
	//���м���������������,����Ƶ�ײü�
	//�ڶ���������ͼ�����ڽ�����ӵ������޳�����Ϊ�˷�����ʾ,
	//���·ֲ�����ͼ����λ��,(�����岽�õ��ķ���ͼ���м仮��,)
	//�õ�4��1/4����ͼ��,��ÿ����ͼ��,��������ͼ��һ�����ޣ�
	//���·ֲ������ĸ������ص���ͼƬ����
	magnitude_image = magnitude_image(Rect(0, 0, magnitude_image.cols&-2, magnitude_image.rows&-2));

	//�������и���Ҷͼ���е�����,ʹ��ԭ��λ��ͼ������;
	int cx = magnitude_image.cols / 2;
	int cy = magnitude_image.rows / 2;
	Mat q0(magnitude_image,Rect(0,0,cx,cy));//ROI��������Ͻ�
	Mat q1(magnitude_image, Rect(cx, 0, cx, cy));//ROI��������Ͻ�
	Mat q2(magnitude_image, Rect(0, cy, cx, cy));//ROI��������½�
	Mat q3(magnitude_image, Rect(cx, cy, cx, cy));//ROI��������½�

	//��������(���������½��н���)
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	//��������(���������½��н���)
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//��һ������0��1֮��ĸ���ֵm������任Ϊ���ӵ�ͼ���ʽ
	//Ϊ����ʾ,�����طֲ���ķ���ͼ,����ͼֵ��Ȼ������
	//����ʾ��Χ[0,1]
	//opencv2
	//normalize(magnitude_image,magnitude_image,0,1,CV_MINMAX);
	//opencv3
	normalize(magnitude_image, magnitude_image, 0, 1, NORM_MINMAX);

	//��ʾЧ��ͼ
	imshow("Ƶ�׷�ֵ", magnitude_image);
	waitKey();

	cout << CV_MAJOR_VERSION << endl;
	waitKey(0);
	system("pause");
	return 0;
}
