/*----------------------------
��ȡ����ͼƬ�γ�������
------------------------------
*/

#pragma once
#include"tree_class.h"

//������
class My_Voxel
{
public:
	My_Voxel(unsigned int _interval,int length);
	~My_Voxel();
	unsigned int getMaxLenthAll();//��ȡ���ߴ�
	unsigned int getInterval(); //��ȡͼƬ���

private:
	unsigned int getMaxLenthOne(Mat& _image);
	void get_images(); //��ȡͼƬ

public:
	vector<Mat> AllImage_m; //����ͼƬ�ľ�������
	unsigned int cols; //��
	unsigned int rows; //��
	unsigned int minlenth;
	//int img_long;

private:
	unsigned int Interval_m; //ͼƬ���
	unsigned int MaxLenthAll_m; //
};