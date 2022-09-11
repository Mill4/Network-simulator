#ifndef NS_SIMULATIONCONTROLBUTTON_H
#define NS_SIMULATIONCONTROLBUTTON_H

#include <QPushButton>
#include <QString>
#include <QDebug>

#include "ns-mode.h"
#include "ns-terminal.h"


/**
 * @brief 
 * 
 */
class NsSimulationControlButton : public QPushButton {
    Q_OBJECT
    public:
        // clients can access only a single instance of the control button
        static NsSimulationControlButton* getInstance();
        void toggleBtnModeTitle() {
            QString text = inst_->text();
            inst_->setText((text == "Run") ? "Stop" : "Run");
        }
        void enableRunMode(NsMode);
    private slots:
        signals:
            void setMode(NsMode);
            
    private:
        static NsSimulationControlButton* inst_;   // The one, single instance
        NsSimulationControlButton() {} // private constructor
        NsSimulationControlButton(const NsSimulationControlButton&);
        NsSimulationControlButton& operator=(const NsSimulationControlButton&); //prevent copying
        NsMode nsMode;
};
#endif