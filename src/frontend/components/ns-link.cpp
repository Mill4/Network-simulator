

#include "ns-link.h"

#include <QPainter>
#include <QDebug>



NsLink::NsLink(QGraphicsPixmapItem *startItem, QGraphicsPixmapItem *endItem, QGraphicsItem *parent)
    : QGraphicsLineItem(parent), myStartItem(startItem), myEndItem(endItem)
{
}

void NsLink::updatePosition()
{
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}

void NsLink::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                  QWidget *)
{
    if (myStartItem->collidesWithItem(myEndItem))
        return;
    QLineF linea(
        mapFromItem(myStartItem, getInterceptionPoint(myStartItem)),
        mapFromItem(myEndItem, getInterceptionPoint(myEndItem)));
    setLine(linea);

    painter->drawLine(line());
}

QPoint NsLink::getInterceptionPoint(QGraphicsPixmapItem *item) {
    QPoint p;
    p.setX(item->pixmap().size().width()/4);
    p.setY(item->pixmap().size().height()/4);
    return p;
}

void NsLink::setLinkId(int linkId){
    linkId_ = linkId;
}

int NsLink::getLinkId() const {
    return linkId_;
}
void NsLink::setLink(Link* link) {
    link_ = link;
}
Link* NsLink::getLink() const {
    return link_;
}




