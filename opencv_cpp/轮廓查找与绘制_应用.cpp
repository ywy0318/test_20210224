void CImageProcessDlg::OnBnClickedButtonTest() //�ѷ���
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Mat Img = img.clone();
	Mat gray;
	Mat element0 = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat element1 = getStructuringElement(MORPH_RECT, Size(7, 7));
	cvtColor(Img, gray, COLOR_RGB2GRAY);
	GaussianBlur(gray, gray, Size(25, 25), 0, 0);  //---��˹�˲�
	adaptiveThreshold(gray, gray, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 3); //---����Ӧ��ֵ 
	erode(gray, gray, element0);
	dilate(gray, gray, element1);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	drawContours(img, contours, -1, Scalar(0, 0, 255), 3, 8, hierarchy);
	if (!(img.empty()))
	{
		resize(img, img, Size(rect.Width(), rect.Height()));   //Resize��С
		imshow("PIC", img);  //��ʾ���
	}
	if (contours.size()>0)
	{
		color_flag = 2;
		SetDlgItemText(IDC_EDIT_RESULT0, _T("ǽ�����ѷ�"));
	}
	else
	{
		color_flag = 1;
		SetDlgItemText(IDC_EDIT_RESULT0, _T("ǽ������"));
	}
}