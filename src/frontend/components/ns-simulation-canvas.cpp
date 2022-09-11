#include "ns-simulation-canvas.h"

NsSimulationCanvas::NsSimulationCanvas(QObject *parent)
    : QGraphicsScene(parent)
{
    nsMode = INSERT;
    line = nullptr;
    nsPanel = nsPanel->getInstance();
    terminal = terminal->getInstance();
    simulationCtrlBtn = simulationCtrlBtn->getInstance();
    simulator = new Simulator();
    deleteItemAct = new QAction("Delete this Item");
    connect(nsPanel, &NsNetworkElementPanel::setMode,
            this, &NsSimulationCanvas::setMode);
    connect(nsPanel, &NsNetworkElementPanel::insertedItemType,
            this, &NsSimulationCanvas::insertedItemType);
    connect(simulationCtrlBtn, &NsSimulationControlButton::setMode,
            this, &NsSimulationCanvas::setMode);
    connect(simulationCtrlBtn, &NsSimulationControlButton::released,
            this, &NsSimulationCanvas::runSimulation);
    connect(deleteItemAct, &QAction::triggered, this, &NsSimulationCanvas::deleteItem);
}

void NsSimulationCanvas::setMode(NsMode mode)
{
    nsMode = mode;
    qDebug() << "Mode is now set to RUN";
}

void NsSimulationCanvas::insertedItemType(NetworkItemType type)
{
    itemType = type;
}

void NsSimulationCanvas::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    if (mouseEvent->button() == Qt::LeftButton)
    {
        QList<QGraphicsItem *> sceneItems = items(mouseEvent->scenePos());
        switch (nsMode)
        {
        case CONNECT:
            line = new QGraphicsLineItem(
                QLineF(
                    mouseEvent->scenePos(),
                    mouseEvent->scenePos()));
            line->setPen(QPen(Qt::black, 2));
            addItem(line);
            break;
        case SEND:
            if (sceneItems.length() > 0)
            {
                if (startItem == nullptr)
                {
                    startItem = qgraphicsitem_cast<NsNetworkItem *>(sceneItems.first());
                }
                else
                {
                    endItem = qgraphicsitem_cast<NsNetworkItem *>(sceneItems.first());
                    if ((startItem->getType() == ENDHOST && endItem->getType() == ENDHOST) &&
                        (startItem->isConnected && endItem->isConnected))
                    {
                        // Enable run button
                        if (simulationCtrlBtn != nullptr)
                            simulationCtrlBtn->enableRunMode(RUN);
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    else if (mouseEvent->button() == Qt::RightButton)
    {
        contextMenuEvent(mouseEvent);
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void NsSimulationCanvas::contextMenuEvent(QGraphicsSceneMouseEvent *event)
{
    deleteItemMenu = new QMenu;
    QList<QGraphicsItem *> sceneItems = items(event->scenePos());
    if (sceneItems.length() > 0)
    {
        modItem = qgraphicsitem_cast<NsNetworkItem *>(sceneItems.first());
        deleteItemMenu->addAction(deleteItemAct);
        deleteItemMenu->exec(QCursor::pos());
    }
}

void NsSimulationCanvas::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (nsMode == CONNECT && line != nullptr)
    {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    }
    else if (nsMode == INSERT)
    {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void NsSimulationCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    msgBox = new QMessageBox;
    if (line != nullptr && nsMode == CONNECT)
    {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;
        if (startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first() != endItems.first())
        {
            NsNetworkItem *startItem = qgraphicsitem_cast<NsNetworkItem *>(startItems.first());
            NsNetworkItem *endItem = qgraphicsitem_cast<NsNetworkItem *>(endItems.first());
            // Add execption for Host to Host connection
            if (startItem->getType() == ENDHOST && endItem->getType() == ENDHOST)
            {
                msgBox->setText("Connection of this nature is not allowed");
                msgBox->exec();
            }
            else if (!endItem->isConnected &&
                     !startItem->isConnected)
            {
                NsLink *nsLink = new NsLink(startItem, endItem);
                nsLink->setZValue(-1000.0);
                Link *link = simulator->AddLink(startItem->getNode(), endItem->getNode(), 100.0);
                nsLink->setLinkId(link->getId());
                addItem(nsLink);
                nsLink->updatePosition();
                if (startItem->getType() == ENDHOST)
                    startItem->isConnected = true;
                if (endItem->getType() == ENDHOST)
                    endItem->isConnected = true;
                // Connect Nodes
                startItem->connectTo(endItem, nsLink);
            }
        }
    }
    line = nullptr;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void NsSimulationCanvas::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    (event->mimeData()
         ->hasFormat("ns/network-element"))
        ? event->accept()
        : event->ignore();
}

void NsSimulationCanvas::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    (event->mimeData()
         ->hasFormat("ns/network-element"))
        ? event->accept()
        : event->ignore();
}

void NsSimulationCanvas::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QByteArray itemData = event->mimeData()->data("ns/network-element");
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    QPixmap pixmap;
    QPoint offset;
    dataStream >> pixmap >> offset;
    NsNetworkItem *item = createNodeItem(pixmap, event->scenePos());
    addItem(item);
}

NsNetworkItem *NsSimulationCanvas::createNodeItem(QPixmap pixmap, QPointF pos)
{
    NsNodeIcon *nsElement = new NsNodeIcon(pixmap);
    NsNetworkItem *item = new NsNetworkItem(this, nsElement);
    Node *node;
    NodeType nodeType;
    QString ip;
    switch (itemType)
    {
    case ROUTER:
        nodeType = router;
        break;
    case ENDHOST:
        nodeType = endhost;
        break;
    default:
        break;
    }
    node = simulator->CreateNode("", nodeType);
    item->setName(pos, QString::fromStdString(node->GetName()));
    item->setIp(pos, QString::fromStdString(node->GetIPAddress()));
    item->setPos(pos);
    item->setType(itemType);
    item->setNode(node);
    return item;
}

/*void NsSimulationCanvas::show_dialog()
{
  //rout->exec();
}*/

void NsSimulationCanvas::deleteItem()
{
    QList<QGraphicsItem *> selectedItems = this->selectedItems();
    NsNetworkItem *item = qgraphicsitem_cast<NsNetworkItem *>(selectedItems.first());
    QList<NsLink *> links = item->getLinks();
    for (auto link : links)
    {
        NsNetworkItem *sItem = qgraphicsitem_cast<NsNetworkItem *>(link->startItem());
        sItem->removeLink(link);
        delete link;
    }
    delete item;
}

void NsSimulationCanvas::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

    QList<QGraphicsItem *> sceneItems = items(event->scenePos());
    if (sceneItems.length() > 0)
    {
        modItem = qgraphicsitem_cast<NsNetworkItem *>(sceneItems.first());
        rout = new Routerdialog();
        if (modItem->getType() == ROUTER)
        {
            rout->exec();
            qDebug() << "bOUBLE click in panel" << modItem;
        }
    }
}

void NsSimulationCanvas::runSimulation()
{

    simulator->AddScenario(startItem->getNode(), endItem->getNode(), 1);

    std::thread simulationThread(&NsSimulationCanvas::Run, this, simulator);
    simulationThread.detach();
}

void NsSimulationCanvas::Run(Simulator *s)
{
    std::string summary = s->RunScenarios();
    terminal->consoleLog(summary);
}

void NsSimulationCanvas::clearCanvas()
{

    bool itemDeleted = true;
    QList<QGraphicsItem *> sceneItems = items();
    for (auto i : sceneItems)
    {
        removeItem(i);
    }
}
