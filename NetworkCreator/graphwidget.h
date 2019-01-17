#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QObject>
#include <QGraphicsView>
#include <QWidget>

class Node;
class GraphWidget : public QGraphicsView
{
    Q_OBJECT
public:
    GraphWidget(QWidget *parent = 0);

    void itemMoved();

    int gridSize() const { return m_gridSize; }
    int gridPenSize() const { return m_gridPenSize; }

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *pEvent) override;
    void timerEvent(QTimerEvent *) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void scaleView(qreal scaleFactor);

private:
    int m_timerId;
    QGraphicsScene *mp_scene;
    Node *mp_centerNode;

    // Grid settings
    // Incapsulate all these settings into different class
    // Smth like "GridSettings"
    int m_gridSize;
    int m_gridPenSize;
};

#endif // GRAPHWIDGET_H
