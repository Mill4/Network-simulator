#include "ns-simulation-control-button.h"
NsSimulationControlButton *NsSimulationControlButton::inst_ = NULL;

NsSimulationControlButton *NsSimulationControlButton::getInstance()
{
   if (inst_ == NULL)
   {
      inst_ = new NsSimulationControlButton();
      inst_->setEnabled(false);
      inst_->setText("Run");
   }
   return (inst_);
}

void NsSimulationControlButton::enableRunMode(NsMode mode)
{
   nsMode = mode;
   if (nsMode == RUN)
   {
      inst_->setEnabled(true);
      emit setMode(mode);
   }
}
