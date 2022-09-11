#ifndef NS_SUMMARYBUTTON_H
#define NS_SUMMARYBUTTON_H

#include <QPushButton>
#include <QString>


/**
 * @brief 
 * 
 */
class NsSummaryButton : public QPushButton {
    
    public:      
     static NsSummaryButton* getInstance();
    void show_dialog();

    private:
    static NsSummaryButton* instance_;
    NsSummaryButton(){}
    NsSummaryButton(const NsSummaryButton&);
    NsSummaryButton& operator=(const NsSummaryButton&); //prevent copying




    
        
};
#endif