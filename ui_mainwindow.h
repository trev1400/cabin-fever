/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
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
    QLabel *snowLevelLabel;
    QSlider *snowLevelSlider;
    QLineEdit *snowLevelTextbox;
    QLabel *windinessLabel;
    QSlider *WindinessSlider;
    QLineEdit *windinessTextbox;

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

        snowballButton = new QPushButton(dockWidgetContents);
        snowballButton->setObjectName(QString::fromUtf8("snowballButton"));
        snowballButton->setGeometry(QRect(50, 80, 141, 32));
        fallenSnow = new QWidget(dockWidgetContents);
        fallenSnow->setObjectName(QString::fromUtf8("fallenSnow"));
        fallenSnow->setGeometry(QRect(10, 140, 231, 61));
        snowLevelLabel = new QLabel(fallenSnow);
        snowLevelLabel->setObjectName(QString::fromUtf8("snowLevelLabel"));
        snowLevelLabel->setGeometry(QRect(0, 0, 71, 16));
        snowLevelSlider = new QSlider(fallenSnow);
        snowLevelSlider->setObjectName(QString::fromUtf8("snowLevelSlider"));
        snowLevelSlider->setGeometry(QRect(80, 0, 81, 22));
        snowLevelSlider->setOrientation(Qt::Horizontal);
        snowLevelTextbox = new QLineEdit(fallenSnow);
        snowLevelTextbox->setObjectName(QString::fromUtf8("snowLevelTextbox"));
        snowLevelTextbox->setGeometry(QRect(180, 0, 51, 21));
        windinessLabel = new QLabel(fallenSnow);
        windinessLabel->setObjectName(QString::fromUtf8("windinessLabel"));
        windinessLabel->setGeometry(QRect(0, 30, 71, 16));
        QFont font1;
        font1.setPointSize(12);
        windinessLabel->setFont(font1);
        WindinessSlider = new QSlider(fallenSnow);
        WindinessSlider->setObjectName(QString::fromUtf8("WindinessSlider"));
        WindinessSlider->setGeometry(QRect(80, 30, 81, 22));
        WindinessSlider->setOrientation(Qt::Horizontal);
        windinessTextbox = new QLineEdit(fallenSnow);
        windinessTextbox->setObjectName(QString::fromUtf8("windinessTextbox"));
        windinessTextbox->setGeometry(QRect(180, 30, 51, 21));
        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
        QObject::connect(snowballButton, SIGNAL(clicked()), MainWindow, SLOT(throwSnowball()));
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "A CS123 Final", nullptr));
        snowSizeLabel->setText(QCoreApplication::translate("MainWindow", "Snow Size", nullptr));
        snowSizeTextbox->setText(QString());
        snowRateLabel->setText(QCoreApplication::translate("MainWindow", "Snow Rate", nullptr));
        snowRateTextbox->setText(QString());
        snowballButton->setText(QCoreApplication::translate("MainWindow", "Throw Snowball!", nullptr));
        snowLevelLabel->setText(QCoreApplication::translate("MainWindow", "Snow Level", nullptr));
        windinessLabel->setText(QCoreApplication::translate("MainWindow", "Jaggedness", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
