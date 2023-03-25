#include "opencvimagefilter.h"

OpenCVImageFilter::OpenCVImageFilter(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//get local file path
	m_dirSet = "./Directory_settings.ini";
	readDirGlobalSetting(m_dirSet, m_gPath);
	ui.label_loadFilePath->setText(m_gPath.imageLoadPath);
	ui.label_saveFilePath->setText(m_gPath.imageSavePath);
	img_data = m_gPath.imageIndexPath;

	ui.edt_filterRadius->setText(QString::number(m_gPath.filterRadius));
	ui.edt_ButterworthNum->setText(QString::number(m_gPath.filterButterworthNum));

	connect(ui.actionLoadImage,		SIGNAL(triggered()),				this,	SLOT(slot_loadImage()));
	connect(ui.actionEditImage,		SIGNAL(triggered()),				this,	SLOT(slot_editImage()));
	connect(ui.actionSaveImage,		SIGNAL(triggered()),				this,	SLOT(slot_saveImage()));

	connect(ui.btn_openLoadPath,	SIGNAL(clicked()),					this,	SLOT(slot_openLoadPath()));
	connect(ui.btn_openSavePath,	SIGNAL(clicked()),					this,	SLOT(slot_openSavePath()));
}

OpenCVImageFilter::~OpenCVImageFilter()
{

}

void OpenCVImageFilter::closeEvent(QCloseEvent *event)
{
	if(ui.edt_filterRadius->text().toInt() != m_gPath.filterRadius
		|| ui.edt_ButterworthNum->text().toInt() != m_gPath.filterButterworthNum)
	{
		int ret = QMessageBox::question(this, tr("question"), tr("The filter arguments have been changed. Do you want to renew them?"));
		if(ret == QMessageBox::Yes)
		{
			QSettings *configIniWrite = new QSettings(m_dirSet, QSettings::IniFormat);
			configIniWrite->setValue("/FILTER_ARGS/FILTER_RADIUS", ui.edt_filterRadius->text().toInt());
			configIniWrite->setValue("/FILTER_ARGS/FILTER_BUTTERWORTH_NUM", ui.edt_ButterworthNum->text().toInt());
			delete configIniWrite;
		}		
	}
}



void OpenCVImageFilter::readDirGlobalSetting(QString fileName, sDIR_GLOBAL_SETTING &glbPath)
{
	QSettings *configIniRead = new QSettings(fileName, QSettings::IniFormat);

	glbPath.sysConfFileName = configIniRead->value("/CONFIG_PATH/SYS_CONF_PATH").toString();				//system cofig path

	glbPath.imageLoadPath = configIniRead->value("/IMAGE_PATH/IMAGE_LOAD_PATH").toString();					//image load path
	glbPath.imageSavePath = configIniRead->value("/IMAGE_PATH/IMAGE_SAVE_PATH").toString();					//image save path
	glbPath.imageIndexPath = configIniRead->value("/IMAGE_PATH/IMAGE_INDEX_PATH").toString();				//image index path

	glbPath.filterRadius = configIniRead->value("/FILTER_ARGS/FILTER_RADIUS").toInt();						//filter radius
	glbPath.filterButterworthNum = configIniRead->value("/FILTER_ARGS/FILTER_BUTTERWORTH_NUM").toInt();		//butterworth coefficient

	delete configIniRead;
}

/***************************image processing*****************************/
/***************************image processing******************************/
/***************************image processing******************************/
/***************************image processing******************************/
/***************************image processing******************************/
void OpenCVImageFilter::slot_loadImage()
{
	QString filename(ui.label_loadFilePath->text());
	QImage image;
	if(image.load(filename))
	{
		//image = stdSize(image);
		ui.label_image->setPixmap(QPixmap::fromImage(image));
	}
	else
	{
		QMessageBox::warning(this, tr("warning"), tr("The picture %1 does not exists!").arg(filename));
		return;
	}
	ui.actionEditImage->setEnabled(true);

}

void OpenCVImageFilter::slot_editImage()
{

	QImage originImage = ui.label_image->pixmap()->toImage();

	QImage newImage;
	QStringList indexFileInfoList;
	QList<int> axisList;
	switch (ui.cmb_imageEditSln->currentIndex())
	{
	case _IES_ORIGIN:
		QMessageBox::warning(this, tr("warning"), tr("Please select an image edit solution!"));
		return;
		break;
	case _IES_AUTO_CUT_ALL:
		indexFileInfoList = getIndexFileInfo(ui.label_loadFilePath->text());
		autoCutAll(originImage, indexFileInfoList,ui.label_loadFilePath->text());
		break;
	case _IES_CUT_IMAGE:
		indexFileInfoList = getIndexFileInfo(ui.label_loadFilePath->text());
		axisList = getCharAxis(indexFileInfoList, ui.edt_lineNum->text().toInt());
		newImage = cutImage(originImage, axisList[0], axisList[1], axisList[2], axisList[3]);
		ui.label_image->setPixmap(QPixmap::fromImage(newImage));
		break;
	case _IES_ROTATE_IMAGE:
		newImage = rotateImage(originImage, 180);
		ui.label_image->setPixmap(QPixmap::fromImage(newImage));
		break;
	case _IES_HIGH_GAUSSIAN_FILTER:
		highGaussianFilter(originImage);
		break;
	case _IES_HIGH_BUTTERWORTH_FILTER:
		highButterworthFilter(originImage);
		break;
	case _IES_LOW_GAUSSIAN_FILTER:
		lowGaussianFilter(originImage);
		break;
	case _IES_LOW_BUTTERWORTH_FILTER:
		lowButterworthFilter(originImage);
		break;
	default:
		QMessageBox::warning(this, tr("warning"), tr("Please select an image edit solution!"));
		return;
		break;
	}
}

void OpenCVImageFilter::slot_saveImage()
{
	if(!ui.label_image->pixmap()->save(ui.label_saveFilePath->text()))
	{
		QMessageBox::warning(this, tr("warning"), tr("The path is wrong!"));
		return;
	}
}



void OpenCVImageFilter::slot_openLoadPath()
{
	QPushButton *btn = qobject_cast<QPushButton *>(sender());

	QString fileName = QFileDialog::getOpenFileName(this,tr("Data Open File"),ui.label_loadFilePath->text()
		,QString::fromLocal8Bit("JPG File(*.jpg);;PNG File(*.png);;ALL File(*.*)"));
	if (!fileName.isNull())
	{
		if (btn == ui.btn_openLoadPath)
		{
			ui.label_loadFilePath->setText(fileName);
		} 
	}
	else
	{
		return;
	}

	m_gPath.imageLoadPath = fileName;
	QSettings *configIniWrite = new QSettings(m_dirSet, QSettings::IniFormat);
	configIniWrite->setValue("/IMAGE_PATH/IMAGE_LOAD_PATH", fileName);
	delete configIniWrite;
}

void OpenCVImageFilter::slot_openSavePath()
{
	QString fileName = QFileDialog::getSaveFileName(this,tr("Data Save File"),ui.label_saveFilePath->text()
		,QString::fromLocal8Bit("JPG File(*.jpg);;PNG File(*.png);;ALL File(*.*)"));
	if (!fileName.isNull())
	{
		ui.label_saveFilePath->setText(fileName);
	}
	else
	{
		return;
	}

	m_gPath.imageSavePath = fileName;
	QSettings *configIniWrite = new QSettings(m_dirSet, QSettings::IniFormat);
	configIniWrite->setValue("/IMAGE_PATH/IMAGE_SAVE_PATH", fileName);
	delete configIniWrite;
}


void OpenCVImageFilter::autoCutAll(QImage originImage, QStringList indexFileInfo,QString imageFileName)
{
	if(indexFileInfo.size() < 2)
	{
		QMessageBox::warning(this,tr("warning"),tr("The image does not have an index file."));
		return;
	}

	QFileInfo  originImageInfo(imageFileName);
	QList<int> axisList;
	QImage qCharImage;

	for (int i = 0; i < indexFileInfo.size();i++)
	{
		axisList = getCharAxis(indexFileInfo, i+1);
		if (axisList[2] == 0 || axisList[3] == 0)
		{
			continue;
		}

		qCharImage = cutImage(originImage, axisList[0], axisList[1], axisList[2], axisList[3]);

		QString stdCharNum = QString("%1").arg(i+1,3,10,QChar('0'));
		QString charImageName = originImageInfo.absolutePath()+ "/char/" + originImageInfo.baseName() + "_" + stdCharNum + ".jpg";
		QPixmap::fromImage(qCharImage).save(charImageName);
	}
}



QStringList OpenCVImageFilter::getIndexFileInfo(QString imageFileName)
{
	QFileInfo  originImageInfo(imageFileName);

	QString indexFileName =  originImageInfo.absolutePath()+ "/index/" + originImageInfo.baseName() + ".txt";

	QFile file(indexFileName);
	QString strAll;

	if(file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream stream(&file);
		strAll = stream.readAll();
	}
	file.close();

	QStringList strAllList = strAll.split('\n');

	return strAllList;
}

QList<int> OpenCVImageFilter::getCharAxis(QStringList strAllList, int lineNum)
{
	QList<int> axisList;

	QString lineData = strAllList[lineNum - 1];

	QStringList lineDataList = lineData.split(' ');

	if(lineDataList.size() < 2)
	{
		for (int i = 0; i < 4;i++)
		{
			axisList.append(0);
		}
	}
	else
	{
		QStringList axisDataList = lineDataList[1].split(',');
		for (int i = 0; i < axisDataList.length();i++)
		{
			axisList.append(axisDataList[i].toInt());
		}
	}

	return axisList;
}

QImage OpenCVImageFilter::cutImage(QImage originImage,int x1,int y1,int x2, int y2)
{
	int newImageWidth;
	int newImageHeight;

	if (x1 < x2 && y1 < y2)
	{
		newImageWidth = x2 - x1;
		newImageHeight = y2 - y1;
	} 
	else
	{
		newImageWidth = x2;
		newImageHeight = y2;
	}

	QImage newImage = originImage.copy(x1, y1, newImageWidth, newImageHeight);

	return newImage;
}

QImage OpenCVImageFilter::rotateImage(QImage originImage, int degree)
{

	QMatrix matrix;
	matrix.rotate(degree);
	QImage newImage = originImage.transformed(matrix,Qt::FastTransformation);
	return newImage;
}

Mat OpenCVImageFilter::QImageToMat(QImage &image) 
{
	Mat mat;
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;

}

void OpenCVImageFilter::myDFT(Mat matGray, Mat& matComplex)
{
	//Expanding the image matrix to increase the operating rate
	int row = getOptimalDFTSize(matGray.rows);
	int col = getOptimalDFTSize(matGray.cols);
	copyMakeBorder(matGray, matGray, 0, row - matGray.rows, 0, col - matGray.cols, BORDER_CONSTANT, Scalar::all(0));

	//Create a dual channel matrix planes to store the real and imaginary parts of the complex matrix
	Mat planes[] = { Mat_<float>(matGray), Mat::zeros(matGray.size(), CV_32F) };

	merge(planes, 2, matComplex);						//Combine the real and imaginary part into the complex matrix
	dft(matComplex, matComplex);						//Discrete Fourier Transform(OpenCV)
	split(matComplex, planes);							//Split the real and imaginary part of the complex matrix
	Mat matReal = planes[0];							//real part
	Mat matImagin = planes[1];							//imaginary part


	Mat matTmp;
	int cx = matComplex.cols / 2;
	int cy = matComplex.rows / 2;

	// redistribute quadrants to make the origin at the center of the real image
	Mat matRealQuad1(matReal, Rect(cx, cy, cx, cy));		// 1st quadrant of the real image
	Mat matRealQuad2(matReal, Rect(cx, 0, cx, cy));			// 2nd quadrant of the real image
	Mat matRealQuad3(matReal, Rect(0, 0, cx, cy));			// 3rd quadrant of the real image
	Mat matRealQuad4(matReal, Rect(0, cy, cx, cy));			// 4th quadrant of the real image
	//swap 1st quadrant with 3rd quadrant
	matRealQuad3.copyTo(matTmp); 
	matRealQuad1.copyTo(matRealQuad3); 
	matTmp.copyTo(matRealQuad1);
	//swap 2nd quadrant with 4th quadrant
	matRealQuad2.copyTo(matTmp); 
	matRealQuad4.copyTo(matRealQuad2); 
	matTmp.copyTo(matRealQuad4);

	// redistribute quadrants to make the origin at the center of the imaginary image
	Mat matImaginQuad1(matImagin, Rect(cx, cy, cx, cy));	// 1st quadrant of the imaginary image
	Mat matImaginQuad2(matImagin, Rect(cx, 0, cx, cy));		// 2nd quadrant of the imaginary image
	Mat matImaginQuad3(matImagin, Rect(0, 0, cx, cy));		// 3rd quadrant of the imaginary image
	Mat matImaginQuad4(matImagin, Rect(0, cy, cx, cy));		// 4th quadrant of the imaginary image
	//swap 1st quadrant with 3rd quadrant
	matImaginQuad3.copyTo(matTmp); 
	matImaginQuad1.copyTo(matImaginQuad3); 
	matTmp.copyTo(matImaginQuad1);
	//swap 2nd quadrant with 4th quadrant
	matImaginQuad2.copyTo(matTmp); 
	matImaginQuad4.copyTo(matImaginQuad2); 
	matTmp.copyTo(matImaginQuad4);

	planes[0] = matReal;						//get the new real image
	planes[1] = matImagin;						//get the new imaginary image
	merge(planes, 2, matComplex);				//Combine the real and imaginary image into the complex image
}

void OpenCVImageFilter::myDFT(Mat matGray, Mat& matSpect, Mat& matComplex)
{
	//Expanding the image matrix to increase the operating rate
	int row = getOptimalDFTSize(matGray.rows);
	int col = getOptimalDFTSize(matGray.cols);
	copyMakeBorder(matGray, matGray, 0, row - matGray.rows, 0, col - matGray.cols, BORDER_CONSTANT, Scalar::all(0));

	//Create a dual channel matrix planes to store the real and imaginary parts of the image
	Mat planes[] = { Mat_<float>(matGray), Mat::zeros(matGray.size(), CV_32F) };
	
	merge(planes, 2, matComplex);						//Combine the real and imaginary image into the complex image
	dft(matComplex, matComplex);						//Discrete Fourier Transform(OpenCV)
	split(matComplex, planes);							//Split the real and imaginary part of the complex image
	Mat matReal = planes[0];							//real part
	Mat matImagin = planes[1];							//imaginary part
	magnitude(planes[0], planes[1], matSpect);			//calculate the magnitude and save in matSpect

	//make the spectrum image visible
	matSpect += Scalar(1);								// add 1 before logging to avoid log0
	log(matSpect, matSpect);							// get log number
	normalize(matSpect, matSpect, 0, 1, NORM_MINMAX);	//normalize

	//Cut and redistribute quadrants of the magnitude image
	Mat matTmp;
	int cx = matComplex.cols / 2;
	int cy = matComplex.rows / 2;

	// redistribute quadrants to make the origin at the center of the real image
	Mat matRealQuad1(matReal, Rect(cx, cy, cx, cy));		// 1st quadrant of the real image
	Mat matRealQuad2(matReal, Rect(cx, 0, cx, cy));			// 2nd quadrant of the real image
	Mat matRealQuad3(matReal, Rect(0, 0, cx, cy));			// 3rd quadrant of the real image
	Mat matRealQuad4(matReal, Rect(0, cy, cx, cy));			// 4th quadrant of the real image
	//swap 1st quadrant with 3rd quadrant
	matRealQuad3.copyTo(matTmp); 
	matRealQuad1.copyTo(matRealQuad3); 
	matTmp.copyTo(matRealQuad1);
	//swap 2nd quadrant with 4th quadrant
	matRealQuad2.copyTo(matTmp); 
	matRealQuad4.copyTo(matRealQuad2); 
	matTmp.copyTo(matRealQuad4);

	// redistribute quadrants to make the origin at the center of the imaginary image
	Mat matImaginQuad1(matImagin, Rect(cx, cy, cx, cy));	// 1st quadrant of the imaginary image
	Mat matImaginQuad2(matImagin, Rect(cx, 0, cx, cy));		// 2nd quadrant of the imaginary image
	Mat matImaginQuad3(matImagin, Rect(0, 0, cx, cy));		// 3rd quadrant of the imaginary image
	Mat matImaginQuad4(matImagin, Rect(0, cy, cx, cy));		// 4th quadrant of the imaginary image
	//swap 1st quadrant with 3rd quadrant
	matImaginQuad3.copyTo(matTmp); 
	matImaginQuad1.copyTo(matImaginQuad3); 
	matTmp.copyTo(matImaginQuad1);
	//swap 2nd quadrant with 4th quadrant
	matImaginQuad2.copyTo(matTmp); 
	matImaginQuad4.copyTo(matImaginQuad2); 
	matTmp.copyTo(matImaginQuad4);

	planes[0] = matReal;						//get the new real image
	planes[1] = matImagin;						//get the new imaginary image
	merge(planes, 2, matComplex);				//Combine the real and imaginary image into the complex image
}

void OpenCVImageFilter::writeFilterImage(QString originImageName, Mat filterImage)
{
	QFileInfo  originImageInfo(originImageName);
	QString filterImageName = originImageInfo.absolutePath()+ "/filter/" + originImageInfo.fileName();

	imwrite(filterImageName.toStdString(),filterImage * 255);
}


void OpenCVImageFilter::highGaussianFilter(QImage originImage)
{
	Mat matOrigin,matGray,matComplex;
	matOrigin = QImageToMat(originImage);					//Convert the original image to a matrix
	cvtColor(matOrigin, matGray, COLOR_RGB2GRAY);			//turn to gray image
	imshow("Gray image", matGray);

	//1.Discrete Fourier Transform: matComplex is the complex matrix we get after using DFT to deal with the image
	myDFT(matGray, matComplex);
	Mat planes[2];
	split(matComplex, planes);								//Split the real and imaginary part of the complex matrix
	imshow("Real image", planes[0]);						//Show the real part of the complex matrix
	imshow("Imaginary image", planes[1]);					//Show the imaginary part of the complex matrix

	//2.High pass Gaussian Filter
	int cx = planes[0].rows / 2;							//x-axis center
	int cy = planes[0].cols / 2;							//y-axis center
	int fr = ui.edt_filterRadius->text().toInt();			//filter radius(input from UI)
	float fc;												//final filter coefficient
	float d;												//square of the distance from current point to the center
	for (int i = 0; i < planes[0].rows; i++)
	{
		for (int j = 0; j < planes[0].cols; j++)
		{
			d = (i - cx) * (i - cx) + (j - cy) * (j - cy);
			fc = 1 - exp((float)-d/ (2 * fr * fr));			//High Gaussian Filter Formula
			planes[0].at<float>(i, j) = planes[0].at<float>(i, j) * fc;
			planes[1].at<float>(i, j) = planes[1].at<float>(i, j) * fc;

		}
	}
	merge(planes, 2, matComplex);							//Combine the real and imaginary part into the complex matrix

	//3.Inverse Discrete Fourier Transform
	Mat matFiltered;
	idft(matComplex, matFiltered);									//Inverse Discrete Fourier Transform(OpenCV)
	split(matFiltered, planes);										//split a multi-channel mat into several mats
	magnitude(planes[0], planes[1], matFiltered);					//calculate the magnitude and save in matFiltered
	normalize(matFiltered, matFiltered, 0, 1, NORM_MINMAX);			//normalize
	imshow("filtered image", matFiltered);
	writeFilterImage(m_gPath.imageLoadPath, matFiltered);			//save the filtered image
}

void OpenCVImageFilter::highButterworthFilter(QImage originImage)
{
	Mat matOrigin,matGray,matComplex;
	matOrigin = QImageToMat(originImage);					//Convert the original image to a matrix
	cvtColor(matOrigin, matGray, COLOR_RGB2GRAY);			//turn to gray image
	imshow("Gray image", matGray);

	//1.Discrete Fourier Transform: matComplex is the complex matrix we get after using DFT to deal with the image
	myDFT(matGray, matComplex);
	Mat planes[2];
	split(matComplex, planes);								//Split the real and imaginary part of the complex matrix
	imshow("Real image", planes[0]);						//Show the real part of the complex matrix
	imshow("Imaginary image", planes[1]);					//Show the imaginary part of the complex matrix

	//2.High pass Gaussian Filter
	int cx = planes[0].rows / 2;							//x-axis center
	int cy = planes[0].cols / 2;							//y-axis center
	int fr = ui.edt_filterRadius->text().toInt();			//filter radius(input from UI)
	float fc;												//final filter coefficient
	float bc = ui.edt_ButterworthNum->text().toInt();		//Butterworth coefficient
	float d;												//square of the distance from current point to the center
	for (int i = 0; i < planes[0].rows; i++)
	{
		for (int j = 0; j < planes[0].cols; j++)
		{
			d = (i - cx) * (i - cx) + (j - cy) * (j - cy);
			fc = 1/(1+pow(((fr*fr)/d) , bc));				//High Butterworth Filter Formula
			planes[0].at<float>(i, j) = planes[0].at<float>(i, j) * fc;
			planes[1].at<float>(i, j) = planes[1].at<float>(i, j) * fc;

		}
	}
	merge(planes, 2, matComplex);							//Combine the real and imaginary part into the complex matrix

	//3.Inverse Discrete Fourier Transform
	Mat matFiltered;
	idft(matComplex, matFiltered);									//Inverse Discrete Fourier Transform(OpenCV)
	split(matFiltered, planes);										//split a multi-channel mat into several mats
	magnitude(planes[0], planes[1], matFiltered);					//calculate the magnitude and save in matFiltered
	normalize(matFiltered, matFiltered, 0, 1, NORM_MINMAX);			//normalize
	imshow("filtered image", matFiltered);
	writeFilterImage(m_gPath.imageLoadPath, matFiltered);			//save the filtered image
}


void OpenCVImageFilter::lowGaussianFilter(QImage originImage)
{
	Mat matOrigin,matGray,matComplex, matFiltered;
	matOrigin = QImageToMat(originImage);

	cvtColor(matOrigin, matGray, COLOR_BGR2GRAY);
	imshow("image_gray", matGray);

	int a = 3;
	GaussianBlur(matGray, matComplex, Size(a, a), 0);
	imshow("image_output", matComplex);

	myfilter(a, matGray, matFiltered);
	imshow("image_output2", matFiltered);
}

void OpenCVImageFilter::lowButterworthFilter(QImage originImage)
{
	Mat matOrigin,matGray,matComplex;
	matOrigin = QImageToMat(originImage);					//Convert the original image to a matrix
	cvtColor(matOrigin, matGray, COLOR_RGB2GRAY);			//turn to gray image
	imshow("Gray image", matGray);

	//1.Discrete Fourier Transform: matComplex is the complex matrix we get after using DFT to deal with the image
	myDFT(matGray, matComplex);
	Mat planes[2];
	split(matComplex, planes);								//Split the real and imaginary part of the complex matrix
	imshow("Real image", planes[0]);						//Show the real part of the complex matrix
	imshow("Imaginary image", planes[1]);					//Show the imaginary part of the complex matrix

	//2.High pass Gaussian Filter
	int cx = planes[0].rows / 2;							//x-axis center
	int cy = planes[0].cols / 2;							//y-axis center
	int fr = ui.edt_filterRadius->text().toInt();			//filter radius(input from UI)
	float fc;												//final filter coefficient
	float bc = ui.edt_ButterworthNum->text().toInt();		//Butterworth coefficient
	float d;												//square of the distance from current point to the center
	for (int i = 0; i < planes[0].rows; i++)
	{
		for (int j = 0; j < planes[0].cols; j++)
		{
			d = (i - cx) * (i - cx) + (j - cy) * (j - cy);
			fc = 1/(1+pow((d/(fr*fr)) , bc));				//Low Butterworth Filter Formula
			planes[0].at<float>(i, j) = planes[0].at<float>(i, j) * fc;
			planes[1].at<float>(i, j) = planes[1].at<float>(i, j) * fc;

		}
	}
	merge(planes, 2, matComplex);							//Combine the real and imaginary part into the complex matrix

	//3.Inverse Discrete Fourier Transform
	Mat matFiltered;
	idft(matComplex, matFiltered);									//Inverse Discrete Fourier Transform(OpenCV)
	split(matFiltered, planes);										//split a multi-channel mat into several mats
	magnitude(planes[0], planes[1], matFiltered);					//calculate the magnitude and save in matFiltered
	normalize(matFiltered, matFiltered, 0, 1, NORM_MINMAX);			//normalize
	imshow("filtered image", matFiltered);
	writeFilterImage(m_gPath.imageLoadPath, matFiltered);			//save the filtered image
}

void OpenCVImageFilter::myfilter(int filter_size, Mat& image_input, Mat& image_output)
{
	image_output = image_input.clone();
	int k = (filter_size - 1) / 2;

	for (int i = k; i < (image_input.rows - k); i++)
	{
		for (int j = k; j < (image_input.cols - k); j++)
		{
			double sum = 0.0;
			double sum1 = 0.0;
			double sigma = 7; 
			double g;
			for (int m = -k; m < k + 1; m++)
			{
				for (int n = -k; n < k + 1; n++)
				{
					g = exp(-(m * m + n * n) / (2 * sigma * sigma));
					sum = sum + g * image_input.at<uchar>(i + m, j + n);
					sum1 = sum1 + g;
				}
			}
			image_output.at<uchar>(i, j) = (int)round(sum / sum1);

		}
	}
}

double OpenCVImageFilter::round(double r)
{ 
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}


