#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QObject>
#include <QGraphicsView>
#include <QWidget>
#include <QSharedPointer>
#include <QDebug>
#include <QVector>

#include "node.h"
#include "nodemanipulatestate.h"

class Node;
class NodeState;
class GraphWidget : public QGraphicsView
{
    Q_OBJECT
public:
    GraphWidget(QWidget *parent = Q_NULLPTR, int gridSize = 1);

    void itemMoved();

    int gridSize() const { return m_gridSize; }
    void setGridSize(int gridSize);

    int gridPenSize() const { return m_gridPenSize; }
    void setGridPenSize(int gridPenSize);

    QGraphicsScene* getScene() const { return mp_scene; }

    QWeakPointer<NodeState> getNodeState() const { return mp_nodeState; }
    void setNodeStateToManipulate()
    {
        mp_nodeState = QSharedPointer<NodeState>(new NodeManipulateState);

        foreach (Node *pNode, mp_nodes) {
            pNode->setState(mp_nodeState);
        }
    }

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *pEvent) override;
    void timerEvent(QTimerEvent *) override;
    void wheelEvent(QWheelEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void scaleView(qreal scaleFactor);

private:
    enum class GraphWidgetState { Manipulate = 0,
                              Node = 1,
                              Edge = 2 };

    int m_timerId;
    GraphWidgetState m_graphState;
//    NodeState* mp_nodeState;
    QSharedPointer<NodeState> mp_nodeState;
    QGraphicsScene *mp_scene;
    Node *mp_centerNode;
    int m_gridSize;
    int m_gridPenSize;
    QVector<Node *> mp_nodes;
    int convertToGridPoint(int pos) const;
};

#endif // GRAPHWIDGET_H
