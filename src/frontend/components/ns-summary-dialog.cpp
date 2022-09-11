#include "ns-summary-dialog.h"
/**
 * @brief Construct a new Ns Summary Dialog:: Ns Summary Dialog object
 * 
 * @param parent 
 */

NsSummaryDialog::NsSummaryDialog(QWidget *parent):QDialog(parent){

    layout = new QVBoxLayout;
    
    nodelabel = new QLabel;
    nodelabel->setAlignment(Qt::AlignLeft);
    reclabel = new QLabel;
    nodelabel->setText("Summary statistics ");
    //reclabel->setText("Receiver");
    setWindowTitle(tr("Summary"));
    setMinimumSize(400, 450);
    layout->addWidget(nodelabel);
    Okbutton = new QPushButton;
    Okbutton->setText("OK");
    layout->addWidget(Okbutton);
    setLayout(layout);
    connect(Okbutton,
                 &QPushButton::clicked,
                 this,
                 &NsSummaryDialog::on_Btn_Ok_dialog_clicked);
    
}

void NsSummaryDialog::on_Btn_Ok_dialog_clicked()
{
  accept();
}