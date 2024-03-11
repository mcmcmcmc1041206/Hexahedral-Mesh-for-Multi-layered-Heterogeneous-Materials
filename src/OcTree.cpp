#include"OcTree.h"



/*-------- CLASS OcTree ---------*/
OcTree::OcTree(My_Voxel& _vox, unsigned int max_lenth, unsigned int min_lenth) : vox(_vox)
{
	this->max_lenth = max_lenth;
	this->min_lenth = min_lenth;
	unsigned int size = this->get_max_hex(); 
	cout << "��ʼ�������С��" << size << endl;
	this->axis = vector<vector<vector<bool>>>(size, vector<vector<bool>>(size, vector<bool>(size, false)));
	this->root = new OcTreeNode(0, 0, 0, false, size, "");
}

void OcTree::build_adaptive_tree()
{
	this->build_tree();//�ֻ��֣�ʵ�ְ˲���
	//vector<OcTreeNode*>* last = new vector<OcTreeNode*>;
	//last->push_back(root);//last�����з��뵱ǰ�ڵ�
	//layer_traversal(last);//���ֳ�ƽ��˲���
	get_leaf_node(root);

	m_subdivision(this->nodes, this->vox);

	//delete last;
}

//��ʼ����
void OcTree::build_tree()
{
	if (this->root == nullptr) return ;
	queue<OcTreeNode*> record;//��¼��ǰ�ڵ�ָ������
	record.push(this->root);
	OcTreeNode* temp = nullptr;
	unsigned int hafLen = 0;
	while (!record.empty())//���������Ϊ�գ���ǰ�ڵ����
	{
		temp = record.front();//ȡ��¼�ĵ�һ���ڵ�
		record.pop();

		if (temp->isfull && temp->lenth <= this->max_lenth) continue;//������
		hafLen = (temp->lenth) / 2;

		temp->node[0] = creat_node(temp->x, temp->y, temp->z, hafLen, temp->ID + '0');//�����µĵ�
		if (temp->node[0] != nullptr) record.push(temp->node[0]);//�µĵ��������

		temp->node[1] = creat_node(hafLen + temp->x, temp->y, temp->z, hafLen, temp->ID + '1');
		if (temp->node[1] != nullptr) record.push(temp->node[1]);

		temp->node[2] = creat_node(temp->x, temp->y, hafLen + temp->z, hafLen, temp->ID + '2');
		if (temp->node[2] != nullptr) record.push(temp->node[2]);

		temp->node[3] = creat_node(hafLen + temp->x, temp->y, hafLen + temp->z, hafLen, temp->ID + '3');
		if (temp->node[3] != nullptr) record.push(temp->node[3]);

		temp->node[4] = creat_node(temp->x, hafLen + temp->y, temp->z, hafLen, temp->ID + '4');
		if (temp->node[4] != nullptr) record.push(temp->node[4]);

		temp->node[5] = creat_node(hafLen + temp->x, hafLen + temp->y, temp->z, hafLen, temp->ID + '5');
		if (temp->node[5] != nullptr) record.push(temp->node[5]);

		temp->node[6] = creat_node(temp->x, hafLen + temp->y, hafLen + temp->z, hafLen, temp->ID + '6');
		if (temp->node[6] != nullptr) record.push(temp->node[6]);

		temp->node[7] = creat_node(hafLen + temp->x, hafLen + temp->y, hafLen + temp->z, hafLen, temp->ID + '7');
		if (temp->node[7] != nullptr) record.push(temp->node[7]);
	}
}

//�����˲����ڵ�ָ��
OcTreeNode* OcTree::creat_node(unsigned x, unsigned y, unsigned z, unsigned lenth, string location)
{

	/*cout << location << "�Žڵ�" << "   " << "���꣺(" << x << ", " << y << ", " << z << ")" << "   " << "����:" << lenth << endl;*/
	if (lenth < min_lenth) return nullptr;
	if (y >= static_cast<unsigned>(vox.rows)
		|| x >= static_cast<unsigned>(vox.cols)
		|| z >= static_cast<unsigned>((vox.AllImage_m.size() - 1) * vox.getInterval())) return nullptr;
	
	
	//�����������ڵ�Ԫ�ڵı�Ե���
	unsigned dim_x = 0, dim_y = 0, dim_z = 0;//��ǰ�ڵ������������ϵı߽�
	
	bool sata = false;
	if (x + lenth >= static_cast<unsigned>(vox.cols))
		dim_x = vox.cols;
	else dim_x = x + lenth + 1;//��ȡ���У������� > y+lenth ��Ϊ�˱������˽ڵ������еĵ�

	if (y + lenth >= static_cast<unsigned>(vox.rows))
		dim_y = vox.rows;
	else dim_y = y + lenth + 1;

	if (z + lenth >= static_cast<unsigned>((vox.AllImage_m.size() - 1) * vox.getInterval()))
		dim_z = vox.AllImage_m.size();// * vox.getInterval();
	else dim_z = ((z + lenth) / vox.getInterval()) + 1;//z + lenth + 1;


	//ȷ��CTͼ����
	unsigned int first_layer = 0;
	if (z % vox.getInterval() == 0)
		first_layer = z / vox.getInterval();
	else
		first_layer = (z / vox.getInterval()) + 1;


	//ȷ����Χ�ڴ��ڵ����ص�����
	unsigned int nums = 0;
	for (unsigned i = first_layer; i < dim_z; ++i)
	{
		for (unsigned j = y; j < dim_y; ++j)
		{
			for (unsigned k = x; k < dim_x; ++k)
			{
				/*if (j >= 757 || k >= 747)
					int a = 1;*/
				//2022.2.19��
				if (vox.AllImage_m[i].at<uchar>(j, k)!=0)//��ȡ��i��j�������أ���Ϊ0������һ
				{
					++nums;
				}
				else if (nums > 0)//�����ֻҶ�ֵ��Ϊ0�����ص㣬�����ڵ��Ǻڽڵ��ҽڵ�
				{
					i = dim_z;//����ѭ��
					j = dim_y;
					k = dim_x;
				}
			}
		}
	}

	if (nums == 0) return nullptr;	//��û�в�����0�����ص㣬�����ýڵ�Ϊ�׽ڵ�
	else
	{
		//axis������xyz���ܳ������ߴ磬������dim_x - 1����������x + lenth
		axis[x][y][z] = axis[x][dim_y - 1][z] = axis[dim_x - 1][y][z] = axis[x][y][dim_z - 1] =
			axis[dim_x - 1][dim_y - 1][z] = axis[dim_x - 1][y][dim_z - 1] = axis[x][dim_y - 1][dim_z - 1] =
			axis[dim_x - 1][dim_y - 1][dim_z - 1] = true;

		if (nums == pow(lenth + 1, 2) * (lenth + 1)) //����num =��lenth+1��ƽ�����ж�����ڵ�Ϊ���ڵ�
		{
			//ֻ�����˶��ˣ�����Ҫ˼���׶˵�Ҫ��Ҫɾ��
			/*if(z + lenth <= vox.AllImage_m.size() - 1)
				sata = true;
			else
				sata = false;*/
			sata = true;
		}
		else
		{
			sata = false;
		}
		return new OcTreeNode(x, y, z, sata, lenth, location);
	}
}

void OcTree::layer_traversal(vector<OcTreeNode*>* last)
{
	if (last->empty())return;
	if ((*(last->begin()))->lenth < this->min_lenth)return;
	vector<OcTreeNode*>* next = new vector<OcTreeNode*>;
	//��������
	for (vector<OcTreeNode*>::iterator it = last->begin(); it != last->end(); it++)
	{
		for (short i = 0; i < 8; i++)
		{
			if ((*it)->node[i] != nullptr)//����ڵ�ָ�벻Ϊ��ָ��
				next->push_back((*it)->node[i]);//���ӽڵ�ָ�����next����
		}
	}
	layer_traversal(next);//�ݹ�
	for (vector<OcTreeNode*>::iterator it = next->begin(); it != next->end(); it++)//����next����
		//�жϽڵ�
		adapted_hexahedral((*it));
	delete next;
}
//
void OcTree::adapted_hexahedral(OcTreeNode* root)
{
	if (root == nullptr) return;
	//stackջ
	stack<OcTreeNode*>record;
	OcTreeNode* temp = nullptr;
	record.push(root);
	while (!record.empty())
	{
		temp = record.top();
		record.pop();
		if (temp->lenth < min_lenth) continue;
		for (short i = 7; i >= 0; i--)
		{
			if (temp->node[i] != nullptr && temp->node[i]->isfull)
			{
				//����г��������ҽڵ�
				if (check_edge(temp->node[i]))
					//�ڵ���
					build_full_node(temp->node[i]);
			}
			if (temp->node[i] != nullptr)
				record.push(temp->node[i]);
		}
	}

}

bool OcTree::check_edge(OcTreeNode* root)
{
	if (root->lenth < 2) return false;
	if (root->lenth > max_lenth) return true;
	unsigned int x = root->x, y = root->y, z = root->z, lenth = root->lenth;
	//if (
	//	//��Ա������ҽڵ��ж�
	//	((axis[x][y + lenth * 0.5]) && (axis[x + lenth][y + lenth * 0.5])) ||
	//	((axis[x + lenth * 0.5][y]) && (axis[x + lenth * 0.5][y + lenth]))
	//	)
	//	return true;//����Եı�ͬʱ�����ҽڵ㣬��Ҫ����

	if (lenth < (4 * min_lenth)) return false;
	if (axis[x][y + lenth * 0.25][z] || axis[x][y + lenth * 0.75][z] || 
		axis[x][y + lenth * 0.25][z + lenth] || axis[x][y + lenth * 0.25][z + lenth] ||
		axis[x][y][z + lenth * 0.25] || axis[x][y][z + lenth * 0.75] ||
		axis[x][y + lenth][z + lenth * 0.25] || axis[x][y + lenth][z + lenth * 0.75] ||
		axis[x + lenth * 0.25][y][z] || axis[x + lenth * 0.25][y + lenth][z] || 
		axis[x + lenth * 0.25][y][z + lenth] || axis[x + lenth * 0.25][y + lenth][z + lenth] ||
		axis[x + lenth * 0.75][y][z] || axis[x + lenth * 0.75][y + lenth][z] ||
		axis[x + lenth * 0.75][y][z + lenth] || axis[x + lenth * 0.75][y + lenth][z + lenth] ||
		axis[x + lenth][y + lenth * 0.25][z] || axis[x + lenth][y + lenth * 0.75][z] ||
		axis[x + lenth][y + lenth * 0.25][z + lenth] || axis[x + lenth][y + lenth * 0.25][z + lenth] ||
		axis[x + lenth][y][z + lenth * 0.25] || axis[x + lenth][y][z + lenth * 0.75] ||
		axis[x + lenth][y + lenth][z + lenth * 0.25] || axis[x + lenth][y + lenth][z + lenth * 0.75])
		return true;
	else
		return false;
}

OcTreeNode* OcTree::creat_full_node(unsigned x, unsigned y, unsigned z, unsigned lenth, string location)
{
	if (lenth < min_lenth) return nullptr;
	unsigned dim_x = x + lenth, dim_y = y + lenth, dim_z = z + lenth;
	axis[x][y][z] = axis[dim_x][y][z] = axis[x][dim_y][z] = axis[x][y][dim_z]
		= axis[dim_x][dim_y][z] = axis[dim_x][y][dim_z] = axis[x][dim_y][dim_z]
		= axis[dim_x][dim_y][dim_z] = true;

	return new OcTreeNode(x, y, z, true, lenth, location);//����һ����ȫ���ڵ�
}

//�������ҽڵ㣬��������
void OcTree::build_full_node(OcTreeNode* root)
{
	if (root == nullptr) return;
	unsigned int hafLen = (root->lenth) / 2;
	//root->done = true;
	root->node[0] = creat_full_node(root->x, root->y, root->z, hafLen, root->ID + '0');
	root->node[1] = creat_full_node(hafLen + root->x, root->y, root->z, hafLen, root->ID + '1');
	root->node[2] = creat_full_node(root->x, root->y, hafLen + root->z, hafLen, root->ID + '2');
	root->node[3] = creat_full_node(hafLen + root->x, root->y, hafLen + root->z, hafLen, root->ID + '3');
	root->node[4] = creat_full_node(root->x, hafLen + root->y, root->z, hafLen, root->ID + '4');
	root->node[5] = creat_full_node(hafLen + root->x, hafLen + root->y, root->z, hafLen, root->ID + '5');
	root->node[6] = creat_full_node(root->x, hafLen + root->y, hafLen + root->z, hafLen, root->ID + '6');
	root->node[7] = creat_full_node(hafLen + root->x, hafLen + root->y, hafLen + root->z, hafLen, root->ID + '7');
}

void OcTree::get_leaf_node(OcTreeNode* root) //�ݹ飬���ƶ��������������
{
	if (root == nullptr) return;
	if (root->node[0] == nullptr && root->node[1] == nullptr && root->node[2] == nullptr && root->node[3] == nullptr &&
		root->node[4] == nullptr && root->node[5] == nullptr && root->node[6] == nullptr && root->node[7] == nullptr && root->isfull )
	{
		Point3D* p0 = new Point3D(root->x, root->y, root->z);
		Point3D* p1 = new Point3D(root->x + root->lenth, root->y, root->z);
		Point3D* p2 = new Point3D(root->x + root->lenth, root->y + root->lenth, root->z);
		Point3D* p3 = new Point3D(root->x, root->y + root->lenth, root->z);
		Point3D* p4 = new Point3D(root->x, root->y, root->z + root->lenth);
		Point3D* p5 = new Point3D(root->x + root->lenth, root->y, root->z + root->lenth);
		Point3D* p6 = new Point3D(root->x + root->lenth, root->y + root->lenth, root->z + root->lenth);
		Point3D* p7 = new Point3D(root->x, root->y + root->lenth, root->z + root->lenth);
		unsigned int index = 1;
		this->nodes.push_back(new Hexahedral3D(p0, p1, p2, p3, p4, p5, p6, p7, index));
	}
	else
	{
		//if����������ʾ����
		//if (root->x < 512 && root->y < 512) {
			get_leaf_node(root->node[0]);
			get_leaf_node(root->node[1]);
			get_leaf_node(root->node[2]);
			get_leaf_node(root->node[3]);
			get_leaf_node(root->node[4]);
			get_leaf_node(root->node[5]);
			get_leaf_node(root->node[6]);
			get_leaf_node(root->node[7]);
		//}
	}
}

unsigned int OcTree::get_max_hex()
{
	//�ú�����Ϊ����ø��ڵ�ĳߴ�Ϊ2��n�η���ֵ����֤�������񻮷ֹ����У������ַ����������ش�С��Ԫ
	//���ݹ�ʽn=[log2max(cols,rows,num)] s=pow(2,n)
	//��ȡ��ֵ��ͼ��������
	unsigned int max_hex = vox.getMaxLenthAll(); //�����������г�������ֵ
	unsigned int dim_z = vox.AllImage_m.size() * vox.getInterval(); //z����������λ��=ͼƬ���*ͼƬ����
	max_hex = max_hex > dim_z ? max_hex : dim_z;
	double num = log(max_hex) / log(2) - log(min_lenth) / log(2);
	num = ceil(num);//ceil(num)���ز�С��num����С����ֵ��Ȼ��ת��Ϊdouble�ͣ�
	max_hex = pow(2, num) * min_lenth;//2��num�η� * min_lenth
	return max_hex;
}

void OcTree::m_subdivision(vector<Hexahedral3D*>& nodes, My_Voxel vox)
{
	vector<Hexahedral3D*> temp;
	int nums = nodes.size();
	for (int i = 0; i < nums; ++i)
	{
		unsigned dim_x = 0, dim_y = 0, dim_z = 0;//��ǰ�ڵ������������ϵı߽�
		dim_x = nodes[i]->p[1]->x;
		dim_y = nodes[i]->p[2]->y;
		dim_z = nodes[i]->p[4]->z;


		//�ڵ����ر�����ʼ����
		int s_x = nodes[i]->p[0]->x;
		int s_y = nodes[i]->p[0]->y;
		int s_z = nodes[i]->p[0]->z;

		//ȷ����ʼͼ��
		unsigned int first_layer = 0;

		if (s_z % vox.getInterval() == 0)
			first_layer = s_z / vox.getInterval();
		else
			first_layer = (s_z / vox.getInterval()) + 1;


		int d_z = first_layer;//���������z����
		//�����еĽڵ㶼�����ڵ㣬����Ҫ��������Ϊ0�����
		uchar index = vox.AllImage_m[first_layer].at<uchar>(s_y, s_x); 

		/*cout << "��ʼ��������" << i << "�����أ�" << endl;*/

		for (int j = first_layer; j < dim_z+1; ++j)
		{
			/*cout <<"����ֵ�ǣ�"<< (int)index << endl;
			cout << "���������z����Ϊ��" << d_z << endl;
			cout << "z��ı߽磺" << dim_z << endl;
			cout << "��ǰz���꣺" << j << endl;*/

			if (vox.AllImage_m[j].at<uchar>(s_y, s_x) != index)
			{
				//�ٻ����Ժ����������
				Point3D* p10 = new Point3D(s_x, s_y, d_z);
				Point3D* p11 = new Point3D(dim_x, s_y, d_z);
				Point3D* p12 = new Point3D(dim_x, dim_y, d_z);
				Point3D* p13 = new Point3D(s_x, dim_y, d_z);
				Point3D* p14 = new Point3D(s_x, s_y, j);
				Point3D* p15 = new Point3D(dim_x, s_y, j);
				Point3D* p16 = new Point3D(dim_x, dim_y, j);
				Point3D* p17 = new Point3D(s_x, dim_y, j);
				unsigned int index1 = 1;
				Hexahedral3D* node1 = new Hexahedral3D(p10, p11, p12, p13, p14, p15, p16, p17, index1);
				temp.push_back(node1);

				//���ݽڵ�ĻҶ�ֵ�жϸ�����Ӧ�ø���ʲô��������
				this->Addnodes(index, node1);

				//�ٻ����Ժ����������
				Point3D* p20 = new Point3D(s_x, s_y, j);
				Point3D* p21 = new Point3D(dim_x, s_y, j);
				Point3D* p22 = new Point3D(dim_x, dim_y, j);
				Point3D* p23 = new Point3D(s_x, dim_y, j);
				Point3D* p24 = new Point3D(s_x, s_y, dim_z);
				Point3D* p25 = new Point3D(dim_x, s_y, dim_z);
				Point3D* p26 = new Point3D(dim_x, dim_y, dim_z);
				Point3D* p27 = new Point3D(s_x, dim_y, dim_z);
				unsigned int index2 = 1;

				delete nodes[i];
				nodes[i] = new Hexahedral3D(p20, p21, p22, p23, p24, p25, p26, p27, index2);
				d_z = j;
				index = vox.AllImage_m[j].at<uchar>(s_y, s_x);
			}
		}
		temp.push_back(nodes[i]);
		//���ݽڵ�ĻҶ�ֵ�жϸ�����Ӧ�ø���ʲô��������
		this->Addnodes(index, nodes[i]);
	}

	cout << temp.size() << endl;
	nodes.clear();


	for (int i = 0; i < temp.size(); ++i)
	{
		nodes.push_back(temp[i]);
	}

	cout << nodes.size() << endl;

}

void OcTree::Addnodes(int index, Hexahedral3D* m_node)
{
	if (index == 200) this->m_node1.push_back(m_node);

	else if (index == 255) this->m_node2.push_back(m_node);

	else if (index == 180) this->m_node3.push_back(m_node);

	else
	{
		cout << "�Ҷ�ֵ���󣡣�" << endl;

		return;
	}
}



OcTree::~OcTree()
{
	if (this->root == nullptr) return;
	queue<OcTreeNode*>record;
	record.push(this->root);
	OcTreeNode* temp = nullptr;
	while (!record.empty())
	{
		temp = record.front();
		record.pop();
		for (short i = 7; i >= 0; i--)
		{
			if (temp->node[i] != nullptr)
				record.push(temp->node[i]);
		}
		delete temp;
	}
}
