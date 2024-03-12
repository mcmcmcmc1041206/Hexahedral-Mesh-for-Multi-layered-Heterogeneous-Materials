#pragma once
#include "Voxel.h"
#include "OcTree.h"
#include <QtWidgets/QMainWindow>
#include "ui_123.h"
#include <QDateTime>
#include "HexActor.h"
#pragma execution_character_set("utf-8")

class QtWidgetsApplication2 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication2(QWidget *parent = nullptr);
    void CreatTxt(string& pathName, const vector<Hexahedral3D*>& m_node1, const vector<Hexahedral3D*>& m_node2, const vector<Hexahedral3D*>& m_node3);
    ~QtWidgetsApplication2();
    vector<Mat> All_images;
    //�ۺ���
    void PushedButton();

    void input_picture();

    void input_material();

    void set_parameter();
    //vtkSmartPointer<vtkActor> set_material_color(vtkSmartPointer<vtkActor>& hexactor, string material);
    //Ui::MainWindow ui;
public:
    vector<vector<string>> material_container;
    unsigned int max_lenth;//�������ֵ
    unsigned int min_lenth;//������Сֵ
    unsigned int interval;//ͼƬ���
    string textpath;//text·��
    bool istextpath;
private:
    HexDisplay hexactor;
    QStringList strPathList;//��ȡͼƬ·��
    QTime datetime;//ʱ��
    //unordered_map<string, vector<double>> umap;//�������治ͬ���϶�Ӧ��RGB��ɫ����

};
