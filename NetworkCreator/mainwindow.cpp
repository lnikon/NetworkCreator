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

    ui->gridPenSizeSlider->setMaximum(20);
    ui->gridPenSizeSlider->setMinimum(1);

    // Predefined values for sliders
    int preferredGridSize = ui->gridSizeSlider->maximum() / 3;
    int preferredGridPenSize = ui->gridPenSizeSlider->maximum() / 10;

    // Connection sliders to apporpiate functions
    connect(ui->gridSizeSlider, &QSlider::valueChanged, this, &MainWindow::gridSizeChangedSlot);
    connect(ui->gridPenSizeSlider, &QSlider::valueChanged, this, &MainWindow::gridPenSizeChangedSlot);

    // Creating graph widget, setting preferred values
    mp_graphWidget = new GraphWidget(this, preferredGridSize, preferredGridPenSize);

    // Setup preferred value for grid size slider
    // Note, that this ui::gridSizeSlider::setValue(int) will emit
    // QSlider::valueChanged() signal,
    // which will cause MainWindow::grisSizeChangeSlot() to be called.
    // So, we need to set initial preferred value for the slider
    // when the GraphWidget creation finished, in order to avoid segmentaion fault.
    // Same stands actual for ui::gridPenSizeSlider::setValue(int)
    ui->gridSizeSlider->setValue(preferredGridSize);
    ui->gridPenSizeSlider->setValue(preferredGridPenSize);

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

void MainWindow::gridPenSizeChangedSlot(int size)
{
    // Draw current value in corresponding label
    ui->gridPenSizeLabel->setText(QString::number(size));

    // Change grid pen size
    mp_graphWidget->setGridPenSize(size);
    // Redraw grid points using new grid pen size
    mp_graphWidget->getScene()->update();
}
