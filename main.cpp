#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "model.h"
#include "recognize.h"
using namespace cv;
using namespace std;
int main()
{   
	
	Mat scr = imread("D:\\duo3.png");                           //��ȡ��ͨ��ԭͼ��
	Mat dst = imread("D:\\duo3.png", CV_LOAD_IMAGE_GRAYSCALE);  //��ȡ�Ҷ�ͼ��
	recognize recog = recognize(scr, dst);
	recog.Number_recognize();
	
	

	/**
	Mat dst = imread("D:\\duo1.png", CV_LOAD_IMAGE_GRAYSCALE);
	threshold(dst, dst, 80,255, THRESH_BINARY_INV|THRESH_OTSU);//��ͼ����ж�ֵ��
	Mat element_e = getStructuringElement(MORPH_RECT, Size(1, 1));//��ʴ�������ں�
	Mat element_d = getStructuringElement(MORPH_RECT, Size(3, 3));//���Ͳ������ں�
	Mat dst1, dst2;
	erode(dst, dst1, element_e);//��ʴ
	dilate(dst1, dst2, element_d);//����
	//erode(dst1, dst2, element);//��ʴ
	//dst = dst1;
	imwrite("D:\\zxf.png", dst2);**/
	/**
	Mat dst = imread("D:\\1.png");
	Mat dst1;
	resize(dst, dst1, Size(108, 87));
	imwrite("D:\\1111.png", dst1);
	**/
}