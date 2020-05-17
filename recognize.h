/*----------------------------
 *   @file：     recognize.h
 *   @version：  1.00[By ZST]
 *   @date：     2020-5-12
 *   @brief：    数字识别 头文件
 *   @Author：   Zheng Shitao 郑时涛
 *   https://github.com/zhengshitao0328/number_recognize-opencv3
 *----------------------------
 */
#ifndef _recognize_H_
#define _recognize_H_
#include <opencv2/opencv.hpp>
#include <vector>
#include "model.h"
using namespace cv;
using namespace std;
class recognize {
public:
	Mat scr;  //原三通道图像
    Mat dst;  //灰度目标图像
    vector<Mat> models;  //模板容器
    vector<Rect> rects;  //数字框容器
public:
	recognize(Mat input_scr, Mat input_dst);
	void prepare();
    void Get_odj_box();
    void Recognize_All();
    void Number_recognize();
	void result_write();
    int distance(Mat scr1, Mat model);
    int recognize_single(Mat scr1);
};
#endif
