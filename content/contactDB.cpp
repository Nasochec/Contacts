#include "contactDB.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"

const QString ContactDB::tableName = "Contacts";

ContactDB::ContactDB(QObject *parent)
    : QObject{parent}
{
    connect();
    createTable();
}

void ContactDB::connect()
{
    // TODO read this from cfg
    db = QSqlDatabase::addDatabase("Contacts");
    db.setHostName("gladkov");
    db.setDatabaseName("contactsdb");
    //    db.setUserName("contacts");
    //    db.setPassword("contacts");
    //    bool ok = db.open();
}

void ContactDB::createTable()
{
    db.open();
    QString queryString =
    R"(CREATE TABLE IF NOT EXISTS :table_name (
      'id' INTEGER PRIMARY KEY NOT NULL,
      'first_name' TEXT NOT NULL,
      'last_name' TEXT NOT NULL,
      'middle_name' TEXT NOT NULL,
      'phone_number' TEXT NOT NULL,
      'home_number' TEXT NOT NULL,
      'address' TEXT NOT NULL,
      'status' TEXT NOT NULL
      )
    )";
    QSqlQuery q;
    q.prepare(queryString);
    q.bindValue(":table_name",tableName);
    q.exec();
    db.close();
}

