#include "ns-terminal.h"

NsTerminal *NsTerminal::inst_ = NULL;

NsTerminal *NsTerminal::getInstance()
{
    if (inst_ == NULL)
    {
        inst_ = new NsTerminal();

        inst_->scrollArea = new QScrollArea;
        inst_->scrollArea->setFixedHeight(200);
        inst_->scrollArea->setWidgetResizable(true);
        QVBoxLayout *layout = new QVBoxLayout;
        inst_->stdOut = new QLabel();
        inst_->stdOut->setWordWrap(true);
        inst_->stdOut->setAlignment(Qt::AlignTop);
        inst_->stdOut->setStyleSheet("color: #3A3A3A; background-color: #E2E2E1; font-size: 16px");

        inst_->scrollArea->setWidget(inst_->stdOut);
        inst_->scrollArea->setFrameStyle(QFrame::NoFrame);
        layout->addWidget(inst_->scrollArea);
        layout->setAlignment(Qt::AlignTop);
        layout->setContentsMargins(QMargins(15, 0, 0, 0));
        inst_->setLayout(layout);
    }
    return (inst_);
}

void NsTerminal::consoleLog(std::string strStrm)
{
    string_lock_.lock();
    str.append(QString::fromStdString(strStrm));
    inst_->stdOut->setText(str);
    string_lock_.unlock();
}

void NsTerminal::consoleLog()
{
    string_lock_.lock();
    str.append("Packet received\n");
    inst_->stdOut->setText(str);
    string_lock_.unlock();
}

void NsTerminal::consoleLogTansfer()
{
    string_lock_.lock();
    str.append("Transfering packet\n");
    inst_->stdOut->setText(str);
    string_lock_.unlock();
}

void NsTerminal::resizeEvent(QResizeEvent *event)
{
    inst_->stdOut->setMinimumSize(inst_->frameSize() + QSize(-28, 70));
}