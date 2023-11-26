#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>
#include "contact.h"

class Actions : public QObject
{
    Q_OBJECT
public:
    explicit Actions(QObject *parent = nullptr);

public slots:
    Contact* getEmptyContact();
    void invite(QString status,QString eventName);
};

#endif // ACTIONS_H
