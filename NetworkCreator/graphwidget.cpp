#include <cmath>

#include <QList>
#include <QVector>
#include <QDebug>

#include "graphwidget.h"
#include "node.h"
#include "edge.h"

GraphWidget::GraphWidget(QWidget *parent, int gridSize, int gridPenSize)
  : QGraphicsView(parent), m_timerId(0), m_gridSize(gridSize), m_gridPenSize(gridPenSize) {
  mp_scene = new QGraphicsScene(this);
  mp_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  mp_scene->setSceneRect(-200, -200, 400, 400);
  setScene(mp_scene);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  scale(qreal(0.8), qreal(0.8));
  setMinimumSize(400, 400);
  setWindowTitle(tr("NetworkCreator 3000"));

  Node *node1 = new Node(this);
  Node *node2 = new Node(this);
  Node *node3 = new Node(this);
  Node *node4 = new Node(this);
  mp_centerNode = new Node(this);
  Node *node6 = new Node(this);
  Node *node7 = new Node(this);
  Node *node8 = new Node(this);
  Node *node9 = new Node(this);
  mp_scene->addItem(node1);
  mp_scene->addItem(node2);
  mp_scene->addItem(node3);
  mp_scene->addItem(node4);
  mp_scene->addItem(mp_centerNode);
  mp_scene->addItem(node6);
  mp_scene->addItem(node7);
  mp_scene->addItem(node8);
  mp_scene->addItem(node9);
  mp_scene->addItem(new Edge(node1, node2));
  mp_scene->addItem(new Edge(node2, node3));
  mp_scene->addItem(new Edge(node2, mp_centerNode));
  mp_scene->addItem(new Edge(node3, node6));
  mp_scene->addItem(new Edge(node4, node1));
  mp_scene->addItem(new Edge(node4, mp_centerNode));
  mp_scene->addItem(new Edge(mp_centerNode, node6));
  mp_scene->addItem(new Edge(mp_centerNode, node8));
  mp_scene->addItem(new Edge(node6, node9));
  mp_scene->addItem(new Edge(node7, node4));
  mp_scene->addItem(new Edge(node8, node7));
  mp_scene->addItem(new Edge(node9, node8));

  node1->setPos(-50, -50);
  node2->setPos(0, -50);
  node3->setPos(50, -50);
  node4->setPos(-50, 0);
  mp_centerNode->setPos(0, 0);
  node6->setPos(50, 0);
  node7->setPos(-50, 50);
  node8->setPos(0, 50);
  node9->setPos(50, 50);
}

void GraphWidget::itemMoved()
{
  if(!m_timerId) {
    m_timerId = startTimer(100 / 25);
  }
}

void GraphWidget::setGridSize(int gridSize)
{
  m_gridSize = gridSize;
}

void GraphWidget::setGridPenSize(int gridPenSize)
{
  m_gridPenSize = gridPenSize;
}

void GraphWidget::zoomIn()
{

}

void GraphWidget::zoomOut()
{

}

void GraphWidget::keyPressEvent(QKeyEvent *pEvent)
{
  switch(pEvent->key()) {
    case Qt::Key_Up:
      mp_centerNode->moveBy(0, -20);
      break;
    case Qt::Key_Down:
      mp_centerNode->moveBy(0, 20);
      break;
    case Qt::Key_Left:
      mp_centerNode->moveBy(-20, 0);
      break;
    case Qt::Key_Right:
      mp_centerNode->moveBy(20, 0);
      break;
    case Qt::Key_Plus:
      zoomIn();
      break;
    case Qt::Key_Minus:
      zoomOut();
      break;
    default:
      QGraphicsView::keyPressEvent(pEvent);
      break;
  }
}

void GraphWidget::timerEvent(QTimerEvent *)
{
  QList<Node *> nodes;
  foreach(QGraphicsItem *pItem, mp_scene->items()) {
    if(Node *pNode = qgraphicsitem_cast<Node *>(pItem)) {
      nodes << pNode;
    }
  }

  bool itemsMoved = false;
  foreach(Node *pNode, nodes) {
    if(pNode->advancePosition()) {
      itemsMoved = true;
    }
  }

  if(!itemsMoved) {
    killTimer(m_timerId);
    m_timerId = 0;
  }
}

void GraphWidget::wheelEvent(QWheelEvent *event) {
  scaleView(std::pow(static_cast<double>(2), -event->delta() / 240.0));
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF & rect)
{
  QPen pen;
  pen.setWidth(m_gridPenSize);
  pen.setCosmetic(true);
  pen.setColor(Qt::black);
  painter->setPen(pen);

  // Returns the x-coordinate of the rectangle's left edge.
  qreal left = int(rect.left()) - (int(rect.left()) % m_gridSize);

  // Returns the y-coordinate of the rectangle's top edge.
  qreal top = int(rect.top()) - (int(rect.top()) % m_gridSize);

  QVector<QPointF> points;
  for(qreal x = left; x < rect.right(); x += m_gridSize) {
    for(qreal y = top; y < rect.bottom(); y += m_gridSize) {
      points.append(QPointF(x, y));
    }
  }

  painter->drawPoints(points);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
  qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
  if (factor < 0.07 || factor > 100)
      return;

  scale(scaleFactor, scaleFactor);
}
