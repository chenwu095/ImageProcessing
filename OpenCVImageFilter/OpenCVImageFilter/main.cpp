#include "opencvimagefilter.h"
#include <QtWidgets/QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTranslator trans;
	trans.load("opencvimagefilter_zh");
	a.installTranslator(&trans);

	OpenCVImageFilter w;
	w.showMaximized();
	return a.exec();
}

