#ifndef NODESTATE_H
#define NODESTATE_H

#include <QObject>
#include <QGraphicsItem>
#include <QVariant>

class Edge;
class GraphWidget;
class NodeState
{
    public:
        NodeState() = default;
        virtual ~NodeState() = default;

        virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change,
                                    const QVariant &value,
                                    QList<Edge *> edges,
                                    GraphWidget *graph) = 0;
};

#endif // NODESTATE_H
