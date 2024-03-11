#pragma once
#include<iostream>
#include "Voxel.h"
#include <string>
#include "OcTree.h"
#include"tree_class.h"
#include "QtWidgetsApplication2.h"
#include <QFileDialog>
#include <QMessageBox>
#include<vtkSmartPointer.h>
#include <vtkLight.h>
#include<vtkConeSource.h>
#include<vtkPolyDataMapper.h>
#include<vtkActor.h>
#include<vtkRenderer.h>
#include<vtkRenderWindow.h>
#include<vtkRenderWindowInteractor.h>
#include <vtkCylinderSource.h>
#include<vtkInteractorStyleTrackballCamera.h>
#include <vtkTransform.h>
#include <vtkBalloonRepresentation.h>
#include <vtkBalloonWidget.h>
#include <vtkCamera.h>
#include "vtkInformation.h"
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCellPicker.h>
#include <vtkImagePlaneWidget.h>
#include <vtkMarchingCubes.h>
#include <vtkImageCast.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkImageMapToColors.h>
#include <vtkProperty.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkAutoInit.h>
#include<vtkShortArray.h>
#include<vtkFixedPointVolumeRayCastMapper.h>
#include<vtkPointdata.h>

Ui::MainWindow ui;
static vector<vtkSmartPointer<vtkActor>> m_actor1;
static vector<vtkSmartPointer<vtkActor>> m_actor2;
static vector<vtkSmartPointer<vtkActor>> m_actor3;


vector<vtkSmartPointer<vtkActor>> match_actor(double* color)
{
    vector<vector<vtkSmartPointer<vtkActor>>> actor_vec = { m_actor1,m_actor2,m_actor3 };
    for (int i = 0; i < actor_vec.size(); i++)
    {
        if (actor_vec[i][0]->GetProperty()->GetColor()[0] == color[0])
            return actor_vec[i];
    }
}
// Handle mouse events
class PropPickerInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
    static PropPickerInteractorStyle* New();
    vtkTypeMacro(PropPickerInteractorStyle, vtkInteractorStyleTrackballCamera);

    PropPickerInteractorStyle()
    {
        LastPickedActor = NULL;
        LastPickedProperty = vtkProperty::New();
        //LastPickedActorarray = vector<vtkActor*>(10000,LastPickedActor);
        //LastPickedPropertyarray = vector<vtkProperty*>(10000, LastPickedProperty);
    }
    virtual ~PropPickerInteractorStyle()
    {
        LastPickedProperty->Delete();
    }
    virtual void OnLeftButtonDown()
    {
        int* clickPos = this->GetInteractor()->GetEventPosition();//������������Ļ����

        // Pick from this location.
        vtkSmartPointer<vtkPropPicker>  picker =
            vtkSmartPointer<vtkPropPicker>::New();
        picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
        //ʵ��ʰȡ�ĺ���������Ĳ�������������˳�򣩣���굱ǰ������x��y��z(һ��Ϊ0)��vtkRenderer����
        double* pos = picker->GetPickPosition();//�����굱ǰ����λ�õ���������ϵ�µ�����ֵ
        // If we picked something before, reset its property
        //double* color1 = picker->GetActor()->GetProperty()->GetColor();
        if (this->LastPickedActor)
        {
            for (int i = 0; i < LastPickedActorarray.size(); i++)
            {
                this->LastPickedActorarray[i]->GetProperty()->SetColor(this->LastPickedProperty->GetColor());
                this->LastPickedActorarray[i]->GetProperty()->SetSpecular(this->LastPickedProperty->GetSpecular());
                this->LastPickedActorarray[i]->GetProperty()->SetSpecularPower(this->LastPickedProperty->GetSpecularPower());
            }
            //this->LastPickedActor->GetProperty()->DeepCopy(this->LastPickedProperty);
        }
        if ((this->LastPickedActor = picker->GetActor()) == nullptr)
            return;
        double* color = this->LastPickedActor->GetProperty()->GetColor();
        //ƥ��actor����
        vector<vtkSmartPointer<vtkActor>> temp = match_actor(color);
        if (this->LastPickedActor)
        {
            this->size = temp.size();
            LastPickedActorarray.resize(this->size);
            for (int i = 0; i < LastPickedActorarray.size(); i++)
            {
                LastPickedActorarray[i] = temp[i];
            }
            // Save the property of the picked actor so that we can restore it next time
            //for (; i < LastPickedPropertyarray.size(); i++)
            //{
            //    if (this->LastPickedPropertyarray[i] == nullptr)
            //            break;
            //    //this->LastPickedPropertyarray[i]->DeepCopy(this->LastPickedActor->GetProperty());
            //}
            //QString size = QString::fromStdString(to_string(i));
            this->LastPickedProperty->DeepCopy(this->LastPickedActor->GetProperty());
            //QString actor_size = QString::fromStdString(to_string(m_actor1.size())) + QString::fromStdString(to_string(m_actor2.size())) + QString::fromStdString(to_string(m_actor3.size()));
            string material_pick = material_find(color);
            //string colorstr = to_string(color[0]) + to_string(color[1]) + to_string(color[2]);
            QString materialstr = QString::fromStdString(material_pick);
            //ui.material->setText(materialstr);
            QTime datetime = QTime::currentTime();
            QString outputtext = datetime.toString() + QString::fromStdString(" ") + materialstr;
            ui.history_output->append(outputtext);
            /*for (auto& i : HexDisplay::umap)
            {
                if (i.second[0] == color[0] && i.second[1] == color[1] && i.second[2] == color[2])
                {
                    cout << "����Ϊ:" << i.first << endl;
                    break;
                }
            }*/
            // Highlight the picked actor by changing its properties
            for (auto& act : temp)
            {
                act->GetProperty()->SetColor(1, 0, 0);
                act->GetProperty()->SetDiffuse(1);
                act->GetProperty()->SetSpecular(0.0);
            }
            /*this->LastPickedActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
            this->LastPickedActor->GetProperty()->SetDiffuse(1.0);
            this->LastPickedActor->GetProperty()->SetSpecular(0.0);*/
            
        }
       // Forward events
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

    string material_find(double* color)
    {
        map<string, vector<double>> umap = material.umap;
        for (auto& i : umap)
        {
            if (i.second[0] == color[0] && i.second[1] == color[1] && i.second[2] == color[2])
            {
                return i.first;
            }
        }
    }
private:
    vtkActor* LastPickedActor;
    vector<vtkActor*> LastPickedActorarray;
    vtkProperty* LastPickedProperty;
    int size;
    //vector<vtkProperty*> LastPickedPropertyarray;
    HexDisplay material;
};
vtkStandardNewMacro(PropPickerInteractorStyle);

void QtWidgetsApplication2::CreatTxt(string& pathName, const vector<Hexahedral3D*>& m_node1, const vector<Hexahedral3D*>& m_node2, const vector<Hexahedral3D*>& m_node3)
{

    //char* path = "C:\\1.txt"; // ��Ҫ�����ļ���·��

    ofstream fout(pathName);
    if (fout)
    { // ��������ɹ�
        fout << "fini" << endl << "/clear" << endl << "/prep7" << endl << "SHPP,off,,nowarn" << endl << "et,1,solid185" << endl;//ǰ������
        //���ò���
        fout << "MP,EX,1,1.69e5" << endl << "MP,PRXY,1,0.275 " << endl
            << "MP,EX,2,1.69e5 " << endl << "MP,PRXY,2,0.28" << endl
            << "MP,EX,3,1.69e5" << endl << "MP,PRXY,3,0.30" << endl;
        /*for (int rows = 0; rows < ui.tableWidget->rowCount(); rows++)
        {
            string ex = (ui.tableWidget->item(rows, 1)->text()).toStdString();
            string prxy = (ui.tableWidget->item(rows, 2)->text()).toStdString();
            fout << "MP,EX," << rows+1 << "," << ex << endl;
            fout << "MP,PRXY," << rows+1 << "," << prxy << endl;
        }*/
        unsigned int j = 1;
        unsigned int k = 771528 + 1;

        //�����������
        fout << "MAT,1" << endl;
        //fout << m_node1.size();
        for (unsigned long i = 0; i < m_node1.size(); i++)
        {
            Hexahedral3D* tmp = m_node1[i];

            fout << "n" << "," << k++ << "," << tmp->p[0]->x << "e-3" << "," << tmp->p[0]->y << "e-3" << "," << tmp->p[0]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[1]->x << "e-3" << "," << tmp->p[1]->y << "e-3" << "," << tmp->p[1]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[2]->x << "e-3" << "," << tmp->p[2]->y << "e-3" << "," << tmp->p[2]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[3]->x << "e-3" << "," << tmp->p[3]->y << "e-3" << "," << tmp->p[3]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[4]->x << "e-3" << "," << tmp->p[4]->y << "e-3" << "," << tmp->p[4]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[5]->x << "e-3" << "," << tmp->p[5]->y << "e-3" << "," << tmp->p[5]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[6]->x << "e-3" << "," << tmp->p[6]->y << "e-3" << "," << tmp->p[6]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[7]->x << "e-3" << "," << tmp->p[7]->y << "e-3" << "," << tmp->p[7]->z << "e-3" << endl;
            fout << "e" << "," << k - 8 << "," << k - 7 << "," << k - 6 << "," << k - 5 << "," << k - 4 << "," << k - 3 << "," << k - 2 << "," << k - 1 << endl;

        }

        //�����������
        fout << "MAT,2" << endl;
        for (unsigned long i = 0; i < m_node2.size(); i++)
        {
            Hexahedral3D* tmp = m_node2[i];

            fout << "n" << "," << k++ << "," << tmp->p[0]->x << "e-3" << "," << tmp->p[0]->y << "e-3" << "," << tmp->p[0]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[1]->x << "e-3" << "," << tmp->p[1]->y << "e-3" << "," << tmp->p[1]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[2]->x << "e-3" << "," << tmp->p[2]->y << "e-3" << "," << tmp->p[2]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[3]->x << "e-3" << "," << tmp->p[3]->y << "e-3" << "," << tmp->p[3]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[4]->x << "e-3" << "," << tmp->p[4]->y << "e-3" << "," << tmp->p[4]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[5]->x << "e-3" << "," << tmp->p[5]->y << "e-3" << "," << tmp->p[5]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[6]->x << "e-3" << "," << tmp->p[6]->y << "e-3" << "," << tmp->p[6]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[7]->x << "e-3" << "," << tmp->p[7]->y << "e-3" << "," << tmp->p[7]->z << "e-3" << endl;
            fout << "e" << "," << k - 8 << "," << k - 7 << "," << k - 6 << "," << k - 5 << "," << k - 4 << "," << k - 3 << "," << k - 2 << "," << k - 1 << endl;

        }

        fout << "MAT,3" << endl;
        for (unsigned long i = 0; i < m_node3.size(); i++)
        {
            Hexahedral3D* tmp = m_node3[i];

            fout << "n" << "," << k++ << "," << tmp->p[0]->x << "e-3" << "," << tmp->p[0]->y << "e-3" << "," << tmp->p[0]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[1]->x << "e-3" << "," << tmp->p[1]->y << "e-3" << "," << tmp->p[1]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[2]->x << "e-3" << "," << tmp->p[2]->y << "e-3" << "," << tmp->p[2]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[3]->x << "e-3" << "," << tmp->p[3]->y << "e-3" << "," << tmp->p[3]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[4]->x << "e-3" << "," << tmp->p[4]->y << "e-3" << "," << tmp->p[4]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[5]->x << "e-3" << "," << tmp->p[5]->y << "e-3" << "," << tmp->p[5]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[6]->x << "e-3" << "," << tmp->p[6]->y << "e-3" << "," << tmp->p[6]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[7]->x << "e-3" << "," << tmp->p[7]->y << "e-3" << "," << tmp->p[7]->z << "e-3" << endl;
            fout << "e" << "," << k - 8 << "," << k - 7 << "," << k - 6 << "," << k - 5 << "," << k - 4 << "," << k - 3 << "," << k - 2 << "," << k - 1 << endl;

        }


        fout << "nummrg,node" << endl << "NUMCMP,node" << endl;
        fout.close();  // ִ���������ر��ļ����
        /*QString time = datetime.toString("hh:mm:ss");
        time += "  successful output txt";
        ui.history_output->append(time);*/
    }
}

//QPixmap* m_crtPixmap; // ��ʾ����ĳ��ͼƬ
QtWidgetsApplication2::QtWidgetsApplication2(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle("������ʲ��ϵ���ѧ���ܲ���");
    ui.output_text->setChecked(1);
    ui.tableWidget->clear();

    ui.tableWidget->setColumnCount(3);//ֻ��������
    ui.tableWidget->setHorizontalHeaderLabels(QStringList() << "����" << "����ģ��" << "���ɱ�");
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//�п��Զ�����
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);//�����ֶ�����
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//����ѡ��
    ui.tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);//��ֹ�޸�
    ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//���Ե�ѡ

    //�����˵���
    QMenuBar* menuBar = new QMenuBar(this);

    //��Ӳ˵�������������
    this->setMenuBar(menuBar);
    //�����˵�
    QMenu* menu1 = new QMenu("�ļ�(J)", this);
    QMenu* menu2 = new QMenu("��ͼ(O)", this);
    QMenu* menu3 = new QMenu("���ӻ�����(K)", this);
    QMenu* menu4 = new QMenu("����(E)", this);
    QMenu* menu5 = new QMenu("����(R)", this);

    //�˵�����Ӳ˵�
    menuBar->addMenu(menu1);
    menuBar->addMenu(menu2);
    menuBar->addMenu(menu3);
    menuBar->addMenu(menu4);
    menuBar->addMenu(menu5);

    //�����˵���
    QAction* action1 = new QAction("�½��ļ�����Ŀ", this);//��ͼ��
    QAction* action2 = new QAction("���ļ�����Ŀ", this);//��ͼ��
    QAction* action3 = new QAction("�˳�", this);

    //�˵���Ӳ˵���
    menu1->addAction(action1);
    menu1->addAction(action2);
    menu1->addSeparator();//����ָ���

    QMenu* menu9 = new QMenu("������ʵ��ļ�", this);
    menu1->addMenu(menu9);//��Ӷ����˵�
    menu9->addAction(new QAction("�����������Ŀ", this));//�����˵���Ӳ˵���

    menu1->addAction(action3);

    //������
    QPushButton* portBtn = new QPushButton(this);
    portBtn->setIcon(QIcon("D:/QT/QTxiangmu/123/image/file.png"));	//��ť���ͼƬ
    portBtn->setToolTip("�ļ�");			//����ƶ�����ť��ʱ��ʾ��ʾ aaaa

    QPushButton* portBtn1 = new QPushButton(this);
    portBtn1->setIcon(QIcon("D:/QT/QTxiangmu/123/image/openfile.png"));	//��ť���ͼƬ
    portBtn1->setToolTip("���ļ�");			//����ƶ�����ť��ʱ��ʾ��ʾ aaaa

    QPushButton* portBtn2 = new QPushButton(this);
    portBtn2->setIcon(QIcon("D:/QT/QTxiangmu/123/image/Xrotate.png"));	//��ť���ͼƬ
    portBtn2->setToolTip("��x����ת");			//����ƶ�����ť��ʱ��ʾ��ʾ aaaa

    QPushButton* portBtn3 = new QPushButton(this);
    portBtn3->setIcon(QIcon("D:/QT/QTxiangmu/123/image/Yrotate.png"));	//��ť���ͼƬ
    portBtn3->setToolTip("��y����ת");			//����ƶ�����ť��ʱ��ʾ��ʾ aaaa

    QPushButton* portBtn4 = new QPushButton(this);
    portBtn4->setIcon(QIcon("D:/QT/QTxiangmu/123/image/Zrotate.png"));	//��ť���ͼƬ
    portBtn4->setToolTip("��z����ת");			//����ƶ�����ť��ʱ��ʾ��ʾ aaaa

    QPushButton* portBtn5 = new QPushButton(this);
    portBtn5->setIcon(QIcon("D:/QT/QTxiangmu/123/image/on.png"));	//��ť���ͼƬ
    portBtn5->setToolTip("����ͼ");			//����ƶ�����ť��ʱ��ʾ��ʾ aaaa

    QPushButton* portBtn6 = new QPushButton(this);
    portBtn6->setIcon(QIcon("D:/QT/QTxiangmu/123/image/under.png"));	//��ť���ͼƬ
    portBtn6->setToolTip("����ͼ");			//����ƶ�����ť��ʱ��ʾ��ʾ aaaa

    QPushButton* portBtn7 = new QPushButton(this);
    portBtn7->setIcon(QIcon("D:/QT/QTxiangmu/123/image/behind.png"));	//��ť���ͼƬ
    portBtn7->setToolTip("����ͼ");			//����ƶ�����ť��ʱ��ʾ��ʾ aaaa

    QPushButton* portBtn8 = new QPushButton(this);
    portBtn8->setIcon(QIcon("D:/QT/QTxiangmu/123/image/front.png"));	//��ť���ͼƬ
    portBtn8->setToolTip("ǰ��ͼ");			//����ƶ�����ť��ʱ��ʾ��ʾ aaaa

    QPushButton* portBtn9 = new QPushButton(this);
    portBtn9->setIcon(QIcon("D:/QT/QTxiangmu/123/image/right.png"));	//��ť���ͼƬ
    portBtn9->setToolTip("����ͼ");			//����ƶ�����ť��ʱ��ʾ��ʾ aaaa

    QPushButton* portBtn10 = new QPushButton(this);
    portBtn10->setIcon(QIcon("D:/QT/QTxiangmu/123/image/left.png"));	//��ť���ͼƬ
    portBtn10->setToolTip("����ͼ");			//����ƶ�����ť��ʱ��ʾ��ʾ aaaa

    QPushButton* portBtn11 = new QPushButton(this);
    portBtn11->setIcon(QIcon("D:/QT/QTxiangmu/123/image/bigger.png"));	//��ť���ͼƬ
    portBtn11->setToolTip("�Ŵ�");			//����ƶ�����ť��ʱ��ʾ��ʾ aaaa

    QPushButton* portBtn12 = new QPushButton(this);
    portBtn12->setIcon(QIcon("D:/QT/QTxiangmu/123/image/smaller.png"));	//��ť���ͼƬ
    portBtn12->setToolTip("��С");			//����ƶ�����ť��ʱ��ʾ��ʾ aaaa

    ui.toolBar->addWidget(portBtn);
    ui.toolBar->addWidget(portBtn1);
    ui.toolBar->addSeparator();
    ui.toolBar->addWidget(portBtn2);
    ui.toolBar->addWidget(portBtn3);
    ui.toolBar->addWidget(portBtn4);
    ui.toolBar->addSeparator();
    ui.toolBar->addWidget(portBtn5);
    ui.toolBar->addWidget(portBtn6);
    ui.toolBar->addWidget(portBtn7);
    ui.toolBar->addWidget(portBtn8);
    ui.toolBar->addWidget(portBtn9);
    ui.toolBar->addWidget(portBtn10);
    ui.toolBar->addSeparator();
    ui.toolBar->addWidget(portBtn11);
    ui.toolBar->addWidget(portBtn12);
    ui.toolBar->addSeparator();

    //״̬��
    ui.statusbar->setSizeGripEnabled(false);

    //������
    ui.statusbar->addWidget(ui.progressBar, 50);
    ui.progressBar->setFixedSize(125, 15);
    ui.progressBar->setOrientation(Qt::Horizontal);  // ˮƽ����
    ui.progressBar->setMinimum(0);  // ��Сֵ
    ui.progressBar->setMaximum(100);  // ���ֵ
    ui.progressBar->setValue(0);  // ��ǰ����
    ui.progressBar->hide();

    connect(ui.pushButton_2, &QPushButton::clicked, this, &QtWidgetsApplication2::PushedButton);
    connect(ui.input_picture, &QPushButton::clicked, this, &QtWidgetsApplication2::input_picture);
    connect(ui.InputButton, &QPushButton::clicked, this, &QtWidgetsApplication2::inputbutton);
    connect(ui.deletButton, &QPushButton::clicked, this, &QtWidgetsApplication2::deletebutton); 


}

QtWidgetsApplication2::~QtWidgetsApplication2()
{}



void QtWidgetsApplication2::PushedButton()
{
    //���԰���
    //vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    //cylinder->SetHeight(3);
    //cylinder->SetRadius(1);
    //cylinder->SetResolution(10);//������������ĵȱ߶���εı���

    //vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    //cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    //vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
    //cylinderActor->SetMapper(cylinderMapper);

    //vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
    //transform->PostMultiply();//��ʾʹ���ҳ˱任����ķ�ʽ
    //transform->RotateX(90);//��ʾ������Z����ת40��
    //transform->Translate(-10, 0, 0);//����ƽ�ƴ�С
    //cylinderActor->SetUserTransform(transform);

    //vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    //vtkSmartPointer<vtkLight> myLight1 = vtkSmartPointer<vtkLight>::New();
    //myLight1->SetColor(1, 0, 0);
    //myLight1->SetPosition(0, 0, 1);
    //myLight1->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
    //renderer->AddLight(myLight1);

    //vtkSmartPointer<vtkLight> myLight2 = vtkSmartPointer<vtkLight>::New();
    //myLight2->SetColor(0, 0, 1);
    //myLight2->SetPosition(0, 0, -1);
    //myLight2->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
    //renderer->AddLight(myLight2);

    //renderer->AddActor(cylinderActor);//��vtkprop���͵Ķ�����ӵ���Ⱦ������
    //renderer->SetBackground(0.1, 0.2, 0.4);//����R��G��B�ĸ�ʽ

    //ui.qvtkWidget->GetRenderWindow()->AddRenderer(renderer); //���vtkRenderWindow
    //vtkSmartPointer<vtkRenderWindowInteractor> iren = ui.qvtkWidget->GetRenderWindow()->GetInteractor();
    //iren->SetRenderWindow(ui.qvtkWidget->GetRenderWindow());

    ////�����������������ת���Ŵ���С����
    //vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    //iren->SetInteractorStyle(style);

    ///*               �������ݣ���ӱ������ȳ���                */
    ////ˢ����Ⱦ
    //ui.qvtkWidget->GetRenderWindow()->Render();
    ////��ʼ��������
    //iren->Initialize();
    ////����������
    //iren->Start();
    
    //unsigned int max_length = 32;
    //unsigned int min_length = 32;
    //unsigned int interval = 1; //ͼƬ�������Ϊ1

    int max_length = ui.spinBox->value();
    int min_length = ui.spinBox_2->value();
    int interval = ui.spinBox_3->value();

    //��ȡtxt
    vector<Hexahedral3D*> temp;

    My_Voxel vox(interval,min_length);
    vox.AllImage_m = All_images;
    vox.cols = vox.AllImage_m[0].cols;
    vox.rows = vox.AllImage_m[0].rows;
    datetime = QTime::currentTime();
    QString outputtext = datetime.toString() + tr(" �ɹ���ȡ��ʼ������");
    ui.history_output->append(outputtext);
    ui.progressBar->show();
    ui.progressBar->setValue(25);  // ��ǰ����

    OcTree My_Tree(vox, max_length, min_length); //������ʼ����������
    datetime = QTime::currentTime();
    outputtext = datetime.toString() + tr(" �ɹ���������������");
    ui.history_output->append(outputtext);
    /*outputtext = "Maximum image size:" + QString::number(vox.getMaxLenthAll(), 10);
    ui.history_output->append(outputtext);*/
    ui.progressBar->setValue(50);  // ��ǰ����
    //cout << "���ͼƬ��С��" << vox.getMaxLenthAll() << endl;

    My_Tree.build_adaptive_tree();
    /*outputtext = "Number of surface meshes:" + QString::number(My_Tree.nodes.size(), 10);
    ui.history_output->append(outputtext);*/
    //cout << "��������������" << My_Tree.nodes.size() << endl;


#if 0
    //�������
    get_Surface sur_node(My_Tree.nodes, vox);
    sur_node.get_SurNode();
    cout << "���浥Ԫ������" << sur_node.sur_nodes.size() << endl;
    cout << "���ʧ�ܵ��棺" << sur_node.fail_faces.size() << endl;
#endif


    //��ȡactor
    HexDisplay hexactor;
    //��Ⱦ����
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    //����
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    
    //VTK��ʾ����
#if 0

    //����������ʾ
    for (int i = 0; i < sur_node.sur_nodes.size(); i++)
    {
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetPosition(sur_node.sur_nodes[i]->p[0]->x, sur_node.sur_nodes[i]->p[0]->y, sur_node.sur_nodes[i]->p[0]->z);
        renderer->AddActor(hexactor.HexActor(sur_node.sur_nodes[i]));
        //text
        //temp.push_back(sur_node.sur_nodes[i]);
    }

#endif
#if 0
    string material = ui.tableWidget->item(0, 0)->text().toStdString();
    for (int i = 0; i < My_Tree.nodes.size(); i++)
    {
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetPosition(My_Tree.nodes[i]->p[0]->x, My_Tree.nodes[i]->p[0]->y, My_Tree.nodes[i]->p[0]->z);
        renderer->AddActor(hexactor.HexActor(My_Tree.nodes[i],material));
        //text
        //temp.push_back(My_Tree.nodes[i]);
    }

#endif 
    vtkSmartPointer<PropPickerInteractorStyle> style =
        vtkSmartPointer<PropPickerInteractorStyle>::New();
    style->SetDefaultRenderer(renderer);
    renderWindowInteractor->SetInteractorStyle(style);

    /*vtkSmartPointer<vtkBalloonRepresentation> balloonRep =
        vtkSmartPointer<vtkBalloonRepresentation>::New();
    balloonRep->SetBalloonLayoutToImageRight();
    vtkSmartPointer<vtkBalloonWidget> balloonWidget =
        vtkSmartPointer<vtkBalloonWidget>::New();
    balloonWidget->SetInteractor(renderWindowInteractor);
    balloonWidget->SetRepresentation(balloonRep);
    balloonWidget->On();*/


#if 1
    string material = ui.tableWidget->item(0, 0)->text().toStdString();
        for (int i = 0; i < My_Tree.m_node1.size(); i++)
        {
            vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
            actor->SetPosition(My_Tree.m_node1[i]->p[0]->x, My_Tree.m_node1[i]->p[0]->y, My_Tree.m_node1[i]->p[0]->z);
            actor = hexactor.HexActor(My_Tree.m_node1[i], material);
            renderer->AddActor(actor);
            m_actor1.push_back(actor);
            /*balloonWidget->AddBalloon(actor, "Hello", NULL);*/
            //text
            temp.push_back(My_Tree.nodes[i]);
        }
        material = ui.tableWidget->item(1, 0)->text().toStdString();
        for (int i = 0; i < My_Tree.m_node2.size(); i++)
        {
            vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
            actor->SetPosition(My_Tree.m_node2[i]->p[0]->x, My_Tree.m_node2[i]->p[0]->y, My_Tree.m_node2[i]->p[0]->z);
            actor = hexactor.HexActor(My_Tree.m_node2[i], material);
            renderer->AddActor(actor);
            m_actor2.push_back(actor);
            /*balloonWidget->AddBalloon(actor, "Hello", NULL);*/
            //text
            temp.push_back(My_Tree.nodes[i]);
        }
        material = ui.tableWidget->item(2, 0)->text().toStdString();
        for (int i = 0; i < My_Tree.m_node3.size(); i++)
        {
            vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
            actor->SetPosition(My_Tree.m_node3[i]->p[0]->x, My_Tree.m_node3[i]->p[0]->y, My_Tree.m_node3[i]->p[0]->z);
            actor = hexactor.HexActor(My_Tree.m_node3[i], material);
            renderer->AddActor(actor);
            m_actor3.push_back(actor);
            /*balloonWidget->AddBalloon(actor, "Hello", NULL);*/
            //text
            temp.push_back(My_Tree.m_node3[i]);
        }
#endif
#if 1
    ////���txt
    //string path1 = "D:\\picture\\CTpicture\\test2.txt";
    ////CreatTxt(path1, My_Tree.m_node1, My_Tree.m_node2, My_Tree.m_node3);
    if (ui.output_text->isChecked())
    {
        //��ȡtxt
        String path = ui.textpath->text().toStdString();//�����ʽ��.../�ļ�����.txt
        CreatTxt(path, My_Tree.m_node1, My_Tree.m_node2, My_Tree.m_node3);
        //�����־
        datetime = QTime::currentTime();
        QString outputtext = datetime.toString() + tr(" �ɹ����txt�ļ�");
        ui.history_output->append(outputtext);
        ui.progressBar->setValue(75);  // ��ǰ����
    }
    
    //ui->statusbar->showMessage(tr("����ɣ�"));
    

#endif
    //vtkSmartPointer<vtkRenderWindow> renderwindow =
        //vtkSmartPointer<vtkRenderWindow>::New();
    datetime = QTime::currentTime();
    outputtext = datetime.toString() + tr(" ����������άģ��");
    ui.history_output->append(outputtext);
    ui.progressBar->setValue(90);  // ��ǰ����


    ui.qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
    renderWindowInteractor->SetRenderWindow(ui.qvtkWidget->GetRenderWindow());


    //������
    //hexactor.createAxes(renderer);
    renderer->SetBackground(0.1, 0.2, 0.4);

    ui.qvtkWidget->GetRenderWindow()->Render();
    datetime = QTime::currentTime();
    outputtext = datetime.toString() + tr(" ��ɣ�");
    ui.history_output->append(outputtext);
    ui.progressBar->setValue(100);
    ui.progressBar->hide();
    /*vtkInteractorStyleTrackballCamera* style =
        vtkInteractorStyleTrackballCamera::New();*/


    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
    
    //�ͷű�������
    /*for (int i = 0; i < sur_node.sur_nodes.size(); i++)
    {
        if (sur_node.sur_nodes[i] != nullptr)
        {
            delete sur_node.sur_nodes[i];
        }
    }*/

    ////�ͷ��ڲ�����
    //for (int i = 0; i < My_Tree.nodes.size(); i++)
    //{
    //	if (My_Tree.nodes[i] != nullptr)
    //	{
    //		delete My_Tree.nodes[i];
    //	}
    //}
}

void QtWidgetsApplication2::input_picture()
{
    //QFileDialog fileDlg(this);
    //fileDlg.setWindowTitle("Choose Pictures/Voxels");
    //QStringList qstrFilters;//�����ļ���������list
    //qstrFilters << "Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm *.vols)";
    //qstrFilters << "Any files (*)";
    //fileDlg.setNameFilters(qstrFilters);//�����ļ�������
    //fileDlg.setFileMode(QFileDialog::ExistingFiles);//������ѡ�����ļ�������ǵ����ļ���д��QFileDialog::ExistingFile
    //if (fileDlg.exec() == QDialog::Accepted)
    //{
    //    vector<Mat> images; //����ԭʼͼƬ
    //    vector<Mat> imgGray; //������ж�ֵ����ĻҶ�ͼƬ
    //    strPathList = fileDlg.selectedFiles();//�õ��û�ѡ��Ķ���ļ���·����list
    //    string path = strPathList[0].toStdString();
    //    /*if (isvols(path))
    //    {
    //        Process_vols(path);
    //    }*/
    //    //QPixmap pixmapTemp;

    //    for (int i = 0; i < strPathList.count(); i++)
    //    {
    //        string path = strPathList[i].toStdString();
    //        Mat image = imread(path);
    //        images.push_back(image);
    //    }

    //    for (unsigned int i = 0; i < images.size(); i++)
    //    {
    //        Mat* img_G = new Mat;
    //        //�ҶȻ�
    //        cvtColor(images[i], *img_G, COLOR_BGR2GRAY);
    //        imgGray.push_back(*img_G);

    //        All_images.push_back(*img_G);
    //        //main_AllImage_m.push_back(*img_G);

    //        //show_picture(cur_picture);
    //    }
    //}
    ///*else
    //{
    //    QMessageBox mesg;
    //    mesg.warning(this, "����", "��ͼƬʧ��!");
    //    return;
    //}*/
    QFileDialog fileDlg(this);
    fileDlg.setWindowTitle("Choose Pictures/Voxels");
    QStringList qstrFilters;//�����ļ���������list
    qstrFilters << "Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm *.vol)";
    qstrFilters << "Any files (*)";
    fileDlg.setNameFilters(qstrFilters);//�����ļ�������
    fileDlg.setFileMode(QFileDialog::ExistingFiles);//������ѡ�����ļ�������ǵ����ļ���д��QFileDialog::ExistingFile
    if (fileDlg.exec() == QDialog::Accepted)
    {
        int m_Width = 0, m_Height = 0, m_Depth = 0;
        float distance1 = 1, distance2 = 1, distance3 = 1;
        vector<vector<vector<float>>> result;
        strPathList = fileDlg.selectedFiles();//�õ��û�ѡ��Ķ���ļ���·����list
        QString path = strPathList[0];
        QFileInfo fileInfo(path);
        string fileClass = fileInfo.suffix().toStdString();
        if (fileClass == "jpg")
        {
            datetime = QTime::currentTime();
            QString outputtext = datetime.toString() + tr(" ���������ͼ������,������������ģ��");
            ui.history_output->append(outputtext);

            vector<Mat> images; //����ԭʼͼƬ
            vector<Mat> imgGray; //������ж�ֵ����ĻҶ�ͼƬ
            for (int i = 0; i < strPathList.count(); i++)
            {
                string path = strPathList[i].toStdString();
                Mat image = imread(path);
                images.push_back(image);
            }

            for (unsigned int i = 0; i < images.size(); i++)
            {
                Mat* img_G = new Mat;
                //�ҶȻ�
                cvtColor(images[i], *img_G, COLOR_BGR2GRAY);
                imgGray.push_back(*img_G);

                All_images.push_back(*img_G);

            }
            //main_AllImage_m.push_back(*img_G);
            //show_picture(cur_picture);




        //��ͼƬ����ת��Ϊ��ά����
            result = vector<vector<vector<float>>>(All_images[0].cols, vector<vector<float>>(All_images[0].rows, vector<float>(All_images.size(), 0)));
            for (int k = 0; k < All_images.size(); ++k)
            {
                for (int i = 0; i < All_images[0].cols; ++i)
                {
                    for (int j = 0; j < All_images[0].rows; ++j)
                    {
                        result[i][j][k] = (int)All_images[k].at<uchar>(i, j);
                    }
                }
            }
            m_Width = All_images[0].cols;
            m_Height = All_images[0].rows;
            m_Depth = All_images.size();

        }

        else if (fileClass == "vol")
        {
            datetime = QTime::currentTime();
            QString outputtext = datetime.toString() + tr(" ���������������");
            ui.history_output->append(outputtext);
            ifstream is(path.toStdString(), ifstream::in | ios::binary);
            if (!is)
            {
                cout << "�ļ����ܴ򿪣�" << endl;
                return;
            }
            // 2. ���������ݳ���
            is.seekg(0, is.end);
            long long length = is.tellg();
            is.seekg(0, is.beg);

            // 3.�����ļ�ͷ
            uint Width = 0;					//ͼ����     //���ǳ�ʼ��
            uint Height = 0;				//ͼ��߶�
            uint Depth = 0;					//ͼ�����
            float maxAttenuation = 0;		//���˥��ϵ��
            uint DataType = 0;				//���ش洢����: unsigned char=01,unsigned short=02,float=03
            float voxelWidth = 0;			//���صĿ��(mm)
            float voxelDepth = 0;			//���صĸ߶�(mm)

            is.read((char*)(&Width), sizeof(Width));
            is.read((char*)(&Height), sizeof(Height));
            is.read((char*)(&Depth), sizeof(Depth));
            is.read((char*)(&maxAttenuation), sizeof(maxAttenuation));
            is.read((char*)(&DataType), sizeof(DataType));
            is.read((char*)(&voxelWidth), sizeof(voxelWidth));
            is.read((char*)(&voxelDepth), sizeof(voxelDepth));
            is.ignore(100);                 //���������ֽ������������

            m_Width = Width;
            m_Height = Height;
            m_Depth = Depth;
            distance1 = voxelWidth;
            distance2 = voxelWidth;
            distance3 = voxelDepth;
            datetime = QTime::currentTime();
            outputtext = datetime.toString() + tr(" �����ݵĿ��Ϊ") + tr(to_string(Width).c_str());
            ui.history_output->append(outputtext);

            datetime = QTime::currentTime();
            outputtext = datetime.toString() + tr(" �����ݵĸ߶�Ϊ") + tr(to_string(Height).c_str());
            ui.history_output->append(outputtext);

            datetime = QTime::currentTime();
            outputtext = datetime.toString() + tr(" �����ݵ����Ϊ") + tr(to_string(Depth).c_str());
            ui.history_output->append(outputtext);

            datetime = QTime::currentTime();
            outputtext = datetime.toString() + tr(" �������صĿ��Ϊ") + tr(to_string(voxelWidth).c_str());
            ui.history_output->append(outputtext);

            datetime = QTime::currentTime();
            outputtext = datetime.toString() + tr(" �������صĸ߶�Ϊ") + tr(to_string(voxelDepth).c_str());
            ui.history_output->append(outputtext);

            //ʡ�Բ���Ҫ��1920������
            is.ignore(1920);


            //��ʼ����������
            result = vector<vector<vector<float>>>(Width, vector<vector<float>>(Height, vector<float>(Depth, 0)));
            for (int k = 0; k < Depth; ++k)
            {
                for (int i = 0; i < Width; ++i)
                {
                    for (int j = 0; j < Height; ++j)
                    {
                        float temp = 0;
                        is.read((char*)(&temp), sizeof(temp));
                        temp = round(temp * 255 / maxAttenuation);
                        result[i][j][k] = temp;
                    }
                }
            }
        }



        //��������ת��Ϊimagedata����
        int extent[6] = { 0,m_Width - 1,0,m_Height - 1,0,m_Depth - 1 };//ȡֵ��Χ
        double spacing[3] = { distance1, distance2, distance3 };//���ص�֮��ľ���
        double origin[3] = { 0 };//��ʼ����

        int size_all = m_Width * m_Height * m_Depth;
        short* pBuf = new short[size_all] {0};
        int index = 0;
        for (int k = 0; k < m_Depth; ++k)
        {
            for (int i = 0; i < m_Width; ++i)
            {
                for (int j = 0; j < m_Height; ++j)
                {
                    pBuf[index++] = result[i][j][k];
                }
            }
        }
        vtkNew<vtkShortArray> dataArray;
        // ����short*�Ļ���ָ��������С���趨ÿ�����ݵ�Ԫ�����Ϊ1��
        dataArray->SetArray(pBuf, size_all, 1);
        vtkNew<vtkImageData> pImageData;
        // ��vtkImageDataָ��VTK_SHORT���ͣ�Ԫ�����Ϊ1��
        pImageData->AllocateScalars(VTK_SHORT, 1);
        pImageData->SetDimensions(m_Width, m_Height, m_Depth);
        pImageData->GetPointData()->SetScalars(dataArray);
        pImageData->SetSpacing(spacing);
        pImageData->SetOrigin(origin);


        vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
        volumeMapper->SetInputData(pImageData);
        volumeMapper->SetAutoAdjustSampleDistances(0);
        volumeMapper->SetImageSampleDistance(0.5);


        //�����������
        vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();//�����������
        volumeProperty->SetInterpolationTypeToLinear();
        volumeProperty->ShadeOn();  //�򿪻��߹ر���Ӱ����
        //vtkVolumePropertyĬ�Ϲر���ӰЧ��,��Ҫ��ʾ�����ShadeOn()����������ӰЧ��
        volumeProperty->SetAmbient(0.4);//������ϵ��
        volumeProperty->SetDiffuse(0.6);  //ɢ���ϵ��
        volumeProperty->SetSpecular(0.2); //�����ϵ��

        //
        //vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
        //compositeOpacity->AddPoint(89, 0.00);//���Ҷ�ֵ1����͸����1��
        //compositeOpacity->AddPoint(130, 0.40);//���Ҷ�ֵ2����͸����2��
        //compositeOpacity->AddPoint(171, 0.60);//���Ҷ�ֵ3����͸����3��
        //volumeProperty->SetScalarOpacity(compositeOpacity); //���ò�͸���ȴ��亯��

        //���ò�ͬ�Ҷ�ֵ�Ĳ�͸����
        vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
        compositeOpacity->AddPoint(70, 0.00);//���Ҷ�ֵ1����͸����1��
        compositeOpacity->AddPoint(90, 0.40);//���Ҷ�ֵ2����͸����2��
        compositeOpacity->AddPoint(180, 0.60);//���Ҷ�ֵ3����͸����3��
        volumeProperty->SetScalarOpacity(compositeOpacity); //���ò�͸���ȴ��亯��

        //�������ز�������,�ԱȲ�ͬ������
        /*compositeOpacity->AddSegment(37,0.00,171,0.4);
        compositeOpacity->AddPoint(171,  0.40,255,1.0);
        volumeProperty->SetScalarOpacity(compositeOpacity);*/


        //vtkNew<vtkPiecewiseFunction> volumeGradientOpacity;
        //volumeGradientOpacity->AddPoint(10, 0.0);//(�ݶ�ֵ1,��͸���ȳ���1)
        //volumeGradientOpacity->AddPoint(90, 0.5);//(�ݶ�ֵ2,��͸���ȳ���2)
        //volumeGradientOpacity->AddPoint(100, 1.0);//(�ݶ�ֵ3,��͸���ȳ���3)
        //volumeProperty->SetGradientOpacity(volumeGradientOpacity);//�����ݶȲ�͸����Ч���Ա�

        vtkSmartPointer<vtkColorTransferFunction> color = vtkSmartPointer<vtkColorTransferFunction>::New();
        color->AddRGBPoint(0.000, 0.00, 0.00, 0.00);//(�Ҷ�ֵ1,r1,g1,b1)
        color->AddRGBPoint(255, 1.00, 0.52, 0.30);//(�Ҷ�ֵ2,r2,g2,b2)
        color->AddRGBPoint(200, 1.00, 1.00, 1.00);//(�Ҷ�ֵ3,r3,g3,b3)
        color->AddRGBPoint(180, 0.20, 0.20, 0.20);//(�Ҷ�ֵ4,r4,g4,b4)
        volumeProperty->SetColor(color);//��ɫ���亯��,�벻͸���ȴ��亯��ʹ������


        vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
        volume->SetMapper(volumeMapper);//�ú�����������Mapper����
        volume->SetProperty(volumeProperty);//�ú��������������Զ���


        //������Ⱦ���ڣ�����vtk�Ľ�����ʽ
        vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
        vtkSmartPointer<vtkRenderWindowInteractor> rwi = vtkSmartPointer<vtkRenderWindowInteractor>::New();
        vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
        style->SetDefaultRenderer(ren);
        rwi->SetInteractorStyle(style);


        //����Ⱦ���ڷ��뵽qt�����н���չʾ
        ren->SetBackground(0.1, 0.2, 0.4);//���ñ�����ɫ
        ren->AddVolume(volume);
        ui.qvtkWidget->GetRenderWindow()->AddRenderer(ren);
        rwi->SetRenderWindow(ui.qvtkWidget->GetRenderWindow());
        ren->ResetCamera();
        ui.qvtkWidget->GetRenderWindow()->Render();
        datetime = QTime::currentTime();
        QString outputtext = datetime.toString() + tr(" �Ѿ���ʾ������ģ��");
        ui.history_output->append(outputtext);
        rwi->Initialize();
        rwi->Start();
        
    }

    /*else
    {
        QMessageBox mesg;
        mesg.warning(this, "����", "��ͼƬʧ��!");
        return;
    }*/
}

void QtWidgetsApplication2::deletebutton()
{
    int rowIndex = ui.tableWidget->currentRow();
    ui.tableWidget->removeRow(rowIndex);
}

void QtWidgetsApplication2::inputbutton()
{
    int RowCont;
    RowCont = ui.tableWidget->rowCount();
    ui.tableWidget->insertRow(RowCont);
}