#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void gridSizeChangedSlot(int size);

    private slots:
    void on_manipulatePushButton_clicked();

    void on_nodePushButton_clicked();

    void on_edgePushButton_clicked();

    private:
    Ui::MainWindow *ui;
    GraphWidget *mp_graphWidget;
};

#endif // MAINWINDOW_H
