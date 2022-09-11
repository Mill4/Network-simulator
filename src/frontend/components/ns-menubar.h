#ifndef NS_MENUBAR_H
#define NS_MENUBAR_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QPixmap>


class NSMenuBar : public QMenuBar
{
public:
    NSMenuBar()
    {
        // Setup File Menu
        fileMenu = addMenu("&File");
        quitAction = new QAction("&Quit", this);
        quitAction->setShortcuts(QKeySequence::Quit);
        newAction = new QAction("&New", this);
        newAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
        fileMenu->addAction(newAction);
        fileMenu->addAction(quitAction);
        fileMenu->addSeparator();
        fileMenu->addAction(quitAction);
        connect(quitAction, &QAction::triggered, this, &QApplication::quit);
        
    }

    QAction *GetNewAction() {
        return newAction;
    }

private:
    QMenu *fileMenu;
    // Actions
    QAction *quitAction;
    QAction *newAction;
};

#endif