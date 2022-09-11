#ifndef NS_NETWORKELEMENTPANEL_H
#define NS_NETWORKELEMENTPANEL_H

#include <QFrame>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QMimeData>
#include <QDrag>
#include <QPainter>
#include <QIcon>
#include <QToolButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QtGui>

#include "ns-element-description.h"
#include "ns-node-icon.h"
#include "ns-mode.h"
#include "routerdialog.h"

class NsNetworkElementPanel : public QFrame
{
    Q_OBJECT
public:
    static NsNetworkElementPanel *getInstance();
    //void show_dialog();
public slots:

signals:
    void setMode(NsMode nsMode);
    void insertedItemType(NetworkItemType type);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    NsMode nsMode;
    NsState nsState = INACTIVE;
    QPixmap pixmap;
    QPainter painter;
    QPixmap tempPixmap;
    NsNodeIcon *nsElement = nullptr;
    NetworkItemType networkItemType;
    Routerdialog *rout;

    void addNetworkElements(QList<ElementDescription> descs);
    void dragAndDropElement(QMouseEvent *event, NsNodeIcon *);
    void toggleSelection(bool isSelected);
    QPixmap getNsElementOnPressEvent(QMouseEvent *event);
    void highlightNsElement();

    static NsNetworkElementPanel *inst_;
    NsNetworkElementPanel() {}
    NsNetworkElementPanel(const NsNetworkElementPanel &);
    NsNetworkElementPanel &operator=(const NsNetworkElementPanel &);
};

#endif