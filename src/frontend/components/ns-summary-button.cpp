#include "ns-summary-button.h"
/**
 * @brief 
 * 
 */

NsSummaryButton* NsSummaryButton::instance_=NULL;

NsSummaryButton* NsSummaryButton::getInstance(){
        if (instance_ == NULL) {
      instance_ = new NsSummaryButton();
      instance_->setText("Summary");
   }
        return(instance_);
    }

