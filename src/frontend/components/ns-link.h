
#ifndef NS_LINK_H
#define NS_LINK_H

#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QLineF>

#include "backend/link.hpp"

class NsLink : public QGraphicsLineItem
{
public:

    NsLink(QGraphicsPixmapItem *startItem, QGraphicsPixmapItem *endItem,
          QGraphicsItem *parent = nullptr);

    QGraphicsPixmapItem *startItem() const { return myStartItem; }
    QGraphicsPixmapItem *endItem() const { return myEndItem; }

    void updatePosition();
    void setLinkId(int);
    int getLinkId() const;
    void setLink(Link*);
    Link* getLink()const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QPoint getInterceptionPoint(QGraphicsPixmapItem *pixmapItem);

private:
    QGraphicsPixmapItem *myStartItem;
    QGraphicsPixmapItem *myEndItem;
    int linkId_;
    Link* link_;
};


#endif // NS_LINK_H
