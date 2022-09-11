#ifndef LINKDIALOG_H
#define LINKDIALOG_H

#include <QPushButton>
#include <QString>
#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QAbstractButton>
#include <QGroupBox>
#include <QRadioButton>

class Linkdialog  : public QDialog 
{
private:
    QVBoxLayout *layout;
    QGroupBox *groupBox;
    QPushButton *Okbutton;
    QGroupBox *createQueueSizeGroup();

signals:
    void on_Btn_Ok_dialog_clicked();
public:
    explicit Linkdialog (QWidget *parent = nullptr);

    ~Linkdialog();
};
#endif