/*----------------------------
��ȡÿһ�����������ʾactor
------------------------------
*/
#pragma once
#include"tree_class.h"
#include<unordered_map>
#include<vector>

class HexDisplay
{
public:
	HexDisplay();
	~HexDisplay();

	//�ڵ���ʾ
	vtkSmartPointer<vtkActor> HexActor(Hexahedral3D* n,string material);
	//�߿�
	vtkSmartPointer<vtkActor> edgeActor(Hexahedral3D* n);
	//vtkSmartPointer<vtkActor> set_material_color(vtkSmartPointer<vtkActor>& hexactor,string material);
	//����������
	void createAxes(vtkSmartPointer<vtkRenderer> renderer);
	map<string, vector<double>> umap;//�������治ͬ���϶�Ӧ��RGB��ɫ����
};

