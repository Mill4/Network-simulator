#include "ns-left-dock-widget.h"

NSLeftDockWidget::NSLeftDockWidget()
{
    initializeDock();
    addDockHeader(this);
    // Create Horizontal layout in the Console title bar Widget
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setAlignment(Qt::AlignHCenter);
    scrollArea->setWidget(elementPanel->getInstance());
    setWidget(scrollArea);
}

void NSLeftDockWidget::initializeDock()
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    setAllowedAreas(Qt::LeftDockWidgetArea);
    setStyleSheet("background-color: #E2E2E1;");
}

void NSLeftDockWidget::addDockHeader(QDockWidget *dock) {
    QHBoxLayout *headLayout = new QHBoxLayout;
    QWidget *header = new QWidget;
    header->setStyleSheet("color: #000; background-color: #B3B2B2; font-size: 16px");
    //Add title to header
    QLabel *title = new QLabel("ELEMENTS");
    headLayout->addWidget(title);
    header->setLayout(headLayout);
    dock->setTitleBarWidget(header);
}