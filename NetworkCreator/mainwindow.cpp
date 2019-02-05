#include <QIntValidator>
#include <QSlider>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Tuning sliders
    ui->gridSizeSlider->setMaximum(99);
    ui->gridSizeSlider->setMinimum(1);

    // Predefined values for sliders
    int preferredGridSize = ui->gridSizeSlider->maximum() / 3;

    // Connection sliders to apporpiate functions
    connect(ui->gridSizeSlider, &QSlider::valueChanged, this, &MainWindow::gridSizeChangedSlot);

    // Creating graph widget, setting preferred values
    mp_graphWidget = new GraphWidget(this, preferredGridSize);

    // Setup preferred value for grid size slider
    // Note, that this ui::gridSizeSlider::setValue(int) will emit
    // QSlider::valueChanged() signal,
    // which will cause MainWindow::grisSizeChangeSlot() to be called.
    // So, we need to set initial preferred value for the slider
    // when the GraphWidget creation finished, in order to avoid segmentaion fault.
    ui->gridSizeSlider->setValue(preferredGridSize);

    // Adding widgets into main window
    ui->graphWidgetGridLayout->addWidget(mp_graphWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::gridSizeChangedSlot(int size)
{
    // Draw current value in corresponding label
    ui->gridSizeLabel->setText(QString::number(size));

    // Change grid size
    mp_graphWidget->setGridSize(size);

    // Redraw grid using new grid size
    mp_graphWidget->getScene()->update();
}
