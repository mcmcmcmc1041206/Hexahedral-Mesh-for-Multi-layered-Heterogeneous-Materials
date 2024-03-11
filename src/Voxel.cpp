#include"Voxel.h"
My_Voxel::My_Voxel(unsigned int _interval,int length)
{
	this->Interval_m = _interval;
	//this->get_images();
	//this->img_long = this->getMaxLenthOne(this->AllImage_m[0]);
	//this->cols = this->AllImage_m[0].cols;
	//this->rows = this->AllImage_m[0].rows;
}


My_Voxel::~My_Voxel()
{

}

unsigned int My_Voxel::getMaxLenthOne(Mat& _image)
{
	unsigned int col = _image.cols;
	unsigned int row = _image.rows;
	row = row > col ? row : col;
	return row;
}

unsigned int My_Voxel::getMaxLenthAll()
{
	return getMaxLenthOne(AllImage_m[0]) > AllImage_m.size() ? getMaxLenthOne(AllImage_m[0]) : AllImage_m.size();
	/*unsigned int max_lenth = 0;
	vector<unsigned int>* M_L = new vector<unsigned int>;
	for (vector<Mat>::iterator i = this->AllImage_m.begin(); i != this->AllImage_m.end(); i++)
	{
		M_L->push_back(getMaxLenthOne(*i));
	}
	for (vector<unsigned int>::iterator i = M_L->begin(); i != M_L->end(); i++)
	{
		max_lenth = *i > max_lenth ? *i : max_lenth;
	}
	delete M_L;
	return max_lenth;*/
}

unsigned int My_Voxel::getInterval()
{
	return this->Interval_m;
}

//��ȡͼƬ
void My_Voxel::get_images()
{
	string path = "D:\\picture\\CTpicture\\*.jpg";
	std::cout << "��ȡ·����" << path << endl;
	vector<String> fn;
	cv::glob(path, fn, false);
	size_t count = fn.size();
	std::cout << "��ȡͼƬ������" << count << endl;	
	//����ͼƬ���˳����ж�ͼ
	vector<Mat> images; //����ԭʼͼƬ
	vector<Mat> imgGray; //������ж�ֵ����ĻҶ�ͼƬ

	for (int i = 1; i < count+1; i++) 
	{
		string name = "D:\\picture\\CTpicture\\" + to_string(i) + ".jpg";//����������ļ�·���Լ��ļ���
		Mat img = imread(name);
		cout << "name: " << name << endl;

		if (img.empty()) //�ж��Ƿ������ЧͼƬ
		{
			cout << "Please input image path" << endl;
			return;
		}
		images.push_back(img);
	}
#if 0
	//����·��
	string path = "C:\\Users\\xushu\\Desktop\\�����ļ�\\CT\\*.jpg";
	std::cout << "��ȡ·����" << path << endl;
	vector<Mat> images;
	vector<Mat> imgGray;
	//cv::String Ϊ cv �е��ַ�������
	vector<String> fn;
	glob(path, fn, false);
	size_t count = fn.size();
	std::cout << "��ȡͼƬ������" << count << endl;
	for (int i = 0; i < count; i++)
	{
		if (!imread(fn[i]).data)
		{
			cout << "Please input image path" << endl;
			return;
		}
		images.push_back(imread(fn[i]));
	}
#endif

#if 0
	for (int i = 0; i < images.size(); i++)
	{

		Mat* img_G = new Mat;
		Mat* relt = new Mat;
		//�ҶȻ�
		cvtColor(images[i], *img_G, COLOR_BGR2GRAY);
		imgGray.push_back(*img_G);
		//��ֵ��
		threshold(imgGray[i], *relt, 150, 255, THRESH_BINARY);
		AllImage_m.push_back(*relt);
		delete img_G;
		delete relt;
	}
#endif


#if 1
	for (int i = 0; i < images.size(); i++)
	{
		Mat* img_G = new Mat;
		//�ҶȻ�
		cvtColor(images[i], *img_G, COLOR_BGR2GRAY);
		imgGray.push_back(*img_G);


		AllImage_m.push_back(*img_G);
	}
#endif
}