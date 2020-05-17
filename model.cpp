/*----------------------------
 *   @file：     model.cpp
 *   @version：  1.00[By ZST]
 *   @date：     2020-5-10
 *   @brief：    数字识别模板制作函数实现  源文件
 *   @Author：   Zheng Shitao 郑时涛
 *   https://github.com/zhengshitao0328/number_recognize-opencv3
 *----------------------------
 */
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "model.h"
using namespace cv;
using namespace std;
/**********************
funtion：  统计每一列的像素值的和
parameter：列数，图像
return:    和
**********************/
int col_total(int col, Mat input)
{
	int total = 0;
	for (int i = 0; i < input.rows; i++)
	{
		total += input.at<uchar>(i, col);
	}
	return total;
}
/**********************
funtion：  统计每一行的像素值的和
parameter：行数，图像
return:    和
**********************/
int row_total(int row, Mat input)
{
	int total = 0;
	for (int j = 0; j < input.cols; j++)
	{
		total += input.at<uchar>(row, j);
	}
	return total;
}
/**********************
funtion：  垂直分割图像（从左往右），将1-9分割开来
parameter：分割的起始位置（左边），待分割的图像 ，存储模板的容器 
return:    下一次分割的起始点（左边）
**********************/
int cut_image_y(int col, Mat dst, vector<Mat>& models)
{
	int right = 0;
	int left = 0;
	int j = 0;
	
	if (col == 0)//对模板数字“1”进行特殊处理
	{
		Mat model, dst2;
		dst2 = dst.clone();
		Rect rec(212, 0, 108, dst.rows);
		model = dst2(rec);
		models.push_back(model);
		return 320;
	}
	for (j = col; j < dst.cols; j++)
	{
		if (col_total(j, dst) > 0)
		{
			right = j;
			left = j;
			break;
		}
	}
	for (j = right; j < dst.cols; j++)
	{
		if (col_total(j, dst) < 1)
		{
			right = j;
			break;
		}
	}
	//printf("left=%d,right=%d", left, right);
	Mat model, dst2;
	dst2 = dst.clone();
	Rect rec(left , 0, right - left , dst.rows);
	model = dst2(rec);
	models.push_back(model);
	//imwrite("D:\\model_" + std::to_string(num) + ".jpg", model);
	return right;
}
/**********************
funtion：  水平分割图像（从上往下），去除数字之外的多余部分
parameter：模板序号（1-9），待分割的图像
return:    无
**********************/
Mat cut_image_x(int num, Mat dst)
{
	int top = 0;
	int bot = 0;
	int i = 0;
	for (i = 0; i < dst.rows; i++)
	{
		if (row_total(i, dst) > 0)
		{
			top = i;
			bot = i;
			break;
		}
	}

	for (i = bot; i < dst.rows; i++)
	{
		if (row_total(i, dst) <= 0)
		{
			bot = i;
			break;
		}
	}
	//printf("top=%d,bot=%d", top, bot);
	Mat model, dst2;
	dst2 = dst.clone();
	Rect rec(0, top, dst.cols, bot - top);
	model = dst2(rec);
	imwrite("D:\\model_s" + std::to_string(num) + ".jpg", model);
	return model;
}
/**********************
funtion：  分别去除数字模板1-9之外的多余部分
parameter：无
return:    无
**********************/
void cut_model(vector<Mat>& models)
{
	for (int i = 0; i < 9; i++)
	{
		Mat a=cut_image_x(i, models[i]);
		models[i] = a;
	}
}
/**********************
funtion：  获得数字图像的9个模板
parameter：无
return:    无
**********************/
void Get_Model(vector<Mat>& models)
{
	Rect rect(0, 690, 2050, 220);//[  start_x,  start_y,  width, height  ]
	Mat scr = imread("D:\\zx.jpg", CV_LOAD_IMAGE_GRAYSCALE);//读取灰度图像
	threshold(scr, scr, 240, 255, 1);//对图像进行二值化
	Mat dst = scr(rect);//截取模板图像的数字部分
	imwrite("D:\\model_zx.jpg", dst);
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));//腐蚀或膨胀操作的内核
	Mat dst1, dst2;
	erode(dst, dst1, element);//腐蚀
	dilate(dst1, dst2, element);//膨胀
	int right = 0;
	for (int i = 0; i < 9; i++)//分割1-9的数字模板，并保存：
	{
		right = cut_image_y(right,dst2, models);
	}
	cut_model(models);
}
