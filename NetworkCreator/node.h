#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QGraphicsItem>
#include <QList>
#include <QPainterPath>
#include <QWeakPointer>

class GraphWidget;
class Edge;
class NodeState;
class Node : public QGraphicsItem
{
public:
    Node(GraphWidget *, QSharedPointer<NodeState>);

    QWeakPointer<NodeState> getState() const { return mp_state; }
    void setState(QSharedPointer<NodeState> pState) { mp_state = pState; }

    void addEdge(Edge *);
    QList<Edge *> getEdges() const { return mp_edges; }

    bool advancePosition();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPointF m_newPos;
    QList<Edge *> mp_edges;
    GraphWidget* mp_graph;
    QWeakPointer<NodeState> mp_state;
};

#endif // NODE_H
