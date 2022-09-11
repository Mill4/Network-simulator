#include "ns-network-item.h"
#include <QDebug>

NsNetworkItem::NsNetworkItem(QGraphicsScene *scene, NsNodeIcon *elementIcon)
{
    if (!elementIcon)
        return;
    elementIcon_ = elementIcon;
    scene_ = scene;
    setPixmap(elementIcon->pixmap());
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}
void NsNetworkItem::setName(QPointF pos, QString name)
{
    name_ = name;
    nameText = new QGraphicsTextItem(name_);
    nameText->setTextInteractionFlags(Qt::TextEditorInteraction);
    nameText->setZValue(1000.0);
    scene_->addItem(nameText);
    nameText->setPos(pos + QPointF(-20, 40));
}

QGraphicsTextItem *NsNetworkItem::addName(QString name)
{
    return new QGraphicsTextItem(name);
}

void NsNetworkItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    nameText->setPos(mouseEvent->scenePos() + QPointF(-20, 23));
    ipText->setPos(mouseEvent->scenePos() + QPointF(-40, 35));
    QGraphicsItem::mouseMoveEvent(mouseEvent);
};

QString NsNetworkItem::getName() const
{
    return name_;
}
void NsNetworkItem::setIp(QPointF pos, QString ip)
{
    ip_ = ip;
    ipText = new QGraphicsTextItem(ip_);
    ipText->setZValue(1000.0);
    scene_->addItem(ipText);
    ipText->setPos(pos + QPointF(-40, 55));
}

QString NsNetworkItem::getIp() const
{
    return ip_;
}

void NsNetworkItem::setType(NetworkItemType type)
{
    type_ = type;
}

NetworkItemType NsNetworkItem::getType() const
{
    return type_;
}
Node *NsNetworkItem::getNode() const
{
    return node_;
}
void NsNetworkItem::setNode(Node *node)
{
    node_ = node;
}

NsNetworkItem::~NsNetworkItem()
{
    scene_->removeItem(nameText);
    scene_->removeItem(ipText);
    delete nameText;
    delete ipText;
    delete node_;
}

void NsNetworkItem::removeLink(NsLink* link) {
    for (auto l : getLinks())
    {
        if(l->getLinkId() == link->getLinkId()) {
             NsNetworkItem *selectedItem = qgraphicsitem_cast<NsNetworkItem *>(link->startItem());
             NsNetworkItem *connectedItem = qgraphicsitem_cast<NsNetworkItem *>(l->endItem());
             selectedItem->links_.removeOne(link);
             connectedItem->links_.removeOne(l);
             scene_->removeItem(link);
            if(selectedItem->getType() == ENDHOST)
                selectedItem->isConnected = false;
            if(connectedItem->getType() == ENDHOST)
                connectedItem->isConnected = false;
        }
    }
}

void NsNetworkItem::connectTo(NsNetworkItem *item, NsLink *link) {
    item->links_.push_back(link);
    links_.push_back(link);
}

QList<NsLink*> NsNetworkItem::getLinks() {
    return links_;
}