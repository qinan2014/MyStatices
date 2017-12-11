#include "namestatic.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NameStatic w;
	w.show();
	return a.exec();
}
