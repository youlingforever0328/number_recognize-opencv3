/*----------------------------
 *   @file��     model.cpp
 *   @version��  1.00[By ZST]
 *   @date��     2020-5-10
 *   @brief��    ����ʶ��ģ����������ʵ��  Դ�ļ�
 *   @Author��   Zheng Shitao ֣ʱ��
 *   http:\\github
 *----------------------------
 */
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "model.h"
using namespace cv;
using namespace std;
/**********************
funtion��  ͳ��ÿһ�е�����ֵ�ĺ�
parameter��������ͼ��
return:    ��
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
funtion��  ͳ��ÿһ�е�����ֵ�ĺ�
parameter��������ͼ��
return:    ��
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
funtion��  ��ֱ�ָ�ͼ�񣨴������ң�����1-9�ָ��
parameter���ָ����ʼλ�ã���ߣ������ָ��ͼ�� ���洢ģ������� 
return:    ��һ�ηָ����ʼ�㣨��ߣ�
**********************/
int cut_image_y(int col, Mat dst, vector<Mat>& models)
{
	int right = 0;
	int left = 0;
	int j = 0;
	
	if (col == 0)//��ģ�����֡�1���������⴦��
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
funtion��  ˮƽ�ָ�ͼ�񣨴������£���ȥ������֮��Ķ��ಿ��
parameter��ģ����ţ�1-9�������ָ��ͼ��
return:    ��
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
funtion��  �ֱ�ȥ������ģ��1-9֮��Ķ��ಿ��
parameter����
return:    ��
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
funtion��  �������ͼ���9��ģ��
parameter����
return:    ��
**********************/
void Get_Model(vector<Mat>& models)
{
	Rect rect(0, 690, 2050, 220);//[  start_x,  start_y,  width, height  ]
	Mat scr = imread("D:\\zx.jpg", CV_LOAD_IMAGE_GRAYSCALE);//��ȡ�Ҷ�ͼ��
	threshold(scr, scr, 240, 255, 1);//��ͼ����ж�ֵ��
	Mat dst = scr(rect);//��ȡģ��ͼ������ֲ���
	imwrite("D:\\model_zx.jpg", dst);
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));//��ʴ�����Ͳ������ں�
	Mat dst1, dst2;
	erode(dst, dst1, element);//��ʴ
	dilate(dst1, dst2, element);//����
	int right = 0;
	for (int i = 0; i < 9; i++)//�ָ�1-9������ģ�壬�����棺
	{
		right = cut_image_y(right,dst2, models);
	}
	cut_model(models);
}
