#ifndef NS_ELEMENTDESCRIPTION_H
#define NS_ELEMENTDESCRIPTION_H

#include <QString>
#include <QList>
#include <QLabel>

enum NetworkItemType {
    ROUTER,
    ENDHOST,
    PACKET,
    LINK
};
struct ElementDescription
{
    QString name;
    NetworkItemType type;
    QString iconPath;
};
#endif