#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QApplication>
#include <QAction>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QTableView>
#include <QDockWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QGraphicsView>

#include "frontend/components/ns-menubar.h"
#include "frontend/components/ns-left-dock-widget.h"
#include "frontend/components/ns-console-dock.h"
#include "frontend/components/ns-simulation-canvas.h"
#include "frontend/components/ns-summary-button.h"
#include "frontend/components/ns-summary-dialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    //MainWindow();
    explicit MainWindow(QWidget *parent = nullptr);

    //signals:
    //void buttonClicked();
    
private slots:
    //void itemInserted(QGraphicsItem *item);
    void show_dialog();
private:
    NSMenuBar *menubar;
    NSLeftDockWidget *leftdock;
    NSConsoleDock *consoledock;
    QGraphicsView *canvasView;
    NsSimulationCanvas *simulationCanvas;
    NsSummaryButton *summarybutton;
    NsSummaryDialog *summarydialog;
};
#endif