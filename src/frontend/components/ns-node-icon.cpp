#include "ns-node-icon.h"

NsNodeIcon::NsNodeIcon(){};
NsNodeIcon::NsNodeIcon(QString name, NetworkItemType type, QString iconPath) {
    
    icon = QIcon(QPixmap(iconPath));
    setPixmap(icon.pixmap(QSize(defaultSize_, defaultSize_)));
    setAttribute(Qt::WA_DeleteOnClose);
    setAlignment(Qt::AlignCenter);
}

NsNodeIcon::NsNodeIcon(QPixmap pixmap) {
    icon = QIcon(pixmap);
    setPixmap(icon.pixmap(QSize(40, 40)));
}

void NsNodeIcon::setName(QString name) {
    name_ = name;
}
QString NsNodeIcon::getName() const {
    return name_;
}
void NsNodeIcon::setType(NetworkItemType type) {
    type_ = type;
}
NetworkItemType NsNodeIcon::getType() const {
    return type_;
}

int NsNodeIcon::getSize() const {
    return defaultSize_;
}
void NsNodeIcon::setIconPath(QString iconPath) {
    iconPath_ = iconPath;
    
    icon = QIcon(QPixmap(iconPath_));
    setPixmap(icon.pixmap(QSize(defaultSize_, defaultSize_)));
}
QString NsNodeIcon::getIconPath() const {
    return iconPath_;
}

