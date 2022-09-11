#ifndef NS_SUMMARYDIALOG_H
#define NS_SUMMARYDIALOG_H

#include <QPushButton>
#include <QString>
#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>

/**
 * @brief 
 * Present an overview of the entire data transmission
 */
class NsSummaryDialog : public QDialog {

    

    public:

        explicit NsSummaryDialog(QWidget *parent = nullptr);
        ~NsSummaryDialog(){}
        
    signals:
    void click();

    private slots:
        void on_Btn_Ok_dialog_clicked();

    private:
    QVBoxLayout *layout;
    QPushButton *Okbutton;
    QTextEdit *textedit;
    QLabel *nodelabel;
    QLabel *reclabel;
    
        
};
#endif 