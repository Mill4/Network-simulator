#ifndef NS_SIMULATIONCANVAS_H
#define NS_SIMULATIONCANVAS_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMimeData>
#include <QIODevice>
#include <QGraphicsSceneMouseEvent>
#include <QTextCursor>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <string>

#include "backend/simulator.hpp"
#include "backend/link.hpp"
#include "ns-mode.h"
#include "ns-link.h"
#include "ns-network-element-panel.h"
#include "routerdialog.h"
#include "ns-network-item.h"
#include "ns-terminal.h"
#include "ns-simulation-control-button.h"

class NsSimulationCanvas : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit NsSimulationCanvas(QObject *parent = nullptr);

public slots:
    void setMode(NsMode nsMode);
    void insertedItemType(NetworkItemType type);
    void runSimulation();
    void deleteItem();
    void Run(Simulator *s);
    //void show_dialog();
    void clearCanvas();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    QString setNodeName(QString);
    NsNetworkItem *createNodeItem(QPixmap, QPointF);
    void contextMenuEvent(QGraphicsSceneMouseEvent *);

private:
    NsMode nsMode;
    QGraphicsLineItem *line;
    QPixmap pixmap;
    NsNetworkElementPanel *nsPanel;
    NetworkItemType itemType;
    QList<QString> routersInCanvas;
    QList<QString> hostInCanvas;
    Simulator *simulator;
    QMessageBox *msgBox;
    QMenu *deleteItemMenu;
    QAction *deleteItemAct;
    QAction *clearAct;
    NsNetworkItem *modItem;
    NsNetworkItem *startItem = nullptr;
    NsNetworkItem *endItem = nullptr;

    NsTerminal *terminal;
    NsSimulationControlButton *simulationCtrlBtn;
    Routerdialog *rout;
};

#endif