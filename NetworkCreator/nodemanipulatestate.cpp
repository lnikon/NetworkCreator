#include "nodemanipulatestate.h"
#include "node.h"
#include "edge.h"
#include "graphwidget.h"

#include <QPainter>
#include <QApplication>
#include <QtMath>
#include <QDebug>
#include <QPair>

QVariant NodeManipulateState::itemChange(QGraphicsItem::GraphicsItemChange change,
                                    const QVariant &value,
                                    QList<Edge *> edges,
                                    GraphWidget *graph)
{
    switch(change) {
        case QGraphicsItem::ItemPositionChange: {
            QPointF newPos = value.toPointF();
            foreach(Edge *edge, edges) {
                edge->adjust();
            }

            if(QApplication::mouseButtons() == Qt::LeftButton) {
                int gridSize = graph->gridSize();
                qreal xV = round(newPos.x() / gridSize) * gridSize;
                qreal yV = round(newPos.y() / gridSize) * gridSize;
                return QPointF(xV, yV);
            }
            graph->itemMoved();
            break;
        }

        // Should not work, when scene isn't in "Edge" mode
        case QGraphicsItem::ItemSelectedChange: {
            QString msg = value.toString();
//            qDebug() << "msg: " << msg << "\n";
            break;
        }
        default:
            break;
    };

    // Default implementation of QGraphicsItem::itemChange(...),
    // does nothing and returns value.
    // We should pass @value to the calee @Node::itemChange(...)
    // and from it call QGraphicsItem::itemChange(...) with
    // @change and @value
    return value;
}
