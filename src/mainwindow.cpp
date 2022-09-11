#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  // layout = new QVBoxLayout(this);
  setWindowTitle("Network Simulator 2");
  setMinimumSize(1000, 700);

  // Add top MenuBar
  menubar = new NSMenuBar;
  setMenuBar(menubar);

  // Dock Area for Network elements
  leftdock = new NSLeftDockWidget;
  addDockWidget(Qt::LeftDockWidgetArea, leftdock);

  // Dock area for standard io and button's control panel
  consoledock = new NSConsoleDock;
  addDockWidget(Qt::BottomDockWidgetArea, consoledock);

  // Dock area for simulations
  simulationCanvas = new NsSimulationCanvas(this);
  simulationCanvas->setSceneRect(QRectF(0, 0, 5000, 5000));
  QHBoxLayout *layout = new QHBoxLayout;
  canvasView = new QGraphicsView(simulationCanvas);
  canvasView->setAcceptDrops(true);
  layout->addWidget(canvasView);
  QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
  setCentralWidget(centralWidget);

  summarybutton = summarybutton->getInstance();
  summarydialog = new NsSummaryDialog(this);

  connect(summarybutton, &QPushButton::released, this, &MainWindow::show_dialog);
  connect(menubar->GetNewAction(),&QAction::triggered,simulationCanvas,&NsSimulationCanvas::clearCanvas);
}

void MainWindow::show_dialog()
{
  summarydialog->show();
}

/*void MainWindow::itemInserted(QGraphicsItem *item)
{
    //pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    //qDebug() << pointerTypeGroup->checkedId();
    //simulationCanvas->setMode(NsSimulationCanvas::NsMode(0));
    //buttonGroup->button(int(item->diagramType()))->setChecked(false);
}*/