#ifndef	__GLOBAL_DATATYPE_H__
#define __GLOBAL_DATATYPE_H__

#include <QString>
#include <QDataStream>
#include <QStringList>
#include <QDateTime>
#include <QObject>
#include <QMetaType>
#include <QTextStream>

//路径结构体
typedef struct _DIR_GLOBAL_SETTING{
	QString sysConfFileName;

	QString imageLoadPath;
	QString imageSavePath;
	QString imageIndexPath;

	int filterRadius;
	int filterButterworthNum;

}sDIR_GLOBAL_SETTING;

enum _eIMAGE_EDIT_SOLUTION
{
	_IES_ORIGIN,							//原图

	_IES_AUTO_CUT_ALL,						//自动截取全文字
	_IES_CUT_IMAGE,							//截取图片
	_IES_ROTATE_IMAGE,						//旋转图片

	_IES_HIGH_GAUSSIAN_FILTER,				//高通高斯滤波
	_IES_HIGH_BUTTERWORTH_FILTER,			//高通巴特沃斯滤波

	_IES_LOW_GAUSSIAN_FILTER,				//低通高斯滤波
	_IES_LOW_BUTTERWORTH_FILTER,			//低通巴特沃斯滤波
};





#endif