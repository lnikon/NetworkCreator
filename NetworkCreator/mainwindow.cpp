#include <QIntValidator>
#include <QSlider>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nodestate.h"
#include "nodemanipulatestate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Tuning sliders
    ui->gridSizeSlider->setMaximum(99);
    ui->gridSizeSlider->setMinimum(1);

    // Connection sliders to apporpiate functions
    connect(ui->gridSizeSlider, &QSlider::valueChanged, this, &MainWindow::gridSizeChangedSlot);

    // Only one button should be in pressed state at the given time
    // This works only when mentioned button belongs to the same parent
    ui->manipulatePushButton->setAutoExclusive(true);
    ui->nodePushButton->setAutoExclusive(true);
    ui->edgePushButton->setAutoExclusive(true);

    // Button should be checked till another one is clicked
    ui->manipulatePushButton->setCheckable(true);
    ui->nodePushButton->setCheckable(true);
    ui->edgePushButton->setCheckable(true);

    // Default state is manipulate
//    ui->manipulatePushButton->click();

    // Predefined values for sliders
    int preferredGridSize = ui->gridSizeSlider->maximum() / 3;

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

void MainWindow::on_manipulatePushButton_clicked()
{
    mp_graphWidget->setNodeState(QSharedPointer<NodeState>(new NodeManipulateState));
}

void MainWindow::on_nodePushButton_clicked()
{

}

void MainWindow::on_edgePushButton_clicked()
{

}
