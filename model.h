/*----------------------------
 *   @file：     model.h
 *   @version：  1.00[By ZST]
 *   @date：     2020-5-10
 *   @brief：    数字识别模板制作  头文件
 *   @Author：   Zheng Shitao 郑时涛
 *   http:\\github
 *----------------------------
 */
#ifndef _model_H_
#define _model_H_
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
using namespace cv;
using namespace std;
using namespace cv;
int col_total(int col, Mat input);
int row_total(int row, Mat input);
int cut_image_y(int col, Mat dst, vector<Mat>& models);
Mat cut_image_x(int num, Mat dst);
void cut_model(vector<Mat>& models);
void Get_Model(vector<Mat>& models);
#endif#pragma once
