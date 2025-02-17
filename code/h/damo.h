#ifndef DAMO_H
#define DAMO_H

#include <QObject>
#include<fellow.h>
class DaMo : public Fellow
{
    Q_OBJECT
public:
    explicit DaMo(QWidget *parent,int x,int y);
};

#endif // DAMO_H
