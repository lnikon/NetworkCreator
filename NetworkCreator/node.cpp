#include "node.h"
#include "edge.h"
#include "graphwidget.h"

#include <QPainter>
#include <QApplication>
#include <QtMath>

Node::Node(GraphWidget *pGraph)
    : mp_graph(pGraph)
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

void Node::moveAround()
{
  if(!scene() || scene()->mouseGrabberItem() == this) {
    if(QApplication::mouseButtons() == Qt::LeftButton) {
      int gridSize = mp_graph->gridSize();
      qreal xv = round(pos().x() / gridSize) * gridSize;
      qreal xy = round(pos().y() / gridSize) * gridSize;

      m_newPos.setX(xv);
      m_newPos.setY(xy);
    } else {
      m_newPos = pos();
    }
  }
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

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}

QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch(change) {
    case ItemPositionChange:
        foreach(Edge *edge, mp_edges) {
            edge->adjust();
        }
        mp_graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
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
