/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
<<<<<<< HEAD
** Created by: Qt User Interface Compiler version 5.15.2
=======
** Created by: Qt User Interface Compiler version 5.14.2
>>>>>>> ca9d388d3169d049a52e0597931f2f801d3b4569
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *canvas;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;

    QWidget *snowSize;
    QGridLayout *gridLayout_6;
    QLabel *snowSizeLabel;
    QLineEdit *snowSizeTextbox;
    QSlider *snowSizeSlider;

    QWidget *snowRate;
    QGridLayout *gridLayout_7;
    QLabel *snowRateLabel;
    QLineEdit *snowRateTextbox;
    QSlider *snowRateSlider;
    QPushButton *snowballButton;

    QWidget *fallenSnow;
    QGridLayout *gridLayout_3;
    QLabel *snowLevelLabel;
    QLineEdit *snowLevelTextbox;
    QSlider *snowLevelSlider;
    QLabel *windinessLabel;
    QLineEdit *windinessTextbox;
    QSlider *windinessSlider;
    QPushButton *shovelButton;

    void setupUi(QMainWindow *MainWindow)
    {

        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1400, 800);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        canvas = new QWidget(centralWidget);
        canvas->setObjectName(QString::fromUtf8("canvas"));
        horizontalLayout->addWidget(canvas);
        MainWindow->setCentralWidget(centralWidget);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setMinimumSize(QSize(250, 39));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));

        // snow size
        snowSize = new QWidget(dockWidgetContents);
        snowSize->setObjectName(QString::fromUtf8("snowSize"));
        snowSize->setGeometry(QRect(10, 40, 230, 22));
        gridLayout_6 = new QGridLayout(snowSize);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        snowSizeLabel = new QLabel(snowSize);
        snowSizeLabel->setObjectName(QString::fromUtf8("snowSizeLabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("Almonte Snow"));
        font.setPointSize(12);
        snowSizeLabel->setFont(font);
        gridLayout_6->addWidget(snowSizeLabel, 0, 0, 1, 1);
        snowSizeTextbox = new QLineEdit(snowSize);
        snowSizeTextbox->setObjectName(QString::fromUtf8("snowSizeTextbox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(snowSizeTextbox->sizePolicy().hasHeightForWidth());
        snowSizeTextbox->setSizePolicy(sizePolicy);
        snowSizeTextbox->setMinimumSize(QSize(55, 0));
        snowSizeTextbox->setMaximumSize(QSize(40, 16777215));
        gridLayout_6->addWidget(snowSizeTextbox, 0, 3, 1, 1);
        snowSizeSlider = new QSlider(snowSize);
        snowSizeSlider->setObjectName(QString::fromUtf8("snowSizeSlider"));
        snowSizeSlider->setOrientation(Qt::Horizontal);
        gridLayout_6->addWidget(snowSizeSlider, 0, 2, 1, 1);

        // snow rate
        snowRate = new QWidget(dockWidgetContents);
        snowRate->setObjectName(QString::fromUtf8("snowRate"));
        snowRate->setGeometry(QRect(10, 10, 230, 22));
        gridLayout_7 = new QGridLayout(snowRate);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        snowRateLabel = new QLabel(snowRate);
        snowRateLabel->setObjectName(QString::fromUtf8("snowRateLabel"));
        snowRateLabel->setFont(font);
        gridLayout_7->addWidget(snowRateLabel, 0, 0, 1, 1);
        snowRateTextbox = new QLineEdit(snowRate);
        snowRateTextbox->setObjectName(QString::fromUtf8("snowRateTextbox"));
        sizePolicy.setHeightForWidth(snowRateTextbox->sizePolicy().hasHeightForWidth());
        snowRateTextbox->setSizePolicy(sizePolicy);
        snowRateTextbox->setMinimumSize(QSize(55, 0));
        snowRateTextbox->setMaximumSize(QSize(40, 16777215));
        gridLayout_7->addWidget(snowRateTextbox, 0, 3, 1, 1);
        snowRateSlider = new QSlider(snowRate);
        snowRateSlider->setObjectName(QString::fromUtf8("snowRateSlider"));
        snowRateSlider->setOrientation(Qt::Horizontal);
        gridLayout_7->addWidget(snowRateSlider, 0, 1, 1, 1);

        // fallen snow
        fallenSnow = new QWidget(dockWidgetContents);
        fallenSnow->setObjectName(QString::fromUtf8("fallenSnow"));
        fallenSnow->setGeometry(QRect(10, 75, 230, 55));
        gridLayout_3 = new QGridLayout(fallenSnow);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        // snow level
        snowLevelLabel = new QLabel(fallenSnow);
        snowLevelLabel->setObjectName(QString::fromUtf8("snowLevelLabel"));
        snowLevelLabel->setFont(font);
        gridLayout_3->addWidget(snowLevelLabel, 0, 1, 1, 1);
        snowLevelTextbox = new QLineEdit(fallenSnow);
        snowLevelTextbox->setObjectName(QString::fromUtf8("snowLevelTextbox"));
        sizePolicy.setHeightForWidth(snowLevelTextbox->sizePolicy().hasHeightForWidth());
        snowLevelTextbox->setSizePolicy(sizePolicy);
        snowLevelTextbox->setMinimumSize(QSize(55, 0));
        snowLevelTextbox->setMaximumSize(QSize(40, 16777215));
        gridLayout_3->addWidget(snowLevelTextbox, 0, 3, 1, 1);
        snowLevelSlider = new QSlider(fallenSnow);
        snowLevelSlider->setObjectName(QString::fromUtf8("snowLevelSlider"));
        snowLevelSlider->setOrientation(Qt::Horizontal);
        gridLayout_3->addWidget(snowLevelSlider, 0, 2, 1, 1);
        // windiness
        windinessLabel = new QLabel(fallenSnow);
        windinessLabel->setObjectName(QString::fromUtf8("windinessLabel"));
        windinessLabel->setFont(font);
        gridLayout_3->addWidget(windinessLabel, 10, 1, 2, 1);
        windinessTextbox = new QLineEdit(fallenSnow);
        windinessTextbox->setObjectName(QString::fromUtf8("windinessTextbox"));
        sizePolicy.setHeightForWidth(windinessTextbox->sizePolicy().hasHeightForWidth());
        windinessTextbox->setSizePolicy(sizePolicy);
        windinessTextbox->setMinimumSize(QSize(55, 0));
        windinessTextbox->setMaximumSize(QSize(40, 16777215));
        gridLayout_3->addWidget(windinessTextbox, 10, 3, 2, 1);
        windinessSlider = new QSlider(fallenSnow);
        windinessSlider->setObjectName(QString::fromUtf8("windinessSlider"));
        windinessSlider->setOrientation(Qt::Horizontal);
        gridLayout_3->addWidget(windinessSlider, 10, 2, 2, 1);


        // snowball Button
        snowballButton = new QPushButton(dockWidgetContents);
        snowballButton->setObjectName(QString::fromUtf8("snowballButton"));
        snowballButton->setGeometry(QRect(60, 120, 141, 32));
        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

        // shovel button
        shovelButton = new QPushButton(dockWidgetContents);
        shovelButton->setObjectName(QString::fromUtf8("shovelButton"));
        shovelButton->setGeometry(QRect(60, 150, 141, 32));
        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

        retranslateUi(MainWindow);
        QMetaObject::connectSlotsByName(MainWindow);
        QObject::connect(snowballButton, SIGNAL(clicked()), MainWindow, SLOT(throwSnowball()));
        QObject::connect(shovelButton, SIGNAL(clicked()), MainWindow, SLOT(shovel()));
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "A CS123 Final", nullptr));
        // sliders
        snowSizeLabel->setText(QCoreApplication::translate("MainWindow", "Snow Size", nullptr));
        snowSizeTextbox->setText(QString());
        snowRateLabel->setText(QCoreApplication::translate("MainWindow", "Snow Rate", nullptr));
        snowRateTextbox->setText(QString());
        snowLevelLabel->setText(QCoreApplication::translate("MainWindow", "Snow Level", nullptr));
        snowLevelTextbox->setText(QString());
        windinessLabel->setText(QCoreApplication::translate("MainWindow", "Windiness", nullptr));
        windinessTextbox->setText(QString());
        // buttons
        snowballButton->setText(QCoreApplication::translate("MainWindow", "Throw Snowball!", nullptr));
        shovelButton->setText(QCoreApplication::translate("MainWindow", "Shovel!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
