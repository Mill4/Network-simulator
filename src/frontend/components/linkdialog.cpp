#include "routerdialog.h"

#include "linkdialog.h"

Linkdialog::Linkdialog(QWidget *parent):QDialog(parent)
{
    layout = new QVBoxLayout;
    setWindowTitle(tr("Queue Size"));
    setMinimumSize(150, 75);
    layout->addWidget(createQueueSizeGroup(),0,Qt::AlignVCenter);
    Okbutton = new QPushButton;
    Okbutton->setText("OK");
    layout->addWidget(Okbutton);
    setLayout(layout);
    connect(Okbutton,
                 &QPushButton::released,
                 this,
                 &Linkdialog::on_Btn_Ok_dialog_clicked);
}

QGroupBox *Linkdialog::createQueueSizeGroup(){
    layout = new QVBoxLayout;
    groupBox = new QGroupBox(tr("Select the preferred queue size"));
    QRadioButton *radio1 = new QRadioButton(tr("100Mbps"));
    QRadioButton *radio2 = new QRadioButton(tr("50Mbps"));
    QRadioButton *radio3 = new QRadioButton(tr("10Mbps"));
    radio1->setChecked(true);
    layout->addWidget(radio1);
    layout->addWidget(radio2);
    layout->addWidget(radio3);
    layout->addStretch(1);
    groupBox->setLayout(layout);
    return groupBox;
}
void Linkdialog::on_Btn_Ok_dialog_clicked()
{
  accept();
}

Linkdialog::~Linkdialog()
{
}
