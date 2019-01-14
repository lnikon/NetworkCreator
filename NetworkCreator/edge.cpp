#include "edge.h"
#include "node.h"

Edge::Edge(Node *pSourceNode, Node *pDestNode)
    : mp_source(pSourceNode), mp_dest(pDestNode), m_arrowSize(10)
{
    setAcceptedMouseButtons(0);
    mp_source->addEdge(this);
    mp_dest->addEdge(this);
    adjust();

}

void Edge::adjust()
{
    if(!mp_source || !mp_dest) {
        return;
    }

    QLineF line(mapFromItem(mp_source, 0, 0), mapFromItem(mp_dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if(length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        m_sourcePoint = line.p1() + edgeOffset;
        m_destPoint = line.p2() - edgeOffset;
    } else {
        m_sourcePoint = m_destPoint = line.p1();
    }
}

QRectF Edge::boundingRect() const
{
    if(!mp_source || !mp_dest) {
        return QRectF();
    }

    qreal penwidth = 1;
    qreal extra = (penwidth + arrowSize) / 2.0;

    return QRectF(m_sourcePoint, QSizeF(m_destPoint.x() - m_sourcePoint.x(),
                                        m_destPoint.y() - m_sourcePoint.y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!source || !dest)
            return;

        QLineF line(sourcePoint, destPoint);
        if (qFuzzyCompare(line.length(), qreal(0.)))
            return;

        // Draw the line itself
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawLine(line);
        // Draw the arrows
         double angle = std::atan2(-line.dy(), line.dx());

         QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                                       cos(angle + M_PI / 3) * arrowSize);
         QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                                       cos(angle + M_PI - M_PI / 3) * arrowSize);
         QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                                   cos(angle - M_PI / 3) * arrowSize);
         QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                                   cos(angle - M_PI + M_PI / 3) * arrowSize);

         painter->setBrush(Qt::black);
         painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
         painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}
