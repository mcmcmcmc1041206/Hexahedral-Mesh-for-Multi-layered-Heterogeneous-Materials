#include "QtWidgetsApplication2.h"
#include <QtWidgets/QApplication>

//***********************************
//˵����һ���򵥵�VTK����
//ʱ�䣺2020.08.10
//���ߣ�BOO
//********************************


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QtWidgetsApplication2  w;
	w.show();

	return a.exec();
}