#ifndef CONTACTLISTVIEW_H
#define CONTACTLISTVIEW_H

#include <QObject>

class ContactListView : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 itemId READ getItemId CONSTANT FINAL)
    Q_PROPERTY(QString name READ getName CONSTANT FINAL)
    Q_PROPERTY(QString status READ getStatus CONSTANT FINAL)
public:
    explicit ContactListView(QObject *parent = nullptr,qint32 itemId=-1,QString name="",QString status="");
    qint32 getItemId() const;
    QString getName() const;
    QString getStatus() const;
private:
    qint32 m_itemId;
    QString m_name;
    QString m_status;
};

#endif // CONTACTLISTVIEW_H
