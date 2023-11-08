#include "contact.h"

Contact::Contact(QObject *parent, qint32 itemId, QString firstName,
                 QString lastName, QString middleName, QString phoneNumber,
                 QString homeNumber, QString address, QString status)
    : QObject(parent) {
    this->itemId = itemId;
    this->firstName = firstName;
    this->lastName = lastName;
    this->middleName = middleName;
    this->phoneNumber = phoneNumber;
    this->homeNumber = homeNumber;
    this->address = address;
    this->status = status;
}

qint32 Contact::getItemId() const { return itemId; }
