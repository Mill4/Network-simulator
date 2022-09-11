#include "ns-console-dock.h"
#include <QDebug>

    NSConsoleDock::NSConsoleDock()
    {
        setUpDockWidget();
        addDockHeader();
        addMainSection();
    }

    void NSConsoleDock::setUpDockWidget()
    {
        setFeatures(QDockWidget::NoDockWidgetFeatures);
        setAllowedAreas(Qt::BottomDockWidgetArea);
        setMinimumSize(QSize(frameSize().width(), (frameSize().height()/2)));
        setStyleSheet("background-color: #E2E2E1;");
    }

    void NSConsoleDock::addDockHeader()
    {
        // Create Horizontal layout in the Console title bar Widget
        QHBoxLayout *consoleTitleLayout = new QHBoxLayout;
        QWidget *consoleTitleBar = new QWidget;
        consoleTitleBar->setStyleSheet("color: #000; background-color: #B3B2B2; font-size: 16px");
        // Create new Label for title
        QLabel *title = new QLabel("CONSOLE");
        consoleTitleLayout->addWidget(title);

        NsSimulationControlButton *simulationCtrlBtn = NsSimulationControlButton::getInstance();
        consoleTitleLayout->addWidget(simulationCtrlBtn, 0, Qt::AlignRight);        
        
        // Add title layout to the title bar
        consoleTitleBar->setLayout(consoleTitleLayout);
        // Add title bar to the console bar
        setTitleBarWidget(consoleTitleBar);
    }

    void NSConsoleDock::addMainSection()
    {
        terminal = terminal->getInstance();
        setWidget(terminal);
        
    }