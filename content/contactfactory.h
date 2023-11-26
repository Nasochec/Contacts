#ifndef CONTACTFACTORY_H
#define CONTACTFACTORY_H

#include <QObject>
#include "contact.h"

class ContactFactory : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
//    explicit contactFactory(QObject *parent = nullptr);
public slots:
    Q_INVOKABLE static Contact* getEmptyContact();
signals:

};

#endif // CONTACTFACTORY_H
