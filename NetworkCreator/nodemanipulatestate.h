#ifndef NODEMANIPULATESTATE_H
#define NODEMANIPULATESTATE_H

#include <QObject>
#include <QDebug>

#include "nodestate.h"

class NodeManipulateState : public NodeState
{
    public:
        NodeManipulateState()
        {
            qDebug() << " *** LOG: NodeManipulateState()\n";
        }

        virtual ~NodeManipulateState() override = default;

        // NodeState Interface
        virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change,
                                    const QVariant &value,
                                    QList<Edge *> edges,
                                    GraphWidget *graph) override;
};

#endif // NODEMANIPULATESTATE_H
