/*----------------------------
 *   @file��     recognize.h
 *   @version��  1.00[By ZST]
 *   @date��     2020-5-12
 *   @brief��    ����ʶ�� ͷ�ļ�
 *   @Author��   Zheng Shitao ֣ʱ��
 *   http:\\github
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
	Mat scr;  //ԭ��ͨ��ͼ��
    Mat dst;  //�Ҷ�Ŀ��ͼ��
    vector<Mat> models;  //ģ������
    vector<Rect> rects;  //���ֿ�����
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
