#include "node.h"
#include "edge.h"
#include "graphwidget.h"
#include "nodestate.h"
#include "nodemanipulatestate.h"

#include <QPainter>
#include <QApplication>
#include <QtMath>
#include <QMessageBox>

Node::Node(GraphWidget *pGraph,
           QSharedPointer<NodeState> pState)
    : mp_graph(pGraph),
      mp_state(pState)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemIsSelectable);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Node::addEdge(Edge *pEdge)
{
    mp_edges << pEdge;
    pEdge->adjust();
}

bool Node::advancePosition()
{
  return !(m_newPos == pos());
}

QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void Node::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *,
                 QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}

QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change,
                          const QVariant &value)
{
    QVariant localValue = mp_state.lock()->itemChange(change, value, mp_edges, mp_graph);
    return QGraphicsItem::itemChange(change, localValue);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
