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

	void readDirGlobalSetting( QString fileName , sDIR_GLOBAL_SETTING &glbPath);	//读取本地文件地址


	void autoCutAll(QImage originImage, QStringList indexFileInfo,QString imageFileName);	//图片文字全截取

	QStringList getIndexFileInfo(QString imageFileName);							// 获取同名坐标文件信息
	QList<int> getCharAxis(QStringList strAllList, int lineNum);
	QImage cutImage(QImage originImage,int x1,int y1,int x2, int y2);				//截取图片
	QImage rotateImage(QImage originImage, int degree);								//旋转图片


	Mat QImageToMat(QImage &image);													//QImage转Mat
	void myDFT(Mat matGray, Mat& matComplex);										//傅里叶变换
	void myDFT(Mat matGray, Mat& matSpect, Mat& matComplex);						//傅里叶变换
	void writeFilterImage(QString originImageName, Mat filterImage);				//输出滤波后图像

	void highGaussianFilter(QImage originImage);									//高通高斯滤波
	void highButterworthFilter(QImage originImage);									//高通巴特沃斯滤波
	void lowGaussianFilter(QImage originImage);										//低通高斯滤波
	void lowButterworthFilter(QImage originImage);									//低通巴特沃斯滤波

	void myfilter(int filter_size, Mat& image_input, Mat& image_output);
	double round(double r);

	QString img_data;

private slots:
	void slot_loadImage();															//加载图片
	void slot_editImage();															//处理图片
	void slot_saveImage();															//保存图片
	void slot_openLoadPath();														//编辑加载路径
	void slot_openSavePath();														//编辑保存路径
};

#endif // OPENCVIMAGEFILTER_H
