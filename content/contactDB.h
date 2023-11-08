#ifndef CONTACTDB_H
#define CONTACTDB_H

#include <QObject>
#include <QQmlEngine>
#include <QtSql/QSqlDatabase>
#include "contact.h"
#include "contacts.h"
#include "contactlistview.h"

class ContactDB : public QObject {
    Q_OBJECT
    //    QML_ELEMENT
    Q_PROPERTY(QAbstractListModel* model READ getModel NOTIFY modelChanged )
    Q_PROPERTY(QString nameFilter MEMBER m_nameFilter NOTIFY nameFilterChanged FINAL)
    Q_PROPERTY(QString statusFilter MEMBER m_statusFilter NOTIFY statusFilterChanged FINAL)
public:
    explicit ContactDB(QObject *parent = nullptr);
    QAbstractListModel* getModel();

signals:
    void dataChanged();
    void modelChanged();
    void nameFilterChanged();
    void statusFilterChanged();
public slots:
    qint32 items();
    void insertContact(Contact *contact);
//    void deleteContact(Contact *contact);
    void deleteContactById(qint32 itemId);
//    void editContact(Contact *contact);

private:
    static const QString tableName;
    Contacts *model = new Contacts();;
    QString m_nameFilter = "", m_statusFilter = "";
    QSqlDatabase db;
    void connect();
    void createTable();
    void fillModel();
    QVector<ContactListView*>* getData();
private slots:

};
#endif // CONTACTDB_H
