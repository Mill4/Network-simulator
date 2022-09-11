#ifndef NS_CONSOLEDOCK_H
#define NS_CONSOLEDOCK_H

#include <QObject>
#include <QScrollArea>
#include <QDockWidget>

#include "ns-terminal.h"
#include "ns-simulation-control-button.h"
#include "ns-summary-button.h"
//#include "ns-summary-dialog.h"

class NSConsoleDock : public QDockWidget
{

private:
    NsTerminal *terminal;

public:
    NSConsoleDock();

    void setUpDockWidget();

    void addDockHeader();

    void addMainSection();
};

#endif