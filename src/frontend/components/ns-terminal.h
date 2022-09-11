#ifndef NS_TERMINAL_H
#define NS_TERMINAL_H

#include <QVBoxLayout>
#include <QLabel>
#include <QLabel>
#include <QString>
#include <QMargins>
#include <QScrollArea>
#include <string>
#include <QDebug>
#include <mutex>

class NsTerminal : public QLabel
{

public:
    // clients can access only a single instance of the console view
    static NsTerminal *getInstance();
public slots:
    void consoleLog(std::string);
    void consoleLog();
    void consoleLogTansfer();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    static NsTerminal *inst_; // The one, single instance
    NsTerminal() {}           // private constructor
    NsTerminal(const NsTerminal &);
    NsTerminal &operator=(const NsTerminal &);
    QScrollArea *scrollArea;
    QLabel *stdOut;
    int count = 0;
    QString str;
    std::mutex string_lock_;
};
#endif
