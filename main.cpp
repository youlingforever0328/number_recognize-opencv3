#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "model.h"
#include "recognize.h"
using namespace cv;
using namespace std;
int main()
{   
	
	Mat scr = imread("D:\\duo3.png");                           //读取三通道原图像
	Mat dst = imread("D:\\duo3.png", CV_LOAD_IMAGE_GRAYSCALE);  //读取灰度图像
	recognize recog = recognize(scr, dst);
	recog.Number_recognize();
	
	

	/**
	Mat dst = imread("D:\\duo1.png", CV_LOAD_IMAGE_GRAYSCALE);
	threshold(dst, dst, 80,255, THRESH_BINARY_INV|THRESH_OTSU);//对图像进行二值化
	Mat element_e = getStructuringElement(MORPH_RECT, Size(1, 1));//腐蚀操作的内核
	Mat element_d = getStructuringElement(MORPH_RECT, Size(3, 3));//膨胀操作的内核
	Mat dst1, dst2;
	erode(dst, dst1, element_e);//腐蚀
	dilate(dst1, dst2, element_d);//膨胀
	//erode(dst1, dst2, element);//腐蚀
	//dst = dst1;
	imwrite("D:\\zxf.png", dst2);**/
	/**
	Mat dst = imread("D:\\1.png");
	Mat dst1;
	resize(dst, dst1, Size(108, 87));
	imwrite("D:\\1111.png", dst1);
	**/
}