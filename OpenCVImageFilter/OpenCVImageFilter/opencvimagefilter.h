#ifndef OPENCVIMAGEFILTER_H
#define OPENCVIMAGEFILTER_H

#include <QtWidgets/QMainWindow>
#include "ui_opencvimagefilter.h"
#include "global_dataType.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QFileDialog>
#include <QSettings>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include<iostream>
#include <fstream>
#include <conio.h>
#include <time.h>

using namespace std;
using namespace cv;

class OpenCVImageFilter : public QMainWindow
{
	Q_OBJECT

public:
	OpenCVImageFilter(QWidget *parent = 0);
	~OpenCVImageFilter();

protected:
	void closeEvent(QCloseEvent *event);	

private:
	Ui::OpenCVImageFilterClass ui;

	//localData
	QString m_dirSet;
	sDIR_GLOBAL_SETTING m_gPath;

	void readDirGlobalSetting( QString fileName , sDIR_GLOBAL_SETTING &glbPath);	//��ȡ�����ļ���ַ


	void autoCutAll(QImage originImage, QStringList indexFileInfo,QString imageFileName);	//ͼƬ����ȫ��ȡ

	QStringList getIndexFileInfo(QString imageFileName);							// ��ȡͬ�������ļ���Ϣ
	QList<int> getCharAxis(QStringList strAllList, int lineNum);
	QImage cutImage(QImage originImage,int x1,int y1,int x2, int y2);				//��ȡͼƬ
	QImage rotateImage(QImage originImage, int degree);								//��תͼƬ


	Mat QImageToMat(QImage &image);													//QImageתMat
	void myDFT(Mat matGray, Mat& matComplex);										//����Ҷ�任
	void myDFT(Mat matGray, Mat& matSpect, Mat& matComplex);						//����Ҷ�任
	void writeFilterImage(QString originImageName, Mat filterImage);				//����˲���ͼ��

	void highGaussianFilter(QImage originImage);									//��ͨ��˹�˲�
	void highButterworthFilter(QImage originImage);									//��ͨ������˹�˲�
	void lowGaussianFilter(QImage originImage);										//��ͨ��˹�˲�
	void lowButterworthFilter(QImage originImage);									//��ͨ������˹�˲�

	void myfilter(int filter_size, Mat& image_input, Mat& image_output);
	double round(double r);

	QString img_data;

private slots:
	void slot_loadImage();															//����ͼƬ
	void slot_editImage();															//����ͼƬ
	void slot_saveImage();															//����ͼƬ
	void slot_openLoadPath();														//�༭����·��
	void slot_openSavePath();														//�༭����·��
};

#endif // OPENCVIMAGEFILTER_H
