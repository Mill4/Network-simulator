#ifndef ROUTERDIALOG_H
#define ROUTERDIALOG_H

#include <QPushButton>
#include <QString>
#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QAbstractButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QtGui>

class Routerdialog  : public QDialog 
{
private:
    QVBoxLayout *layout;
    QGroupBox *groupBox;
    QPushButton *Okbutton;
    QGroupBox *createQueueSizeGroup();

signals:
    void on_Btn_Ok_dialog_clicked();
public:
     explicit Routerdialog (QWidget *parent = nullptr);

    ~Routerdialog();
};
#endif