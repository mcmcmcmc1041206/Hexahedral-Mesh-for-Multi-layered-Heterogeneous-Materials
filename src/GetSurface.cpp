#include"GetSurface.h"
#include <windows.h>


//ʹ�ù�ϣ���ж��Ƿ�Ϊ�ⲿ��s3
bool get_Surface::out_face_index(Point3D* point)
{
	//��ϣ���в�����˵��Ϊ�ⲿ��
	return nodeHash.find(*point) == nodeHash.end() ? true : false;
	
}
//�ж�һ����ڵ��ĳ��������0��1��2��3��4��5��6���������Ƿ�Ϊ�����s2
bool get_Surface::out_face(Hexahedral3D* node, int direction)
{
	
	//�Ƿ�Ϊ�ⲿ��
	// ����һ���������������ڴ洢���1
	bool i = 0;
	double len = node->p[1]->x - node->p[0]->x;//����������ı߳�1
	//cout << "len = " << len << "this->vox.minlenth = " << this->vox.minlenth << endl;//len ��minlenth��һ������
	Point3D* point = new Point3D(0.0, 0.0, 0.0);// ����һ���µĵ�������ڴ洢���ĵ�����1
	/*
			z
			|
		   / \
		  x   y
	*/
	switch (direction)
	{
	case 0:// ����Ϊx�Ḻ����1
		// �������ĵ�����1
		point->x = node->p[0]->x;
		point->y = node->p[0]->y - len;
		point->z = node->p[0]->z;
		//i = this->out_face_index(nodes, point);
		i = this->out_face_index(point);// ����out_face_index�������жϸõ��Ƿ����ⲿ1
		delete point;
		break;
	case 1:// ����Ϊx��������1
		point->x = node->p[0]->x + len;
		point->y = node->p[0]->y;
		point->z = node->p[0]->z;
		//i = this->out_face_index(nodes, point);
		i = this->out_face_index(point);
		delete point;
		break;
	case 2:// ����Ϊy��������1
		point->x = node->p[0]->x;
		point->y = node->p[0]->y + len;
		point->z = node->p[0]->z;
		//i = this->out_face_index(nodes, point);
		i = this->out_face_index(point);
		delete point;
		break;
	case 3:// ����Ϊy�Ḻ����1
		point->x = node->p[0]->x - len;
		point->y = node->p[0]->y;
		point->z = node->p[0]->z;
		//i = this->out_face_index(nodes, point);
		i = this->out_face_index(point);
		delete point;
		break;
	case 4:// ����Ϊz��������1
		point->x = node->p[0]->x;
		point->y = node->p[0]->y;
		point->z = node->p[0]->z + len;
		i = this->out_face_index(point);
		//i = 0;
		delete point;
		break;
	case 5:// ����Ϊz�Ḻ����1
		point->x = node->p[0]->x;
		point->y = node->p[0]->y;
		point->z = node->p[0]->z - len;
		i = this->out_face_index(point);
		//i = 0;
		delete point;
		break;
	default:
		delete point;
		break;
	}
	return i;
}


//��ȡ�����s1
get_Surface::get_Surface(vector<Hexahedral3D*>& nodes, My_Voxel& _vox) : vox(_vox)//s1
{
	clock_t begin = clock();
	int n1 = nodes.size();

	//������ϣ��

	for (int i = 0; i < n1; ++i)
	{
		this->nodeHash.insert(*nodes[i]->p[0]);//��ÿ��Hexahedral3D����ĵ�һ���ڵ���뵽��ϣ����1
		
	}
	


	//�����������-jh
#if 0

	int n2 = nodes.size();
	set<Point3D, myCompare> s;

	for (int i =0; i < n2; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (s.find(*nodes[i]->p[j]) != s.end())
			{
				continue;
			}
			s.insert(*nodes[i]->p[j]);
			double lenth = this->vox.minlenth;
			bool x1 = 0;
			bool x2 = 0;
			bool y1 = 0;
			bool y2 = 0;
			bool z1 = 0;
			bool z2 = 0;
			Point3D p0(*nodes[i]->p[j]);
			if (nodeHash.find(p0) != nodeHash.end())
			{
				continue;

			}
			Point3D p1((*nodes[i]->p[j]).x - lenth, (*nodes[i]->p[j]).y, (*nodes[i]->p[j]).z);
			Point3D p2((*nodes[i]->p[j]).x + lenth, (*nodes[i]->p[j]).y, (*nodes[i]->p[j]).z);
			Point3D p3((*nodes[i]->p[j]).x , (*nodes[i]->p[j]).y - lenth, (*nodes[i]->p[j]).z);
			Point3D p4((*nodes[i]->p[j]).x , (*nodes[i]->p[j]).y + lenth, (*nodes[i]->p[j]).z);
			Point3D p5((*nodes[i]->p[j]).x, (*nodes[i]->p[j]).y, (*nodes[i]->p[j]).z - lenth);
			Point3D p6((*nodes[i]->p[j]).x, (*nodes[i]->p[j]).y, (*nodes[i]->p[j]).z + lenth);
	
			if (nodeHash.find(p1) != nodeHash.end())
			{
				x1 = 1;

			}
			if (nodeHash.find(p2) != nodeHash.end())
			{
				x2 = 1;
			}
			if (nodeHash.find(p3) != nodeHash.end())
			{
				y1 = 1;
			}
			if (nodeHash.find(p4) != nodeHash.end())
			{
				y2 = 1;
			}
			if (nodeHash.find(p5) != nodeHash.end())
			{
				z1 = 1;
			}
			if (nodeHash.find(p6) != nodeHash.end())
			{
				z2 = 1;
			}
			if ((x1 && x2 && y1 && !y2 )|| (x1 && x2 && !y1 && y2)|| (x1 && !x2 && y1 && y2)|| (!x1 && x2 && y1 && y2)||
				(z1 && z2 && y1 && !y2) || (z1 && z2 && !y1 && y2)|| (z1 && !z2 && y1 && y2)|| (!z1 && z2 && y1 && y2)||
				(x1 && x2 && z1 && !z2) || (x1 && x2 && !z1 && z2)|| (x1 && !x2 && z1 && z2)|| (!x1 && x2 && z1 && z2))
			{
				Point3D* n0 = new Point3D(p0.x, p0.y, p0.z);
				Point3D* n1 = new Point3D(p0.x+lenth, p0.y, p0.z);
				Point3D* n2 = new Point3D(p0.x + lenth, p0.y + lenth, p0.z);
				Point3D* n3 = new Point3D(p0.x, p0.y + lenth, p0.z);
				Point3D* n4 = new Point3D(p0.x, p0.y, p0.z+lenth);
				Point3D* n5 = new Point3D(p0.x + lenth, p0.y, p0.z+lenth);
				Point3D* n6 = new Point3D(p0.x + lenth, p0.y + lenth, p0.z+lenth);
				Point3D* n7 = new Point3D(p0.x, p0.y + lenth, p0.z+lenth);
				
				unsigned int index = 1;//index����δ֪
				nodes.push_back(new Hexahedral3D(n0, n1, n2, n3, n4, n5, n6, n7, index));
				this->nodeHash.insert(p0);
			}
			


		}


	}

#endif


#if 1
	int n = nodes.size();
	//max_z������Ҫ��һ
	unsigned int max_z = (this->vox.AllImage_m.size() - 1) * this->vox.getInterval();
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			if (this->out_face(nodes[i], j) &&//������ұ����ĸ��㶼��ȫΪ0��max_z
				!(nodes[i]->f[j]->p[0]->z == 0 && nodes[i]->f[j]->p[1]->z == 0 &&
					nodes[i]->f[j]->p[2]->z == 0 && nodes[i]->f[j]->p[3]->z == 0) &&
				!(nodes[i]->f[j]->p[0]->z == max_z && nodes[i]->f[j]->p[1]->z == max_z &&nodes[i]->f[j]->p[2]->z == max_z && nodes[i]->f[j]->p[3]->z == max_z)) //&& !((int)(nodes[i]->f[j]->p[0]->z) == 32 && (int)(nodes[i]->f[j]->p[1]->z)==32 && (int)(nodes[i]->f[j]->p[2]->z)  == 32 && (int)(nodes[i]->f[j]->p[3]->z)  == 32)
			{
				//cout << "zzuobiao"<<nodes[i]->f[j]->p[0]->z << endl;

//2023/6/5 
#if 0 

				if (nodes[i]->f[j]->n->i != 0)//�ж������ķ�������x�������Ƿ��з���1
				{
					int a = int(abs(nodes[i]->f[j]->n->i) / nodes[i]->f[j]->n->i);//������������ķ��ţ���Ϊ1����Ϊ-11
					Point3D p0(*nodes[i]->f[j]->p[0]);//��ȡ�����ĵ�һ����1
					Point3D p1(*nodes[i]->f[j]->p[1]);
					Point3D p2(*nodes[i]->f[j]->p[2]);
					Point3D p3(*nodes[i]->f[j]->p[3]);
					int n0 = p0.z / this->vox.getInterval();//�����һ�������ڵ����ز����1
					int n1 = p1.z / this->vox.getInterval();
					int n2 = p2.z / this->vox.getInterval();
					int n3 = p3.z / this->vox.getInterval();
					if (this->vox.AllImage_m[n0].at<uchar>(p0.y, p0.x + a) != 255 && this->
						vox.AllImage_m[n1].at<uchar>(p1.y, p1.x + a) != 255 &&
						this->vox.AllImage_m[n2].at<uchar>(p2.y, p2.x + a) != 255 && this->vox.
						AllImage_m[n3].at<uchar>(p3.y, p3.x + a) != 255)//�ж����ĸ�����x������ƫ��һ����λ�󣬶�Ӧ��������ɫֵ�Ƿ񶼲�Ϊ255����ɫ��1
					{
						continue;//�������Ϊ255��˵��������������ⲿ�����������1
					}
				}
				if (nodes[i]->f[j]->n->j != 0)//�ж������ķ�������y�������Ƿ��з����������߼�ͬ�ϣ�ֻ�ǻ���y������ƫ��һ����λ1
				{
					int a = int(abs(nodes[i]->f[j]->n->j) / nodes[i]->f[j]->n->j);
					Point3D p0(*nodes[i]->f[j]->p[0]);
					Point3D p1(*nodes[i]->f[j]->p[1]);
					Point3D p2(*nodes[i]->f[j]->p[2]);
					Point3D p3(*nodes[i]->f[j]->p[3]);
					int n0 = p0.z / this->vox.getInterval();
					int n1 = p1.z / this->vox.getInterval();
					int n2 = p2.z / this->vox.getInterval();
					int n3 = p3.z / this->vox.getInterval();
					if (this->vox.AllImage_m[n0].at<uchar>(p0.y + a, p0.x) != 255 && this->vox
						.AllImage_m[n1].at<uchar>(p1.y + a, p1.x) != 255 &&
						this->vox.AllImage_m[n2].at<uchar>(p2.y + a, p2.x) != 255 && this->vox.
						AllImage_m[n3].at<uchar>(p3.y + a, p3.x) != 255)
					{
						continue;
					}
				}
				if (nodes[i]->f[j]->n->k != 0)//z����1
				{
					int a = int(abs(nodes[i]->f[j]->n->k) / nodes[i]->f[j]->n->k);
					Point3D p0(*nodes[i]->f[j]->p[0]);
					Point3D p1(*nodes[i]->f[j]->p[1]);
					Point3D p2(*nodes[i]->f[j]->p[2]);
					Point3D p3(*nodes[i]->f[j]->p[3]);
					int n0 = p0.z / this->vox.getInterval();
					if (this->vox.AllImage_m[n0 + a].at<uchar>(p0.y, p0.x) != 255 && this->vox
						.AllImage_m[n0 + a].at<uchar>(p1.y, p1.x) != 255 &&
						this->vox.AllImage_m[n0 + a].at<uchar>(p2.y, p2.x) != 255 && this->vox.
						AllImage_m[n0 + a].at<uchar>(p3.y, p3.x) != 255)
					{
						continue;
					}
				}

#endif
				//��������Ϊz�ı��浥������
				/*if (nodes[i]->f[j]->n->k != 0)
				{
					this->sur_faces_z.push_back(nodes[i]->f[j]);
					for (int fa = 0; fa < 8; fa++)
					{
						this->all_sur_faces_z.push_back(nodes[i]->f[fa]);
					}
					continue;
				}*/
				this->sur_faces.push_back(nodes[i]->f[j]);//���ͨ�������ϵ��жϣ�˵���������λ�������ϵģ��������뵽sur_faces������1
				//2022.4.21
				for (int num = 0; num < 4; ++num) //�����������ĸ���1
				{
					//�����-��Ԫӳ���ϣ���ֵ��������ĵ�Ԫ
					
					
					//���Ӧ��������ϣ��
					if (vecHash.find(*nodes[i]->f[j]->p[num]) == vecHash.end())//�����������ϣ����û���ҵ�p[num]
					{
						vecHash[*nodes[i]->f[j]->p[num]] = *nodes[i]->f[j]->n;//���ڶ�Ӧ��p[num]���f[j]������n

					}
					else
					{
						vecHash[*nodes[i]->f[j]->p[num]] = vecHash[*nodes[i]->f[j]->p[num]] + *nodes[i]->f[j]->n;//�������ԭ�л����ϰ�����n����ȥ	
					}	
				}
			}
		}
	}
#if 0
	//��һ���������������з�0��СֵΪ1
	for (auto it = vecHash.begin(); it != vecHash.end(); ++it) 
	{
		int index = 100;
		int i = abs(it->second.i), j = abs(it->second.j), k = abs(it->second.k);

		if (i >= 1) index = i < index ? i : index;

		if (j >= 1) index = j < index ? j : index;

		if (k >= 1) index = k < index ? k : index;
		
		if (index == 100) index = 1;

		if (index > 1)
		{
			it->second.i /= index;
			it->second.j /= index;
			it->second.k /= index;
		}

	}
	//cout << "1";
#endif 
#if 0
	//����ɳ���������񴦵Ķ��㷨����
	int index_i = 0, index_j = 0, index_k = 0;//��������ı�ʶ��
	bool flag = 0;

	for (int m = 0; m < sur_faces.size(); ++m)
	{
		flag = 0;
		//�ĸ������У��Ƿ���ڶ��㷨����ƽ��������
		for (int n = 0; n < 4; ++n)
		{
			index_i = vecHash[*sur_faces[m]->p[n]].i;
			index_j = vecHash[*sur_faces[m]->p[n]].j;
			index_k = vecHash[*sur_faces[m]->p[n]].k;
			
			if ((index_i != 0 && index_j == 0 && index_k == 0) ||
				(index_i == 0 && index_j != 0 && index_k == 0) ||
				(index_i == 0 && index_j == 0 && index_k != 0))
			{
				flag = 1;
				break;
			}
			
		
			
		}

		if (!flag) continue;

		if (abs(index_i) == 3 || abs(index_j) == 3 || abs(index_k) == 3) continue;

		//��������
		if (index_i != 0)
		{
			for (int n = 0; n < 4; ++n)
			{
				if (vecHash[*sur_faces[m]->p[n]].j - (int)vecHash[*sur_faces[m]->p[n]].j != 0 || vecHash[*sur_faces[m]->p[n]].k - (int)vecHash[*sur_faces[m]->p[n]].k != 0) continue;
				vecHash[*sur_faces[m]->p[n]].j /= 2;
				vecHash[*sur_faces[m]->p[n]].k /= 2;
			}
		}
		else if(index_j != 0)
		{
			for (int n = 0; n < 4; ++n)
			{
				if (vecHash[*sur_faces[m]->p[n]].i - (int)vecHash[*sur_faces[m]->p[n]].i != 0 || vecHash[*sur_faces[m]->p[n]].k - (int)vecHash[*sur_faces[m]->p[n]].k != 0) continue;
				vecHash[*sur_faces[m]->p[n]].i /= 2;
				vecHash[*sur_faces[m]->p[n]].k /= 2;
			}
		}
		else if (index_k != 0)
		{
			for (int n = 0; n < 4; ++n)
			{
				if (vecHash[*sur_faces[m]->p[n]].i - (int)vecHash[*sur_faces[m]->p[n]].i != 0 || vecHash[*sur_faces[m]->p[n]].j - (int)vecHash[*sur_faces[m]->p[n]].j != 0) continue;
				vecHash[*sur_faces[m]->p[n]].i /= 2;
				vecHash[*sur_faces[m]->p[n]].j /= 2;
			}
		}

	}
	cout << "1";
#endif

#endif
#if 0
	//5.26 ����
	for(int i=0;i< this->sur_faces.size();i++)
	{
		for (int num = 0; num < 4; ++num)
		{
			
			//���Ӧ��λ��������ϣ��
			if (unitVecHash.find(*sur_faces[i]->p[num]) == unitVecHash.end())//�����������ϣ����û���ҵ�p[num]
			{
				double x = vecHash[*sur_faces[i]->p[num]].i;
				double y = vecHash[*sur_faces[i]->p[num]].j;
				double z = vecHash[*sur_faces[i]->p[num]].k;
				double m = x * x + y * y + z * z;

				unitVecHash[*sur_faces[i]->p[num]].i = x / sqrt(m);
				unitVecHash[*sur_faces[i]->p[num]].j = y / sqrt(m);
				unitVecHash[*sur_faces[i]->p[num]].k = z / sqrt(m);


			//	sur_faces[i]->p[num]. = sur_faces[i]->n->i / sqrt(m);
			//	sur_faces[i]->p[num]->n->j = sur_faces[i]->n->j / sqrt(m);
			//	sur_faces[i]->p[num]->n->k = sur_faces[i]->n->k / sqrt(m);
			//	unitVecHash[*sur_faces[i]->p[num]] = *sur_faces[i]->n;//���ڶ�Ӧ��p[num]���f[j]������n

			}
			//else
			//{
			//	
			//	*sur_faces[i]->n = unitVecHash[*sur_faces[i]->p[num]];
			//}
		}
	}
	vecHash = unitVecHash;
#endif


	clock_t end = clock();
	cout << "��ȡ�������������ʱ�䣺" << (end - begin) / 1000 << endl;
	cout << "�����������" << this->sur_faces.size() << endl;
}
//���3D���Ƿ�λ��3D����
bool get_Surface::check(Face3D* face, Point3D* point)
{
	//�����Ƿ����ڴ���
	for (int i = 0; i < 4; ++i)
	{
		if (face->p[i]->x == point->x &&
			face->p[i]->y == point->y &&
			face->p[i]->z == point->z)
		{
			return true;
		}
	}
	return false;
}

//���Թ�ϣ����߲�ѯЧ��
Vec3D* get_Surface::point_vec(Point3D* point)
{
	Vec3D* p_Vec = new Vec3D(0.0, 0.0, 0.0);//�����ĵ������
	//int num_f = 0;//����˵�������
	int n = this->sur_faces.size();
	for (int i = 0; i < n; ++i)
	{
		if (this->check(this->sur_faces[i], point))
		{
			p_Vec->i += this->sur_faces[i]->n->i;
			p_Vec->j += this->sur_faces[i]->n->j;
			p_Vec->k += this->sur_faces[i]->n->k;
			//num_f++;
		}
	}
	//p_Vec->i = p_Vec->i;
	//p_Vec->j = p_Vec->j;
	//p_Vec->k = p_Vec->k;
	return p_Vec;
}

double get_Surface::distance2(const Point& p1, double x, double y) {
	return std::sqrt(std::pow(p1.x - x, 2) + std::pow(p1.y - y, 2));
}
//��ȡ��ά��������s7
Point3D* get_Surface::get_outline_point(Point3D* point, Vec3D vec_p,int index)
{   
	//1-2023/5/30���д�Ĵ���
#if 0

	//����
	if (index >= this->vox.AllImage_m.size())
	{
		index = this->vox.AllImage_m.size() - 1;
	}
	//���Ȱѳ�ʼ��x\y\i\j�����ó���
	double x0 = point->x;
	double y0 = point->y;
	double z0 = point->z;

	double i = vec_p.i;
	double j = vec_p.j;
	double k = vec_p.k;
	int lenth = this->vox.minlenth * 4;
	//int lenth =INT_MAX;
	//int lenth = this->vox.minlenth;
	int cols = this->vox.cols;//�п� x�������
	int rows = this->vox.rows;//�п� y�������
	int flag = 0;
	if (i != 0 && j != 0 && k == 0) flag = 1;//xoyƽ�������������
	if (i == 0 && j != 0 && k != 0) flag = 2;//yozƽ�������������
	if (i != 0 && j == 0 && k != 0) flag = 3;//xozƽ�������������
	if (i != 0 && j == 0 && k == 0) flag = 4;//x������������
	if (i == 0 && j != 0 && k == 0) flag = 5;//yƽ�������������
	if (i == 0 && j == 0 && k != 0) flag = 6;//zƽ�������������
	int xx = 0;
	switch (flag)
	{
	case 1:
		if (i > 0 && j > 0)  xx = 1;
		else if (i < 0 && j > 0)  xx = 2;
		else if (i < 0 && j < 0)  xx = 3;
		else if (i > 0 && j < 0)  xx = 4;
		switch (xx)
		{
		case 1:
			for (int n = 1; n <= lenth; n++)
			{
				if (x0 + n >= cols || y0 + n >= rows)   return new Point3D(x0 + n - 1, y0 + n - 1, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0 + n, x0 + n) != 255) return new Point3D(x0 + n - 1, y0 + n - 1, z0);
			}
			return new Point3D(x0 + lenth, y0 + lenth, z0);
			break;
		case 2:
			for (int n = 1; n <= lenth; n++)
			{
				if (x0 - n <= 0 || y0 + n >= rows)   return new Point3D(x0 - n + 1, y0 + n - 1, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0 + n, x0 - n) != 255) return new Point3D(x0 - n + 1, y0 + n - 1, z0);
			}
			return new Point3D(x0 - lenth, y0 + lenth, z0);
			break;
		case 3:
			for (int n = 1; n <= lenth; n++)
			{
				if (x0 - n <= 0 || y0 - n <= 0)   return new Point3D(x0 - n + 1, y0 - n + 1, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0 - n, x0 - n) != 255) return new Point3D(x0 - n + 1, y0 - n + 1, z0);
			}
			return new Point3D(x0 - lenth, y0 - lenth, z0);
			break;
		case 4:
			for (int n = 1; n <= lenth; n++)
			{
				if (x0 + n >= cols || y0 - n <= 0)   return new Point3D(x0 + n - 1, y0 - n + 1, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0 - n, x0 + n) != 255) return new Point3D(x0 + n - 1, y0 - n + 1, z0);
			}
			return new Point3D(x0 + lenth, y0 - lenth, z0);
			break;
		default:
			break;
		}
		break;
	case 2:
		if (k > 0 && j > 0)  xx = 1;
		else if (k < 0 && j > 0)  xx = 2;
		else if (k < 0 && j < 0)  xx = 3;
		else if (k > 0 && j < 0)  xx = 4;
		switch (xx)
		{
		case 1:
			for (int n = 1; n <= lenth; n++)
			{
				if (index + n >= this->vox.AllImage_m.size() - 1 || y0 + n >= rows)   return new Point3D(x0, y0 + n - 1, z0 + n - 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index + n].at<uchar>(y0 + n, x0) != 255) return new Point3D(x0, y0 + n - 1, z0 + n - 1);
			}
			return new Point3D(x0, y0 + lenth, z0 + lenth);
			break;
		case 2:
			for (int n = 1; n <= lenth; n++)
			{
				if (index - n <= 0 || y0 + n >= rows)   return new Point3D(x0, y0 + n - 1, z0 - n + 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index - n].at<uchar>(y0 + n, x0) != 255) return new Point3D(x0, y0 + n - 1, z0 - n + 1);
			}
			return new Point3D(x0, y0 + lenth, z0 - lenth);
			break;
		case 3:
			for (int n = 1; n <= lenth; n++)
			{
				if (index - n <= 0 || y0 - n <= 0)   return new Point3D(x0, y0 - n + 1, z0 - n + 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index - n].at<uchar>(y0 - n, x0) != 255) return new Point3D(x0, y0 - n + 1, z0 - n + 1);
			}
			return new Point3D(x0, y0 - lenth, z0 - lenth);
			break;
		case 4:
			for (int n = 1; n <= lenth; n++)
			{

				if (index + n >= this->vox.AllImage_m.size() - 1 || y0 - n <= 0)   return new Point3D(x0, y0 - n + 1, z0 + n - 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index + n].at<uchar>(y0 - n, x0) != 255) return new Point3D(x0, y0 - n + 1, z0 + n - 1);
			}
			return new Point3D(x0, y0 - lenth, z0 + lenth);
			break;
		default:
			break;
		}
		break;
	case 3:
		if (i > 0 && k > 0)  xx = 1;
		else if (i < 0 && k > 0)  xx = 2;
		else if (i < 0 && k < 0)  xx = 3;
		else if (i > 0 && k < 0)  xx = 4;
		switch (xx)
		{
		case 1:
			for (int n = 1; n <= lenth; n++)
			{
				if (x0 + n >= cols || index + n >= this->vox.AllImage_m.size() - 1)   return new Point3D(x0 + n - 1, y0, z0 + n - 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index + n].at<uchar>(y0, x0 + n) != 255) return new Point3D(x0 + n - 1, y0, z0 + n - 1);
			}
			return new Point3D(x0 + lenth, y0, z0 + lenth);
			break;
		case 2:
			for (int n = 1; n <= lenth; n++)
			{
				if (x0 - n <= 0 || index + n >= this->vox.AllImage_m.size() - 1)   return new Point3D(x0 - n + 1, y0, z0 + n - 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index + n].at<uchar>(y0, x0 - n) != 255) return new Point3D(x0 - n + 1, y0, z0 + n - 1);
			}
			return new Point3D(x0 - lenth, y0, z0 + lenth);
			break;
		case 3:
			for (int n = 1; n <= lenth; n++)
			{
				if (x0 - n <= 0 || index - n <= 0)   return new Point3D(x0 - n + 1, y0, z0 - n + 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index - n].at<uchar>(y0, x0 - n) != 255) return new Point3D(x0 - n + 1, y0, z0 - n + 1);
			}
			return new Point3D(x0 - lenth, y0, z0 - lenth);
			break;
		case 4:
			for (int n = 1; n <= lenth; n++)
			{
				if (x0 + n >= cols || index - n <= 0)   return new Point3D(x0 + n - 1, y0, z0 - n + 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index - n].at<uchar>(y0, x0 + n) != 255) return new Point3D(x0 + n - 1, y0, z0 - n + 1);
			}
			return new Point3D(x0 + lenth, y0, z0 - lenth);
			break;
		default:
			break;
		}
		break;

	case 4:
		if (i > 0)
		{
			for (int n = 1; n <= lenth; n++)
			{
				if (x0 + n >= cols)   return new Point3D(x0 + n - 1, y0, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0, x0 + n) != 255) return new Point3D(x0 + n - 1, y0, z0);
			}
			return 	new Point3D(x0 + lenth, y0, z0);
		}
		else
		{
			for (int n = 1; n <= lenth; n++)
			{
				if (x0 - n <= 0)   return new Point3D(x0 - n + 1, y0, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0, x0 - n) != 255) return new Point3D(x0 - n + 1, y0, z0);
			}
			return 	new Point3D(x0 - lenth, y0, z0);
		}
		break;
	case 5:
		if (j > 0)
		{
			for (int n = 1; n <= lenth; n++)
			{
				if (y0 + n >= rows)   return new Point3D(x0, y0 + n - 1, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0 + n, x0) != 255) return new Point3D(x0, y0 + n - 1, z0);
			}
			return 	new Point3D(x0, y0 + lenth, z0);
		}
		else
		{
			for (int n = 1; n <= lenth; n++)
			{
				if (y0 - n <= 0)   return new Point3D(x0, y0 - n + 1, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0 - n, x0) != 255) return new Point3D(x0, y0 - n + 1, z0);
			}
			return 	new Point3D(x0, y0 - lenth, z0);
		}
		break;
	case 6:
		if (k > 0)
		{
			for (int n = 1; n <= lenth; n++)
			{
				if (index + n >= this->vox.AllImage_m.size() - 1)   return new Point3D(x0, y0, z0 + n - 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index + n].at<uchar>(y0, x0) != 255) return new Point3D(x0, y0, z0 + n - 1);
			}
			return 	new Point3D(x0, y0, z0 + lenth);
		}
		else
		{
			for (int n = 1; n <= lenth; n++)
			{
				if (index - n <= 0)   return new Point3D(x0, y0, z0 - n + 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index - n].at<uchar>(y0, x0) != 255) return new Point3D(x0, y0, z0 - n + 1);
			}
			return 	new Point3D(x0, y0, z0 - lenth);
		}
		break;
	default:
		break;
	}
	return point;

#if 0
	Point P1;//P1��¼p��ƽ������
	P1.x = p->x;
	P1.y = p->y;
	double dis_goodfeatures = Dis_goodfeatures(this->GoodFeatures[index], P1);//opencv�Դ���pointpolygontest�ӿڲ�����Ҫ�Լ�����д

	if (dis_goodfeatures < 8) {
		Point p_fit = Get_NearestPT(this->GoodFeatures[index], P1, dis_goodfeatures);
		//cout << "---------------------------------ʹ��TS�㷨֮ǰp�����꣺ X: " << p->x << "   Y: " << p->y << "   Z: " << p->z << endl;
		p->x = p_fit.x;
		p->y = p_fit.y;
		p->z = index * this->vox.getInterval();
		this->delete_goodfeatures(this->GoodFeatures[index], p_fit);
		//cout << "---------------------------------ʹ��TS�㷨֮��p�����꣺ X: " << p->x << "   Y: " << p->y << "   Z: " << p->z << endl;
	}


#endif
	//cout << "ʹ��TS�㷨֮��p�����꣺ X: " << p->x << "   Y: " << p->y << "   Z: " << p->z << endl;



#endif
	//2-���ʦ�ַ���
#if 0

	//����
	if (index >= this->vox.AllImage_m.size())
	{
		index = this->vox.AllImage_m.size() - 1;
	}
	//���Ȱѳ�ʼ��x\y\i\j�����ó���
	//int x0 = point->x;
	//int y0 = point->y;
	//int z0 = point->z;
	double x0 = point->x;
	double y0 = point->y;
	double z0 = point->z;

	double i = vec_p.i;
	double j = vec_p.j;
	double k = vec_p.k;
	//int lenth = this->vox.minlenth*3;
	int lenth = INT_MAX;
	int cols = this->vox.cols;//�п� x�������
	int rows= this->vox.rows;//�п� y�������
	int flag = 0;
	if (i != 0 && j != 0 && k == 0) flag = 1;//xoyƽ�������������
	if (i == 0 && j != 0 && k != 0)  flag = 2;//yozƽ�������������
	if (i != 0 && j == 0 && k != 0) flag = 3;//xozƽ�������������
	if (i != 0 && j == 0 && k == 0) flag = 4;//x������������
	if (i == 0 && j != 0 && k == 0) flag = 5;//yƽ�������������
	if (i == 0 && j == 0 && k != 0) flag = 6;//zƽ�������������
	switch (flag)
	{
	case 1:
		for (int n = 1; n <= lenth; n++)
		{
			if (i > 0 && j > 0)//һ���޲���
			{
				if (x0 + n >= cols || y0 + n >= rows)   return new Point3D(x0 + n - 1, y0 + n - 1, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0 + n, x0 + n) != 255) return new Point3D(x0 + n - 1, y0 + n - 1, z0);

			}
			if (i < 0 && j > 0)//�����޲���
			{
				if (x0 - n <= 0 || y0 + n >= rows)   return new Point3D(x0 - n + 1, y0 + n - 1, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0 + n, x0 - n) != 255) return new Point3D(x0 - n + 1, y0 + n - 1, z0);
			}
			if (i < 0 && j < 0)//�����޲���
			{
				if (x0 - n <= 0 || y0 - n <= 0)   return new Point3D(x0 - n + 1, y0 - n + 1, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0 - n, x0 - n) != 255) return new Point3D(x0 - n + 1, y0 - n + 1, z0);
			}
			if (i > 0 && j < 0)//�����޲���
			{
				if (x0 + n >= cols || y0 - n <= 0)   return new Point3D(x0 + n - 1, y0 - n + 1, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0 - n, x0 + n) != 255) return new Point3D(x0 + n - 1, y0 - n + 1, z0);
			}
		}
		break;

	case 2:
		for (int n = 1; n <= lenth; n++)
		{
			if (k > 0 && j > 0)//һ���޲���
			{
				if (index + n >= this->vox.AllImage_m.size() - 1 || y0 + n >= rows)   return new Point3D(x0, y0 + n - 1, z0 + n - 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index + n].at<uchar>(y0 + n, x0) != 255) return new Point3D(x0, y0 + n - 1, z0 + n - 1);

			}
			if (k < 0 && j > 0)//�����޲���
			{
				if (index - n <= 0 || y0 + n >= rows)   return new Point3D(x0, y0 + n - 1, z0 - n + 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index - n].at<uchar>(y0 + n, x0) != 255) return new Point3D(x0, y0 + n - 1, z0 - n + 1);
			}
			if (k < 0 && j < 0)//�����޲���
			{
				if (index - n <= 0 || y0 - n <= 0)   return new Point3D(x0, y0 - n + 1, z0 - n + 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index - n].at<uchar>(y0 - n, x0) != 255) return new Point3D(x0, y0 - n + 1, z0 - n + 1);
			}
			if (k > 0 && j < 0)//�����޲���
			{
				if (index + n >= this->vox.AllImage_m.size() - 1 || y0 - n <= 0)   return new Point3D(x0, y0 - n + 1, z0 + n - 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index + n].at<uchar>(y0 - n, x0) != 255) return new Point3D(x0, y0 - n + 1, z0 + n - 1);
			}
		}
		break;

	case 3:
		for (int n = 1; n <= lenth; n++)
		{
			if (i > 0 && k > 0)//һ���޲���
			{
				if (x0 + n >= cols || index + n >= this->vox.AllImage_m.size() - 1)   return new Point3D(x0 + n - 1, y0, z0 + n - 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index + n].at<uchar>(y0, x0 + n) != 255) return new Point3D(x0 + n - 1, y0, z0 + n - 1);

			}
			if (i < 0 && k > 0)//�����޲���
			{
				if (x0 - n <= 0 || index + n >= this->vox.AllImage_m.size() - 1)   return new Point3D(x0 - n + 1, y0, z0 + n - 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index + n].at<uchar>(y0, x0 - n) != 255) return new Point3D(x0 - n + 1, y0, z0 + n - 1);
			}
			if (i < 0 && k < 0)//�����޲���
			{
				if (x0 - n <= 0 || index - n <= 0)   return new Point3D(x0 - n + 1, y0, z0 - n + 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index - n].at<uchar>(y0, x0 - n) != 255) return new Point3D(x0 - n + 1, y0, z0 - n + 1);
			}
			if (i > 0 && k < 0)//�����޲���
			{
				if (x0 + n >= cols || index - n <= 0)   return new Point3D(x0 + n - 1, y0, z0 - n + 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index - n].at<uchar>(y0, x0 + n) != 255) return new Point3D(x0 + n - 1, y0, z0 - n + 1);
			}
		}


		break;

	case 4:
		if (i > 0)
		{
			for (int n = 1; n <= lenth; n++)
			{
				if (x0 + n >= cols)   return new Point3D(x0 + n - 1, y0, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0, x0 + n) != 255) return new Point3D(x0 + n - 1, y0, z0);
			}
		}
		else
		{
			for (int n = 1; n <= lenth; n++)
			{
				if (x0 - n <= 0)   return new Point3D(x0 - n + 1, y0, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0, x0 - n) != 255) return new Point3D(x0 - n + 1, y0, z0);
			}
		}
		break;
	case 5:
		if (j > 0)
		{
			for (int n = 1; n <= lenth; n++)
			{
				if (y0 + n >= rows)   return new Point3D(x0, y0 + n - 1, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0 + n, x0) != 255) return new Point3D(x0, y0 + n - 1, z0);
			}
		}
		else
		{
			for (int n = 1; n <= lenth; n++)
			{
				if (y0 - n <= 0)   return new Point3D(x0, y0 - n + 1, z0);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index].at<uchar>(y0 - n, x0) != 255) return new Point3D(x0, y0 - n + 1, z0);
			}
		}
		break;
	case 6:
		if (k > 0)
		{
			for (int n = 1; n <= lenth; n++)
			{
				if (index + n >= this->vox.AllImage_m.size() - 1)   return new Point3D(x0, y0, z0 + n - 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index + n - 1].at<uchar>(y0, x0) != 255) return new Point3D(x0, y0, z0 + n - 1);
			}
		}
		else
		{
			for (int n = 1; n <= lenth; n++)
			{
				if (index - n <= 0)   return new Point3D(x0, y0, z0 - n + 1);//������Ƿ�Խ��
				if (this->vox.AllImage_m[index - n + 1].at<uchar>(y0, x0) != 255) return new Point3D(x0, y0, z0 - n + 1);
			}
		}
		break;
	default:
		return point;
		break;
	}
	return point;
	/*cout << "----------------------------------------------" << endl;
	cout << "vec_p.i: " << vec_p.i<<"   vec_p.j: " << vec_p.j <<endl;*/
	//int rows = this->vox.cols;//�п� x�������
	//int cols = this->vox.rows;//�п� y�������
//
//	Point3D* p = new Point3D(0.0, 0.0, 0.0);//p����άֱ���뵥��ͼƬ�����Ľ���
//
//	if (i == 0 && j == 0) return point;
//	else if (i > 0 && j == 0) {//��x�����������ͶӰ
//		for (int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//				p->x = x0;
//				p->y = y0;
//				p->z = index * this->vox.getInterval();
//			/*	cout << "-------------------------------------------------------------" << endl;
//				cout << "x������������" << endl;				
//				cout << "point->y" << point->x << "point->y" << point->y << endl;
//				cout << ">>x�� " << x0 << "  >>y�� " << y0 << endl;*/
//				break;
//				//return p;
//			}
//			x0 = x1;
//			y0 = y1;
//			x1++;
//		}
//	}
//	else if (i < 0 && j == 0) {//��x�Ḻ�������ͶӰ
//		for (int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//			//��¼��
//			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//				p->x = x0;
//				p->y = y0;
//				p->z = index * this->vox.getInterval();
//				break;
//				//return p;
//			}
//			x0 = x1;
//			y0 = y1;
//			x1--;
//		}
//	}
//	else if (i == 0 && j > 0) {//��y�����������ͶӰ
//		for (int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//				p->x = x0;
//				p->y = y0;
//				p->z = index * this->vox.getInterval();
//				break;
//				//return p;
//			}
//			x0 = x1;
//			y0 = y1;
//			y1++;
//		}
//	}
//	else if (i == 0 && j < 0) {//��y�Ḻ�������ͶӰ
//		/*cout << "i == 0 && j < 0 " << endl;*/
//		for (int x1 = x0, y1 = y0,l =0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows;l++ ) {
//			/*cout << "int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; " << endl;
//			cout << "x1:  " << x1 << "   y1:" << y1 << endl;
//			cout << "cols:  " << cols << "   row:" << rows << endl;
//			cout << "index : " << index << endl;
//			cout << "l : " << l << endl;*/
//			//if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
//				p->x = x0;
//				p->y = y0;
//				p->z = index * this->vox.getInterval();
//				break;
//				//return p;
//			}
//			x0 = x1;
//			y0 = y1;
//			y1--;
//		}
//	}
//	else if (i > 0 && j > 0) {
//		//λ�ڵ�һ���ޣ�����slope�����Ϊ�ĵ�
//		/*cout << "i > 0 && j > 0" << endl;*/
//		if (slope < 1.5) {
//			/*cout << "slope: " << slope <<endl;
//			cout << "slope < 1.5" << endl;
//			cout << "x0; " << x0 << "   y0: " << y0 << "   rows:" << rows << "  cols:" << cols << endl;*/
//			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; x1++,y1++) {
//				/*cout << "int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < rows && y1 < cols;" << endl;*/
//				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//					p->x = x0;
//					p->y = y0;
//					p->z = index * this->vox.getInterval();
//					break;
//					//return p;
//				}
//
//				x0 = x1;
//				y0 = y1;
//
//			}
//
//
//		}
//		else if (slope >= 1.5 && slope < 2.5) {
//
//			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//					p->x = x0;
//					p->y = y0;
//					p->z = index * this->vox.getInterval();
//					break;
//					//return p;
//				}
//
//				x0 = x1;
//				y0 = y1;
//				x1++;
//				y1 = y1 + 2;
//			}
//		}
//		else if (slope >= 2.5 && slope < 3.5) {
//
//			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//					p->x = x0;
//					p->y = y0;
//					p->z = index * this->vox.getInterval();
//					break;
//					//return p;
//				}
//
//				x0 = x1;
//				y0 = y1;
//				x1++;
//				y1 = y1 + 3;
//			}
//		}
//		else {
//			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//					p->x = x0;
//					p->y = y0;
//					p->z = index * this->vox.getInterval();
//					break;
//					//return p;
//				}
//	
//				x0 = x1;
//				y0 = y1;
//				y1++;
//			}
//		}
//	}
//	else if (i < 0 && j > 0) {
//		//λ�ڵڶ�����
//		/*cout << "i < 0 && j > 0" << endl;*/
//		if (slope < 1.5) {
//			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//					p->x = x0;
//					p->y = y0;
//					p->z = index * this->vox.getInterval();
//					break;
//					//return p;
//				}
//				x0 = x1;
//				y0 = y1;
//				x1--;
//				y1++;
//			}
//		}
//		else if (slope >= 1.5 && slope < 2.5) {
//			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//					p->x = x0;
//					p->y = y0;
//					p->z = index * this->vox.getInterval();
//					break;
//					//return p;
//				}
//				x0 = x1;
//				y0 = y1;
//				x1--;
//				y1 = y1 + 2;
//			}
//		}
//		else if (slope >= 2.5 && slope < 3.5) {
//			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//					p->x = x0;
//					p->y = y0;
//					p->z = index * this->vox.getInterval();
//					break;
//					//return p;
//				}
//				x0 = x1;
//				y0 = y1;
//				x1--;
//				y1 = y1 + 3;
//			}
//		}
//		else {
//			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//					p->x = x0;
//					p->y = y0;
//					p->z = index * this->vox.getInterval();
//					break;
//					//return p;
//				}
//				x0 = x1;
//				y0 = y1;
//				y1++;
//			}
//		}
//
//
//
//
//	}
//	else if (i < 0 && j < 0) {
//	/*cout << "i < 0 && j < 0" << endl;*/
//	//λ�ڵ�������
//	if (slope < 1.5) {
//		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//				p->x = x0;
//				p->y = y0;
//				p->z = index * this->vox.getInterval();
//				break;
//				//return p;
//			}
//			x0 = x1;
//			y0 = y1;
//			x1--;
//			y1--;
//		}
//	}
//	else if (slope >= 1.5 && slope < 2.5) {
//		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//				p->x = x0;
//				p->y = y0;
//				p->z = index * this->vox.getInterval();
//				break;
//				//return p;
//			}
//			x0 = x1;
//			y0 = y1;
//			x1--;
//			y1 = y1 - 2;
//		}
//	}
//	else if (slope >= 2.5 && slope < 3.5) {
//		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//				p->x = x0;
//				p->y = y0;
//				p->z = index * this->vox.getInterval();
//				break;
//				//return p;
//			}
//			x0 = x1;
//			y0 = y1;
//			x1--;
//			y1 = y1 - 3;
//		}
//	}
//	else {
//		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//				p->x = x0;
//				p->y = y0;
//				p->z = index * this->vox.getInterval();
//				break;
//				//return p;
//			}
//			x0 = x1;
//			y0 = y1;
//			y1--;
//		}
//	}
//}
//	else if (i > 0 && j < 0) {
//	//cout << "i > 0 && j < 0" << endl;
//	//λ�ڵ�������
//	if (slope < 1.5) {
//		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//				p->x = x0;
//				p->y = y0;
//				p->z = index * this->vox.getInterval();
//				break;
//				//return p;
//			}
//			x0 = x1;
//			y0 = y1;
//			x1++;
//			y1--;
//		}
//	}
//	else if (slope >= 1.5 && slope < 2.5) {
//		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//				p->x = x0;
//				p->y = y0;
//				p->z = index * this->vox.getInterval();
//				break;
//				//return p;
//			}
//			x0 = x1;
//			y0 = y1;
//			x1++;
//			y1 = y1 - 2;
//		}
//	}
//	else if (slope >= 2.5 && slope < 3.5) {
//		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//				p->x = x0;
//				p->y = y0;
//				p->z = index * this->vox.getInterval();
//				break;
//				//return p;
//			}
//			x0 = x1;
//			y0 = y1;
//			x1++;
//			y1 = y1 - 3;
//		}
//	}
//	else {
//		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
//
//			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
//				p->x = x0;
//				p->y = y0;
//				p->z = index * this->vox.getInterval();
//				break;
//				//return p;
//			}
//			x0 = x1;
//			y0 = y1;
//			y1--;
//		}
//	}
//}

	//����Ϊֹ����p�ǰ������������ߣ��ҵ��ĵ�һ���Ҷ�ͻ���
	//cout << "ʹ��TS�㷨֮ǰp�����꣺ X: " << p->x <<"   Y: " <<p->y<<"   Z: " <<p->z<< endl;
	//������Ϊ�ǵ�����ʶ�𲿷�
#if 0
	Point P1;//P1��¼p��ƽ������
	P1.x = p->x;
	P1.y = p->y;
	double dis_goodfeatures = Dis_goodfeatures(this->GoodFeatures[index], P1);//opencv�Դ���pointpolygontest�ӿڲ�����Ҫ�Լ�����д

	if (dis_goodfeatures < 8) {
		Point p_fit = Get_NearestPT(this->GoodFeatures[index], P1, dis_goodfeatures);
		//cout << "---------------------------------ʹ��TS�㷨֮ǰp�����꣺ X: " << p->x << "   Y: " << p->y << "   Z: " << p->z << endl;
		p->x = p_fit.x;
		p->y = p_fit.y;
		p->z = index * this->vox.getInterval();
		this->delete_goodfeatures(this->GoodFeatures[index], p_fit);
		//cout << "---------------------------------ʹ��TS�㷨֮��p�����꣺ X: " << p->x << "   Y: " << p->y << "   Z: " << p->z << endl;
	}


#endif
	//cout << "ʹ��TS�㷨֮��p�����꣺ X: " << p->x << "   Y: " << p->y << "   Z: " << p->z << endl;



#endif
	//3-���ص���Ϸ�������������������ij����ͶӰģ��  ֻ�в���Ϊ1 ֱ�Ӳ��ұ߽�
#if 1

	//����
	if (index >= this->vox.AllImage_m.size())
	{
		index = this->vox.AllImage_m.size() - 1;
	}
	//���Ȱѳ�ʼ��x\y\i\j�����ó���
	int x0 = point->x;
	int y0 = point->y;
	int z0 = point->z;
	double i = vec_p.i;
	double j = vec_p.j;
	double k = vec_p.k;
	int lenth = this->vox.minlenth;

	int flag = 0;
	double slope = i / j;

	//cout << "slope = " << slope << endl;
	/*cout << "----------------------------------------------" << endl;
	cout << "vec_p.i: " << vec_p.i<<"   vec_p.j: " << vec_p.j <<endl;*/
	int cols = this->vox.cols;//�п� x�������
	int rows = this->vox.rows;//�п� y�������

	Point3D* p = new Point3D(0.0, 0.0, 0.0);//p����άֱ���뵥��ͼƬ�����Ľ���

	if (i == 0 && j == 0) return point;
	else if (i > 0 && j == 0) {//��x�����������ͶӰ
		for (int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
				p->x = x0;
				p->y = y0;
				p->z = index * this->vox.getInterval();
			/*	cout << "-------------------------------------------------------------" << endl;
				cout << "x������������" << endl;				
				cout << "point->y" << point->x << "point->y" << point->y << endl;
				cout << ">>x�� " << x0 << "  >>y�� " << y0 << endl;*/
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1++;
		}
	}
	else if (i < 0 && j == 0) {//��x�Ḻ�������ͶӰ
		for (int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
			//��¼��
			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
				p->x = x0;
				p->y = y0;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1--;
		}
	}
	else if (i == 0 && j > 0) {//��y�����������ͶӰ
		for (int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
				p->x = x0;
				p->y = y0;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			y1++;
		}
	}
	else if (i == 0 && j < 0) {//��y�Ḻ�������ͶӰ
		/*cout << "i == 0 && j < 0 " << endl;*/
		for (int x1 = x0, y1 = y0,l =0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows;l++ ) {
			/*cout << "int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; " << endl;
			cout << "x1:  " << x1 << "   y1:" << y1 << endl;
			cout << "cols:  " << cols << "   row:" << rows << endl;
			cout << "index : " << index << endl;
			cout << "l : " << l << endl;*/
			//if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				p->x = x0;
				p->y = y0;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			y1--;
		}
	}
	else if (i > 0 && j > 0) {
		//λ�ڵ�һ���ޣ�����slope�����Ϊ�ĵ�
		/*cout << "i > 0 && j > 0" << endl;*/
		if (slope < 1.5) {
			/*cout << "slope: " << slope <<endl;
			cout << "slope < 1.5" << endl;
			cout << "x0; " << x0 << "   y0: " << y0 << "   rows:" << rows << "  cols:" << cols << endl;*/
			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; x1++,y1++) {
				/*cout << "int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < rows && y1 < cols;" << endl;*/
				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
					p->x = x0;
					p->y = y0;
					p->z = index * this->vox.getInterval();
					break;
					//return p;
				}

				x0 = x1;
				y0 = y1;

			}


		}
		else if (slope >= 1.5 && slope < 2.5) {

			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
					p->x = x0;
					p->y = y0;
					p->z = index * this->vox.getInterval();
					break;
					//return p;
				}

				x0 = x1;
				y0 = y1;
				x1++;
				y1 = y1 + 2;//Ϊë+2��������
			}
		}
		else if (slope >= 2.5 && slope < 3.5) {

			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
					p->x = x0;
					p->y = y0;
					p->z = index * this->vox.getInterval();
					break;
					//return p;
				}

				x0 = x1;
				y0 = y1;
				x1++;
				y1 = y1 + 3;
			}
		}
		else {
			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
					p->x = x0;
					p->y = y0;
					p->z = index * this->vox.getInterval();
					break;
					//return p;
				}
	
				x0 = x1;
				y0 = y1;
				y1++;
			}
		}
	}
	else if (i < 0 && j > 0) {
		//λ�ڵڶ�����
		/*cout << "i < 0 && j > 0" << endl;*/
		if (slope < 1.5) {
			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
					p->x = x0;
					p->y = y0;
					p->z = index * this->vox.getInterval();
					break;
					//return p;
				}
				x0 = x1;
				y0 = y1;
				x1--;
				y1++;
			}
		}
		else if (slope >= 1.5 && slope < 2.5) {
			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
					p->x = x0;
					p->y = y0;
					p->z = index * this->vox.getInterval();
					break;
					//return p;
				}
				x0 = x1;
				y0 = y1;
				x1--;
				y1 = y1 + 2;
			}
		}
		else if (slope >= 2.5 && slope < 3.5) {
			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
					p->x = x0;
					p->y = y0;
					p->z = index * this->vox.getInterval();
					break;
					//return p;
				}
				x0 = x1;
				y0 = y1;
				x1--;
				y1 = y1 + 3;
			}
		}
		else {
			for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
					p->x = x0;
					p->y = y0;
					p->z = index * this->vox.getInterval();
					break;
					//return p;
				}
				x0 = x1;
				y0 = y1;
				y1++;
			}
		}




	}
	else if (i < 0 && j < 0) {
	/*cout << "i < 0 && j < 0" << endl;*/
	//λ�ڵ�������
	if (slope < 1.5) {
		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
				p->x = x0;
				p->y = y0;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1--;
			y1--;
		}
	}
	else if (slope >= 1.5 && slope < 2.5) {
		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
				p->x = x0;
				p->y = y0;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1--;
			y1 = y1 - 2;
		}
	}
	else if (slope >= 2.5 && slope < 3.5) {
		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
				p->x = x0;
				p->y = y0;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1--;
			y1 = y1 - 3;
		}
	}
	else {
		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
				p->x = x0;
				p->y = y0;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			y1--;
		}
	}
}
	else if (i > 0 && j < 0) {
	//cout << "i > 0 && j < 0" << endl;
	//λ�ڵ�������
	if (slope < 1.5) {
		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
				p->x = x0;
				p->y = y0;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1++;
			y1--;
		}
	}
	else if (slope >= 1.5 && slope < 2.5) {
		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
				p->x = x0;
				p->y = y0;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1++;
			y1 = y1 - 2;
		}
	}
	else if (slope >= 2.5 && slope < 3.5) {
		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
				p->x = x0;
				p->y = y0;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1++;
			y1 = y1 - 3;
		}
	}
	else {
		for (int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
				p->x = x0;
				p->y = y0;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			y1--;
		}
	}
}
return p;
	//����Ϊֹ����p�ǰ������������ߣ��ҵ��ĵ�һ���Ҷ�ͻ���
	//cout << "ʹ��TS�㷨֮ǰp�����꣺ X: " << p->x <<"   Y: " <<p->y<<"   Z: " <<p->z<< endl;
	//������Ϊ�ǵ�����ʶ�𲿷�
#if 0
	Point P1;//P1��¼p��ƽ������
	P1.x = p->x;
	P1.y = p->y;
	double dis_goodfeatures = Dis_goodfeatures(this->GoodFeatures[index], P1);//opencv�Դ���pointpolygontest�ӿڲ�����Ҫ�Լ�����д

	if (dis_goodfeatures < 8) {
		Point p_fit = Get_NearestPT(this->GoodFeatures[index], P1, dis_goodfeatures);
		//cout << "---------------------------------ʹ��TS�㷨֮ǰp�����꣺ X: " << p->x << "   Y: " << p->y << "   Z: " << p->z << endl;
		p->x = p_fit.x;
		p->y = p_fit.y;
		p->z = index * this->vox.getInterval();
		this->delete_goodfeatures(this->GoodFeatures[index], p_fit);
		//cout << "---------------------------------ʹ��TS�㷨֮��p�����꣺ X: " << p->x << "   Y: " << p->y << "   Z: " << p->z << endl;
	}


#endif
	//cout << "ʹ��TS�㷨֮��p�����꣺ X: " << p->x << "   Y: " << p->y << "   Z: " << p->z << endl;



#endif
	//4-���ص���Ϸ�����������������ͶӰģ��ֻʹ������
#if 0
/*if (index <0 || index>this->vox.AllImage_m.size()) {
	cout << "index"<<index<< endl;
}
cout << "index" << index << endl;*/
if (vec_p.i == 0 && vec_p.j == 0)return nullptr;

Point3D* p = new Point3D(0.0, 0.0, 0.0);
//p1��p2Ϊֱ�߶˵�
Point* p1 = new Point(point->x, point->y);
int x = p1->x;
int y = p1->y;
//cout << "x= " << x << "  y=  " << y << endl;

int cols = this->vox.cols;//�п�
int rows = this->vox.rows;//�п�
//cout << "cols=" << cols << endl;
//cout << "rows=" << rows << endl;
double i = vec_p.i ;
double j = vec_p.j ;
//cout << "i= " << i << "  j=  " << j << endl;
for (int k = 1; x + k * i < rows && y + k * j < cols && x + k * i>0 && y + k * j>0; ++k) {
	int  x1 = x + k * i;
	int  y1 = y + k * j;
	/*cout << "k=" << k << endl;
	cout << "x1=" << x1 << endl;
	cout << "y1=" << y1 << endl;*/
	if (0 <= x1 && x1 < rows && 0 <= y1 && y1 < cols)
	{

		if ((int)this->vox.AllImage_m[index].at<uchar>(x1, y1) == 0)
		{
			//cout << "this->vox.AllImage_m[index].at<uchar>(x1, y1) = " << (int)this->vox.AllImage_m[index].at<uchar>(x1, y1) << endl;
			p->x = x1;
			p->y = y1;
			p->z = index * this->vox.getInterval();
			//cout << ">>x�� " << x << "  >>y�� " << y << endl;
			return p;
		}
	}


}

return p;
#endif
    //5-��������Ϸ���---����
#if 0
//p����άֱ���뵥��ͼƬ�����Ľ���
Point3D* p = new Point3D(0.0, 0.0, 0.0);

//ͼƬ�ĳ���
int xSize = this->vox.cols;
int ySize = this->vox.rows;

Point* p1 = new Point(point->x, point->y);
Point* p2 = new Point(0, 0);
//б�ʲ����ڣ���y�᷽��
if (vec_p.i == 0)
{
	if (vec_p.j > 0)
	{

		p2->y = ySize;
		p2->x = p1->x;
	}
	else if (vec_p.j < 0)
	{
		p2->y = 0;
		p2->x = p1->x;
	}
	else
	{
		return point;
	}
}
//б�ʴ���
else
{
	float k = vec_p.j / vec_p.i;
	//1024ΪͼƬ��С����ͨ�����������ʵʱ�޸�
	//һ���޷���
	if (vec_p.i > 0 && vec_p.j > 0)
	{
		if (k * (xSize - p1->x) + p1->y > ySize)
		{
			p2->y = ySize;
			p2->x = (ySize - p1->y) / k + p1->x;
		}
		else
		{
			p2->x = xSize;
			p2->y = k * (xSize - p1->x) + p1->y;
		}
	}
	//�����޷���
	else if (vec_p.i > 0 && vec_p.j < 0)
	{
		if (k * (xSize - p1->x) + p1->y < 0)
		{
			p2->y = 0;
			p2->x = p1->x - (p1->y / k);
		}
		else
		{
			p2->x = xSize;
			p2->y = k * (xSize - p1->x) + p1->y;
		}
	}
	//�����޷���
	else if (vec_p.i < 0 && vec_p.j > 0)
	{
		if (p1->y - (k * p1->x) > ySize)
		{
			p2->y = ySize;
			p2->x = (ySize - p1->y) / k + p1->x;
		}
		else
		{
			p2->x = 0;
			p2->y = p1->y - (k * p1->x);
		}
	}
	//�����޷���
	else if (vec_p.i < 0 && vec_p.j < 0)
	{
		if (p1->y - (k * p1->x) < 0)
		{
			p2->y = 0;
			p2->x = p1->x - (p1->y / k);
		}
		else
		{
			p2->x = 0;
			p2->y = p1->y - (k * p1->x);
		}
	}
	//x�᷽��
	else if (vec_p.j == 0)
	{
		if (vec_p.i > 0)
		{
			p2->x = xSize;
			p2->y = p1->y;
		}
		else
		{
			p2->x = 0;
			p2->y = p1->y;
		}
	}
}

//������ȡ
vector<vector<Point>>* contours = new vector<vector<Point>>;
vector<Point>* allContour = new vector<Point>;
std::vector<cv::Mat> contourImages; // �洢��������ͼ�������
//vector<Vec4i> hierarchy;//���������ľ���
//��ֹ����ͼƬ�������鷶Χ
if (index >= this->vox.AllImage_m.size())
{
	index = this->vox.AllImage_m.size() - 1;
}
/*
// ָ��ͼ���ļ��е�·��
const std::string imageFolderPath = "C:/Users/ll/Desktop/����������/����������/����������/image_edge";
cv::String pattern = imageFolderPath + "/*.png"; // ʹ�� glob ��ƥ��ģʽ
std::vector<std::string> imageFileNames; // �޸�Ϊ std::string ����
cv::glob(pattern, imageFileNames, true); // ��ȡƥ����ļ���

// ʹ�÷�Χѭ����ȡ����Ӷ���ͼ��
for (const std::string& fileName : imageFileNames) {
	cv::Mat contourImage = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
	if (!contourImage.empty()) {
		contourImages.push_back(contourImage); // ��ͼ����ӵ�������
	}
	else {
		std::cout << "Failed to read image: " << fileName << std::endl;
	}
}
*contours = Obtain_contours(contourImages[index]);*/
/*cout << "��ǰ��" << index << endl;
cv::Mat contourImage = cv::Mat::zeros(this->vox.AllImage_m[index].size(), CV_8UC3);
cv::drawContours(contourImage, *contours, -1, cv::Scalar(0, 0, 255), 1); // ʹ�ú�ɫ������������
cv::imshow("Contours Image", contourImage);
cv::waitKey(0);*/
findContours(this->vox.AllImage_m[index], *contours, RETR_TREE, CHAIN_APPROX_NONE);
//�洢������
//vector<Point>* allContour = new vector<Point>;
/*cv::Mat contourImage = cv::Mat::zeros(this->vox.AllImage_m[index].size(), CV_8UC3);
cv::drawContours(contourImage, *contours, -1, cv::Scalar(255, 255, 255), 1); // ʹ�ú�ɫ������������
cv::imwrite("F:/xihua/4444.png", contourImage);
cv::imshow("Contours Image", contourImage);
cv::waitKey(0);*/
for (int i = 0; i < (*contours).size(); i++)
{
	for (int j = 0; j < (*contours)[i].size(); j++)
	{
		allContour->push_back((*contours)[i][j]);
	}
}


//�������ϵĵ�
double dis = 1;//��ʼ�����趨��0����
LineIterator it(*p1, *p2, 8);
for (int i = 0; i < it.count; ++i, ++it)
{
	//Point pt(it.pos());//����߶��ϵĵ�
	//cout << ">> it.pos(): " << it.pos() << endl;
	dis = pointPolygonTest(*allContour, it.pos(), true);
	//cout << "dis: " << dis << endl;
	//cout << ">> dis =   " << dis << "      i=  " << i << endl;
	if (dis <= 0 && dis > -2)
	{
		if ((int)abs(dis) == 0)
		{
			p->x = it.pos().x;
			p->y = it.pos().y;
			p->z = index * this->vox.getInterval();
			break;
		}
		double dis_goodfeatures = pointPolygonTest(this->GoodFeatures[index], it.pos(), true);
		//cout << ">> dis_goodfeatures =   " << dis_goodfeatures << "      i=  " << i << endl;
		if (dis_goodfeatures < 2 && dis_goodfeatures > -2) {
			Point p_fit = Get_NearestPT(this->GoodFeatures[index], it.pos(), dis_goodfeatures);
			p->x = p_fit.x;
			p->y = p_fit.y;
			p->z = index * this->vox.getInterval();
			break;
		}
		Point p_fit = Get_NearestPT(*allContour, it.pos(), dis);
		p->x = p_fit.x;
		p->y = p_fit.y;
		p->z = index * this->vox.getInterval();
		break;

		/*if (abs(dis) == 0)
		{
			p->x = it.pos().x;
			p->y = it.pos().y;
			p->z = index * this->vox.getInterval();
			break;
		}
		else if (dis > -1 && dis < 0)
		{
			p->x = it.pos().x;
			p->y = it.pos().y;
			p->z = index * this->vox.getInterval();
			break;
		}*/
	}

}


delete p1;
delete p2;
delete contours;
delete allContour;
return p;
#endif

//2023-09-01
#if 0
//���Ȱѳ�ʼ��x\y\i\j�����ó���
double x0 = point->x;
double y0 = point->y;
double z0 = point->z;
double i = vec_p.i;
double j = vec_p.j;
double k = vec_p.k;
Point3D* p = new Point3D(0.0, 0.0, 0.0);
p->x= point->x;
p->y = point->y;
p->z = point->z;
double slope = i / j;
//ͼƬ�ĳ���
int cols = this->vox.cols;//�п� x�������
int rows = this->vox.rows;//�п� y�������

//������ȡ
vector<vector<Point>>* contours = new vector<vector<Point>>;
vector<Point2f>* allContour = new vector<Point2f>;
std::vector<cv::Mat> contourImages; // �洢��������ͼ�������
//vector<Vec4i> hierarchy;//���������ľ���
//��ֹ����ͼƬ�������鷶Χ
if (index >= this->vox.AllImage_m.size())
{
	index = this->vox.AllImage_m.size() - 1;
}

//findContours(this->vox.AllImage_m[index], *contours, RETR_TREE, CHAIN_APPROX_NONE);

//�洢������
*allContour = GetBSpline(vox.AllImage_m[index]);
/*for (int i = 0; i < (*contours).size(); i++)
{
	for (int j = 0; j < (*contours)[i].size(); j++)
	{
		allContour->push_back((*contours)[i][j]);
	}
}*/
if (i == 0 && j == 0) return point;
else if (i > 0 && j == 0) {//��x�����������ͶӰ
	for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

		if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, x0, y0);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			p->x = nearestPoint.x;
			p->y = nearestPoint.y;
			p->z = index * this->vox.getInterval();
			break;
			//return p;
		}
		x0 = x1;
		y0 = y1;
		x1++;
	}
}
else if (i < 0 && j == 0) {//��x�Ḻ�������ͶӰ
	for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
		//��¼��
		if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, x0, y0);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			p->x = nearestPoint.x;
			p->y = nearestPoint.y;
			p->z = index * this->vox.getInterval();
			break;
			//return p;
		}
		x0 = x1;
		y0 = y1;
		x1--;
	}
}
else if (i == 0 && j > 0) {//��y�����������ͶӰ
	for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

		if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, x0, y0);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			p->x = nearestPoint.x;
			p->y = nearestPoint.y;
			p->z = index * this->vox.getInterval();
			break;
			//return p;
		}
		x0 = x1;
		y0 = y1;
		y1++;
	}
}
else if (i == 0 && j < 0) {//��y�Ḻ�������ͶӰ
	/*cout << "i == 0 && j < 0 " << endl;*/
	for (double x1 = x0, y1 = y0, l = 0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; l++) {
		/*cout << "int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; " << endl;
		cout << "x1:  " << x1 << "   y1:" << y1 << endl;
		cout << "cols:  " << cols << "   row:" << rows << endl;
		cout << "index : " << index << endl;
		cout << "l : " << l << endl;*/
		//if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) ==0) {
		if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, x0, y0);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			p->x = nearestPoint.x;
			p->y = nearestPoint.y;
			p->z = index * this->vox.getInterval();
			break;
			//return p;
		}
		x0 = x1;
		y0 = y1;
		y1--;
	}
}
else if (i > 0 && j > 0) {
	//λ�ڵ�һ���ޣ�����slope�����Ϊ�ĵ�
	/*cout << "i > 0 && j > 0" << endl;*/
	if (slope < 1.5) {
		/*cout << "slope: " << slope <<endl;
		cout << "slope < 1.5" << endl;
		cout << "x0; " << x0 << "   y0: " << y0 << "   rows:" << rows << "  cols:" << cols << endl;*/
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; x1++, y1++) {
			/*cout << "int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < rows && y1 < cols;" << endl;*/
			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
								double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}

			x0 = x1;
			y0 = y1;

		}


	}
	else if (slope >= 1.5 && slope < 2.5) {

		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}

			x0 = x1;
			y0 = y1;
			x1++;
			y1 = y1 + 2;//Ϊë+2��������
		}
	}
	else if (slope >= 2.5 && slope < 3.5) {

		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				cout << "ԭʼ��" << x0 << "," << y0 << endl;
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				cout << "������ĵ�" << nearestPoint << endl;
				break;
				//return p;
			}

			x0 = x1;
			y0 = y1;
			x1++;
			y1 = y1 + 3.0;
		}
	}
	else {
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}

			x0 = x1;
			y0 = y1;
			y1++;
		}
	}
}
else if (i < 0 && j > 0) {
	//λ�ڵڶ�����
	/*cout << "i < 0 && j > 0" << endl;*/
	if (slope < 1.5) {
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1--;
			y1++;
		}
	}
	else if (slope >= 1.5 && slope < 2.5) {
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1--;
			y1 = y1 + 2;
		}
	}
	else if (slope >= 2.5 && slope < 3.5) {
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1--;
			y1 = y1 + 3.0;
		}
	}
	else {
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			y1++;
		}
	}




}
else if (i < 0 && j < 0) {
	/*cout << "i < 0 && j < 0" << endl;*/
	//λ�ڵ�������
	if (slope < 1.5) {
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1--;
			y1--;
		}
	}
	else if (slope >= 1.5 && slope < 2.5) {
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1--;
			y1 = y1 - 2.0;
		}
	}
	else if (slope >= 2.5 && slope < 3.5) {
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1--;
			y1 = y1 - 3.0;
		}
	}
	else {
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			y1--;
		}
	}
}
else if (i > 0 && j < 0) {
	//cout << "i > 0 && j < 0" << endl;
	//λ�ڵ�������
	if (slope < 1.5) {
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1++;
			y1--;
		}
	}
	else if (slope >= 1.5 && slope < 2.5) {
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1++;
			y1 = y1 - 2.0;
		}
	}
	else if (slope >= 2.5 && slope < 3.5) {
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			x1++;
			y1 = y1 - 3.0;
		}
	}
	else {
		for (double x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, x0, y0);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				p->x = nearestPoint.x;
				p->y = nearestPoint.y;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			y1--;
		}
	}
}
return p;
/*if (i == 0 && j == 0) return point;
else if (i > 0 && j == 0) {//��x�����������ͶӰ
	while (x0 <= xSize && y0 <= ySize)
	{
		// ʹ�� std::find ����Ŀ���
		auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
		if (it != allContour->end()) {
			return p;
		}
		else {
			x0++;
			p->y = y0;
			p->x = x0;
			p->z = index * this->vox.getInterval();
		}
	}
}
else if (i < 0 && j == 0) {//��x�Ḻ�������ͶӰ
	while (x0 <= xSize && y0 <= ySize)
	{
		// ʹ�� std::find ����Ŀ���
		auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
		if (it != allContour->end()) {
			return p;
		}
		else {
			x0--;
			p->y = y0;
			p->x = x0;
			p->z = index * this->vox.getInterval();
		}
	}
}
else if (i == 0 && j > 0) {//��y�����������ͶӰ
	while (x0 <= xSize && y0 <= ySize)
	{
		// ʹ�� std::find ����Ŀ���
		auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
		if (it != allContour->end()) {
			return p;
		}
		else {
			y0++;
			p->y = y0;
			p->x = x0;
			p->z = index * this->vox.getInterval();
		}
	}
}
else if (i == 0 && j < 0) {//��y�Ḻ�������ͶӰ
	while (x0 <= xSize && y0 <= ySize)
	{
		auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
		if (it != allContour->end()) {
			return p;
		}
		else {
			y0--;
			p->y = y0;
			p->x = x0;
			p->z = index * this->vox.getInterval();
		}
	}
}
else if (i > 0 && j > 0) {
	//λ�ڵ�һ���ޣ�����slope�����Ϊ�ĵ�
	//cout << "i > 0 && j > 0" << endl;
	if (slope < 1.5) {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0++;
				x0++;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		 }

		}

	else if (slope >= 1.5 && slope < 2.5) {

		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0=y0+2;
				x0++;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
	else if (slope >= 2.5 && slope < 3.5) {

		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0 = y0 + 3;
				x0++;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
	else {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0++;
				x0;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
}
else if (i < 0 && j > 0) {
	//λ�ڵڶ�����
	//cout << "i < 0 && j > 0" << endl;
	if (slope < 1.5) {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0++;
				x0--;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
	else if (slope >= 1.5 && slope < 2.5) {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0=y0+2;
				x0--;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
	else if (slope >= 2.5 && slope < 3.5) {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0 = y0 + 3;
				x0--;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
	else {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0++;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}




	}
else if (i < 0 && j < 0) {
	//cout << "i < 0 && j < 0" << endl;
	//λ�ڵ�������
	if (slope < 1.5) {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0--;
				x0--;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
	else if (slope >= 1.5 && slope < 2.5) {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0=y0-2;
				x0--;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
	else if (slope >= 2.5 && slope < 3.5) {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0 = y0 - 3;
				x0--;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
	else {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0--;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
}
else if (i > 0 && j < 0) {
	//cout << "i > 0 && j < 0" << endl;
	//λ�ڵ�������
	if (slope < 1.5) {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0--;
				x0++;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
	else if (slope >= 1.5 && slope < 2.5) {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0=y0-2;
				x0++;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
	else if (slope >= 2.5 && slope < 3.5) {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0 = y0 - 3;
				x0++;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
	else {
		while (x0 <= xSize && y0 <= ySize)
		{
			auto it = std::find(allContour->begin(), allContour->end(), cv::Point(p->x, p->y));
			if (it != allContour->end()) {
				return p;
			}
			else {
				y0--;
				p->y = y0;
				p->x = x0;
				p->z = index * this->vox.getInterval();
			}
		}
	}
}
delete contours;
delete allContour;
return p;*/
#endif
//2023-09-15���Բ��ı�ͶӰ����
#if 0
//���Ȱѳ�ʼ��x\y\i\j�����ó���
double x0 = point->x;
double y0 = point->y;
double z0 = point->z;
double i = vec_p.i;
double j = vec_p.j;
double k = vec_p.k;
Point3D* p = new Point3D(0.0, 0.0, 0.0);
p->x = point->x;
p->y = point->y;
p->z = point->z;
double slope = i / j;
//ͼƬ�ĳ���
int cols = this->vox.cols;//�п� x�������
int rows = this->vox.rows;//�п� y�������

vector<vector<Point>>* contours = new vector<vector<Point>>;
vector<Point2f>* allContour = new vector<Point2f>;
std::vector<cv::Mat> contourImages; // �洢��������ͼ�������
//��ֹ����ͼƬ�������鷶Χ
if (index >= this->vox.AllImage_m.size())
{
	index = this->vox.AllImage_m.size() - 1;
}
//�洢������
*allContour = GetBSpline(vox.AllImage_m[index]);

if (i == 0 && j == 0) return point;
else if (i > 0 && j == 0) {//��x�����������ͶӰ
	cv::Point2f startPoint(x0, y0);
	cv::Point2f endPoint(x0+5.0, y0);
	std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
	cv::Point2f nearestPoint;
	float nearestDistance = std::numeric_limits<float>::max();

	for (const cv::Point2f& contourPoint : *allContour) {
		for (const cv::Point2f& linePoint : linePoints) {
			float dist = distance3(linePoint, contourPoint);

			if (dist < nearestDistance) {
				nearestDistance = dist;
				nearestPoint = contourPoint; // ʹ�� linePoint
			}
		}
	}
	p->x = nearestPoint.x;
	p->y = nearestPoint.y;
	p->z = index * this->vox.getInterval();
}
else if (i < 0 && j == 0) {//��x�Ḻ�������ͶӰ
	cv::Point2f startPoint(x0, y0);
	cv::Point2f endPoint(x0 - 5.0, y0);
	std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
	cv::Point2f nearestPoint;
	float nearestDistance = std::numeric_limits<float>::max();

	for (const cv::Point2f& contourPoint : *allContour) {
		for (const cv::Point2f& linePoint : linePoints) {
			float dist = distance3(linePoint, contourPoint);

			if (dist < nearestDistance) {
				nearestDistance = dist;
				nearestPoint = contourPoint; // ʹ�� linePoint
			}
		}
	}
	p->x = nearestPoint.x;
	p->y = nearestPoint.y;
	p->z = index * this->vox.getInterval();
}
else if (i == 0 && j > 0) {//��y�����������ͶӰ
	cv::Point2f startPoint(x0, y0);
	cv::Point2f endPoint(x0 , y0 + 5.0);
	std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
	cv::Point2f nearestPoint;
	float nearestDistance = std::numeric_limits<float>::max();

	for (const cv::Point2f& contourPoint : *allContour) {
		for (const cv::Point2f& linePoint : linePoints) {
			float dist = distance3(linePoint, contourPoint);

			if (dist < nearestDistance) {
				nearestDistance = dist;
				nearestPoint = contourPoint; // ʹ�� linePoint
			}
		}
	}
	p->x = nearestPoint.x;
	p->y = nearestPoint.y;
	p->z = index * this->vox.getInterval();
}
else if (i == 0 && j < 0) {//��y�Ḻ�������ͶӰ
	cv::Point2f startPoint(x0, y0);
	cv::Point2f endPoint(x0, y0 - 5.0);
	std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
	cv::Point2f nearestPoint;
	float nearestDistance = std::numeric_limits<float>::max();

	for (const cv::Point2f& contourPoint : *allContour) {
		for (const cv::Point2f& linePoint : linePoints) {
			float dist = distance3(linePoint, contourPoint);

			if (dist < nearestDistance) {
				nearestDistance = dist;
				nearestPoint = contourPoint; // ʹ�� linePoint
			}
		}
	}
	p->x = nearestPoint.x;
	p->y = nearestPoint.y;
	p->z = index * this->vox.getInterval();
}
else if (i > 0 && j > 0) {
	//λ�ڵ�һ���ޣ�����slope�����Ϊ�ĵ�
	/*cout << "i > 0 && j > 0" << endl;*/
	if (slope < 1.5) {
		/*cout << "slope: " << slope <<endl;
		cout << "slope < 1.5" << endl;
		cout << "x0; " << x0 << "   y0: " << y0 << "   rows:" << rows << "  cols:" << cols << endl;*/
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0 + 5.0, y0 + 5.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else if (slope >= 1.5 && slope < 2.5) {

		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0 + 4.0, y0 + 8.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else if (slope >= 2.5 && slope < 3.5) {

		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0 + 4.0, y0 + 12.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0, y0 + 5.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
}
else if (i < 0 && j > 0) {
	//λ�ڵڶ�����
	/*cout << "i < 0 && j > 0" << endl;*/
	if (slope < 1.5) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0-5.0, y0 + 5.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else if (slope >= 1.5 && slope < 2.5) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0-4.0, y0 + 8.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else if (slope >= 2.5 && slope < 3.5) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0-4.0, y0 + 12.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0, y0 + 5.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	} 
}
else if (i < 0 && j < 0) {
	/*cout << "i < 0 && j < 0" << endl;*/
	//λ�ڵ�������
	if (slope < 1.5) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0 - 5.0, y0 - 5.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else if (slope >= 1.5 && slope < 2.5) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0 - 4.0, y0 - 8.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else if (slope >= 2.5 && slope < 3.5) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0 - 4.0, y0 - 12.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0, y0 - 5.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
}
else if (i > 0 && j < 0) {
	//cout << "i > 0 && j < 0" << endl;
	//λ�ڵ�������
	if (slope < 1.5) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0 + 5.0, y0 - 5.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else if (slope >= 1.5 && slope < 2.5) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0 + 4.0, y0 - 8.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else if (slope >= 2.5 && slope < 3.5) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0 + 4.0, y0 - 12.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();
		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0, y0 - 5.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
      }
	return p;
#endif
//2023-09-26ֻ��45��ͶӰ
#if 0
	//���Ȱѳ�ʼ��x\y\i\j�����ó���
	double x0 = point->x;
	double y0 = point->y;
	double z0 = point->z;
	double i = vec_p.i;
	double j = vec_p.j;
	double k = vec_p.k;
	Point3D* p = new Point3D(0.0, 0.0, 0.0);
	p->x = point->x;
	p->y = point->y;
	p->z = point->z;
	//ͼƬ�ĳ���

	vector<vector<Point>>* contours = new vector<vector<Point>>;
	vector<Point2f>* allContour = new vector<Point2f>;
	std::vector<cv::Mat> contourImages; // �洢��������ͼ�������
	//��ֹ����ͼƬ�������鷶Χ
	if (index >= this->vox.AllImage_m.size())
	{
		index = this->vox.AllImage_m.size() - 1;
	}
	//�洢������
	*allContour = GetBSpline(vox.AllImage_m[index]);

	if (i == 0 && j == 0) return point;
	else if (i > 0 && j == 0) {//��x�����������ͶӰ
		/*int po = this->vox.AllImage_m[index].at<uchar>(x0 + 4.0, y0);
		if (po == 255)
		{
			p->x = x0 + 4.0;
			p->y = y0;
			p->z = index * this->vox.getInterval();
			return p;
		}*/
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0 + 4.0, y0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else if (i < 0 && j == 0) {//��x�Ḻ�������ͶӰ
		/*int po = this->vox.AllImage_m[index].at<uchar>(x0 - 4.0, y0);
		if (po == 255)
		{
			p->x = x0 - 4.0;
			p->y = y0;
			p->z = index * this->vox.getInterval();
			return p;
		}*/
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0 - 4.0, y0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else if (i == 0 && j > 0) {//��y�����������ͶӰ
		/*int po = this->vox.AllImage_m[index].at<uchar>(x0, y0 + 4.0);
		if (po == 255)
		{
			p->x = x0;
			p->y = y0 + 4.0;
			p->z = index * this->vox.getInterval();
			return p;
		}*/
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0, y0 + 4.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else if (i == 0 && j < 0) {//��y�Ḻ�������ͶӰ
		/*int po = this->vox.AllImage_m[index].at<uchar>(x0, y0 - 4.0);
		if (po == 255)
		{
			p->x = x0;
			p->y = y0 - 4.0;
			p->z = index * this->vox.getInterval();
			return p;
		}*/
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0, y0 - 4.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		p->x = nearestPoint.x;
		p->y = nearestPoint.y;
		p->z = index * this->vox.getInterval();
	}
	else if (i > 0 && j > 0) {
//λ�ڵ�һ���ޣ�����slope�����Ϊ�ĵ�
           /* int po = this->vox.AllImage_m[index].at<uchar>(x0 + 4.0, y0 + 4.0);
            if (po == 255)
             {
	          p->x = x0 + 4.0;
	          p->y = y0 + 4.0;
	          p->z = index * this->vox.getInterval();
	          return p;
               }*/
			cv::Point2f startPoint(x0, y0);
			cv::Point2f endPoint(x0 + 4.0, y0 + 4.0);
			std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
			cv::Point2f nearestPoint;
			float nearestDistance = std::numeric_limits<float>::max();

			for (const cv::Point2f& contourPoint : *allContour) {
				for (const cv::Point2f& linePoint : linePoints) {
					float dist = distance3(linePoint, contourPoint);

					if (dist < nearestDistance) {
						nearestDistance = dist;
						nearestPoint = contourPoint; // ʹ�� linePoint
					}
				}
			}
			p->x = nearestPoint.x;
			p->y = nearestPoint.y;
			p->z = index * this->vox.getInterval();
		
	}
	else if (i < 0 && j > 0) {
             //λ�ڵڶ�����
			 /*int po = this->vox.AllImage_m[index].at<uchar>(x0 - 4.0, y0 + 4.0);
            if (po == 255)
              {
	             p->x = x0 - 4.0;
	             p->y = y0 + 4.0;
	             p->z = index * this->vox.getInterval();
	             return p;
                 }*/
			cv::Point2f startPoint(x0, y0);
			cv::Point2f endPoint(x0 - 4.0, y0 + 4.0);
			std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
			cv::Point2f nearestPoint;
			float nearestDistance = std::numeric_limits<float>::max();

			for (const cv::Point2f& contourPoint : *allContour) {
				for (const cv::Point2f& linePoint : linePoints) {
					float dist = distance3(linePoint, contourPoint);

					if (dist < nearestDistance) {
						nearestDistance = dist;
						nearestPoint = contourPoint; // ʹ�� linePoint
					}
				}
			}
			p->x = nearestPoint.x;
			p->y = nearestPoint.y;
			p->z = index * this->vox.getInterval();
	}
	else if (i < 0 && j < 0) {
            //λ�ڵ�������
			/*int po = this->vox.AllImage_m[index].at<uchar>(x0 - 4.0, y0 - 4.0);
            if (po == 255)
               {
	            p->x = x0 - 4.0;
	            p->y = y0 - 4.0;
	            p->z = index * this->vox.getInterval();
	            return p;
             }*/
			cv::Point2f startPoint(x0, y0);
			cv::Point2f endPoint(x0 - 4.0, y0 - 4.0);
			std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
			cv::Point2f nearestPoint;
			float nearestDistance = std::numeric_limits<float>::max();

			for (const cv::Point2f& contourPoint : *allContour) {
				for (const cv::Point2f& linePoint : linePoints) {
					float dist = distance3(linePoint, contourPoint);

					if (dist < nearestDistance) {
						nearestDistance = dist;
						nearestPoint = contourPoint; // ʹ�� linePoint
					}
				}
			}
			p->x = nearestPoint.x;
			p->y = nearestPoint.y;
			p->z = index * this->vox.getInterval();
	}
	else if (i > 0 && j < 0) {
             //λ�ڵ�������
			 /*int po = this->vox.AllImage_m[index].at<uchar>(x0 + 4.0, y0 - 4.0);
           if (po == 255)
             {
	           p->x = x0 + 4.0;
	           p->y = y0 - 4.0;
	           p->z = index * this->vox.getInterval();
	             return p;
                 }*/
	cv::Point2f startPoint(x0, y0);
	cv::Point2f endPoint(x0 + 4.0, y0 - 4.0);
	std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
	cv::Point2f nearestPoint;
	float nearestDistance = std::numeric_limits<float>::max();

	for (const cv::Point2f& contourPoint : *allContour) {
		for (const cv::Point2f& linePoint : linePoints) {
			float dist = distance3(linePoint, contourPoint);

			if (dist < nearestDistance) {
				nearestDistance = dist;
				nearestPoint = contourPoint; // ʹ�� linePoint
			}
		}
	}
	p->x = nearestPoint.x;
	p->y = nearestPoint.y;
	p->z = index * this->vox.getInterval();
	}
	return p;
#endif
#if 0
	//����
	if (index >= this->vox.AllImage_m.size())
	{
		index = this->vox.AllImage_m.size() - 1;
	}
	//���Ȱѳ�ʼ��x\y\i\j�����ó���
	int x0 = point->x;
	int y0 = point->y;
	int z0 = point->z;
	double i = vec_p.i;
	double j = vec_p.j;
	double k = vec_p.k;
	int lenth = this->vox.minlenth;
	int cols = this->vox.cols;//�п� x�������
	int rows = this->vox.rows;//�п� y�������

	Point3D* p = new Point3D(0.0, 0.0, 0.0);//p����άֱ���뵥��ͼƬ�����Ľ���

	if (i == 0 && j == 0) return point;
	else if (i > 0 && j == 0) {//��x�����������ͶӰ
		int x2 = x0 + 4;
		for (int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
			
			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				p->x = x1;
				p->y = y1;
				p->z = index * this->vox.getInterval();
				break;
			}
			x0 = x1;
			y0 = y1;
			x1++;
		}
	}
	else if (i < 0 && j == 0) {//��x�Ḻ�������ͶӰ
		int x2 = x0 - 4;
		for (int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {
			//��¼��
			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				p->x = x1;
				p->y = y1;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			
			y0 = y1;
			x1--;
		}
	}
	else if (i == 0 && j > 0) {//��y�����������ͶӰ
		int y2 = y0 + 4;
		for (int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				p->x = x1;
				p->y = y1;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			y1++;
		}
	}
	else if (i == 0 && j < 0) {//��y�Ḻ�������ͶӰ
		int y2 = y0 - 4;
		for (int x1 = x0, y1 = y0, l = 0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; l++) {
			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				p->x = x1;
				p->y = y1;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}
			x0 = x1;
			y0 = y1;
			y1--;
		}
	}
	else if (i > 0 && j > 0) {
		//λ�ڵ�һ���ޣ�����slope�����Ϊ�ĵ�
		int x2 = x0 + 4;
		int y2 = y0 + 4;
		for (int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; x1++, y1++) {
			/*cout << "int x1 = x0,  y1 = y0; x1 > 0 && y1 > 0 && x1 < rows && y1 < cols;" << endl;*/
			if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
				p->x = x1;
				p->y = y1;
				p->z = index * this->vox.getInterval();
				break;
				//return p;
			}

			x0 = x1;
			y0 = y1;

		}

	}
	else if (i < 0 && j > 0) {
		//λ�ڵڶ�����
		/*cout << "i < 0 && j > 0" << endl;*/
		    int x2 = x0 - 4;
		    int y2 = y0 + 4;
			for (int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
					p->x = x1;
					p->y = y1;
					p->z = index * this->vox.getInterval();
					break;
					//return p;
				}
				x0 = x1;
				y0 = y1;
				x1--;
				y1++;
		}
	
	}
	else if (i < 0 && j < 0) {
		/*cout << "i < 0 && j < 0" << endl;*/
		//λ�ڵ�������
		    int x2 = x0 - 4;
		    int y2 = y0 - 4;
			for (int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
					p->x = x1;
					p->y = y1;
					p->z = index * this->vox.getInterval();
					break;
					//return p;
				}
				x0 = x1;
				y0 = y1;
				x1--;
				y1--;
		}
	}
	else if (i > 0 && j < 0) {
		//cout << "i > 0 && j < 0" << endl;
		//λ�ڵ�������
		    int x2 = x0 + 4;
		    int y2 = y0 - 4;
			for (int x1 = x0, y1 = y0; x1 > 0 && y1 > 0 && x1 < cols && y1 < rows; ) {

				if ((int)this->vox.AllImage_m[index].at<uchar>(y1, x1) == 0) {
					p->x = x1;
					p->y = y1;
					p->z = index * this->vox.getInterval();
					break;
					//return p;
				}
				x0 = x1;
				y0 = y1;
				x1++;
				y1--;
			
		}
		
	}
	return p;
#endif
}

//��������������
Point3D* get_Surface::get_intersection_point(Point3D* p1, Point3D* p2, Point3D* p3, Point3D* p4)//�������ռ�ֱ�ߵĽ���
{
	//�����ĵ㹹��ƽ��ķ�����
	Point3d* v = new Point3d(0, 0, 0);

	double x_13, x_12, x_34, y_12, y_13, y_34, z_12, z_13, z_34;

	x_12 = p1->x - p2->x;
	x_13 = p1->x - p3->x;
	x_34 = p3->x - p4->x;

	y_12 = p1->y - p2->y;
	y_13 = p1->y - p3->y;
	y_34 = p3->y - p4->y;

	z_12 = p1->z - p2->z;
	z_13 = p1->z - p3->z;
	z_34 = p3->z - p4->z;

	v->x = (y_12 * z_34) - (y_34 * z_12);//���������v�Ǵ�ֱ��ֱ��P1P2,P3P4�Ĺ���������
	v->y = (z_12 * x_34) - (z_34 * x_12);//?????
	v->z = (x_12 * y_34) - (x_34 * y_12);

	double t_xy = ((y_34 * x_13) - (y_13 * x_34)) / ((y_12 * x_34) - (y_34 * x_12));//���� t�ķ����Ǵ�ֱ��p1p3��p3p4�ķ�������t_xy��t��v�ϵ�ӳ��
	double t_xz = ((z_34 * x_13) - (z_13 * x_34)) / ((z_12 * x_34) - (z_34 * x_12));
	double t_yz = ((z_34 * y_13) - (z_13 * y_34)) / ((z_12 * y_34) - (z_34 * y_12));

	//������������λ����
	Point3d* n_x = new Point3d(1, 0, 0);
	Point3d* n_y = new Point3d(0, 1, 0);
	Point3d* n_z = new Point3d(0, 0, 1);
	//������ĵ�
	Point3D* p_relt = new Point3D(0.0, 0.0, 0.0);

	if (n_x->dot(*v) == 0 && (n_z->dot(*v) == 0 || n_y->dot(*v) != 0))//n_x->dot(*v)����v��x�������ĵ�������Ϊ0��ֱ
	{
		p_relt->x = p1->x + (x_12 * t_xz);
		p_relt->y = p1->y + (y_12 * t_xz);
		p_relt->z = p1->z + (z_12 * t_xz);
	}
	else if (n_x->dot(*v) != 0 && (n_z->dot(*v) == 0 || n_y->dot(*v) == 0))
	{
		p_relt->x = p1->x + (x_12 * t_yz);
		p_relt->y = p1->y + (y_12 * t_yz);
		p_relt->z = p1->z + (z_12 * t_yz);
	}
	else
	{
		p_relt->x = p1->x + (x_12 * t_xy);
		p_relt->y = p1->y + (y_12 * t_xy);
		p_relt->z = p1->z + (z_12 * t_xy);
	}
	delete v;
	delete n_x;
	delete n_y;
	delete n_z;

	return p_relt;
}

//s6
Point3D* get_Surface::get_fit_point(Point3D* point, Vec3D vec_p)
{
//1-��ʦ�����
#if 0
	int cols = this->vox.cols;
	int rows = this->vox.rows;
	double x0 = point->x;
	double y0 = point->y;
	double z0 = point->z;
	double i = vec_p.i;
	double j = vec_p.j;
	double k = vec_p.k;
	int minlenth = this->vox.minlenth;
	//��������z0�����ж�
	//���ж�pointλ�ڶ���͵ײ�ͼ������

	int index = point->z / this->vox.getInterval();//z����ȡ��
	//����λ���±��� ��ֱ�Ӳ�������
	if (index == 0) {
		/*cout <<"point->x: " << point->x << "  point->y: " << point->y << "  point->z: " << point->z << endl;*/
		/*cout << "�����λ��ͼ��ײ�Ŷ��������������" << endl;*/
		return this->get_outline_point(point, vec_p, index);
	}
	if (index == this->vox.AllImage_m.size() - 1) {
		/*cout << "�����λ��ͼ�񶥲�Ŷ��������������" << endl;*/
		return this->get_outline_point(point, vec_p, index);
	}
	if (k == 0) {//������9�����
		return this->get_outline_point(point, vec_p, index);
	}//9
	if (k > 0 && j == 0 && i == 0) {
		for (int n = 1; n <= minlenth; ++n) {
			if ((int)this->vox.AllImage_m[index + n].at<uchar>(y0, x0) != 255) {
				return new  Point3D(x0, y0, index + n - 1);
			}
		}
	}
	//10
	if (k < 0 && j == 0 && i == 0) {
		for (int n = 1; n <= minlenth; ++n) {
			if ((int)this->vox.AllImage_m[index - n].at<uchar>(y0, x0) != 255) {
				return new  Point3D(x0, y0, index - n + 1);
			}
		}
	}
	//11
	/*if (k == 0 && j > 0 && i == 0) {
		for (int n = 1; n <= minlenth; ++n) {
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + n, x0) != 255) {
				return new  Point3D(x0, y0 + n - 1, z0);
			}
		}
	}
	if (k == 0 && j < 0 && i == 0) {
		for (int n = 1; n <= minlenth; ++n) {
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - n, x0) != 255) {
				return new  Point3D(x0, y0 - n + 1, z0);
			}
		}
	}
	if (k == 0 && j == 0 && i > 0) {
		for (int n = 1; n <= minlenth; ++n) {
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 , x0+ n) != 255) {
				return new  Point3D(x0+n-1, y0 , z0);
			}
		}
	}
	if (k == 0 && j == 0 && i < 0) {
		for (int n = 1; n <= minlenth; ++n) {
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 , x0- n) != 255) {
				return new  Point3D(x0- n+1, y0  , z0);
			}
		}
	}*/
	if (k > 0 && j > 0 && i > 0) {
		return new  Point3D(x0+minlenth/2, y0 + minlenth / 2, z0 + minlenth / 2);
	}
	//12
	if (k > 0 && j > 0 && i < 0) {
		return new  Point3D(x0 - minlenth / 2, y0 + minlenth / 2, z0 + minlenth / 2);
	}
	//13
	if (k > 0 && j < 0 && i > 0) {
		return new  Point3D(x0 + minlenth / 2, y0 - minlenth / 2, z0 + minlenth / 2);
	}
	//14
	if (k > 0 && j < 0 && i < 0) {
		return new  Point3D(x0 - minlenth / 2, y0 - minlenth / 2, z0 + minlenth / 2);
	}
	//15
    if (k < 0 && j > 0 && i > 0) {
			return new  Point3D(x0 + minlenth / 2, y0 + minlenth / 2, z0 - minlenth / 2);
	}
	//16
	if (k < 0 && j > 0 && i < 0) {
		return new  Point3D(x0 - minlenth / 2, y0 + minlenth / 2, z0 - minlenth / 2);
	}
	//17
	if (k < 0 && j < 0 && i > 0) {
		return new  Point3D(x0 + minlenth / 2, y0 - minlenth / 2, z0 - minlenth / 2);
	}
	//18
	if (k < 0 && j > 0 && i < 0) {
		return new  Point3D(x0 - minlenth / 2, y0 + minlenth / 2, z0 - minlenth / 2);
	}
	//19
	if (k > 0 && j > 0 && i == 0) {
		return new  Point3D(x0 , y0 + minlenth / 2, z0 + minlenth / 2);
	}
	//20
	if (k > 0 && j < 0 && i == 0) {
		return new  Point3D(x0 , y0 - minlenth / 2, z0 + minlenth / 2);
	}
	//21
	if (k > 0 && j == 0 && i > 0) {
		return new  Point3D(x0+ minlenth / 2, y0 , z0 + minlenth / 2);
	}
	//22
	if (k > 0 && j == 0 && i < 0) {
		return new  Point3D(x0- minlenth / 2, y0 , z0 + minlenth / 2);
	}
	//23
	if (k < 0 && j > 0 && i == 0) {
		return new  Point3D(x0, y0 + minlenth / 2, z0 - minlenth / 2);
	}
	//24
	if (k < 0 && j < 0 && i == 0) {
		return new  Point3D(x0, y0 - minlenth / 2, z0 - minlenth / 2);
	}
	//25
	if (k < 0 && j == 0 && i > 0) {
		return new  Point3D(x0 + minlenth / 2, y0, z0 - minlenth / 2);
	}
	//26
	if (k < 0 && j == 0 && i < 0) {
		return new  Point3D(x0 - minlenth / 2, y0, z0 - minlenth / 2);
	}
	//27
	return point;

#endif
	
//2-ʹ���������� ����minlenth���ҷ�Χ
#if 0
	int cols = this->vox.cols;
	int rows = this->vox.rows;
	double x0 = point->x;
	double y0 = point->y;
	double z0 = point->z;
	double i = vec_p.i;
	double j = vec_p.j;
	double k = vec_p.k;
	//��������z0�����ж�
	//���ж�pointλ�ڶ���͵ײ�ͼ������

	int index = point->z / this->vox.getInterval();//z����ȡ��
	//����λ���±��� ��ֱ�Ӳ�������
	if (index == 0) {
		/*cout <<"point->x: " << point->x << "  point->y: " << point->y << "  point->z: " << point->z << endl;*/
		/*cout << "�����λ��ͼ��ײ�Ŷ��������������" << endl;*/
		return this->get_outline_point(point, vec_p, index);
	}
	if (index == this->vox.AllImage_m.size() - 1) {
		/*cout << "�����λ��ͼ�񶥲�Ŷ��������������" << endl;*/
		return this->get_outline_point(point, vec_p, index);
	}
	//��point ��z�᷽���ϵ�����Ϊ0����ֱ���ڵ���ͼ�������
	if (k == 0) {//������9�����
		return this->get_outline_point(point, vec_p, index);
	}
	else {
		//j
		int minlenth = this->vox.minlenth/4;
		/*for (int i0 = 1; i0 < minlenth; i0++) {
			if ((int)this->vox.AllImage_m[index + i0].at<uchar>(y0 + j, x0) != (int)this->vox.AllImage_m[index + i0-1].at<uchar>(y0 +j, x0))
				return new Point3D();
		
		}*/
		if (k > 0) {
			for (int n = 1; n <= minlenth; ++n) {

				if (y0 + (int)(n * j / k) >= rows || y0 + (int)(n * j / k) <= 0 || x0 + (int)(n * i / k) >= cols || x0 + (int)(n * i / k) <= 0)
					return new Point3D(x0 + (int)((n - 1) * i / k), y0 + (int)((n - 1) * j / k), index + n - 1);
				if (abs((int)(n * j / k)) >= minlenth)
				{
					return new Point3D(x0 + (int)(minlenth * i / j), y0 + minlenth, index + (int)(minlenth * k / j));
				}
				if (abs((int)(n * i / k)) >= minlenth)
				{
					return new Point3D(x0 + minlenth, y0 + (int)(minlenth * j / i), index + (int)(minlenth * k / i));
				}

				if ((int)this->vox.AllImage_m[index + n].at<uchar>(y0 + (int)(n * j / k), x0 + (int)(n * i / k)) != 255)
				{
					return new Point3D(x0 + (int)((n - 1) * i / k), y0 + (int)((n - 1) * j / k), index + n - 1);
				}

			}
		}
		if (k < 0) {
			for (int n = 1; n <= minlenth; ++n) {

				if (y0 - (int)(n * j / k) >= rows || y0 - (int)(n * j / k) <= 0 || x0 - (int)(n * i / k) >= cols || x0 - (int)(n * i / k) <= 0)			
					return new Point3D(x0 - (int)((n - 1) * i / k), y0 - (int)((n - 1) * j / k), index - n + 1);

				if (abs((int)(n * j / k)) >= minlenth)
				{
					return new Point3D(x0 - (int)(minlenth * i / j), y0 - minlenth, index -abs( (int)(minlenth * k / j)));
				}
				if (abs((int)(n * i / k)) >= minlenth)
				{
					return new Point3D(x0 + minlenth, y0 + (int)(minlenth * j / i), index -abs( (int)(minlenth * k / i)));
				}

				if ((int)this->vox.AllImage_m[index - n].at<uchar>(y0 + (int)(n * j / k), x0 + (int)(n * i / k)) != 255)
				{
					return new Point3D(x0 + (int)((n - 1) * i / k), y0 + (int)((n - 1) * j / k), index + n - 1);
				}

			}
		}
	
		return new Point3D(x0 + (int)(minlenth * i / k), y0 + (int)(minlenth * j / k), index + minlenth);

	}//2
	

#endif

//3-ʹ�õݹ����ͼƬ�߽�--δ�趨minlenth��Χ
#if 1
	//�Ȱ�point���xyzijk������ȡ����
	double x0 = point->x;
	double y0 = point->y;
	double z0 = point->z;
	double i = vec_p.i;
	double j = vec_p.j;
	double k = vec_p.k;
	//��������z0�����ж�
	//���ж�pointλ�ڶ���͵ײ�ͼ������

	int index = point->z / this->vox.getInterval();//z����ȡ��

	if (index == 0) {
		/*cout <<"point->x: " << point->x << "  point->y: " << point->y << "  point->z: " << point->z << endl;*/
		/*cout << "�����λ��ͼ��ײ�Ŷ��������������" << endl;*/
		return this->get_outline_point(point, vec_p, index);
	}
	if (index == this->vox.AllImage_m.size() - 1) {
		/*cout << "�����λ��ͼ�񶥲�Ŷ��������������" << endl;*/
		return this->get_outline_point(point, vec_p, index);
	}
	//��point ��z�᷽���ϵ�����Ϊ0����ֱ���ڵ���ͼ�������


	if (k == 0) {//������9�����
		return this->get_outline_point(point, vec_p, index);
	}
	//��point ��z�᷽���ϵ�������Ϊ0�����Եݹ�ķ�ʽ�������

	if(k > 0 && j > 0 && i == 0){
		Point3D* p = new Point3D(x0 , y0 + 1, z0 + 1);
		int index1 = p->z / this->vox.getInterval();
		//if()
		if (y0 + 1 >= this->vox.rows) { return point; }
		if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0 + 1, x0 )) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	
	}//2
	else if(k > 0 && j < 0 && i == 0) {
		Point3D* p = new Point3D(x0, y0 - 1, z0 + 1);
		int index1 = p->z / this->vox.getInterval();
		if (y0 - 1 <= 0) { return point; }
		if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0-1 , x0)) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);

	}//5
	else if (k > 0 && j == 0 && i == 0) {
		Point3D* p = new Point3D(x0 , y0 , z0 + 1);
		int index1 = p->z / this->vox.getInterval();
		if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0 , x0 )) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}//8
	else if (k < 0 && j > 0 && i == 0) {
		Point3D* p = new Point3D(x0 , y0 + 1, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (y0 + 1 >= this->vox.rows) { return point; }
		if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0+1 , x0)) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}//11
	else if (k < 0 && j < 0 && i == 0) {
		Point3D* p = new Point3D(x0 , y0 - 1, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (y0 - 1 <= 0) { return point; }
		if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0-1 , x0 )) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}//14
	else if (k < 0 && j == 0 && i == 0) {
		Point3D* p = new Point3D(x0 , y0 , z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0 , x0 )) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}//17
	double slope = abs(j / i);
//k>0 j>0
	if (k > 0 && j > 0 && i > 0) {
		if (slope < 1.5) {
			Point3D* p = new Point3D(x0 + 1, y0 + 1, z0 + 1);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 1 >= this->vox.rows||x0+1>=this->vox.cols ) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0+1, x0+1) != 255) {
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 1.5 && slope < 2.5) {
			Point3D* p = new Point3D(x0 + 1, y0 + 2, z0 + 1);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 2 >= this->vox.rows || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0+2, x0+1) != 255) {
				cout << "slopeӦ�ò�������������" << endl;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 2.5 && slope < 3.5) {
			Point3D* p = new Point3D(x0 + 1, y0 + 3, z0 + 1);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 3 >= this->vox.rows || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0+3, x0+1) != 255) {
				cout << "slope" <<slope << endl;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else {
			Point3D* p = new Point3D(x0 + 1, y0 + 4, z0 + 1);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 4 >= this->vox.rows || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0+4, x0+1) != 255) {
				cout << "slopeӦ�ò�������������" << endl;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
	
	}//1

	else if (k > 0 && j > 0 && i < 0) {
		if (slope < 1.5) {
			Point3D* p = new Point3D(x0 - 1, y0 + 1, z0 + 1);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 1 >= this->vox.rows || x0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0+1, x0-1) != 255) {
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 1.5 && slope < 2.5) {
			Point3D* p = new Point3D(x0 - 1, y0 + 2, z0 + 1);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 2 >= this->vox.rows || x0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0+2, x0-1) != 255) {
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 2.5 && slope < 3.5) {
			Point3D* p = new Point3D(x0 - 1, y0 + 3, z0 + 1);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 3 >= this->vox.rows || x0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0+3, x0-1) != 255) {
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else {
			Point3D* p = new Point3D(x0 - 1, y0 + 4, z0 + 1);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 4 >= this->vox.rows || x0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0+4, x0-1) != 255) {
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
	}//3
	else if (k > 0 && j < 0 && i > 0) {
		if (slope < 1.5) {
			Point3D* p = new Point3D(x0 + 1, y0 - 1, z0 + 1);
			int index1 = p->z / this->vox.getInterval();
			if (y0 - 1 <= 0 || x0 + 1 >= this->vox.cols ) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0-1, x0+1) != 255) {
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 1.5 && slope < 2.5) {
			Point3D* p = new Point3D(x0 + 1, y0 - 2, z0 + 1);
			int index1 = p->z / this->vox.getInterval();
			if (y0 - 2 <= 0 || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0-2, x0+1) != 255) {
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 2.5 && slope < 3.5) {
			Point3D* p = new Point3D(x0 + 1, y0 - 3, z0 + 1);
			int index1 = p->z / this->vox.getInterval();
			if (y0 - 3 <= 0 || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0-3, x0+1) != 255) {
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else {
			Point3D* p = new Point3D(x0 + 1, y0 - 4, z0 + 1);
			int index1 = p->z / this->vox.getInterval();
			if (y0 - 4 <= 0 || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0-4, x0+1) != 255) {
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
	}//4

	else if (k > 0 && j < 0 && i < 0) {
	if (slope < 1.5) {
		Point3D* p = new Point3D(x0 - 1, y0 - 1, z0 + 1);
		int index1 = p->z / this->vox.getInterval();
		if (y0 - 1 <= 0 || x0 - 1 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0-1, x0-1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else if (slope >= 1.5 && slope < 2.5) {
		Point3D* p = new Point3D(x0 - 1, y0 - 2, z0 + 1);
		int index1 = p->z / this->vox.getInterval();
		if (y0 - 2 <= 0 || x0 - 1 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0-2, x0-1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else if (slope >= 2.5 && slope < 3.5) {
		Point3D* p = new Point3D(x0 - 1, y0 - 3, z0 + 1);
		int index1 = p->z / this->vox.getInterval();
		if (y0 - 3 <= 0 || x0 - 1 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0-3, x0-1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else {
		Point3D* p = new Point3D(x0 - 1, y0 - 4, z0 + 1);
		int index1 = p->z / this->vox.getInterval();
		if (y0 - 4 <= 0 || x0 - 1 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0-4, x0-1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	}//6
	else if (k > 0 && j == 0 && i > 0) {
	Point3D* p = new Point3D(x0 + 1, y0 , z0 + 1);
	int index1 = p->z / this->vox.getInterval();
	if ( x0 + 1 >= this->vox.cols ) { return point; }
	if ((int)this->vox.AllImage_m[index].at<uchar>(y0, x0+1) != 255) {
		return point;
	}
	else return this->get_fit_point(p, vec_p);
}//7

	else if (k > 0 && j == 0 && i < 0) {
	Point3D* p = new Point3D(x0 - 1, y0, z0 + 1);
	int index1 = p->z / this->vox.getInterval();
	if (x0 - 1 <=0 ) { return point; }
	if ((int)this->vox.AllImage_m[index].at<uchar>(y0, x0-1) != 255) {
		return point;
	}
	else return this->get_fit_point(p, vec_p);
}//9
	else if (k < 0 && j > 0 && i > 0) {
	if (slope < 1.5) {
		Point3D* p = new Point3D(x0 + 1, y0 + 1, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 + 1 >= this->vox.cols || y0+1 >=this->vox.rows) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0+1, x0+1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else if (slope >= 1.5 && slope < 2.5) {
		Point3D* p = new Point3D(x0 + 1, y0 + 2, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 + 1 >= this->vox.cols || y0 + 2 >= this->vox.rows) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0+2, x0+1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else if (slope >= 2.5 && slope < 3.5) {
		Point3D* p = new Point3D(x0 + 1, y0 + 3, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 + 1 >= this->vox.cols || y0 + 3 >= this->vox.rows) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0+3, x0+1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else {
		Point3D* p = new Point3D(x0 + 1, y0 + 4, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 + 1 >= this->vox.cols || y0 + 4 >= this->vox.rows) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0+4, x0+1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
}//10

	else if (k < 0 && j > 0 && i < 0) {
	if (slope < 1.5) {
		Point3D* p = new Point3D(x0 - 1, y0 + 1, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 - 1 <= 0  || y0 + 1 >= this->vox.rows) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0+1, x0-1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else if (slope >= 1.5 && slope < 2.5) {
		Point3D* p = new Point3D(x0 - 1, y0 + 2, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 - 1 <= 0 || y0 + 2 >= this->vox.rows) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0+2, x0-1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else if (slope >= 2.5 && slope < 3.5) {
		Point3D* p = new Point3D(x0 - 1, y0 + 3, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 - 1 <= 0 || y0 + 3 >= this->vox.rows) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0+3, x0-1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else {
		Point3D* p = new Point3D(x0 - 1, y0 + 4, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 + 1 >= this->vox.cols  || y0 + 4 >= this->vox.rows) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0+4, x0+1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
}//12
	else if (k < 0 && j < 0 && i > 0) {
	if (slope < 1.5) {
		Point3D* p = new Point3D(x0 + 1, y0 - 1, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 + 1 >= this->vox.cols || y0 - 1 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0-1, x0+1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else if (slope >= 1.5 && slope < 2.5) {
		Point3D* p = new Point3D(x0 + 1, y0 - 2, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 + 1 >= this->vox.cols || y0 - 2 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0-2, x0+1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else if (slope >= 2.5 && slope < 3.5) {
		Point3D* p = new Point3D(x0 + 1, y0 - 3, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 + 1 >= this->vox.cols || y0 - 3 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0-3, x0+1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else {
		Point3D* p = new Point3D(x0 + 1, y0 - 4, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 + 1 >= this->vox.cols || y0 - 4 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0-4, x0+1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
}//13

	else if (k < 0 && j < 0 && i < 0) {
	if (slope < 1.5) {
		Point3D* p = new Point3D(x0 - 1, y0 - 1, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 - 1 <= 0 || y0 - 1 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0-1, x0-1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else if (slope >= 1.5 && slope < 2.5) {
		Point3D* p = new Point3D(x0 - 1, y0 - 2, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 - 1 <= 0 || y0 - 2 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0-2, x0-1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else if (slope >= 2.5 && slope < 3.5) {
		Point3D* p = new Point3D(x0 - 1, y0 - 3, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 - 1 <= 0 || y0 - 3 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0-3, x0-1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
	else {
		Point3D* p = new Point3D(x0 - 1, y0 - 4, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 - 1 <= 0 || y0 - 4 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0-4, x0-1) != 255) {
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}
}//15
	else if (k < 0 && j == 0 && i > 0) {
	Point3D* p = new Point3D(x0 + 1, y0 , z0 - 1);
	int index1 = p->z / this->vox.getInterval();
	if (x0 + 1 >=this->vox.cols) { return point; }
	if ((int)this->vox.AllImage_m[index].at<uchar>(y0, x0+1) != 255) {
		return point;
	}
	else return this->get_fit_point(p, vec_p);
}//16

	else if (k < 0 && j == 0 && i < 0) {
	Point3D* p = new Point3D(x0 - 1, y0 , z0 - 1);
	int index1 = p->z / this->vox.getInterval();
	if (x0 - 1 <= 0) { return point; }
	if ((int)this->vox.AllImage_m[index].at<uchar>(y0, x0-1) != 255) {
		return point;
	}
	else return this->get_fit_point(p, vec_p);
}//18 //18+9 == 27


#endif

//4-����ʦ�ַ���
#if 0
	Point3D* p_fit = new Point3D(0.0, 0.0, 0.0);
	//p0,p1Ϊ������ϵĵ㣬p2,p3Ϊ�߽����ϵĵ�
	Point3D* p[4] = { new Point3D(0.0, 0.0, 0.0), new Point3D(0.0, 0.0, 0.0), new Point3D(0.0, 0.0, 0.0), new Point3D(0.0, 0.0, 0.0) };
	p[0] = point;

	//ͼƬ����
	int pic_index = point->z / this->vox.getInterval();
	/*cout << "___________________________________________  " << endl;
	cout << "get_fit_point�е�x����:  " << (double)point->x << endl;
	cout << "get_fit_point�е�y����:  " << (double)point->y << endl;
	cout << "get_fit_point�е�z����:  " << (double)point->z << endl;
	cout << "get_fit_point�е�i����:  " << (double)vec_p.i<< endl;
	cout << "get_fit_point�е�j����:  " << (double)vec_p.j << endl;
	cout << "get_fit_point�е�k����:  " << (double)vec_p.k << endl;*/

	//i==0 j==0��ʱ���ڶ�άͶӰ��һ���㣬�����޷�����ֱ���󽻵�
	if (vec_p.i == 0)
	{
		if (vec_p.j == 0)
		{
			if (vec_p.k == 0) return point;
			//��ע��������Ҫ���Ʋ�ѯ�������߽粻�ö���ײ�
			else if (vec_p.k > 0)
			{
				//��ֱ���ϲ���
				while (pic_index <= (this->vox.AllImage_m.size() - 1))
				{
					if (this->vox.AllImage_m[pic_index].at<uchar>(point->y, point->x) == 255)
					{
						p_fit->x = point->x;
						p_fit->y = point->y;
						p_fit->z = pic_index * this->vox.getInterval();
						pic_index++;
					}
					else
					{
						
						return p_fit;
					}
				}
				
				return p_fit;
			}
			else
			{
				//��ֱ���²���
				while (pic_index >= 0)
				{
					if (this->vox.AllImage_m[pic_index].at<uchar>(point->y, point->x) == 255)
					{
						p_fit->x = point->x;
						p_fit->y = point->y;
						p_fit->z = pic_index * this->vox.getInterval();
						pic_index--;
					}
					else
					{
						//============˼��================
						
						return p_fit;
					}
				}
				
				return p_fit;
			}
		}
		else
		{
			//�����������һ����
			p[1]->y = p[0]->y + 1;
			p[1]->x =vec_p.i / vec_p.j + p[0]->x;// p[0]->x//
			p[1]->z = vec_p.k / vec_p.j + p[0]->z;
		}
	}
	else
	{   
		p[1]->x = p[0]->x + 1;
		p[1]->y = vec_p.j / vec_p.i + p[0]->y;
		p[1]->z = vec_p.k / vec_p.i + p[0]->z;
	}

	//������Ҫ���ұ߽��ͼƬ
	//ͼƬ����
	int index_1 = point->z / vox.getInterval();
	int index_2 = index_1 + 1;

	if (index_2 >= this->vox.AllImage_m.size()) index_2 = this->vox.AllImage_m.size() - 1;

	//������������
	p[2] = this->get_outline_point(point, vec_p, index_1);
	p[3] = this->get_outline_point(point, vec_p, index_2);

	if (p[2]->x == p[3]->x && p[2]->y == p[3]->y && p[2]->z == p[3]->z)//�о�z���������
	{
		return p[2];
	}
	//������άֱ�߽��� (ȱ��ƽ������Ľ������)
	p_fit = this->get_intersection_point(p[0], p[1], p[2], p[3]);
	
	//-----------�о�������------------------
	while (index_1 >= 0 && index_2 <= (this->vox.AllImage_m.size() - 1))
	{
		//�жϽ���λ���Ƿ��ڵ�ǰ��ͼ��֮��
		if (p_fit->z < index_1 * this->vox.getInterval())
		{
			if (index_1 == 0)
			{
				p_fit = this->get_outline_point(point, vec_p, index_1);
				
				return p_fit;
			}
			else
			{
				index_1--;
				index_2--;
				p[2] = this->get_outline_point(point, vec_p, index_1);
				p[3] = this->get_outline_point(point, vec_p, index_2);
				p_fit = this->get_intersection_point(p[0], p[1], p[2], p[3]);
				if (p_fit->z > index_2 * this->vox.getInterval()) {
					
					return p_fit;
				}
					
			}
		}
		else if (p_fit->z > index_2 * this->vox.getInterval())
		{
			if (index_2 == this->vox.AllImage_m.size() - 1)
			{
				p_fit = this->get_outline_point(point, vec_p, index_2);
				
				return p_fit;
			}
			else
			{
				index_1++;
				index_2++;
				p[2] = this->get_outline_point(point, vec_p, index_1);
				p[3] = this->get_outline_point(point, vec_p, index_2);
				p_fit = this->get_intersection_point(p[0], p[1], p[2], p[3]);
				if (p_fit->z < index_1 * this->vox.getInterval()) {
					
					return p_fit;
				}
			}
		}
		else
		{
			
			return p_fit;
		}
	}
	
	return p_fit;
#endif

//5-2023/5/28 д----ֱ�Ӳ�ͼ��߽�
#if 0
	//�Ȱ�point���xyzijk������ȡ����
	double x0 = point->x;
	double y0 = point->y;
	double z0 = point->z;
	double i = vec_p.i;
	double j = vec_p.j;
	double k = vec_p.k;
	int index = point->z / this->vox.getInterval();//z����ȡ��

	if (index == 0) {
		/*cout <<"point->x: " << point->x << "  point->y: " << point->y << "  point->z: " << point->z << endl;*/
		/*cout << "�����λ��ͼ��ײ�Ŷ��������������" << endl;*/
		return this->get_outline_point(point, vec_p, index);
	}
	if (index == this->vox.AllImage_m.size() - 1) {
		/*cout << "�����λ��ͼ�񶥲�Ŷ��������������" << endl;*/
		return this->get_outline_point(point, vec_p, index);
	}
	if (k == 0) {
		return this->get_outline_point(point, vec_p, index);
	}
	if (k > 0) {
		Point3D* p = new Point3D(point->x, point->y, point->z+1);
		return this->get_outline_point(p, vec_p, index+1);
	}
	if (k < 0) {
		Point3D* p = new Point3D(point->x, point->y, point->z - 1);
		return this->get_outline_point(p, vec_p, index - 1);
	}
	return point;
#endif

//6-2023/5/30д
#if 0
	int cols = this->vox.cols;
	int rows = this->vox.rows;
	double x0 = point->x;
	double y0 = point->y;
	double z0 = point->z;
	double i = vec_p.i;
	double j = vec_p.j;
	double k = vec_p.k;
	//��������z0�����ж�
	//���ж�pointλ�ڶ���͵ײ�ͼ������
	int cnt = 0;
	if (i != 0) cnt++;
	if (j != 0) cnt++;
	if (k != 0) cnt++;
	int index = point->z / this->vox.getInterval();//z����ȡ��
	//����λ�����±��� ����k����0  ��ֱ�Ӳ�������
	//if (i == 0 && j == 0 && k == 0) return point;
	if (cnt <= 2 || index == 0 || index == this->vox.AllImage_m.size() - 1)
	{
		return this->get_outline_point(point, vec_p, index);
	}
	if (cnt == 3)
	{
		//j
		int minlenth = this->vox.minlenth;
		int flag = 0;

		if (k > 0 && i > 0 && j > 0)  flag = 1;
		else if (k > 0 && i > 0 && j < 0) flag = 2;
		else if (k > 0 && i < 0 && j > 0) flag = 3;
		else if (k > 0 && i < 0 && j < 0) flag = 4;
		else if (k < 0 && i > 0 && j > 0) flag = 5;
		else if (k < 0 && i > 0 && j < 0) flag = 6;
		else if (k < 0 && i < 0 && j > 0) flag = 7;
		else if (k < 0 && i < 0 && j < 0) flag = 8;
		switch (flag)
		{
			//k > 0 && i > 0 && j > 0
		case 1:
			for (int n = 1; n <= minlenth; n++)
			{
				if (x0 + n >= cols || y0 + n >= rows || z0 + n >= this->vox.AllImage_m.size() - 1)
					return new  Point3D(x0 + n - 1, y0 + n - 1, z0 + n - 1);
				if (this->vox.AllImage_m[index + n].at<uchar>(y0 + n, x0 + n) != 255)
					return new  Point3D(x0 + n - 1, y0 + n - 1, z0 + n - 1);
			}
			return new  Point3D(x0 + minlenth, y0 + minlenth, z0 + minlenth);
			break;
			//k > 0 && i > 0 && j < 0
		case 2:
			for (int n = 1; n <= minlenth; n++)
			{
				if (x0 + n >= cols || y0 - n <= 0 || z0 + n >= this->vox.AllImage_m.size() - 1)
					return new  Point3D(x0 + n - 1, y0 - n + 1, z0 + n - 1);
				if (this->vox.AllImage_m[index + n].at<uchar>(y0 - n, x0 + n) != 255)
					return new  Point3D(x0 + n - 1, y0 - n + 1, z0 + n - 1);;
			}
			return new  Point3D(x0 + minlenth, y0 - minlenth, z0 + minlenth);
			break;
			//	k > 0 && i < 0 && j > 0
		case 3:
			for (int n = 1; n <= minlenth; n++)
			{
				if (x0 - n <= 0 || y0 + n >= rows || z0 + n >= this->vox.AllImage_m.size() - 1)
					return new  Point3D(x0 - n + 1, y0 + n - 1, z0 + n - 1);
				if (this->vox.AllImage_m[index + n].at<uchar>(y0 + n, x0 - n) != 255)
					return new  Point3D(x0 - n + 1, y0 + n - 1, z0 + n - 1);
			}
			return new  Point3D(x0 - minlenth, y0 + minlenth, z0 + minlenth);
			break;
			//k > 0 && i < 0 && j < 0
		case 4:
			for (int n = 1; n <= minlenth; n++)
			{
				if (x0 - n <= 0 || y0 - n <= 0 || z0 + n >= this->vox.AllImage_m.size() - 1)
					return new  Point3D(x0 - n + 1, y0 - n + 1, z0 + n - 1);
				if (this->vox.AllImage_m[index + n].at<uchar>(y0 - n, x0 - n) != 255)
					return new  Point3D(x0 - n + 1, y0 - n + 1, z0 + n - 1);
			}
			return new  Point3D(x0 - minlenth, y0 - minlenth, z0 + minlenth);
			break;
			//k < 0 && i > 0 && j > 0
		case 5:
			for (int n = 1; n <= minlenth; n++)
			{
				if (x0 + n >= cols || y0 + n >= rows || z0 - n <= 0)
					return new  Point3D(x0 + n - 1, y0 + n - 1, z0 - n + 1);
				if (this->vox.AllImage_m[index - n].at<uchar>(y0 + n, x0 + n) != 255)
					return new  Point3D(x0 + n - 1, y0 + n - 1, z0 - n + 1);
			}
			return new  Point3D(x0 + minlenth, y0 + minlenth, z0 - minlenth);

			break;
			//k < 0 && i > 0 && j < 0
		case 6:
			for (int n = 1; n <= minlenth; n++)
			{
				if (x0 + n >= cols || y0 - n <= 0 || z0 - n <= 0)
					return new  Point3D(x0 + n - 1, y0 - n + 1, z0 - n + 1);
				if (this->vox.AllImage_m[index - n].at<uchar>(y0 - n, x0 + n) != 255)
					return new  Point3D(x0 + n - 1, y0 - n + 1, z0 - n + 1);
			}
			return new  Point3D(x0 + minlenth, y0 - minlenth, z0 - minlenth);
			break;
			//k < 0 && i < 0 && j > 0
		case 7:
			for (int n = 1; n <= minlenth; n++)
			{
				if (x0 - n <= 0 || y0 + n >= rows || z0 - n <= 0)
					return new  Point3D(x0 - n + 1, y0 + n - 1, z0 - n + 1);
				if (this->vox.AllImage_m[index - n].at<uchar>(y0 + n, x0 - n) != 255)
					return new  Point3D(x0 - n + 1, y0 + n - 1, z0 - n + 1);
			}
			return new  Point3D(x0 - minlenth, y0 + minlenth, z0 - minlenth);
			break;
			//k < 0 && i < 0 && j < 0
		case 8:
			for (int n = 1; n <= minlenth; n++)
			{
				if (x0 - n <= 0 || y0 - n <= 0 || z0 - n <= 0)
					return new  Point3D(x0 - n + 1, y0 - n + 1, z0 - n + 1);
				if (this->vox.AllImage_m[index - n].at<uchar>(y0 - n, x0 - n) != 255)
					return new  Point3D(x0 - n + 1, y0 - n + 1, z0 - n + 1);
			}
			return new  Point3D(x0 - minlenth, y0 - minlenth, z0 - minlenth);
			break;
		default:
			return point;
			break;

		}

	}
	return point;

#endif
//2023-09-02
#if 0
	//�Ȱ�point���xyzijk������ȡ����
	double x0 = point->x;
	double y0 = point->y;
	double z0 = point->z;
	double i = vec_p.i;
	double j = vec_p.j;
	double k = vec_p.k;
	//��������z0�����ж�
	//���ж�pointλ�ڶ���͵ײ�ͼ������

	int index = point->z / this->vox.getInterval();//z����ȡ��

	if (index == 0) {
		/*cout <<"point->x: " << point->x << "  point->y: " << point->y << "  point->z: " << point->z << endl;*/
		/*cout << "�����λ��ͼ��ײ�Ŷ��������������" << endl;*/
		return this->get_outline_point(point, vec_p, index);
	}
	if (index == this->vox.AllImage_m.size() - 1) {
		/*cout << "�����λ��ͼ�񶥲�Ŷ��������������" << endl;*/
		return this->get_outline_point(point, vec_p, index);
	}
	//��point ��z�᷽���ϵ�����Ϊ0����ֱ���ڵ���ͼ�������


	if (k == 0) {//������9�����
		return this->get_outline_point(point, vec_p, index);
	}
	vector<vector<Point>>* contours = new vector<vector<Point>>;
	vector<Point2f>* allContour = new vector<Point2f>;
	*allContour = GetBSpline(vox.AllImage_m[index]);
	//findContours(this->vox.AllImage_m[index], *contours, RETR_TREE, CHAIN_APPROX_NONE);
	//�洢������

	/*for (int i = 0; i < (*contours).size(); i++)
	{
		for (int j = 0; j < (*contours)[i].size(); j++)
		{
			allContour->push_back((*contours)[i][j]);
		}
	}*/
	//��point ��z�᷽���ϵ�������Ϊ0�����Եݹ�ķ�ʽ�������
	if (k > 0 && j > 0 && i == 0) {
		Point3D* p = new Point3D(x0, y0 + 1, z0 + 2);
		int index1 = p->z / this->vox.getInterval();
		//if()
		if (y0 + 1 >= this->vox.rows) { return point; }
		if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0 + 1, x0)) {

			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, point->x, point->y);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);

	}//2
	else if (k > 0 && j < 0 && i == 0) {
		Point3D* p = new Point3D(x0, y0 - 1, z0 + 2);
		int index1 = p->z / this->vox.getInterval();
		if (y0 - 1 <= 0) { return point; }
		if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0 - 1, x0)) {
			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, point->x, point->y);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);

	}//5
	else if (k > 0 && j == 0 && i == 0) {
		Point3D* p = new Point3D(x0, y0, z0 + 2);
		int index1 = p->z / this->vox.getInterval();
		if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0, x0)) {
			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, point->x, point->y);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}//8
	else if (k < 0 && j > 0 && i == 0) {
		Point3D* p = new Point3D(x0, y0 + 1, z0 - 2);
		int index1 = p->z / this->vox.getInterval();
		if (y0 + 1 >= this->vox.rows) { return point; }
		if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0 + 1, x0)) {
			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, point->x, point->y);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}//11
	else if (k < 0 && j < 0 && i == 0) {
		Point3D* p = new Point3D(x0, y0 - 1, z0 - 2);
		int index1 = p->z / this->vox.getInterval();
		if (y0 - 1 <= 0) { return point; }
		if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0 - 1, x0)) {
			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, point->x, point->y);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}//14
	else if (k < 0 && j == 0 && i == 0) {
		Point3D* p = new Point3D(x0, y0, z0 - 2);
		int index1 = p->z / this->vox.getInterval();
		if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0, x0)) {
			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, point->x, point->y);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}//17
	double slope = abs(j / i);
	//k>0 j>0
	if (k > 0 && j > 0 && i > 0) {
		if (slope < 1.5) {
			Point3D* p = new Point3D(x0 + 1, y0 + 1, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 1 >= this->vox.rows || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 1, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 1.5 && slope < 2.5) {
			Point3D* p = new Point3D(x0 + 1, y0 + 2, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 2 >= this->vox.rows || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 2, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				cout << "slopeӦ�ò�������������" << endl;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 2.5 && slope < 3.5) {
			Point3D* p = new Point3D(x0 + 1, y0 + 3, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 3 >= this->vox.rows || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 3, x0 + 1) != 255) {
				cout << "����ǰ" << "(" << point->x << "," << point->y << ")" << endl;
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				cout << "slope" << slope << endl;
				cout << "������" << "(" << point->x << "," << point->y << ")" << endl;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else {
			Point3D* p = new Point3D(x0 + 1, y0 + 4, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 4 >= this->vox.rows || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 4, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				cout << "slopeӦ�ò�������������" << endl;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}

	}//1

	else if (k > 0 && j > 0 && i < 0) {
		if (slope < 1.5) {
			Point3D* p = new Point3D(x0 - 1, y0 + 1, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 1 >= this->vox.rows || x0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 1, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 1.5 && slope < 2.5) {
			Point3D* p = new Point3D(x0 - 1, y0 + 2, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 2 >= this->vox.rows || x0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 2, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 2.5 && slope < 3.5) {
			Point3D* p = new Point3D(x0 - 1, y0 + 3, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 3 >= this->vox.rows || x0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 3, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else {
			Point3D* p = new Point3D(x0 - 1, y0 + 4, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 + 4 >= this->vox.rows || x0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 4, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
	}//3
	else if (k > 0 && j < 0 && i > 0) {
		if (slope < 1.5) {
			Point3D* p = new Point3D(x0 + 1, y0 - 1, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 - 1 <= 0 || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 1, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 1.5 && slope < 2.5) {
			Point3D* p = new Point3D(x0 + 1, y0 - 2, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 - 2 <= 0 || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 2, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 2.5 && slope < 3.5) {
			Point3D* p = new Point3D(x0 + 1, y0 - 3, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 - 3 <= 0 || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 3, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else {
			Point3D* p = new Point3D(x0 + 1, y0 - 4, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 - 4 <= 0 || x0 + 1 >= this->vox.cols) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 4, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
	}//4

	else if (k > 0 && j < 0 && i < 0) {
		if (slope < 1.5) {
			Point3D* p = new Point3D(x0 - 1, y0 - 1, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 - 1 <= 0 || x0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 1, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 1.5 && slope < 2.5) {
			Point3D* p = new Point3D(x0 - 1, y0 - 2, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 - 2 <= 0 || x0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 2, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 2.5 && slope < 3.5) {
			Point3D* p = new Point3D(x0 - 1, y0 - 3, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 - 3 <= 0 || x0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 3, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else {
			Point3D* p = new Point3D(x0 - 1, y0 - 4, z0 + 2);
			int index1 = p->z / this->vox.getInterval();
			if (y0 - 4 <= 0 || x0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 4, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
	}//6
	else if (k > 0 && j == 0 && i > 0) {
		Point3D* p = new Point3D(x0 + 1, y0, z0 + 2);
		int index1 = p->z / this->vox.getInterval();
		if (x0 + 1 >= this->vox.cols) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0, x0 + 1) != 255) {
			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, point->x, point->y);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}//7

	else if (k > 0 && j == 0 && i < 0) {
		Point3D* p = new Point3D(x0 - 1, y0, z0 + 2);
		int index1 = p->z / this->vox.getInterval();
		if (x0 - 1 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0, x0 - 1) != 255) {
			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, point->x, point->y);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}//9
	else if (k < 0 && j > 0 && i > 0) {
		if (slope < 1.5) {
			Point3D* p = new Point3D(x0 + 1, y0 + 1, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 + 1 >= this->vox.cols || y0 + 1 >= this->vox.rows) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 1, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 1.5 && slope < 2.5) {
			Point3D* p = new Point3D(x0 + 1, y0 + 2, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 + 1 >= this->vox.cols || y0 + 2 >= this->vox.rows) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 2, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 2.5 && slope < 3.5) {
			Point3D* p = new Point3D(x0 + 1, y0 + 3, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 + 1 >= this->vox.cols || y0 + 3 >= this->vox.rows) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 3, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else {
			Point3D* p = new Point3D(x0 + 1, y0 + 4, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 + 1 >= this->vox.cols || y0 + 4 >= this->vox.rows) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 4, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
	}//10

	else if (k < 0 && j > 0 && i < 0) {
		if (slope < 1.5) {
			Point3D* p = new Point3D(x0 - 1, y0 + 1, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 - 1 <= 0 || y0 + 1 >= this->vox.rows) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 1, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 1.5 && slope < 2.5) {
			Point3D* p = new Point3D(x0 - 1, y0 + 2, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 - 1 <= 0 || y0 + 2 >= this->vox.rows) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 2, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 2.5 && slope < 3.5) {
			Point3D* p = new Point3D(x0 - 1, y0 + 3, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 - 1 <= 0 || y0 + 3 >= this->vox.rows) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 3, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else {
			Point3D* p = new Point3D(x0 - 1, y0 + 4, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 + 1 >= this->vox.cols || y0 + 4 >= this->vox.rows) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 4, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
	}//12
	else if (k < 0 && j < 0 && i > 0) {
		if (slope < 1.5) {
			Point3D* p = new Point3D(x0 + 1, y0 - 1, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 + 1 >= this->vox.cols || y0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 1, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 1.5 && slope < 2.5) {
			Point3D* p = new Point3D(x0 + 1, y0 - 2, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 + 1 >= this->vox.cols || y0 - 2 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 2, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 2.5 && slope < 3.5) {
			Point3D* p = new Point3D(x0 + 1, y0 - 3, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 + 1 >= this->vox.cols || y0 - 3 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 3, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else {
			Point3D* p = new Point3D(x0 + 1, y0 - 4, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 + 1 >= this->vox.cols || y0 - 4 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 4, x0 + 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
	}//13

	else if (k < 0 && j < 0 && i < 0) {
		if (slope < 1.5) {
			Point3D* p = new Point3D(x0 - 1, y0 - 1, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 - 1 <= 0 || y0 - 1 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 1, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 1.5 && slope < 2.5) {
			Point3D* p = new Point3D(x0 - 1, y0 - 2, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 - 1 <= 0 || y0 - 2 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 2, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else if (slope >= 2.5 && slope < 3.5) {
			Point3D* p = new Point3D(x0 - 1, y0 - 3, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 - 1 <= 0 || y0 - 3 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 3, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
		else {
			Point3D* p = new Point3D(x0 - 1, y0 - 4, z0 - 2);
			int index1 = p->z / this->vox.getInterval();
			if (x0 - 1 <= 0 || y0 - 4 <= 0) { return point; }
			if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 4, x0 - 1) != 255) {
				double minDistance = std::numeric_limits<double>::max();
				Point2f nearestPoint;
				// ���� allContour �еĵ㣬�ҵ�����ĵ�
				for (const Point2f& contourPoint : *allContour) {
					double dist = distance2(contourPoint, point->x, point->y);
					if (dist < minDistance) {
						minDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				point->x = nearestPoint.x;
				point->y = nearestPoint.y;
				return point;
			}
			else return this->get_fit_point(p, vec_p);
		}
	}//15
	else if (k < 0 && j == 0 && i > 0) {
		Point3D* p = new Point3D(x0 + 1, y0, z0 - 2);
		int index1 = p->z / this->vox.getInterval();
		if (x0 + 1 >= this->vox.cols) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0, x0 + 1) != 255) {
			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, point->x, point->y);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}//16

	else if (k < 0 && j == 0 && i < 0) {
		Point3D* p = new Point3D(x0 - 1, y0, z0 - 2);
		int index1 = p->z / this->vox.getInterval();
		if (x0 - 1 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0, x0 - 1) != 255) {
			double minDistance = std::numeric_limits<double>::max();
			Point2f nearestPoint;
			// ���� allContour �еĵ㣬�ҵ�����ĵ�
			for (const Point2f& contourPoint : *allContour) {
				double dist = distance2(contourPoint, point->x, point->y);
				if (dist < minDistance) {
					minDistance = dist;
					nearestPoint = contourPoint;
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
	}//18 //18+9 == 27


#endif
//only����45��
#if 0
//�Ȱ�point���xyzijk������ȡ����
double x0 = point->x;
double y0 = point->y;
double z0 = point->z;
double i = vec_p.i;
double j = vec_p.j;
double k = vec_p.k;
//��������z0�����ж�
//���ж�pointλ�ڶ���͵ײ�ͼ������

int index = point->z / this->vox.getInterval();//z����ȡ��

if (index == 0) {
	/*cout <<"point->x: " << point->x << "  point->y: " << point->y << "  point->z: " << point->z << endl;*/
	/*cout << "�����λ��ͼ��ײ�Ŷ��������������" << endl;*/
	return this->get_outline_point(point, vec_p, index);
}
if (index == this->vox.AllImage_m.size() - 1) {
	/*cout << "�����λ��ͼ�񶥲�Ŷ��������������" << endl;*/
	return this->get_outline_point(point, vec_p, index);
}
//��point ��z�᷽���ϵ�����Ϊ0����ֱ���ڵ���ͼ�������


if (k == 0 ||k>0 ) {//������9�����
	return this->get_outline_point(point, vec_p, index);
}
vector<vector<Point>>* contours = new vector<vector<Point>>;
vector<Point2f>* allContour = new vector<Point2f>;
*allContour = GetBSpline(vox.AllImage_m[index]);
//findContours(this->vox.AllImage_m[index], *contours, RETR_TREE, CHAIN_APPROX_NONE);
//�洢������

/*for (int i = 0; i < (*contours).size(); i++)
{
	for (int j = 0; j < (*contours)[i].size(); j++)
	{
		allContour->push_back((*contours)[i][j]);
	}
}*/
//��point ��z�᷽���ϵ�������Ϊ0�����Եݹ�ķ�ʽ�������
if (k > 0 && j > 0 && i == 0) {
	Point3D* p = new Point3D(x0, y0 + 0.3, z0 + 1);
	int index1 = p->z / this->vox.getInterval();
	//if()
	if (y0 + 1 >= this->vox.rows) { return point; }
	if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0 + 1, x0)) {

		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0, y0+4.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		point->x = nearestPoint.x;
		point->y = nearestPoint.y;
		return point;
	}
	else return this->get_fit_point(p, vec_p);

}//2
else if (k > 0 && j < 0 && i == 0) {
	Point3D* p = new Point3D(x0, y0 - 0.3, z0 + 1);
	int index1 = p->z / this->vox.getInterval();
	if (y0 - 1 <= 0) { return point; }
	if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0 - 1, x0)) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0, y0 - 4.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		point->x = nearestPoint.x;
		point->y = nearestPoint.y;
		return point;
	}
	else return this->get_fit_point(p, vec_p);

}//5
else if (k > 0 && j == 0 && i == 0) {
	Point3D* p = new Point3D(x0, y0, z0 + 1);
	int index1 = p->z / this->vox.getInterval();
	if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0, x0)) {
		cv::Point2f startPoint(x0-2.0, y0-2.0);
		cv::Point2f endPoint(x0+2.0, y0+2.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		point->x = nearestPoint.x;
		point->y = nearestPoint.y;
		return point;
	}
	else return this->get_fit_point(p, vec_p);
}//8
else if (k < 0 && j > 0 && i == 0) {
	Point3D* p = new Point3D(x0, y0 + 0.3, z0 - 1);
	int index1 = p->z / this->vox.getInterval();
	if (y0 + 1 >= this->vox.rows) { return point; }
	if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0 + 1, x0)) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0, y0 + 4.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		point->x = nearestPoint.x;
		point->y = nearestPoint.y;
		return point;
	}
	else return this->get_fit_point(p, vec_p);
}//11
else if (k < 0 && j < 0 && i == 0) {
	Point3D* p = new Point3D(x0, y0 - 0.3, z0 - 1);
	int index1 = p->z / this->vox.getInterval();
	if (y0 - 1 <= 0) { return point; }
	if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0 - 1, x0)) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0, y0 - 4.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		point->x = nearestPoint.x;
		point->y = nearestPoint.y;
		return point;
	}
	else return this->get_fit_point(p, vec_p);
}//14
else if (k < 0 && j == 0 && i == 0) {
	Point3D* p = new Point3D(x0, y0, z0 - 1);
	int index1 = p->z / this->vox.getInterval();
	if (255 != (int)this->vox.AllImage_m[index1].at<uchar>(y0, x0)) {
		cv::Point2f startPoint(x0-2.0, y0-2.0);
		cv::Point2f endPoint(x0+2.0, y0 +2.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		point->x = nearestPoint.x;
		point->y = nearestPoint.y;
		return point;
	}
	else return this->get_fit_point(p, vec_p);
}//17
double slope = abs(j / i);
//k>0 j>0
if (k > 0 && j > 0 && i > 0) {
	
		Point3D* p = new Point3D(x0 + 0.3, y0 + 0.3, z0 + 1);
		int index1 = p->z / this->vox.getInterval();
		if (y0 + 1 >= this->vox.rows || x0 + 1 >= this->vox.cols) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 1, x0 + 1) != 255) {
			cv::Point2f startPoint(x0, y0);
			cv::Point2f endPoint(x0+4.0, y0 + 4.0);
			std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
			cv::Point2f nearestPoint;
			float nearestDistance = std::numeric_limits<float>::max();

			for (const cv::Point2f& contourPoint : *allContour) {
				for (const cv::Point2f& linePoint : linePoints) {
					float dist = distance3(linePoint, contourPoint);

					if (dist < nearestDistance) {
						nearestDistance = dist;
						nearestPoint = contourPoint; // ʹ�� linePoint
					}
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
}//1

else if (k > 0 && j > 0 && i < 0) {
	
		Point3D* p = new Point3D(x0 - 0.3, y0 + 0.3, z0 + 1);
		int index1 = p->z / this->vox.getInterval();
		if (y0 + 1 >= this->vox.rows || x0 - 1 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 1, x0 - 1) != 255) {
			cv::Point2f startPoint(x0, y0);
			cv::Point2f endPoint(x0-4.0, y0 + 4.0);
			std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
			cv::Point2f nearestPoint;
			float nearestDistance = std::numeric_limits<float>::max();

			for (const cv::Point2f& contourPoint : *allContour) {
				for (const cv::Point2f& linePoint : linePoints) {
					float dist = distance3(linePoint, contourPoint);

					if (dist < nearestDistance) {
						nearestDistance = dist;
						nearestPoint = contourPoint; // ʹ�� linePoint
					}
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
}//3
else if (k > 0 && j < 0 && i > 0) {
		Point3D* p = new Point3D(x0 + 0.3, y0 - 0.3, z0 + 1);
		int index1 = p->z / this->vox.getInterval();
		if (y0 - 1 <= 0 || x0 + 1 >= this->vox.cols) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 1, x0 + 1) != 255) {
			cv::Point2f startPoint(x0, y0);
			cv::Point2f endPoint(x0+4.0, y0 - 4.0);
			std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
			cv::Point2f nearestPoint;
			float nearestDistance = std::numeric_limits<float>::max();

			for (const cv::Point2f& contourPoint : *allContour) {
				for (const cv::Point2f& linePoint : linePoints) {
					float dist = distance3(linePoint, contourPoint);

					if (dist < nearestDistance) {
						nearestDistance = dist;
						nearestPoint = contourPoint; // ʹ�� linePoint
					}
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
}//4

else if (k > 0 && j < 0 && i < 0) {
		Point3D* p = new Point3D(x0 - 0.3, y0 - 0.3, z0 + 1);
		int index1 = p->z / this->vox.getInterval();
		if (y0 - 1 <= 0 || x0 - 1 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 1, x0 - 1) != 255) {
			cv::Point2f startPoint(x0, y0);
			cv::Point2f endPoint(x0-4.0, y0 - 4.0);
			std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
			cv::Point2f nearestPoint;
			float nearestDistance = std::numeric_limits<float>::max();

			for (const cv::Point2f& contourPoint : *allContour) {
				for (const cv::Point2f& linePoint : linePoints) {
					float dist = distance3(linePoint, contourPoint);

					if (dist < nearestDistance) {
						nearestDistance = dist;
						nearestPoint = contourPoint; // ʹ�� linePoint
					}
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
}//6
else if (k > 0 && j == 0 && i > 0) {
	Point3D* p = new Point3D(x0 + 0.3, y0, z0 + 1);
	int index1 = p->z / this->vox.getInterval();
	if (x0 + 1 >= this->vox.cols) { return point; }
	if ((int)this->vox.AllImage_m[index].at<uchar>(y0, x0 + 1) != 255) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0+4.0, y0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		point->x = nearestPoint.x;
		point->y = nearestPoint.y;
		return point;
	}
	else return this->get_fit_point(p, vec_p);
}//7

else if (k > 0 && j == 0 && i < 0) {
	Point3D* p = new Point3D(x0 - 0.3, y0, z0 + 1);
	int index1 = p->z / this->vox.getInterval();
	if (x0 - 1 <= 0) { return point; }
	if ((int)this->vox.AllImage_m[index].at<uchar>(y0, x0 - 1) != 255) {
		cv::Point2f startPoint(x0-4.0, y0);
		cv::Point2f endPoint(x0, y0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		point->x = nearestPoint.x;
		point->y = nearestPoint.y;
		return point;
	}
	else return this->get_fit_point(p, vec_p);
}//9
else if (k < 0 && j > 0 && i > 0) {
		Point3D* p = new Point3D(x0 + 0.3, y0 + 0.3, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 + 1 >= this->vox.cols || y0 + 1 >= this->vox.rows) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 1, x0 + 1) != 255) {
			cv::Point2f startPoint(x0, y0);
			cv::Point2f endPoint(x0+4.0, y0 + 4.0);
			std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
			cv::Point2f nearestPoint;
			float nearestDistance = std::numeric_limits<float>::max();

			for (const cv::Point2f& contourPoint : *allContour) {
				for (const cv::Point2f& linePoint : linePoints) {
					float dist = distance3(linePoint, contourPoint);

					if (dist < nearestDistance) {
						nearestDistance = dist;
						nearestPoint = contourPoint; // ʹ�� linePoint
					}
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
}//10

else if (k < 0 && j > 0 && i < 0) {
		Point3D* p = new Point3D(x0 - 0.3, y0 + 0.3, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 - 1 <= 0 || y0 + 1 >= this->vox.rows) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0 + 1, x0 - 1) != 255) {
			cv::Point2f startPoint(x0, y0);
			cv::Point2f endPoint(x0-4.0, y0 + 4.0);
			std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
			cv::Point2f nearestPoint;
			float nearestDistance = std::numeric_limits<float>::max();

			for (const cv::Point2f& contourPoint : *allContour) {
				for (const cv::Point2f& linePoint : linePoints) {
					float dist = distance3(linePoint, contourPoint);

					if (dist < nearestDistance) {
						nearestDistance = dist;
						nearestPoint = contourPoint; // ʹ�� linePoint
					}
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
}//12
else if (k < 0 && j < 0 && i > 0) {
		Point3D* p = new Point3D(x0 + 0.3, y0 - 0.3, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 + 1 >= this->vox.cols || y0 - 1 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 1, x0 + 1) != 255) {
			cv::Point2f startPoint(x0, y0);
			cv::Point2f endPoint(x0+4.0, y0 - 4.0);
			std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
			cv::Point2f nearestPoint;
			float nearestDistance = std::numeric_limits<float>::max();

			for (const cv::Point2f& contourPoint : *allContour) {
				for (const cv::Point2f& linePoint : linePoints) {
					float dist = distance3(linePoint, contourPoint);

					if (dist < nearestDistance) {
						nearestDistance = dist;
						nearestPoint = contourPoint; // ʹ�� linePoint
					}
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
}//13

else if (k < 0 && j < 0 && i < 0) {
		Point3D* p = new Point3D(x0 - 0.3, y0 - 0.3, z0 - 1);
		int index1 = p->z / this->vox.getInterval();
		if (x0 - 1 <= 0 || y0 - 1 <= 0) { return point; }
		if ((int)this->vox.AllImage_m[index].at<uchar>(y0 - 1, x0 - 1) != 255) {
			cv::Point2f startPoint(x0, y0);
			cv::Point2f endPoint(x0-4.0, y0 - 4.0);
			std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
			cv::Point2f nearestPoint;
			float nearestDistance = std::numeric_limits<float>::max();

			for (const cv::Point2f& contourPoint : *allContour) {
				for (const cv::Point2f& linePoint : linePoints) {
					float dist = distance3(linePoint, contourPoint);

					if (dist < nearestDistance) {
						nearestDistance = dist;
						nearestPoint = contourPoint; // ʹ�� linePoint
					}
				}
			}
			point->x = nearestPoint.x;
			point->y = nearestPoint.y;
			return point;
		}
		else return this->get_fit_point(p, vec_p);
}//15
else if (k < 0 && j == 0 && i > 0) {
	Point3D* p = new Point3D(x0 + 0.3, y0, z0 - 1);
	int index1 = p->z / this->vox.getInterval();
	if (x0 + 1 >= this->vox.cols) { return point; }
	if ((int)this->vox.AllImage_m[index].at<uchar>(y0, x0 + 1) != 255) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0+4.0, y0 - 4.0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		point->x = nearestPoint.x;
		point->y = nearestPoint.y;
		return point;
	}
	else return this->get_fit_point(p, vec_p);
}//16

else if (k < 0 && j == 0 && i < 0) {
	Point3D* p = new Point3D(x0 - 0.3, y0, z0 - 1);
	int index1 = p->z / this->vox.getInterval();
	if (x0 - 1 <= 0) { return point; }
	if ((int)this->vox.AllImage_m[index].at<uchar>(y0, x0 - 1) != 255) {
		cv::Point2f startPoint(x0, y0);
		cv::Point2f endPoint(x0-4.0, y0);
		std::vector<cv::Point2f> linePoints = generateLinePoints(startPoint, endPoint);
		cv::Point2f nearestPoint;
		float nearestDistance = std::numeric_limits<float>::max();

		for (const cv::Point2f& contourPoint : *allContour) {												
			for (const cv::Point2f& linePoint : linePoints) {
				float dist = distance3(linePoint, contourPoint);

				if (dist < nearestDistance) {
					nearestDistance = dist;
					nearestPoint = contourPoint; // ʹ�� linePoint
				}
			}
		}
		point->x = nearestPoint.x;
		point->y = nearestPoint.y;
		return point;
	}
	else return this->get_fit_point(p, vec_p);
}//18 //18+9 == 27


#endif
}

//�Ż�1
Point3D get_Surface::optimize(Point3D p, Vec3D v)
{
	Point3D res(p);
	//double a = this.
	double a = this->vox.minlenth * 3 / 8;//��Ԫ�ߴ��3/8
	//x
	if (v.i > 0)
	{
		res.x = p.x - a;
	}
	else if (v.i < 0)
	{
		res.x = p.x + a;
	}
	//y
	if (v.j > 0)
	{
		res.y = p.y - a;
	}
	else if (v.j < 0)
	{
		res.y = p.y + a;
	}
	//z
	if (v.k > 0)
	{
		res.z = p.z - a;
	}
	else if (v.k < 0)
	{
		res.z = p.z + a;
	}
	return res;
}

//�Ż�2
void get_Surface::optimize2()
{
	Point3D point(0.0, 0.0, 0.0);
	//�����Ż�
	for (int i = 0; i < poor_point.size(); ++i) 
	{
		//���յ�ǰ�㣬��ֹ��������ʱ�ı�����ֵ
		Point3D tmp = *poor_point[i];

		//�˵��Ӧ���ڵ�ƽ����
		int n = broPoint[tmp].size();//���ڵ����
		for (int j = 0; j < n; j++)
		{
			//�����ڵ�ĺ�
			point.x += broPoint[tmp][j]->x;
			point.y += broPoint[tmp][j]->y;
			point.z += broPoint[tmp][j]->z;
		}
		//��ƽ��ֵ
		point.x /= n;
		point.y /= n;
		point.z /= n;

		//---------------------�ж��Ƿ���Ҫ�������ڵ㣬������δ�䣬˵������ԭ���趨�ĵ���Ч ----------------------------------
		//---------------------��Ҫ���ڵ��ڵ�Ϊ broPoint[tmp] �е����е㣬��Ӧ�������ں����һ��bro---------------------------
		if (tmp.x == point.x && tmp.y == point.y && tmp.z == point.z)
		{
			Point3D pointBro(0.0, 0.0, 0.0);
			//��ÿ�����ڵ����ƽ��
			for (int k = 0; k < broPoint[tmp].size(); k++)
			{
				//���յ�ǰ�㣬��ֹ��������ʱ�ı�����ֵ
				Point3D tmpBro = *broPoint[tmp][k];

				//�˵��Ӧ���ڵ�ƽ����
				int nBro = broPoint[tmpBro].size();//���ڵ����
				for (int mBro = 0; mBro < nBro; mBro++)
				{
					//�����ڵ�ĺ�
					pointBro.x += broPoint[tmpBro][mBro]->x;
					pointBro.y += broPoint[tmpBro][mBro]->y;
					pointBro.z += broPoint[tmpBro][mBro]->z;
				}
				//��ƽ��ֵ
				pointBro.x /= nBro;
				pointBro.y /= nBro;
				pointBro.z /= nBro;

				//����ԭ����
				for (int mBro = 0; mBro < optPoint[tmpBro].size(); mBro++)
				{
					optPoint[tmpBro][mBro]->x = pointBro.x;
					optPoint[tmpBro][mBro]->y = pointBro.y;
					optPoint[tmpBro][mBro]->z = pointBro.z;
				}
				pointBro.x = 0;
				pointBro.y = 0;
				pointBro.z = 0;
			}
		}
		//----------------------------------����Ϊ���ڵ�ƽ��----------------------------------------------------
		//------------------------------------------------------------------------------------------------------

		//����ԭ����
		for (int j = 0; j < optPoint[tmp].size(); j++)
		{
			optPoint[tmp][j]->x = point.x;
			optPoint[tmp][j]->y = point.y;
			optPoint[tmp][j]->z = point.z;
		}
		point.x = 0;
		point.y = 0;
		point.z = 0;
	}
}

//�Ż�3 �޲��ƽ��
void get_Surface::optimize3()
{
	Point3D point(0.0, 0.0, 0.0);
	//�����Ż�
	auto it = broPoint.begin();
	for (; it != broPoint.end(); ++it)
	{
		int n = it->second.size();
		for (int j = 0; j < n; j++)
		{
			//�����ڵ�ĺ�
			point.x += it->second[j]->x;
			point.y += it->second[j]->y;
			point.z += it->second[j]->z;
		}
		//��ƽ��ֵ
		point.x /= n;
		point.y /= n;
		point.z /= n;

		//����ԭ����
		for (int j = 0; j < optPoint[it->first].size(); j++)
		{
			optPoint[it->first][j]->x = point.x;
			optPoint[it->first][j]->y = point.y;
			optPoint[it->first][j]->z = point.z;
		}
		point.x = 0;
		point.y = 0;
		point.z = 0;
	}
}

//s4
void get_Surface::get_SurNode()
{
	vector<Point3D> sur_point;//���ƹ�˳s4
	//�ڻ�ȡ���浥Ԫ֮ǰ�ǵ�������ϣ������
	for (int index = 0; index < this->vox.AllImage_m.size(); ++index) {
		this->Get_TotomasiFeatures(index, 50);
	}
	cout << "���ǰ����CTͼƬʣ��ǵ������� " << GoodFeatures[0].size() << endl;
#if 0
	vector<Point3f>* allContour = new vector<Point3f>;
	map<Point3D, Point3D, myCompare> fitNodeHash;
	*allContour = Get3DBSpline(vox);
	for (int i = 0; i < this->sur_faces.size(); i++)
	{
		Point3D* fit_p[4] = { new Point3D(0.0, 0.0, 0.0), new Point3D(0.0, 0.0, 0.0), new Point3D(0.0, 0.0, 0.0), new Point3D(0.0, 0.0, 0.0) };
		for (int j = 0; j < 4; j++)
		{
			cv::Point3f nearestPoint;
			if (fitNodeHash.find(*this->sur_faces[i]->p[j]) != fitNodeHash.end())//��Ϲ���ֱ�Ӷ�ȡ
			{
				//�����ֱ�Ӷ�ȡ	
				*fit_p[j] = fitNodeHash[*this->sur_faces[i]->p[j]];
			}

			else {

				double nearestDistance = std::numeric_limits<float>::max();
				for (const cv::Point3f& contourPoint : *allContour) {
					double dist = distance(*this->sur_faces[i]->p[j], contourPoint);
					if (dist < nearestDistance) {
						nearestDistance = dist;
						nearestPoint = contourPoint;
					}
				}
				fit_p[j]->x = nearestPoint.x;
				fit_p[j]->y = nearestPoint.y;
				fit_p[j]->z = nearestPoint.z;
			}
			fitNodeHash[*this->sur_faces[i]->p[j]] = *fit_p[j];
		}

		Hexahedral3D* node = new Hexahedral3D(this->sur_faces[i]->p[0],
			this->sur_faces[i]->p[1], this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
			fit_p[0], fit_p[1], fit_p[2], fit_p[3], 1);
		this->sur_nodes.push_back(node);

	}

#endif

	Vec3D temp_p(0.0, 0.0, 0.0);
	clock_t begin = clock();
	//��-��ϵ�Ĺ�ϣ����ֹ�ظ������ϵ� 2022.4.23
	map<Point3D, Point3D, myCompare> fitNodeHash;
	map<Point3D, Point3D, myCompare> fitNodeHash2;
	//�ڵ�-�������Ĺ�ϣ��
	map<Point3D, Point3D, myCompare> optNodeHash;
	//get_faces();
	int num_n = 0;
#if 1
		int num = 0;//���Լ����˶��ٴ���ϵ�
		int sum = 0;
		for (int i = 0; i < this->sur_faces.size(); i++)
		{
				Point3D* fit_p[4] = { new Point3D(0.0, 0.0, 0.0), new Point3D(0.0, 0.0, 0.0), new Point3D(0.0, 0.0, 0.0), new Point3D(0.0, 0.0, 0.0) };
				int num_fail = 0;
				//��ϵ����
				/*for (int s = 0; s < 4; s++)
				{
					cout << "λ�÷ֲ�:"<<this->sur_faces[i]->p[s]->x<<","<< this->sur_faces[i]->p[s]->y << 
						","<< this->sur_faces[i]->p[s]->z << endl;
				}*/
	
				for (int j = 0; j < 4; j++)
				{
					//��ϣ���ֹ�ظ������ϵ�
					if (fitNodeHash.find(*this->sur_faces[i]->p[j]) != fitNodeHash.end())//��Ϲ���ֱ�Ӷ�ȡ
					{
						//�����ֱ�Ӷ�ȡ	
						*fit_p[j] = fitNodeHash[*this->sur_faces[i]->p[j]];
	
						//����ԭ���� �Ż�����
						if (optNodeHash.find(*this->sur_faces[i]->p[j]) != optNodeHash.end())
							*this->sur_faces[i]->p[j] = optNodeHash[*this->sur_faces[i]->p[j]];
					}
					else //δ�����������
					{
						//��ķ�����
						temp_p = vecHash[*this->sur_faces[i]->p[j]];//��ķ�����ֱ�Ӳ�ѯ��ϣ����
	
						//��ϵ����
						fit_p[j] = this->get_fit_point(this->sur_faces[i]->p[j], temp_p);
						/*		cout << "������ϵ������" << endl;
								cout << "���ǰxyz������Ϊ��x; " << this->sur_faces[i]->p[j]->x << " y; " << this->sur_faces[i]->p[j]->y << " z:  " << this->sur_faces[i]->p[j]->z << endl;
								cout << "��������Ϊ: i:" << temp_p.i << " j:" << temp_p.j << " k:" << temp_p.k << endl;
								cout << "fit_p[j].x; " << fit_p[j]->x << "fit_p[j].y: " << fit_p[j]->y << "fit_p[j].z: " << fit_p[j]->z << endl;
								if(fit_p[j]==nullptr)
									cout << "fit_p[j]���ֿ�ָ��������������������������������"<< endl;*/
									//����ϵ�����ڵ��Ӧ���� 2022-5-15��
						vecHash[*fit_p[j]] = vecHash[*this->sur_faces[i]->p[j]];
						//������ϵ������ϵ��ϣ��
						fitNodeHash2[*this->sur_faces[i]->p[j]] = *fit_p[j]; 
	#if 1
						//��������Ӧ��ϵ���� ƽ��  �Ż�����
						double dis = distance(fit_p[j], this->sur_faces[i]->p[j]);
						if (dis < ((this->vox.minlenth  * this->vox.minlenth * 9) / 64))//���������Ԫ��ֵ ��СΪ��Ԫ�ߴ�3/8��ƽ�� 
						{
							//cout << "��Ŀ����λ�þ������" << endl;
							Point3D tmp = optimize(*this->sur_faces[i]->p[j], temp_p);//�Ե�λ�ý��е���
							optNodeHash[*this->sur_faces[i]->p[j]] = tmp;
							*this->sur_faces[i]->p[j] = tmp;
							fitNodeHash[tmp] = *fit_p[j];
						}
						else
						{
							optNodeHash[*this->sur_faces[i]->p[j]] = *this->sur_faces[i]->p[j];
						}
	#endif				
					}
					//�ж�����Ƿ�ɹ�����ϵ����꣨0��0��0����Ϊ�����ʧ��
					if (fit_p[j]->x == 0 && fit_p[j]->y == 0 && fit_p[j]->z == 0) {
						num_fail++;
					}
	
	
				}
				
	
				//����õĵ���ԭ���Ķ��㹹����浥Ԫ
				if (num_fail != 0)
				{
					this->fail_faces.push_back(this->sur_faces[i]);
				}
				else
				{
					/*Point3D p4 = { 0.0,0.0,0.0 };
					Point3D p5 = { 1.0,0.0,0.0 };
					Point3D p1 = { 1.0,1.0,0.0 };
					Point3D p0 = { 0.0,1.0,0.0 };
					Point3D p6 = { 1.0,0.0,1.0 };
					Point3D p7 = { 0.0,0.0,1.0 };
					Point3D p3 = { 0.0,1.0,1.0 };
					Point3D p2 = { 1.0,1.0,1.0 };
					float J = 0.0;
					J = Scaled_Jacobian(p0,p1,p2,p3,p4,p5,p6,p7);
					cout << "J:" << J << endl;*/
					//Hexahedral3D* node = new Hexahedral3D( &p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, 1);
					//�����ſɱ�ֵ
					/*float J = 0.0;
					vector<Point2f>* pContour1 = new vector<Point2f>;
					vector<Point2f>* pContour2 = new vector<Point2f>;
					vector<Point2f>* pContour3 = new vector<Point2f>;
					vector<Point2f>* pContour4 = new vector<Point2f>;
					vector<Point2f>* pContour11 = new vector<Point2f>;
					vector<Point2f>* pContour22 = new vector<Point2f>;
					vector<Point2f>* pContour33 = new vector<Point2f>;
					vector<Point2f>* pContour44 = new vector<Point2f>;
					*pContour1 = GetBSpline(vox.AllImage_m[(fit_p[0]->z/ this->vox.getInterval())]);
					*pContour2 = GetBSpline(vox.AllImage_m[(fit_p[1]->z / this->vox.getInterval())]);
					*pContour3 = GetBSpline(vox.AllImage_m[(fit_p[2]->z / this->vox.getInterval())]);
					*pContour4 = GetBSpline(vox.AllImage_m[(fit_p[3]->z / this->vox.getInterval())]);
					for (const cv::Point2f& Point11 : *pContour11) {

						float dis = sqrt(std::pow(Point11.x - fit_p[0]->x, 2) + std::pow(Point11.y - fit_p[0]->y, 2));
						if (dis<=8.0) {

							pContour11->push_back(Point11);
						}

					}
					for (const cv::Point2f& Point22 : *pContour22) {

						float dis = sqrt(std::pow(Point22.x - fit_p[0]->x, 2) + std::pow(Point22.y - fit_p[0]->y, 2));
						if (dis <= 8.0) {

							pContour22->push_back(Point22);
						}

					}
					for (const cv::Point2f& Point33 : *pContour33) {

						float dis = sqrt(std::pow(Point33.x - fit_p[0]->x, 2) + std::pow(Point33.y - fit_p[0]->y, 2));
						if (dis <= 8.0) {

							pContour33->push_back(Point33);
						}

					}
					for (const cv::Point2f& Point44 : *pContour44) {

						float dis = sqrt(std::pow(Point44.x - fit_p[0]->x, 2) + std::pow(Point44.y - fit_p[0]->y, 2));
						if (dis <= 8.0) {

							pContour44->push_back(Point44);
						}

					}
					double maxJ = -DBL_MAX;  // ��ʼ����� J Ϊ������
					std::vector<cv::Point2f> pointsWithMaxJ(4);
					if (J > 1 || J < 0.2)
					{
					for (const cv::Point2f& Point11 : *pContour11) {
						fit_p[0]->x = Point11.x;
						fit_p[0]->y = Point11.y;
						for (const cv::Point2f& Point22 : *pContour22) {
							fit_p[1]->x = Point22.x;
							fit_p[1]->y = Point22.y;
							for (const cv::Point2f& Point33 : *pContour33) {
								fit_p[2]->x = Point33.x;
								fit_p[2]->y = Point33.y;
								for (const cv::Point2f& Point44 : *pContour44) {
									fit_p[3]->x = Point44.x;
									fit_p[3]->y = Point44.y;
									J = Scaled_Jacobian(*this->sur_faces[i]->p[0],
										*this->sur_faces[i]->p[1], *this->sur_faces[i]->p[2], *this->sur_faces[i]->p[3],
										*fit_p[0], *fit_p[1], *fit_p[2], *fit_p[3]);

									if (J > maxJ) {
										maxJ = J;
										pointsWithMaxJ[0] = Point11;
										pointsWithMaxJ[1] = Point22;
										pointsWithMaxJ[2] = Point33;
										pointsWithMaxJ[3] = Point44;
									}
								}
							}

						}
					}
						cout << "�ſɱ�ֵ" << maxJ << endl;
					}
					fit_p[0]->x = pointsWithMaxJ[0].x;
					fit_p[0]->y = pointsWithMaxJ[0].y;
					fit_p[1]->x = pointsWithMaxJ[1].x;
					fit_p[1]->y = pointsWithMaxJ[1].y;
					fit_p[2]->x = pointsWithMaxJ[2].x;
					fit_p[2]->y = pointsWithMaxJ[2].y;
					fit_p[3]->x = pointsWithMaxJ[3].x;
					fit_p[3]->y = pointsWithMaxJ[3].y;
					*/
					/*Face3D* face1;
					face1 = jud_point(this->sur_faces[i]);
					Point3D* ppp[4];
					 if (face1 == nullptr)
					  {
						 ppp[0] = fit_p[0];
						 ppp[1] = fit_p[1];
						 ppp[2] = fit_p[2];
						 ppp[3] = fit_p[3];
					  }
					 else
					  {
						 for (int kk = 0; kk < 4; kk++)
						 {
						   ppp[kk] = fit_p[kk];
						   for (int hh = 0; hh < 4; hh++)
						  {
							   if (ppp[kk]->x == face1->p[hh]->x && ppp[kk]->y == face1->p[hh]->y && ppp[kk]->z == face1->p[hh]->z)
							   {
								   ppp[kk] = face1->p[hh];
							   }
							}
						  }
					  }*/
#if 0
					Point3D* fit_p_d_new = new Point3D(0.0, 0.0, 0.0);
					double dist1 = distance(fit_p[0], fit_p[1]);
					double dist2 = distance(fit_p[2], fit_p[3]);
					bool cos01 = get_cos(vecHash[*this->sur_faces[i]->p[0]], vecHash[*this->sur_faces[i]->p[1]]);
					bool cos23 = get_cos(vecHash[*this->sur_faces[i]->p[2]], vecHash[*this->sur_faces[i]->p[3]]);
					bool cos03 = get_cos(vecHash[*this->sur_faces[i]->p[0]], vecHash[*this->sur_faces[i]->p[3]]);
					bool cos12 = get_cos(vecHash[*this->sur_faces[i]->p[1]], vecHash[*this->sur_faces[i]->p[2]]);
					fit_p_d_new->x = (this->sur_faces[i]->p[0]->x + this->sur_faces[i]->p[1]->x + this->sur_faces[i]->p[2]->x + this->sur_faces[i]->p[3]->x +
						fit_p[0]->x + fit_p[1]->x + fit_p[2]->x + fit_p[3]->x) / 8.0;
					fit_p_d_new->y = (this->sur_faces[i]->p[0]->y + this->sur_faces[i]->p[1]->y + this->sur_faces[i]->p[2]->y + this->sur_faces[i]->p[3]->y +
						fit_p[0]->y + fit_p[1]->y + fit_p[2]->y + fit_p[3]->y) / 8.0;
					fit_p_d_new->z = (this->sur_faces[i]->p[0]->z + this->sur_faces[i]->p[1]->z + this->sur_faces[i]->p[2]->z + this->sur_faces[i]->p[3]->z +
						fit_p[0]->z + fit_p[1]->z + fit_p[2]->z + fit_p[3]->z) / 8.0;
					
						if (cos03 == 0 && cos12 == 0)
						{
							if (dist1 < 2.0 && dist2 < 2.0)
							{
								if (vecHash[*this->sur_faces[i]->p[0]].i != 0 && vecHash[*this->sur_faces[i]->p[0]].j != 0)
								{
									fit_p[1] = fit_p[0];
									fitNodeHash[*this->sur_faces[i]->p[1]] = *fit_p[0];
								}
								else if (vecHash[*this->sur_faces[i]->p[1]].i != 0 && vecHash[*this->sur_faces[i]->p[1]].j != 0)
								{
									fit_p[0] = fit_p[1];
									fitNodeHash[*this->sur_faces[i]->p[0]] = *fit_p[1];
								}
								if (vecHash[*this->sur_faces[i]->p[2]].i != 0 && vecHash[*this->sur_faces[i]->p[2]].j != 0)
								{
									fit_p[3] = fit_p[2];
									fitNodeHash[*this->sur_faces[i]->p[3]] = *fit_p[2];
								}
								else if (vecHash[*this->sur_faces[i]->p[3]].i != 0 && vecHash[*this->sur_faces[i]->p[3]].j != 0)
								{
									fit_p[2] = fit_p[3];
									fitNodeHash[*this->sur_faces[i]->p[2]] = *fit_p[3];
								}
								Hexahedral3D* node = new Hexahedral3D(this->sur_faces[i]->p[0],
									this->sur_faces[i]->p[1], fit_p[1], fit_p[0], this->sur_faces[i]->p[3], this->sur_faces[i]->p[2],
									fit_p[2], fit_p[3], 1);
								this->sur_nodes.push_back(node);
							}
							else if (dist1 >= 2.0 && dist2 < 2.0)
							{
								if (vecHash[*this->sur_faces[i]->p[2]].i != 0 && vecHash[*this->sur_faces[i]->p[2]].j != 0)
								{
										fit_p[3] = fit_p[2];
										fitNodeHash[*this->sur_faces[i]->p[3]] = *fit_p[2];
								}
								else if (vecHash[*this->sur_faces[i]->p[3]].i != 0 && vecHash[*this->sur_faces[i]->p[3]].j != 0)
								{
										fit_p[2] = fit_p[3];
										fitNodeHash[*this->sur_faces[i]->p[2]] = *fit_p[3];
								}

								Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[0],
									this->sur_faces[i]->p[1], this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
									fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
								this->sur_nodes.push_back(node1);
								Hexahedral3D* node2 = new Hexahedral3D(this->sur_faces[i]->p[1],
									this->sur_faces[i]->p[0], fit_p[0], fit_p[1], 
									fit_p_d_new, fit_p_d_new,fit_p_d_new, fit_p_d_new, 1);
								this->sur_nodes.push_back(node2);
								Hexahedral3D* node3 = new Hexahedral3D(this->sur_faces[i]->p[2],
									this->sur_faces[i]->p[3], fit_p[3], fit_p[2],
									fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
								this->sur_nodes.push_back(node3);
								Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[0],
									this->sur_faces[i]->p[3], fit_p[3], fit_p[0],
									fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
								this->sur_nodes.push_back(node4);
								Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[1],
									this->sur_faces[i]->p[2], fit_p[2], fit_p[1],
									fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
								this->sur_nodes.push_back(node5);
								Hexahedral3D* node6 = new Hexahedral3D(fit_p[0], fit_p[1], fit_p[2], fit_p[3],
									fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
								this->sur_nodes.push_back(node6);
							}
							else if (dist1 < 2.0 && dist2 >= 2.0)
							{
								if (vecHash[*this->sur_faces[i]->p[0]].i != 0 && vecHash[*this->sur_faces[i]->p[0]].j != 0)
								{
									fit_p[1] = fit_p[0];
									fitNodeHash[*this->sur_faces[i]->p[1]] = *fit_p[0];
								}
								else if (vecHash[*this->sur_faces[i]->p[1]].i != 0 && vecHash[*this->sur_faces[i]->p[1]].j != 0)
								{
									fit_p[0] = fit_p[1];
									fitNodeHash[*this->sur_faces[i]->p[0]] = *fit_p[1];
								}

								Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[0],
									this->sur_faces[i]->p[1], this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
									fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
								this->sur_nodes.push_back(node1);
								Hexahedral3D* node2 = new Hexahedral3D(this->sur_faces[i]->p[1],
									this->sur_faces[i]->p[0], fit_p[0], fit_p[1],
									fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
								this->sur_nodes.push_back(node2);
								Hexahedral3D* node3 = new Hexahedral3D(this->sur_faces[i]->p[2],
									this->sur_faces[i]->p[3], fit_p[3], fit_p[2],
									fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
								this->sur_nodes.push_back(node3);
								Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[0],
									this->sur_faces[i]->p[3], fit_p[3], fit_p[0],
									fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
								this->sur_nodes.push_back(node4);
								Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[1],
									this->sur_faces[i]->p[2], fit_p[2], fit_p[1],
									fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
								this->sur_nodes.push_back(node5);
								Hexahedral3D* node6 = new Hexahedral3D(fit_p[2], fit_p[3], fit_p[0], fit_p[1],
									fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
								this->sur_nodes.push_back(node6);
							}
							else
							{
								Hexahedral3D* node = new Hexahedral3D(this->sur_faces[i]->p[0],
									this->sur_faces[i]->p[1], this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
									fit_p[0], fit_p[1], fit_p[2], fit_p[3], 1);
								this->sur_nodes.push_back(node);
							}
						}
					   else if (cos03 == 1 || cos12 == 1)
					   {
					        if (cos01 == 1)
					          {
						         if (dist1 < 2.0)
						         {
							     if (vecHash[*this->sur_faces[i]->p[0]].i != 0 && vecHash[*this->sur_faces[i]->p[0]].j != 0)
							      {
								     fit_p[1] = fit_p[0];
								     fitNodeHash[*this->sur_faces[i]->p[1]] = *fit_p[0];
							          }
							     else if (vecHash[*this->sur_faces[i]->p[1]].i != 0 && vecHash[*this->sur_faces[i]->p[1]].j != 0)
							      {
								      fit_p[0] = fit_p[1];
								      fitNodeHash[*this->sur_faces[i]->p[0]] = *fit_p[1];
							          }
							Hexahedral3D* node8 = new Hexahedral3D(fit_p[2],
								fit_p[3], fit_p[0], fit_p[0],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node8);
						         }
						         else if(dist1>= 2.0)
						         {
							Hexahedral3D* node8 = new Hexahedral3D(fit_p[2],
								fit_p[3], fit_p[0], fit_p[0],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node8);
							Hexahedral3D* node9 = new Hexahedral3D(fit_p[1],
								fit_p[2], fit_p[0], fit_p[0],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node9);
						          }

					        }
							else if (cos23 == 1)
					           {
						            if (dist2 < 2.0)
						            {
							            if (vecHash[*this->sur_faces[i]->p[2]].i != 0 && vecHash[*this->sur_faces[i]->p[2]].j != 0)
							            {
								fit_p[3] = fit_p[2];
								fitNodeHash[*this->sur_faces[i]->p[3]] = *fit_p[2];
							            }
							            else if (vecHash[*this->sur_faces[i]->p[3]].i != 0 && vecHash[*this->sur_faces[i]->p[3]].j != 0)
							            {
								fit_p[2] = fit_p[3];
								fitNodeHash[*this->sur_faces[i]->p[2]] = *fit_p[3];
							            }
							Hexahedral3D* node8 = new Hexahedral3D(fit_p[0],
								fit_p[1], fit_p[2], fit_p[2],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node8);
						            }
						      else
						      {
							Hexahedral3D* node8 = new Hexahedral3D(fit_p[0],
								fit_p[1], fit_p[2], fit_p[2],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node8);
							Hexahedral3D* node9 = new Hexahedral3D(fit_p[2],
								fit_p[3], fit_p[0], fit_p[0],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node9);
						       }

					          }
					Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[1],
						this->sur_faces[i]->p[0], fit_p[0], fit_p[1],
						fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					this->sur_nodes.push_back(node1);
					Hexahedral3D* node2 = new Hexahedral3D(this->sur_faces[i]->p[2],
						this->sur_faces[i]->p[3], fit_p[3], fit_p[2],
						fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					this->sur_nodes.push_back(node2);
					Hexahedral3D* node3 = new Hexahedral3D(this->sur_faces[i]->p[0],
						this->sur_faces[i]->p[3], fit_p[3], fit_p[3],
						fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					this->sur_nodes.push_back(node3);
					Hexahedral3D* node4 = new Hexahedral3D(fit_p[0],
						this->sur_faces[i]->p[0], fit_p[3], fit_p[3],
						fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					this->sur_nodes.push_back(node4);
					Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[1],
						this->sur_faces[i]->p[2], fit_p[2], fit_p[2],
						fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					this->sur_nodes.push_back(node5);
					Hexahedral3D* node6 = new Hexahedral3D(fit_p[1],
						this->sur_faces[i]->p[1], fit_p[2], fit_p[2],
						fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					this->sur_nodes.push_back(node6);
					Hexahedral3D* node7 = new Hexahedral3D(this->sur_faces[i]->p[0],
						this->sur_faces[i]->p[1], this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
						fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					this->sur_nodes.push_back(node7);
					
					}
					
					/*if (cos1 == 1 && cos2 == 0 && dist1 > 1.0 && dist1<4.0)
					{
						if (vecHash[*this->sur_faces[i]->p[0]].i != 0 && vecHash[*this->sur_faces[i]->p[0]].j != 0)
						{
							Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[0],
								this->sur_faces[i]->p[3], fit_p[3], fit_p[3],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node1);
							Hexahedral3D* node2 = new Hexahedral3D(fit_p[0],
								this->sur_faces[i]->p[0], fit_p[3], fit_p[3],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node2);
							Hexahedral3D* node3 = new Hexahedral3D(fit_p[1],
								fit_p[2], fit_p[0], fit_p[0],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node3);
							Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[1], this->sur_faces[i]->p[2],
								fit_p[2], fit_p[1],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node4);
							Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
								fit_p[3], fit_p[2],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node5);
							Hexahedral3D* node6 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[1],
								this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node6);
							Hexahedral3D* node7 = new Hexahedral3D(this->sur_faces[i]->p[1], this->sur_faces[i]->p[0],
								fit_p[0], fit_p[1],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node7);
							Hexahedral3D* node8 = new Hexahedral3D(fit_p[2], fit_p[3],
								fit_p[0], fit_p[0],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node8);
						}
						else if (vecHash[*this->sur_faces[i]->p[1]].i != 0 && vecHash[*this->sur_faces[i]->p[1]].j != 0)
						{
							Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[1],
								this->sur_faces[i]->p[2], fit_p[2], fit_p[2],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node1);
							Hexahedral3D* node2 = new Hexahedral3D(fit_p[1],
								this->sur_faces[i]->p[1], fit_p[2], fit_p[2],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node2);
							Hexahedral3D* node3 = new Hexahedral3D(fit_p[3],
								fit_p[0], fit_p[1], fit_p[1],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node3);
							Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[3],
								fit_p[3], fit_p[0],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node4);
							Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
								fit_p[3], fit_p[2],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node5);
							Hexahedral3D* node6 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[1],
								this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node6);
							Hexahedral3D* node7 = new Hexahedral3D(this->sur_faces[i]->p[1], this->sur_faces[i]->p[0],
								fit_p[0], fit_p[1],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node7);
							Hexahedral3D* node8 = new Hexahedral3D(fit_p[2], fit_p[3],
								fit_p[1], fit_p[1],
								fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
							this->sur_nodes.push_back(node8);
						}
					}*/
					//else if (cos1 == 0 && cos2 == 1 && dist2 > 1.0 && dist1 < 4.0)
					//{
					//	if (vecHash[*this->sur_faces[i]->p[2]].i != 0 && vecHash[*this->sur_faces[i]->p[2]].j != 0)
					//	{
					//		Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[2],
					//			this->sur_faces[i]->p[1], fit_p[1], fit_p[1],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node1);
					//		Hexahedral3D* node2 = new Hexahedral3D(fit_p[2],
					//			this->sur_faces[i]->p[2], fit_p[1], fit_p[1],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node2);
					//		Hexahedral3D* node3 = new Hexahedral3D(fit_p[2],
					//			fit_p[0], fit_p[1], fit_p[1],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node3);
					//		Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[3], this->sur_faces[i]->p[0],
					//			fit_p[0], fit_p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node4);
					//		Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[3], this->sur_faces[i]->p[2],
					//			fit_p[2], fit_p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node5);
					//		Hexahedral3D* node6 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[1],
					//			this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node6);
					//		Hexahedral3D* node7 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[1],
					//			fit_p[1], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node7);
					//		Hexahedral3D* node8 = new Hexahedral3D(fit_p[2], fit_p[3],
					//			fit_p[0], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node8);
					//	}
					//	else if (vecHash[*this->sur_faces[i]->p[3]].i != 0 && vecHash[*this->sur_faces[i]->p[3]].j != 0)
					//	{
					//		Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[3],
					//			this->sur_faces[i]->p[0], fit_p[0], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node1);
					//		Hexahedral3D* node2 = new Hexahedral3D(fit_p[3],
					//			this->sur_faces[i]->p[3], fit_p[0], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node2);
					//		Hexahedral3D* node3 = new Hexahedral3D(fit_p[1],
					//			fit_p[3], fit_p[0], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node3);
					//		Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[2], this->sur_faces[i]->p[1],
					//			fit_p[1], fit_p[2],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node4);
					//		Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[3], this->sur_faces[i]->p[2],
					//			fit_p[2], fit_p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node5);
					//		Hexahedral3D* node6 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[1],
					//			this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node6);
					//		Hexahedral3D* node7 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[1],
					//			fit_p[1], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node7);
					//		Hexahedral3D* node8 = new Hexahedral3D(fit_p[2], fit_p[3],
					//			fit_p[1], fit_p[1],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node8);
					//	}
					//}
					//else if(cos1 == 1 && cos2 == 0 && dist1 <= 1.0)
					//	{
					//		if (vecHash[*this->sur_faces[i]->p[0]].i != 0 && vecHash[*this->sur_faces[i]->p[0]].j != 0)
					//		{
					//			fit_p[1] = fit_p[0];
					//			fitNodeHash[*this->sur_faces[i]->p[1]] = *fit_p[0];
					//			Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[0],
					//				this->sur_faces[i]->p[3], fit_p[3], fit_p[3],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node1);
					//			Hexahedral3D* node2 = new Hexahedral3D(fit_p[0],
					//				this->sur_faces[i]->p[0], fit_p[3], fit_p[3],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node2);
					//			Hexahedral3D* node3 = new Hexahedral3D(fit_p[2],
					//				fit_p[3], fit_p[0], fit_p[0],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node3);
					//			Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[1], this->sur_faces[i]->p[2],
					//				fit_p[2], fit_p[1],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node4);
					//			Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//				fit_p[3], fit_p[2],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node5);
					//			Hexahedral3D* node6 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[1],
					//				this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node6);
					//			Hexahedral3D* node7 = new Hexahedral3D(this->sur_faces[i]->p[1], this->sur_faces[i]->p[0],
					//				fit_p[0], fit_p[1],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node7);
					//			/*Hexahedral3D* node8 = new Hexahedral3D(fit_p[2], fit_p[3],
					//				fit_p[0], fit_p[0],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node8);*/
					//		}
					//		else if (vecHash[*this->sur_faces[i]->p[1]].i != 0 && vecHash[*this->sur_faces[i]->p[1]].j != 0)
					//		{
					//			fit_p[0] = fit_p[1];
					//			fitNodeHash[*this->sur_faces[i]->p[0]] = *fit_p[1];
					//			Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[1],
					//				this->sur_faces[i]->p[2], fit_p[2], fit_p[2],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node1);
					//			Hexahedral3D* node2 = new Hexahedral3D(fit_p[1],
					//				this->sur_faces[i]->p[1], fit_p[2], fit_p[2],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node2);
					//			Hexahedral3D* node3 = new Hexahedral3D(fit_p[2],
					//				fit_p[3], fit_p[1], fit_p[1],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node3);
					//			Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[3],
					//				fit_p[3], fit_p[0],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node4);
					//			Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//				fit_p[3], fit_p[2],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node5);
					//			Hexahedral3D* node6 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[1],
					//				this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node6);
					//			Hexahedral3D* node7 = new Hexahedral3D(this->sur_faces[i]->p[1], this->sur_faces[i]->p[0],
					//				fit_p[0], fit_p[1],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node7);
					//			/*Hexahedral3D* node8 = new Hexahedral3D(fit_p[2], fit_p[3],
					//				fit_p[1], fit_p[1],
					//				fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//			this->sur_nodes.push_back(node8);*/
					//		}
					//	}
					//else if (cos1 == 0 && cos2 == 1 && dist2 <= 1.0)
					//	{
					//	if (vecHash[*this->sur_faces[i]->p[2]].i != 0 && vecHash[*this->sur_faces[i]->p[2]].j != 0)
					//	{
					//		fit_p[3] = fit_p[2];
					//		fitNodeHash[*this->sur_faces[i]->p[3]] = *fit_p[2];
					//		Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[2],
					//			this->sur_faces[i]->p[1], fit_p[1], fit_p[1],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node1);
					//		Hexahedral3D* node2 = new Hexahedral3D(fit_p[2],
					//			this->sur_faces[i]->p[2], fit_p[1], fit_p[1],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node2);
					//		Hexahedral3D* node3 = new Hexahedral3D(fit_p[2],
					//			fit_p[0], fit_p[1], fit_p[1],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node3);
					//		Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[3], this->sur_faces[i]->p[0],
					//			fit_p[0], fit_p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node4);
					//		Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[3], this->sur_faces[i]->p[2],
					//			fit_p[2], fit_p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node5);
					//		Hexahedral3D* node6 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[1],
					//			this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node6);
					//		Hexahedral3D* node7 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[1],
					//			fit_p[1], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node7);
					//		/*Hexahedral3D* node8 = new Hexahedral3D(fit_p[2], fit_p[3],
					//			fit_p[0], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node8);*/
					//	}
					//	else if (vecHash[*this->sur_faces[i]->p[3]].i != 0 && vecHash[*this->sur_faces[i]->p[3]].j != 0)
					//	{
					//		fit_p[2] = fit_p[3];
					//		fitNodeHash[*this->sur_faces[i]->p[2]] = *fit_p[3];
					//		Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[3],
					//			this->sur_faces[i]->p[0], fit_p[0], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node1);
					//		Hexahedral3D* node2 = new Hexahedral3D(fit_p[3],
					//			this->sur_faces[i]->p[3], fit_p[0], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node2);
					//		Hexahedral3D* node3 = new Hexahedral3D(fit_p[1],
					//			fit_p[3], fit_p[0], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node3);
					//		Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[2], this->sur_faces[i]->p[1],
					//			fit_p[1], fit_p[2],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node4);
					//		Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[3], this->sur_faces[i]->p[2],
					//			fit_p[2], fit_p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node5);
					//		Hexahedral3D* node6 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[1],
					//			this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node6);
					//		Hexahedral3D* node7 = new Hexahedral3D(this->sur_faces[i]->p[0], this->sur_faces[i]->p[1],
					//			fit_p[1], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node7);
					//		/*Hexahedral3D* node8 = new Hexahedral3D(fit_p[2], fit_p[3],
					//			fit_p[1], fit_p[1],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node8);*/
					//	}
					//	}
					//else if(cos1 == 1 && cos2 == 1 )
					//{

					//if (dist1 <= 1.0 && dist2 <= 1.0)
					//{
					//	fit_p[1] = fit_p[0];
					//	fit_p[3] = fit_p[2];
					//	fitNodeHash[*this->sur_faces[i]->p[1]] = *fit_p[0];
					//	fitNodeHash[*this->sur_faces[i]->p[3]] = *fit_p[2];
					//	Hexahedral3D* node = new Hexahedral3D(this->sur_faces[i]->p[1],
					//		this->sur_faces[i]->p[0], fit_p[0], fit_p[1], 
					//		this->sur_faces[i]->p[2], this->sur_faces[i]->p[3] , fit_p[3], fit_p[2], 1);	
					//	this->sur_nodes.push_back(node);
					//	}
					//else if (dist1 > 1.0 && dist2 <= 1.0)
					//{
					//	fit_p[3] = fit_p[2];
					//	fitNodeHash[*this->sur_faces[i]->p[3]] = *fit_p[2];
					//	Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[3],
					//		this->sur_faces[i]->p[0], fit_p[0], fit_p[3],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node1);
					//	Hexahedral3D* node2 = new Hexahedral3D(this->sur_faces[i]->p[1],
					//		this->sur_faces[i]->p[2], fit_p[2], fit_p[1],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node2);
					//	Hexahedral3D* node3 = new Hexahedral3D(this->sur_faces[i]->p[2],
					//		this->sur_faces[i]->p[3], fit_p[3], fit_p[2],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node3);
					//	Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[0],
					//		this->sur_faces[i]->p[1], this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node4);
					//	Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[1],
					//		this->sur_faces[i]->p[0], fit_p[0], fit_p[1],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node5);
					//	Hexahedral3D* node6 = new Hexahedral3D(fit_p[0], fit_p[1],
					//		fit_p[2], fit_p[3], fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node6);
					//    }
					//else if (dist1 <= 1.0 && dist2 > 1.0)
					//{
					//	fit_p[1] = fit_p[0];
					//	fitNodeHash[*this->sur_faces[i]->p[1]] = *fit_p[0];
					//	Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[3],
					//		this->sur_faces[i]->p[0], fit_p[0], fit_p[3],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node1);
					//	Hexahedral3D* node2 = new Hexahedral3D(this->sur_faces[i]->p[1],
					//		this->sur_faces[i]->p[2], fit_p[2], fit_p[1],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node2);
					//	Hexahedral3D* node3 = new Hexahedral3D(this->sur_faces[i]->p[2],
					//		this->sur_faces[i]->p[3], fit_p[3], fit_p[2],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node3);
					//	Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[0],
					//		this->sur_faces[i]->p[1], this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node4);
					//	Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[1],
					//		this->sur_faces[i]->p[0], fit_p[0], fit_p[1],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node5);
					//	Hexahedral3D* node6 = new Hexahedral3D(fit_p[2], fit_p[3], fit_p[0], fit_p[1],
					//		 fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node6);
					//}
					//else if (dist1 <1.0 && dist2 > 4.0)
					//{
					//	if (vecHash[*this->sur_faces[i]->p[0]].i != 0 && vecHash[*this->sur_faces[i]->p[0]].j != 0)
					//	{ 
					//		fit_p[1] = fit_p[0];
					//		fitNodeHash[*this->sur_faces[i]->p[1]] = *fit_p[0];
					//		Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[0],
					//			this->sur_faces[i]->p[3], fit_p[3], fit_p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node1);
					//		Hexahedral3D* node2 = new Hexahedral3D(this->sur_faces[i]->p[0],
					//			fit_p[0], fit_p[3], fit_p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node2);
					//		Hexahedral3D* node3 = new Hexahedral3D(fit_p[2],
					//			fit_p[3], fit_p[0], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node3);
					//		Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[1],
					//			fit_p[2], fit_p[1], fit_p[1],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node4);
					//		Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[2],
					//			this->sur_faces[i]->p[1], fit_p[2], fit_p[2],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node5);
					//		Hexahedral3D* node6 = new Hexahedral3D(this->sur_faces[i]->p[0],
					//			this->sur_faces[i]->p[1], this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node6);
					//		Hexahedral3D* node7 = new Hexahedral3D(this->sur_faces[i]->p[1],
					//			this->sur_faces[i]->p[0], fit_p[0], fit_p[1],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node7);
					//		Hexahedral3D* node8 = new Hexahedral3D(this->sur_faces[i]->p[2],
					//			this->sur_faces[i]->p[3], fit_p[3], fit_p[2],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node8);
					//	}
					//	else if (vecHash[*this->sur_faces[i]->p[1]].i != 0 && vecHash[*this->sur_faces[i]->p[1]].j != 0)
					//	{
					//		fit_p[0] = fit_p[1];
					//		fitNodeHash[*this->sur_faces[i]->p[0]] = *fit_p[1];
					//		Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[0],
					//			this->sur_faces[i]->p[3], fit_p[3], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node1);
					//		Hexahedral3D* node2 = new Hexahedral3D(fit_p[2],
					//			fit_p[3], fit_p[0], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node2);
					//		Hexahedral3D* node3 = new Hexahedral3D(fit_p[2],
					//			fit_p[3], fit_p[0], fit_p[0],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node3);
					//		Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[1],
					//			fit_p[2], fit_p[1], fit_p[1],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node4);
					//		Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[2],
					//			this->sur_faces[i]->p[1], fit_p[2], fit_p[2],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node5);
					//		Hexahedral3D* node6 = new Hexahedral3D(this->sur_faces[i]->p[0],
					//			this->sur_faces[i]->p[1], this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node6);
					//		Hexahedral3D* node7 = new Hexahedral3D(this->sur_faces[i]->p[1],
					//			this->sur_faces[i]->p[0], fit_p[0], fit_p[1],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node7);
					//		Hexahedral3D* node8 = new Hexahedral3D(this->sur_faces[i]->p[2],
					//			this->sur_faces[i]->p[3], fit_p[3], fit_p[2],
					//			fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//		this->sur_nodes.push_back(node8);
					//	}
					//	
					//}
					//else if (dist2 <1.0 && dist1 > 4.0)
					//{
					//if (vecHash[*this->sur_faces[i]->p[0]].i != 0 && vecHash[*this->sur_faces[i]->p[0]].j != 0)
					//{
					//	fit_p[1] = fit_p[0];
					//	fitNodeHash[*this->sur_faces[i]->p[1]] = *fit_p[0];
					//	Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[0],
					//		this->sur_faces[i]->p[3], fit_p[3], fit_p[3],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node1);
					//	Hexahedral3D* node2 = new Hexahedral3D(this->sur_faces[i]->p[0],
					//		fit_p[0], fit_p[3], fit_p[3],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node2);
					//	Hexahedral3D* node3 = new Hexahedral3D(fit_p[2],
					//		fit_p[3], fit_p[0], fit_p[0],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node3);
					//	Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[1],
					//		fit_p[2], fit_p[1], fit_p[1],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node4);
					//	Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[2],
					//		this->sur_faces[i]->p[1], fit_p[2], fit_p[2],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node5);
					//	Hexahedral3D* node6 = new Hexahedral3D(this->sur_faces[i]->p[0],
					//		this->sur_faces[i]->p[1], this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node6);
					//	Hexahedral3D* node7 = new Hexahedral3D(this->sur_faces[i]->p[1],
					//		this->sur_faces[i]->p[0], fit_p[0], fit_p[1],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node7);
					//	Hexahedral3D* node8 = new Hexahedral3D(this->sur_faces[i]->p[2],
					//		this->sur_faces[i]->p[3], fit_p[3], fit_p[2],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node8);
					//}
					//else if (vecHash[*this->sur_faces[i]->p[1]].i != 0 && vecHash[*this->sur_faces[i]->p[1]].j != 0)
					//{
					//	fit_p[0] = fit_p[1];
					//	fitNodeHash[*this->sur_faces[i]->p[0]] = *fit_p[1];
					//	Hexahedral3D* node1 = new Hexahedral3D(this->sur_faces[i]->p[0],
					//		this->sur_faces[i]->p[3], fit_p[3], fit_p[0],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node1);
					//	Hexahedral3D* node2 = new Hexahedral3D(fit_p[2],
					//		fit_p[3], fit_p[0], fit_p[0],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node2);
					//	Hexahedral3D* node3 = new Hexahedral3D(fit_p[2],
					//		fit_p[3], fit_p[0], fit_p[0],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node3);
					//	Hexahedral3D* node4 = new Hexahedral3D(this->sur_faces[i]->p[1],
					//		fit_p[2], fit_p[1], fit_p[1],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node4);
					//	Hexahedral3D* node5 = new Hexahedral3D(this->sur_faces[i]->p[2],
					//		this->sur_faces[i]->p[1], fit_p[2], fit_p[2],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node5);
					//	Hexahedral3D* node6 = new Hexahedral3D(this->sur_faces[i]->p[0],
					//		this->sur_faces[i]->p[1], this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node6);
					//	Hexahedral3D* node7 = new Hexahedral3D(this->sur_faces[i]->p[1],
					//		this->sur_faces[i]->p[0], fit_p[0], fit_p[1],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node7);
					//	Hexahedral3D* node8 = new Hexahedral3D(this->sur_faces[i]->p[2],
					//		this->sur_faces[i]->p[3], fit_p[3], fit_p[2],
					//		fit_p_d_new, fit_p_d_new, fit_p_d_new, fit_p_d_new, 1);
					//	this->sur_nodes.push_back(node8);
					//}

					//}
					//}
#endif					
Hexahedral3D* node = new Hexahedral3D(this->sur_faces[i]->p[0],
			this->sur_faces[i]->p[1], this->sur_faces[i]->p[2], this->sur_faces[i]->p[3],
			fit_p[0], fit_p[1], fit_p[2], fit_p[3], 1);

					//�ж���ϵ�����Ƿ�ϸ�
					if (fit_p[0]->z == fit_p[1]->z)
					{
						//���ڵ�洢 0-1,2-3
						broPoint[*fit_p[0]].push_back(fit_p[1]);
						broPoint[*fit_p[1]].push_back(fit_p[0]);
	
						broPoint[*fit_p[2]].push_back(fit_p[3]);
						broPoint[*fit_p[3]].push_back(fit_p[2]);
						
						//�Ż��ر�1
	#if 0
						double dis = distance(fit_p[0], fit_p[1]);
						if (dis < (this->vox.minlenth/2 * this->vox.minlenth / 2))//���������Ԫ��ֵ ��СΪ��Ԫ�ߴ�/2��ƽ��
						{
							//poor_nodes.push_back(node);//���Ż���ϵ㹲��Ԫ
	
							//���Ż��㼯��
							if (vecHash[*fit_p[0]].i == 0 || vecHash[*fit_p[0]].j == 0)//����0���ж϶�Ӧ����ϵ�0�Ƿ�Ϊ���Ż���
							{
								if (poor_point_hash.find(*node->p[4]) == poor_point_hash.end())
								{
									poor_point_hash.insert(*node->p[4]);//���Ż�������
									poor_point.push_back(node->p[4]);//���Ż������
	
									poor_point_hash.insert(*node->p[7]);
									poor_point.push_back(node->p[7]);
								}
								else if (poor_point_hash.find(*node->p[7]) == poor_point_hash.end())
								{
									poor_point_hash.insert(*node->p[7]);
									poor_point.push_back(node->p[7]);
								}
							}
							else
							{
								if (poor_point_hash.find(*node->p[5]) == poor_point_hash.end())
								{
									poor_point_hash.insert(*node->p[5]);//���Ż�������
									poor_point.push_back(node->p[5]);//���Ż������
	
									poor_point_hash.insert(*node->p[6]);
									poor_point.push_back(node->p[6]);
								}
								else if (poor_point_hash.find(*node->p[6]) == poor_point_hash.end())
								{
									poor_point_hash.insert(*node->p[6]);
									poor_point.push_back(node->p[6]);
								}
					}
				}
	
	#endif
			}
					else if (fit_p[0]->z == fit_p[3]->z)
					{
						//���ڵ�洢 0-3,1-2
						broPoint[*fit_p[0]].push_back(fit_p[3]);
						broPoint[*fit_p[3]].push_back(fit_p[0]);
	
						broPoint[*fit_p[1]].push_back(fit_p[2]);
						broPoint[*fit_p[2]].push_back(fit_p[1]);
						//�Ż��ر�2
	#if 0
						double dis = distance(fit_p[0], fit_p[3]);
						if (dis < (this->vox.minlenth / 2 * this->vox.minlenth / 2))//���������Ԫ��ֵ ��СΪ��Ԫ�ߴ�/2��ƽ��
						{
							//poor_nodes.push_back(node);
	
							//���Ż��㼯��
							if (vecHash[*fit_p[0]].i == 0 || vecHash[*fit_p[0]].j == 0)//����0���ж϶�Ӧ����ϵ�0�Ƿ�Ϊ���Ż���
							{
								if (poor_point_hash.find(*node->p[4]) == poor_point_hash.end())
								{
									poor_point_hash.insert(*node->p[4]);//���Ż�������
									poor_point.push_back(node->p[4]);//���Ż������
	
									poor_point_hash.insert(*node->p[5]);//���Ż�������
									poor_point.push_back(node->p[5]);//���Ż������
								}
								else if (poor_point_hash.find(*node->p[5]) == poor_point_hash.end())
								{
									poor_point_hash.insert(*node->p[5]);
									poor_point.push_back(node->p[5]);
								}
							}
							else
							{
								if (poor_point_hash.find(*node->p[7]) == poor_point_hash.end())
								{
									poor_point_hash.insert(*node->p[7]);//���Ż�������
									poor_point.push_back(node->p[7]);//���Ż������
	
									poor_point_hash.insert(*node->p[6]);//���Ż�������
									poor_point.push_back(node->p[6]);//���Ż������
								}
								else if (poor_point_hash.find(*node->p[6]) == poor_point_hash.end())
								{
									poor_point_hash.insert(*node->p[6]);
									poor_point.push_back(node->p[6]);
					}
		}
	}
	#endif
				}
	
					for (int index = 4; index < 8; index++)
					{
						//������ϵ������Ӧ�ĵ�ָ��
						optPoint[*node->p[index]].push_back(node->p[index]);
					}
	#if 1
					int cnt = 0;
					if (this->sur_faces[i]->p[0] == fit_p[0]) cnt++;
					if (this->sur_faces[i]->p[1] == fit_p[1]) cnt++;
					if (this->sur_faces[i]->p[2] == fit_p[2]) cnt++;
					if (this->sur_faces[i]->p[3] == fit_p[3]) cnt++;
					if (fit_p[0] == fit_p[1]) cnt++;
					if (fit_p[0] == fit_p[2]) cnt++;
					if (fit_p[0] == fit_p[3]) cnt++;
					if (fit_p[2] == fit_p[1]) cnt++;
					if (fit_p[3] == fit_p[1]) cnt++;
					if (fit_p[3] == fit_p[2]) cnt++;
	
					if (cnt > 1)
						continue;
	#endif
					this->sur_nodes.push_back(node);
					//2022.4.21
					//�����-��Ԫӳ���ϣ���ֵ��������ϵ�Ԫ
					for (int k = 0; k < 8; ++k)
					{
						pointHash[*node->p[k]].push_back(node);
					}
			
			}
			
			
	
		}
#endif
		cout << "sum:" << sum << endl;
		//�Ż�2
		//optimize2();
		//optimize3();
		cout << "����굥��CTͼƬʣ��ǵ������� " << GoodFeatures[0].size() << endl;
		cout << "��ϵ��ϣ���С��" << fitNodeHash.size() << endl;
		clock_t end = clock();
		cout << "�������ʱ�䣺" << end - begin << endl;

	}
	
//����������ά��ľ���
double get_Surface::Distance_Two2Dpoint(Point2d p1, Point2d p2) {
	double dis = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	return dis;
}

//��ȡһ��ͼƬ�ϵĽǵ�����
//���������vector<Point3D*>  ����void 
void get_Surface::Get_TotomasiFeatures(int index, int MaxCornerNumber = 100) {//���ó�ʼ�ǵ�s5
	//������ز���
	vector<Point>* corners = new vector<Point>;//����һ��vector�����洢�Ķ�ά��
	double qualityLevel = 0.01;//�ǵ���ɽ��ܵ���С����ֵ
	double minDistance = 8;//�ǵ�֮�����С����,��������άmain�е�minlenth
	int blockSize = 3;//���㵼������ؾ���ʱָ��������Χ
	double k = 0.04;//Ȩ��ϵ��

	//����Shi-Tomasi�ǵ���
	goodFeaturesToTrack(this->vox.AllImage_m[index], *corners, MaxCornerNumber, qualityLevel, minDistance, Mat(), blockSize, false, k);

	//��corner����Ž���ϣ��GoodFeatures��
	for (int i = 0; i < (*corners).size(); i++) {
		GoodFeatures[index].push_back((*corners)[i]);
	}
	delete corners;
}


Point get_Surface::Get_NearestPT(vector<Point>GoodFeatures, Point it, double distance) {
	vector<Point>& pts = GoodFeatures;
	map<int, vector<Point>> pts_x, pts_y;
	for (auto pt : pts)
	{
		pts_x[pt.x].push_back(pt);
		pts_y[pt.y].push_back(pt);
	}
	bool rectFlag = false;
	bool findFlag = false;
	Point nearestPt;
	int max_d = INT_MAX;
	double min_dist = DBL_MAX;

	int x = it.x;
	int y = it.y;

	int min_d = static_cast<int>(abs(0.707 * distance));

	for (int d = min_d; d < max_d; d++)
	{
		//���ε��������ұ߽磬�ֱ��ж��������߽�����
		int minx = x - d, maxx = x + d, miny = y - d, maxy = y + d;

		for (auto pt : pts_x[minx])
		{
			if (pt.y >= miny && pt.y <= maxy)
			{
				double temp_d = sqrt(pow(pt.x - x, 2) + pow(pt.y - y, 2));
				if (abs(temp_d - abs(distance)) < 0.01)
				{
					//���ҵ��ĵ����P�ľ�����distance����һ��ʱֱ�ӽ�������
					nearestPt = pt;
					findFlag = true;
					break;
				}
				if (!rectFlag)
				{
					//�����ο��״θ��ǵ������ϵĵ�ʱ��ȷ��max_d
					rectFlag = true;
					max_d = sqrt(pow(pt.x - x, 2) + pow(pt.y - y, 2)) + 0.5;
				}
				if (temp_d < min_dist)
				{
					min_dist = temp_d;
					nearestPt = pt;
				}
			}
		}
		if (findFlag) break;

		for (auto pt : pts_y[miny])
		{
			if (pt.x >= minx && pt.x <= maxx)
			{
				double temp_d = sqrt(pow(pt.x - x, 2) + pow(pt.y - y, 2));
				if (abs(temp_d - abs(distance)) < 0.01)
				{
					nearestPt = pt;
					findFlag = true;
					break;
				}
				if (!rectFlag)
				{
					rectFlag = true;
					max_d = sqrt(pow(pt.x - x, 2) + pow(pt.y - y, 2)) + 0.5;
				}
				if (temp_d < min_dist)
				{
					min_dist = temp_d;
					nearestPt = pt;
				}
			}
		}
		if (findFlag) break;

		for (auto pt : pts_x[maxx])
		{
			if (pt.y >= miny && pt.y <= maxy)
			{
				double temp_d = sqrt(pow(pt.x - x, 2) + pow(pt.y - y, 2));
				if (abs(temp_d - abs(distance)) < 0.01)
				{
					nearestPt = pt;
					findFlag = true;
					break;
				}
				if (!rectFlag)
				{
					rectFlag = true;
					max_d = sqrt(pow(pt.x - x, 2) + pow(pt.y - y, 2)) + 0.5;
				}
				if (temp_d < min_dist)
				{
					min_dist = temp_d;
					nearestPt = pt;
				}
			}
		}
		if (findFlag) break;

		for (auto pt : pts_y[maxy])
		{
			if (pt.x >= minx && pt.x <= maxx)
			{
				double temp_d = sqrt(pow(pt.x - x, 2) + pow(pt.y - y, 2));
				if (abs(temp_d - abs(distance)) < 0.01)
				{
					nearestPt = pt;
					findFlag = true;
					break;
				}
				if (!rectFlag)
				{
					rectFlag = true;
					max_d = sqrt(pow(pt.x - x, 2) + pow(pt.y - y, 2)) + 0.5;
				}
				if (temp_d < min_dist)
				{
					min_dist = temp_d;
					nearestPt = pt;
				}
			}
		}
		if (findFlag) break;
	}

	return nearestPt;
}




double get_Surface::Dis_goodfeatures(vector<Point>& GoodFeatures, Point it) {
	double res =DBL_MAX;
	double dis2 = DBL_MAX;
	for (int i = 0; i < GoodFeatures.size(); i++) {
		dis2 = (GoodFeatures[i].x - it.x) * (GoodFeatures[i].x - it.x) + (GoodFeatures[i].y - it.y) * (GoodFeatures[i].y - it.y);
		if (res >= dis2) {
			res = dis2;
		}
	}
	return sqrt(res);
}

void get_Surface::delete_goodfeatures(vector<Point>& GoodFeatures, Point it) {
	int j = 0;
	for (int i = 0; i < GoodFeatures.size(); i++) {
		if (GoodFeatures[i].x == it.x&& GoodFeatures[i].y == it.y) {
			GoodFeatures[i].x = 0;
			GoodFeatures[i].y = 0;
			j = i;
		}
	}
	for (int k = j+1; k <  GoodFeatures.size(); k++) {
		GoodFeatures[j].x = GoodFeatures[k].x;
		GoodFeatures[j].y = GoodFeatures[k].y;
		j++;
	}
	GoodFeatures[GoodFeatures.size() - 1].x = 0;
	GoodFeatures[GoodFeatures.size() - 1].y = 0;
	GoodFeatures.resize(GoodFeatures.size() - 1);
	cout << "�ǵ�ƥ������ɣ�ɾ���ǵ��ֹ�ظ����" << endl;
}

//����һ�������㹲��Ƭ������
int get_Surface::num_face(Point3D* point) {
	int num_f = 0;//����˵�������
	int n = this->sur_faces.size();
	for (int i = 0; i < n; ++i)
	{
		if (this->check(this->sur_faces[i], point))
		{
			num_f++;
		}
	}

	return num_f;
}


get_Surface::~get_Surface()
{

}