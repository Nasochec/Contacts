#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <QQmlEngine>

class Contact : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(qint32 itemId READ getItemId NOTIFY dataChanged CONSTANT FINAL)
    Q_PROPERTY(QString firstName MEMBER firstName NOTIFY dataChanged FINAL)
    Q_PROPERTY(QString lastName MEMBER lastName NOTIFY dataChanged FINAL)
    Q_PROPERTY(QString middleName MEMBER middleName NOTIFY dataChanged FINAL)
    Q_PROPERTY(QString phoneNumber MEMBER phoneNumber NOTIFY dataChanged FINAL)
    Q_PROPERTY(QString homeNumber MEMBER homeNumber NOTIFY dataChanged FINAL)
    Q_PROPERTY(QString address MEMBER address NOTIFY dataChanged FINAL)
    Q_PROPERTY(QString status MEMBER status NOTIFY dataChanged FINAL)
public:
  explicit Contact(QObject *parent = nullptr, qint32 itemId = -1,
                   QString firstName = nullptr, QString lastName = nullptr,
                   QString middleName = nullptr, QString phoneNumber = nullptr,
                   QString homeNumber = nullptr, QString address = nullptr,
                   QString status = nullptr);
  qint32 getItemId() const;
//  QString getFirstName() const;
//  void setFirstName(QString firstName);
//  QString getLastName() const;
//  void setLastName(QString lastName);
//  QString getMiddleName() const;
//  void setMiddleName(QString middleName);
//  QString getPhoneNumber() const;
//  void setPhoneNumber(QString phoneNumber);
//  QString getHomeNumber() const;
//  void setHomeNumber(QString homeNumber);
//  QString getAddress() const;
//  void setAddress(QString address);
//  QString getStatus() const;
//  void setStatus(QString status);
    QString firstName;
    QString lastName;
    QString middleName;
    QString phoneNumber;
    QString homeNumber;
    QString address;
    QString status;
signals:
    void dataChanged();
private:
    qint32 itemId;

};

#endif // CONTACT_H
