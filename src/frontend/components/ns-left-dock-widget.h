#ifndef NS_LEFTDOCKWIDGET_H
#define NS_LEFTDOCKWIDGET_H
#include <QLabel>
#include <QToolButton>
#include <QPixmap>
#include <QBitmap>
#include <Qt>
#include <QColor>
#include <QDockWidget>
#include <QVBoxLayout>

#include "ns-network-element-panel.h"

class NSLeftDockWidget : public QDockWidget
{

public:
    NSLeftDockWidget();
    

private:
    void initializeDock();
    void addDockHeader(QDockWidget *dock);
    NsNetworkElementPanel *elementPanel;

};

#endif