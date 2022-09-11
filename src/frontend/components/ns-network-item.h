
#ifndef NS_NETWORKITEM_H
#define NS_NETWORKITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include "ns-node-icon.h"
#include "ns-element-description.h"
#include "backend/node.hpp"
#include "ns-link.h"

class NsNetworkItem : public QGraphicsPixmapItem
{
    
public:
    NsNetworkItem(QGraphicsScene *, NsNodeIcon *);
    ~NsNetworkItem();
    void setItemPos(QPointF);
    void setName(QPointF, QString);
    QString getName() const;
    void setIp(QPointF, QString);
    QString getIp() const;
    void setType(NetworkItemType);
    NetworkItemType getType() const;
    void setNode(Node *node);
    Node* getNode() const;
    QList<NsLink*> getLinks();
    void setLink(NsLink*);
    void removeLink(NsLink*);
    void connectTo(NsNetworkItem*, NsLink*);

    bool isConnected = false;
    
protected:
    QGraphicsTextItem *addName(QString);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    NsNodeIcon *elementIcon_;
    QString name_;
    QString ip_;
    QGraphicsTextItem *nameText;
    QGraphicsTextItem *ipText;
    NetworkItemType type_;
    Node *node_;
    QGraphicsScene *scene_;
    QList<NsLink*> links_;
    QList<NsNetworkItem*> connectedItems;
};
#endif