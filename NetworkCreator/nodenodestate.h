#ifndef NODENODESTATE_H
#define NODENODESTATE_H

#include "nodestate.h"

#include <QObject>

class NodeNodeState : public NodeState
{
    public:
        NodeNodeState();
        virtual ~NodeNodeState() override = default;
        // NodeState Interface
        virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange,
                                    const QVariant &value,
                                    QList<Edge *>,
                                    GraphWidget *) override;
};

#endif // NODENODESTATE_H
