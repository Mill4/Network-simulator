#include "ns-network-element-panel.h"
#include <QDebug>

NsNetworkElementPanel *NsNetworkElementPanel::inst_;

const QString iconPath = "src/frontend/resources/images/";

ElementDescription link = {"Link", LINK, iconPath + "ns-network-cable.svg"};
ElementDescription networkPacket = {"Packet", PACKET, iconPath + "ns-network-packet.svg"};
ElementDescription router = {"Router", ROUTER, iconPath + "ns-router.svg"};
ElementDescription endhost = {"Host", ENDHOST, iconPath + "ns-computer.svg"};

QList<ElementDescription> networkElements =
    {router, endhost, link, networkPacket};

NsNetworkElementPanel *NsNetworkElementPanel::getInstance()
{

    if (inst_ == NULL)
    {
        inst_ = new NsNetworkElementPanel();
        inst_->setAcceptDrops(true);
        inst_->addNetworkElements(networkElements);
        inst_->nsMode = INSERT;
    }

    return (inst_);
}

void NsNetworkElementPanel::mousePressEvent(QMouseEvent *event)
{
    pixmap = getNsElementOnPressEvent(event);
    networkItemType = nsElement->getType();
    if (!nsElement)
        return;
    insertedItemType(networkItemType);

    switch (networkItemType)
    {
    case ROUTER:
    case ENDHOST:
        dragAndDropElement(event, nsElement);
        nsMode = INSERT;
        break;
    case LINK:
        nsMode = CONNECT;
        break;
    case PACKET:
        nsMode = SEND;
        break;
    default:
        break;
    }
    emit setMode(nsMode);
}

/*void NsNetworkElementPanel::show_dialog()
{
    rout = new Routerdialog;
    rout->show();
}*/

void NsNetworkElementPanel::addNetworkElements(QList<ElementDescription> descs)
{
    QVBoxLayout *layout = new QVBoxLayout();
    for (auto desc = descs.begin(); desc != descs.end(); desc++)
    {
        NsNodeIcon *nodeIcon = new NsNodeIcon;
        nodeIcon->setName(desc->name);
        nodeIcon->setType(desc->type);
        nodeIcon->setIconPath(desc->iconPath);
        layout->addWidget(nodeIcon);
    }
    inst_->setLayout(layout);
}

void NsNetworkElementPanel::dragAndDropElement(QMouseEvent *event, NsNodeIcon *NsElement)
{
    if (!pixmap)
        return;
    highlightNsElement();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - NsElement->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("ns/network-element", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - NsElement->pos());
    drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
    NsElement->setPixmap(pixmap);
}

void NsNetworkElementPanel::toggleSelection(bool isSelected)
{
    isSelected = !isSelected;
}

QPixmap NsNetworkElementPanel::getNsElementOnPressEvent(QMouseEvent *event)
{
    nsElement = static_cast<NsNodeIcon *>(childAt(event->pos()));
    return nsElement->pixmap();
}

void NsNetworkElementPanel::highlightNsElement()
{
    tempPixmap = pixmap;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();
    nsElement->setPixmap(tempPixmap);
}