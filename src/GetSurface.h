/*----------------------------
��ȡ������������漯��
��ȡ���浥Ԫ
------------------------------
*/
#pragma once
#include"tree_class.h"
#include"OcTree.h"

class myCompare
{
public:
	//���أ���
	bool operator()(const Point3D& p1, const Point3D& p2)const
	{
		bool i = false;
		if (p1.x != p2.x) {
			i = p1.x < p2.x;
		}
		else if (p1.y != p2.y) {
			i = p1.y < p2.y;
		}
		else if (p1.z != p2.z) {
			i = p1.z < p2.z;
		}
		return i;


		//if (p1.x != p2.x) { return p1.x < p2.x; }
		//else if (p1.y != p2.y) { return p1.y < p2.y; }
		//else if (p1.z != p2.z) { return p1.z < p2.z; }
		//return i;
	}
};

class get_Surface
{
public:
	//��ȡ���нڵ㲢ʶ��������
	get_Surface(vector<Hexahedral3D*>& nodes, My_Voxel& _vox);
	//��ȡ���浥Ԫ
	void get_SurNode();

	//�Ż�1 �߽絥Ԫ �ڵ�-��ϵ��
	Point3D optimize(Point3D p, Vec3D v);

	//�Ż�2 �߽絥Ԫ ��ϵ�-��ϵ�
	void optimize2();
	//�Ż�3
	void optimize3();


	~get_Surface();
private:
	//�ж��Ƿ�Ϊ�����
	bool out_face(Hexahedral3D* node, int direction);
	//���뵥Ԫ������ϵ
	bool out_face_index(Point3D* point);

	vector<vector<Point>> Obtain_contours(const cv::Mat& image_index);

	vector<Point2f> BSplineFit(vector<Point2f> discretePoints, bool closed, double stride = 0.01);
	vector<Point3f> BSplineFit3D(std::vector<Point3f> discretePoints, bool closed, double stride);
	vector<Point2f> GetBSpline(const cv::Mat& image_index);
	vector<Point3f> Get3DBSpline(My_Voxel& _vox);
	bool jud_Surface(Face3D* face1, Face3D* face2,int i);
	void get_faces();
	Face3D* neighbour_faces(Point3D* p, Face3D* face);
	bool jud_crop(Point3D* p);
	Face3D* jud_point(Face3D* p);
	Point3D* find_point(Face3D* face1, Face3D* face2, Face3D* face3);
	bool get_cos(Vec3D vec1, Vec3D vec2);

	vector<Point2f> generateLinePoints(const cv::Point2f& start, const cv::Point2f& end);
	void normalize1(double& x, double& y, double& z);
	float determinant(const Point3D& p1, const Point3D& p2, const Point3D& p3);
	float Scaled_Jacobian(Point3D p0, Point3D p1, Point3D p2, Point3D p3, Point3D p4, Point3D p5, Point3D p6, Point3D p7);
	//���Թ�ϣ����߲�ѯЧ��
	//��ȡ������
	Vec3D* point_vec(Point3D* point); 
	//������������ϵ
	bool check(Face3D* face, Point3D* point);
	double distance2(const Point& p1, double x, double y);
	//��ά�ռ���ֱ����ͼ�������Ľ���
	Point3D* get_outline_point(Point3D* point, Vec3D vec_p, int index);
	Point3D* get_outline_point_spe(Point3D* point, Vec3D vec_p, int index, Face3D* face1);
	//��ά�ռ�����ֱ�߽���
	Point3D* get_intersection_point(Point3D* p1, Point3D* p2, Point3D* p3, Point3D* p4);
	//���Ӧ�߽��
	Point3D* get_fit_point(Point3D* point, Vec3D vec_p);
	
	//��������ƽ��
	double distance(Point3D* p1, Point3D* p2)
	{
		double dis = (p1->x - p2->x) * (p1->x - p2->x) +
			(p1->y - p2->y) * (p1->y - p2->y) +
			(p1->z - p2->z) * (p1->z - p2->z);
		return dis;
	}
	
	float distance3(const cv::Point2f& p1, const cv::Point2f& p2) {
		return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
	}
public:
	//�洢ʶ����ı�����Ƭ
	vector<Face3D*> sur_faces;

	//���淨����Ϊz�ı���
	vector<Face3D*> sur_faces_z;
	//��������
	vector<Face3D*> all_sur_faces_z;
	//�����������2
	vector<Face3D*> need_faces_double;
	vector<Face3D*> faces_double_z;
	//�����������1
	vector<Face3D*> need_faces_single;
	unordered_set<Face3D*> need_faces_single1;
	vector<Face3D*> neighbour_faces_single;
	//δ��ϵ���Ƭ
	vector<Face3D*> fail_faces;
	//�õ����ı���ڵ�
	vector<Hexahedral3D*> sur_nodes;
	//��Ҫ���ڵı߽絥Ԫ
	vector<Hexahedral3D*> poor_nodes;
	//�����ڵ�����
	vector<Point3D*> poor_point;
	set<Point3D, myCompare> poor_point_hash;

	//���ݵ�Ԫ��0�����ϣ��
	set<Point3D, myCompare> nodeHash;
	//��������ͬһ��ĵ�Ԫ�����ϣ�����ڲ�ѯ����ĳһ��ĵ�Ԫ��  2022.4.21
	map<Point3D, vector<Hexahedral3D*>, myCompare> pointHash;
	//���Ӧ�����Ĺ�ϣ�� 2022.4.23
	map<Point3D, Vec3D, myCompare> vecHash;

	//���Ӧ��λ�����Ĺ�ϣ�� 2022.5.26
	map<Point3D, Vec3D, myCompare> unitVecHash;
	//�������Ӧ���ڵ�
	map<Point3D, vector<Point3D*>, myCompare> broPoint;
	//��ϵ��Ӧ�����ڵ�
	map<Point3D, vector<Point3D*>, myCompare> optPoint;

	//����
	My_Voxel& vox;

	//--------------------------------------------------------------����ȫ2023.3.22
//����<index,vector<Point>>�Ĺ�ϣ��洢����CT��Ƭͼ��Ľǵ����飬�����������������в���
	unordered_map<int, vector<Point>> GoodFeatures;


	//����������ά��ľ���
	double Distance_Two2Dpoint(Point2d p1, Point2d p2);

	//ʹ��tomasi�㷨������Ƭͼ���ϵ�������
	void Get_TotomasiFeatures(int index, int MaxCornerNumber);//�����ʾͼƬ������int����,��Ҫ��ȡ�����ǵ�����

	//��������������
	Point Get_NearestPT(vector<Point>GoodFeatures, Point it, double r);//����������������Ͱ뾶

	//���Ҿ�������������ĵ�ľ���
	double Dis_goodfeatures(vector<Point>& GoodFeatures, Point it);

	//����ϵ��������㵯����ֹ�ظ����
	void delete_goodfeatures(vector<Point>& GoodFeatures, Point it);
	
	//����һ�������㹲��Ƭ������
	int num_face(Point3D* point);
};

