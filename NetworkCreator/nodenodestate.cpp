#include <QDebug>

#include "nodenodestate.h"

NodeNodeState::NodeNodeState()
{

}

QVariant NodeNodeState::itemChange(QGraphicsItem::GraphicsItemChange change,
                                   const QVariant &value,
                                   QList<Edge *>,
                                   GraphWidget *)
{
    // Simply returns @value
    // In that state of @GraphWidget, all actions
    // are mainly applied to the @GraphicScene,
    // and there is nothing to do with nodes, yet
    switch(change)
    {
        case QGraphicsItem::ItemSelectedChange:
            qDebug() << " *** LOG: NodeNodeState::itemChange() = " << value.toString() << "\n";
        break;

        default:
        break;
    }

    return value;
}
