#ifndef NS_NODEICON_H
#define NS_NODEICON_H
#include <QIcon>
#include "ns-element-description.h"

class NsNodeIcon : public QLabel { 
    public:
        NsNodeIcon();
        NsNodeIcon(QString name, NetworkItemType type, QString iconPath);
        NsNodeIcon(QPixmap pixmap);
        void setName(QString name);
        QString getName() const;
        void setType(NetworkItemType type);
        NetworkItemType getType() const;
        int getSize() const;
        void setIconPath(QString iconPath);
        QString getIconPath() const;


    private:
        QString name_;
        NetworkItemType type_;
        int defaultSize_ = 40;
        QString iconPath_;

        QIcon icon;

};
#endif