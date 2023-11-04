#ifndef CONTACTDB_H
#define CONTACTDB_H

#include <QObject>
#include <QQmlEngine>
#include <QtSql/QSqlDatabase>

class ContactDB : public QObject
{
    Q_OBJECT
//    QML_ELEMENT
public:
    explicit ContactDB(QObject *parent = nullptr);

signals:
    void insertContact();


private:
    static const QString tableName;
    QSqlDatabase db;
    void connect();
    void createTable();
};



#endif // CONTACTDB_H
