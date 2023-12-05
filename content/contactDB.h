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
    Q_PROPERTY(QAbstractListModel* model READ getModel NOTIFY modelChanged )
public:
    explicit ContactDB(QObject *parent = nullptr);
    static ContactDB* getInstance();
    QAbstractListModel* getModel();
    static ContactDB* instance;
signals:
    void dataChanged();
    void modelChanged();
public slots:
    qint32 items();
    Contact* getContact(qint32 id);
    QVector<Contact*>* getByStatus(QString status);
    void insertContact(Contact *contact);
    void deleteContactById(qint32 itemId);
    void editContact(Contact *contact);
    Contact* getEmptyContact();
    void sortByName();
    void sortByStatus();
protected:

private:


    enum class SortBy{
        Name,
        Status
    };
    static const QString tableName;
    Contacts *model = new Contacts();
    QSqlDatabase db;
    SortBy sort = SortBy::Name;
    void connect();
    void createTable();
    void fillModel();
    QVector<ContactListView*>* getData();
private slots:

};
#endif // CONTACTDB_H
