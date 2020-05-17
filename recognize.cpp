/*----------------------------
 *   @file：     recognize.cpp
 *   @version：  1.00[By ZST]
 *   @date：     2020-5-12
 *   @brief：    数字识别及函数实现  源文件
 *   @Author：   Zheng Shitao 郑时涛
 *   https://github.com/zhengshitao0328/number_recognize-opencv3
 *----------------------------
 */
#include "recognize.h"
/**********************
 funtion：  recognize类的构造函数
 parameter：原三通道图像，灰度目标图像
**********************/
recognize::recognize(Mat input_scr, Mat input_dst)
{
	scr = input_scr;//初始化自己的scr属性
    dst = input_dst;//初始化自己的dst属性
}
/**********************
funtion：  dst 预处理
parameter：无
return:    无
**********************/
void recognize::prepare()
{
	threshold(dst, dst, 80, 255, THRESH_BINARY_INV | THRESH_OTSU);//对图像进行二值化
	Mat element_e = getStructuringElement(MORPH_RECT, Size(1, 1));//腐蚀操作的内核
	Mat element_d = getStructuringElement(MORPH_RECT, Size(3, 3));//膨胀操作的内核
	Mat dst1, dst2;
	erode(dst, dst1, element_e);//腐蚀
	dilate(dst1, dst2, element_d);//膨胀
    dst = dst2;
}
/**********************
funtion：  模板匹配法求两张图片之间的距离
parameter：匹配图像，模板图像
return:    两张图片之间的距离
**********************/
int recognize::distance(Mat scr1, Mat model)
{
	if (scr1.size() != model.size())
	{
		printf("The two image is not in the same size！！！！！");
		return 0.0;
	}
	int sum = 0;
	int dis = 0;
	int width = scr1.cols, height = scr1.rows;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			dis = scr1.at<uchar>(i, j) - model.at<uchar>(i, j);
			sum += abs(dis) / 255;
		}
	}
	return sum;
}
/**********************
funtion：  获取 dst 目标图像上所有数字的最小外接框
parameter：无
return:    无
**********************/
void recognize::Get_odj_box()
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(dst, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0, 0));    //提取所有数字的轮廓
	Rect min_box;//数字的最小外接矩形框
	for (int i = 0; i < contours.size(); i++)
	{
		min_box = boundingRect(contours[i]);
		rects.push_back(boundingRect(contours[i]));      //储存最小外接矩形框
	}
}
/**********************
funtion：  识别单个数字
parameter：待识别的分割之后的数字二值化图像，num_img : dst经矩形框截取之后的图像
return:    识别结果
**********************/
int recognize::recognize_single(Mat num_img)
{
	Mat temp;
	long int min = 100000000;
	int recog_num = 0;
	int dis = 0;
	for (int i = 0; i < 9; i++)
	{
		temp = num_img.clone();
		Mat Template = models[i];//已经是二值化后的图像
		resize(temp, temp, Template.size(),INTER_AREA);//调整到和模板一样的大小		
		dis = distance(temp,Template);//求目标与模板之间的距离
		printf("distance = %d\n", dis);
		if (dis < min)
		{
			min = dis;
			recog_num = i + 1;
		}
	}
	printf("图片与模板的最短距离是%d \n", min);
	printf("匹配的数字是%d\n", recog_num);
	return recog_num;
}
/**********************
funtion：  识别一张图片上的所有数字
parameter：无
return:    无
**********************/
void recognize::Recognize_All()
{
	int num = 0; //存储数字识别的结果
	Mat num_img, dst_temp;
	dst_temp = dst.clone();
	for (int i = 0; i < rects.size(); i++) //对图像中所有数字分别识别
	{
		num_img = dst_temp(rects[i]);      //截取副本dst的数字部分
		rectangle(scr, rects[i], CV_RGB(255, 0, 0));  //在自己的原图上标出数字区域框
		num = recognize_single(num_img);  //匹配得到识别结果
		putText(scr,
			std::to_string(num),
			Point(rects[i].x, rects[i].y - 5),
			FONT_HERSHEY_COMPLEX,
			2,
			CV_RGB(0, 0, 205));//在原图像上标出别结果
	}
}
/**********************
funtion：  保存识别结果
parameter：无
return:    无
**********************/
void recognize::result_write()
{
	imwrite("D:\\result.jpg", scr);
}
/**********************
funtion：  识别数字主函数
parameter：无
return:    无
**********************/
void recognize::Number_recognize()
{
	Get_Model(models);//填充自己的models, 得到9个模板图像;
	prepare();        //预处理目标图像,处理 dst；
	Get_odj_box();    //得到所有数字框，通过 自己的 dst 填充 自己的 rects
	Recognize_All();  //识别所有数字
	result_write();   //保存结果
}
