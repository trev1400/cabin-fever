#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGLFormat>
#include "Databinding.h"
#include "Settings.h"
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    QGLFormat qglFormat;
    qglFormat.setVersion(4,0);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    m_ui->setupUi(this);

    // phong widget
    QGridLayout *gridLayout = new QGridLayout(m_ui->canvas);    
    m_glWidget = new GLWidget(qglFormat, this);
    m_glWidget->setMinimumSize(50, 50);
    gridLayout->addWidget(m_glWidget, 0, 1);

    settings.loadSettingsOrDefaults();
    dataBind();

    QSettings qtSettings("cabin-fever", "cabin-fever");
}

void MainWindow::dataBind() {
    // Snow dock
#define BIND(b) { \
    DataBinding *_b = (b); \
    m_bindings.push_back(_b); \
    assert(connect(_b, SIGNAL(dataChanged()), this, SLOT(settingsChanged()))); \
}
    BIND(FloatBinding::bindSliderAndTextbox(
        m_ui->snowRateSlider, m_ui->snowRateTextbox, settings.snowRate, 0.f, 50.f))
    BIND(FloatBinding::bindSliderAndTextbox(
        m_ui->snowSizeSlider, m_ui->snowSizeTextbox, settings.snowSize, 0.f, 50.f))

#undef BIND

   // make sure the aspect ratio updates when m_canvas3D changes size
   // connect(m_canvas3D, SIGNAL(aspectRatioChanged()), this, SLOT(updateAspectRatio()));
}

MainWindow::~MainWindow()
{
    foreach (DataBinding *b, m_bindings)
        delete b;
    delete m_ui;
    delete m_glWidget;
}

void MainWindow::settingsChanged() {
    std::cout << "settings changed" << std::endl;
    std::cout << "snow rate: " << settings.snowRate << std::endl;
    std::cout << "snow size: " << settings.snowSize << std::endl;
}

void MainWindow::throwSnowball() {
    std::cout << "throw Snowball" << std::endl;
}
