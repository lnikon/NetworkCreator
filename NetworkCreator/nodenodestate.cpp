#include "nodenodestate.h"

NodeNodeState::NodeNodeState()
{

}

QVariant NodeNodeState::itemChange(QGraphicsItem::GraphicsItemChange,
                                   const QVariant &value,
                                   QList<Edge *>,
                                   GraphWidget *)
{
    // Simply returns @value
    // In that state of @GraphWidget, all actions
    // are mainly applied to the @GraphicScene,
    // and there is nothing to do with nodes, yet
    return value;
}
