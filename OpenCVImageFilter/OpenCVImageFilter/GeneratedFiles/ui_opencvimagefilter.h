/********************************************************************************
** Form generated from reading UI file 'opencvimagefilter.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENCVIMAGEFILTER_H
#define UI_OPENCVIMAGEFILTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpenCVImageFilterClass
{
public:
    QAction *actionLoadImage;
    QAction *actionEditImage;
    QAction *actionSaveImage;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_openLoadPath;
    QLabel *label_loadFilePath;
    QPushButton *btn_openSavePath;
    QLabel *label_saveFilePath;
    QGridLayout *gridLayout;
    QComboBox *cmb_imageEditSln;
    QLabel *label;
    QLineEdit *edt_filterRadius;
    QLabel *label_2;
    QLineEdit *edt_ButterworthNum;
    QLabel *label_3;
    QLineEdit *edt_lineNum;
    QLabel *label_image;
    QMenuBar *menuBar;
    QMenu *menuImage;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OpenCVImageFilterClass)
    {
        if (OpenCVImageFilterClass->objectName().isEmpty())
            OpenCVImageFilterClass->setObjectName(QStringLiteral("OpenCVImageFilterClass"));
        OpenCVImageFilterClass->resize(1069, 816);
        actionLoadImage = new QAction(OpenCVImageFilterClass);
        actionLoadImage->setObjectName(QStringLiteral("actionLoadImage"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/OpenCVImageFilter/Resources/save3.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoadImage->setIcon(icon);
        actionEditImage = new QAction(OpenCVImageFilterClass);
        actionEditImage->setObjectName(QStringLiteral("actionEditImage"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/OpenCVImageFilter/Resources/rst.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEditImage->setIcon(icon1);
        actionSaveImage = new QAction(OpenCVImageFilterClass);
        actionSaveImage->setObjectName(QStringLiteral("actionSaveImage"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/OpenCVImageFilter/Resources/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveImage->setIcon(icon2);
        centralWidget = new QWidget(OpenCVImageFilterClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btn_openLoadPath = new QPushButton(centralWidget);
        btn_openLoadPath->setObjectName(QStringLiteral("btn_openLoadPath"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_openLoadPath->sizePolicy().hasHeightForWidth());
        btn_openLoadPath->setSizePolicy(sizePolicy);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/OpenCVImageFilter/Resources/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_openLoadPath->setIcon(icon3);

        horizontalLayout_2->addWidget(btn_openLoadPath);

        label_loadFilePath = new QLabel(centralWidget);
        label_loadFilePath->setObjectName(QStringLiteral("label_loadFilePath"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_loadFilePath->sizePolicy().hasHeightForWidth());
        label_loadFilePath->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_loadFilePath);

        btn_openSavePath = new QPushButton(centralWidget);
        btn_openSavePath->setObjectName(QStringLiteral("btn_openSavePath"));
        sizePolicy.setHeightForWidth(btn_openSavePath->sizePolicy().hasHeightForWidth());
        btn_openSavePath->setSizePolicy(sizePolicy);
        btn_openSavePath->setIcon(icon3);

        horizontalLayout_2->addWidget(btn_openSavePath);

        label_saveFilePath = new QLabel(centralWidget);
        label_saveFilePath->setObjectName(QStringLiteral("label_saveFilePath"));
        sizePolicy1.setHeightForWidth(label_saveFilePath->sizePolicy().hasHeightForWidth());
        label_saveFilePath->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_saveFilePath);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        cmb_imageEditSln = new QComboBox(centralWidget);
        cmb_imageEditSln->setObjectName(QStringLiteral("cmb_imageEditSln"));
        sizePolicy1.setHeightForWidth(cmb_imageEditSln->sizePolicy().hasHeightForWidth());
        cmb_imageEditSln->setSizePolicy(sizePolicy1);
        cmb_imageEditSln->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(cmb_imageEditSln, 0, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        edt_filterRadius = new QLineEdit(centralWidget);
        edt_filterRadius->setObjectName(QStringLiteral("edt_filterRadius"));

        gridLayout->addWidget(edt_filterRadius, 0, 2, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        edt_ButterworthNum = new QLineEdit(centralWidget);
        edt_ButterworthNum->setObjectName(QStringLiteral("edt_ButterworthNum"));

        gridLayout->addWidget(edt_ButterworthNum, 0, 4, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 5, 1, 1);

        edt_lineNum = new QLineEdit(centralWidget);
        edt_lineNum->setObjectName(QStringLiteral("edt_lineNum"));

        gridLayout->addWidget(edt_lineNum, 0, 6, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        label_image = new QLabel(centralWidget);
        label_image->setObjectName(QStringLiteral("label_image"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_image->sizePolicy().hasHeightForWidth());
        label_image->setSizePolicy(sizePolicy2);
        label_image->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_image, 2, 0, 1, 1);

        OpenCVImageFilterClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(OpenCVImageFilterClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1069, 26));
        menuImage = new QMenu(menuBar);
        menuImage->setObjectName(QStringLiteral("menuImage"));
        OpenCVImageFilterClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OpenCVImageFilterClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setIconSize(QSize(80, 80));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        OpenCVImageFilterClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(OpenCVImageFilterClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        OpenCVImageFilterClass->setStatusBar(statusBar);

        menuBar->addAction(menuImage->menuAction());
        menuImage->addAction(actionLoadImage);
        menuImage->addAction(actionEditImage);
        menuImage->addAction(actionSaveImage);
        mainToolBar->addAction(actionLoadImage);
        mainToolBar->addAction(actionEditImage);
        mainToolBar->addAction(actionSaveImage);

        retranslateUi(OpenCVImageFilterClass);

        cmb_imageEditSln->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(OpenCVImageFilterClass);
    } // setupUi

    void retranslateUi(QMainWindow *OpenCVImageFilterClass)
    {
        OpenCVImageFilterClass->setWindowTitle(QApplication::translate("OpenCVImageFilterClass", "OpenCVImageFilter", 0));
        actionLoadImage->setText(QApplication::translate("OpenCVImageFilterClass", "loadImage", 0));
        actionEditImage->setText(QApplication::translate("OpenCVImageFilterClass", "editImage", 0));
        actionSaveImage->setText(QApplication::translate("OpenCVImageFilterClass", "saveImage", 0));
        btn_openLoadPath->setText(QApplication::translate("OpenCVImageFilterClass", "openLoadPath", 0));
        label_loadFilePath->setText(QApplication::translate("OpenCVImageFilterClass", "../1.jpg", 0));
        btn_openSavePath->setText(QApplication::translate("OpenCVImageFilterClass", "openSavePath", 0));
        label_saveFilePath->setText(QApplication::translate("OpenCVImageFilterClass", "../2.jpg", 0));
        cmb_imageEditSln->clear();
        cmb_imageEditSln->insertItems(0, QStringList()
         << QApplication::translate("OpenCVImageFilterClass", "-----------Please select an image editing----------", 0)
         << QApplication::translate("OpenCVImageFilterClass", "autoCutAll", 0)
         << QApplication::translate("OpenCVImageFilterClass", "cutImage", 0)
         << QApplication::translate("OpenCVImageFilterClass", "rotateImage", 0)
         << QApplication::translate("OpenCVImageFilterClass", "highGaussianFilter", 0)
         << QApplication::translate("OpenCVImageFilterClass", "highButterworthFilter", 0)
         << QApplication::translate("OpenCVImageFilterClass", "lowGaussianFilter", 0)
         << QApplication::translate("OpenCVImageFilterClass", "lowButterworthFilter", 0)
        );
        label->setText(QApplication::translate("OpenCVImageFilterClass", "filterRadius", 0));
        label_2->setText(QApplication::translate("OpenCVImageFilterClass", "ButterworthNum", 0));
        label_3->setText(QApplication::translate("OpenCVImageFilterClass", "lineNum", 0));
        edt_lineNum->setText(QApplication::translate("OpenCVImageFilterClass", "1", 0));
        label_image->setText(QApplication::translate("OpenCVImageFilterClass", "Please load an image.", 0));
        menuImage->setTitle(QApplication::translate("OpenCVImageFilterClass", "image", 0));
    } // retranslateUi

};

namespace Ui {
    class OpenCVImageFilterClass: public Ui_OpenCVImageFilterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENCVIMAGEFILTER_H
