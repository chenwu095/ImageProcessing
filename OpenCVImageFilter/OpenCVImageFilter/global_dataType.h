#ifndef	__GLOBAL_DATATYPE_H__
#define __GLOBAL_DATATYPE_H__

#include <QString>
#include <QDataStream>
#include <QStringList>
#include <QDateTime>
#include <QObject>
#include <QMetaType>
#include <QTextStream>

//·���ṹ��
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
	_IES_ORIGIN,							//ԭͼ

	_IES_AUTO_CUT_ALL,						//�Զ���ȡȫ����
	_IES_CUT_IMAGE,							//��ȡͼƬ
	_IES_ROTATE_IMAGE,						//��תͼƬ

	_IES_HIGH_GAUSSIAN_FILTER,				//��ͨ��˹�˲�
	_IES_HIGH_BUTTERWORTH_FILTER,			//��ͨ������˹�˲�

	_IES_LOW_GAUSSIAN_FILTER,				//��ͨ��˹�˲�
	_IES_LOW_BUTTERWORTH_FILTER,			//��ͨ������˹�˲�
};





#endif