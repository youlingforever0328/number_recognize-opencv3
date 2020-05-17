/*----------------------------
 *   @file��     recognize.cpp
 *   @version��  1.00[By ZST]
 *   @date��     2020-5-12
 *   @brief��    ����ʶ�𼰺���ʵ��  Դ�ļ�
 *   @Author��   Zheng Shitao ֣ʱ��
 *   http:\\github
 *----------------------------
 */
#include "recognize.h"
/**********************
 funtion��  recognize��Ĺ��캯��
 parameter��ԭ��ͨ��ͼ�񣬻Ҷ�Ŀ��ͼ��
**********************/
recognize::recognize(Mat input_scr, Mat input_dst)
{
	scr = input_scr;//��ʼ���Լ���scr����
    dst = input_dst;//��ʼ���Լ���dst����
}
/**********************
funtion��  dst Ԥ����
parameter����
return:    ��
**********************/
void recognize::prepare()
{
	threshold(dst, dst, 80, 255, THRESH_BINARY_INV | THRESH_OTSU);//��ͼ����ж�ֵ��
	Mat element_e = getStructuringElement(MORPH_RECT, Size(1, 1));//��ʴ�������ں�
	Mat element_d = getStructuringElement(MORPH_RECT, Size(3, 3));//���Ͳ������ں�
	Mat dst1, dst2;
	erode(dst, dst1, element_e);//��ʴ
	dilate(dst1, dst2, element_d);//����
    dst = dst2;
}
/**********************
funtion��  ģ��ƥ�䷨������ͼƬ֮��ľ���
parameter��ƥ��ͼ��ģ��ͼ��
return:    ����ͼƬ֮��ľ���
**********************/
int recognize::distance(Mat scr1, Mat model)
{
	if (scr1.size() != model.size())
	{
		printf("The two image is not in the same size����������");
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
funtion��  ��ȡ dst Ŀ��ͼ�����������ֵ���С��ӿ�
parameter����
return:    ��
**********************/
void recognize::Get_odj_box()
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(dst, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0, 0));    //��ȡ�������ֵ�����
	Rect min_box;//���ֵ���С��Ӿ��ο�
	for (int i = 0; i < contours.size(); i++)
	{
		min_box = boundingRect(contours[i]);
		rects.push_back(boundingRect(contours[i]));      //������С��Ӿ��ο�
	}
}
/**********************
funtion��  ʶ�𵥸�����
parameter����ʶ��ķָ�֮������ֶ�ֵ��ͼ��num_img : dst�����ο��ȡ֮���ͼ��
return:    ʶ����
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
		Mat Template = models[i];//�Ѿ��Ƕ�ֵ�����ͼ��
		resize(temp, temp, Template.size(),INTER_AREA);//��������ģ��һ���Ĵ�С		
		dis = distance(temp,Template);//��Ŀ����ģ��֮��ľ���
		printf("distance = %d\n", dis);
		if (dis < min)
		{
			min = dis;
			recog_num = i + 1;
		}
	}
	printf("ͼƬ��ģ�����̾�����%d \n", min);
	printf("ƥ���������%d\n", recog_num);
	return recog_num;
}
/**********************
funtion��  ʶ��һ��ͼƬ�ϵ���������
parameter����
return:    ��
**********************/
void recognize::Recognize_All()
{
	int num = 0; //�洢����ʶ��Ľ��
	Mat num_img, dst_temp;
	dst_temp = dst.clone();
	for (int i = 0; i < rects.size(); i++) //��ͼ�����������ֱַ�ʶ��
	{
		num_img = dst_temp(rects[i]);      //��ȡ����dst�����ֲ���
		rectangle(scr, rects[i], CV_RGB(255, 0, 0));  //���Լ���ԭͼ�ϱ�����������
		num = recognize_single(num_img);  //ƥ��õ�ʶ����
		putText(scr,
			std::to_string(num),
			Point(rects[i].x, rects[i].y - 5),
			FONT_HERSHEY_COMPLEX,
			2,
			CV_RGB(0, 0, 205));//��ԭͼ���ϱ������
	}
}
/**********************
funtion��  ����ʶ����
parameter����
return:    ��
**********************/
void recognize::result_write()
{
	imwrite("D:\\result.jpg", scr);
}
/**********************
funtion��  ʶ������������
parameter����
return:    ��
**********************/
void recognize::Number_recognize()
{
	Get_Model(models);//����Լ���models, �õ�9��ģ��ͼ��;
	prepare();        //Ԥ����Ŀ��ͼ��,���� dst��
	Get_odj_box();    //�õ��������ֿ�ͨ�� �Լ��� dst ��� �Լ��� rects
	Recognize_All();  //ʶ����������
	result_write();   //������
}
