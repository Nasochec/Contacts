#include "contactDB.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>>

const QString ContactDB::tableName = "Contacts";

ContactDB::ContactDB(QObject *parent)
    : QObject{parent}
{
    connect();
    createTable();
    fillModel();
    QObject::connect(this,&ContactDB::dataChanged,this,&ContactDB::fillModel);
}

void ContactDB::connect()
{
    // TODO read this from cfg
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("gladkov");
    db.setDatabaseName("contactsdb.sqlite");
    //    db.setUserName("contacts");
    //    db.setPassword("contacts");
}

void ContactDB::createTable()
{
    db.open();
    QSqlQuery q;
    q.prepare("CREATE TABLE IF NOT EXISTS Contacts"
      " ('id' INTEGER PRIMARY KEY NOT NULL,"
      " 'first_name' TEXT NOT NULL,"
      " 'last_name' TEXT NOT NULL,"
      " 'middle_name' TEXT NOT NULL,"
      " 'phone_number' TEXT NOT NULL,"
      " 'home_number' TEXT NOT NULL,"
      " 'address' TEXT NOT NULL,"
      " 'status' TEXT NOT NULL)");
    qDebug()<<"Create table:"<<q.exec();
    db.close();
}

QVector<ContactListView*>* ContactDB::getData(){
    db.open();
    QString queryString=
        R"(
        SELECT id, (first_name || ' ' || last_name || ' ' || middle_name) as name, status FROM Contacts
        WHERE name LIKE :name_filter AND status LIKE :status_filter
        )";
    QSqlQuery q;
    q.prepare(queryString);
    qDebug()<<QString("%%1%").arg(m_nameFilter)<<QString("%%1%").arg(m_statusFilter) ;
    q.bindValue(":name_filter",QString("%%1%").arg(m_nameFilter));
    q.bindValue(":status_filter",QString("%%1%").arg(m_statusFilter));
    qDebug()<<"getData():"<<q.exec();
    qDebug()<<q.boundValue(":name_filter")<<q.boundValue(":status_filter");
    QVector<ContactListView*>* rez = new QVector<ContactListView*>();
    while(q.next()){
        rez->append(new ContactListView(nullptr,q.value("id").toInt(),q.value("name").toString(),q.value("status").toString()));
    }
    db.close();
    return rez;
}

void ContactDB::fillModel(){
    QVector<ContactListView*>* data = getData();
    qDebug()<<"qmllox"<<data->length();
    model->setData(data);
    emit modelChanged();
}


QAbstractListModel* ContactDB::getModel(){
    return model;
}

void ContactDB::insertContact(Contact* contact){
    Contact* c = new  Contact(nullptr,-1,"gladko","artemy","gladkov","+88005553535","720198","yaroslavl","chelovek");
    contact = c;
    QString queryString=
        "INSERT INTO Contacts (first_name,last_name,middle_name,\
            phone_number,home_number,address,status)\
            VALUES(:first_name,:last_name,:middle_name,:phone_number,\
            :home_number,:address,:status)";
    db.open();
    QSqlQuery q;
    q.prepare(queryString);
    q.prepare("INSERT INTO Contacts (first_name,last_name,middle_name,phone_number,home_number,address,status) "
              "VALUES(:first_name,:last_name,:middle_name,:phone_number,:home_number,:address,:status)");
    q.bindValue(":table_name",tableName);
    q.bindValue(":first_name",contact->firstName);
    q.bindValue(":last_name",contact->lastName);
    q.bindValue(":middle_name",contact->middleName);
    q.bindValue(":phone_number",contact->phoneNumber);
    q.bindValue(":home_number",contact->homeNumber);
    q.bindValue(":address",contact->address);
    q.bindValue(":status",contact->status);

    qDebug()<<"Insert Conatct:"<<q.exec();
    db.close();
    emit dataChanged();
}
//void deleteContact(QVariant *contact);
//void deleteContactById(qint32 itemId);
//void editContact(QVariant *contact);

qint32 ContactDB::items(){
    db.open();
    QString queryString=
        R"(
        SELECT COUNT(id) as items FROM :table_name
        WHERE name LIKE :name_filter AND status LIKE :status_filter
        )";
    QSqlQuery q;
    q.prepare(queryString);
    q.bindValue(":table_name",tableName);
    q.bindValue(":name_filter",m_nameFilter);
    q.bindValue(":status_filter",m_statusFilter);
    q.exec();
    qint32 rez=-1;
    if(q.next()){
        rez = q.value("items").toInt();
    }
    db.close();
    return rez;

}
void ContactDB::deleteContactById(qint32 itemId){
    db.open();
    QSqlQuery q;
    q.prepare("DELETE FROM Contacts WHERE id=:id");
    q.bindValue(":id",itemId);
    qDebug() << "Delete contact by id: " <<itemId<<q.exec();
    db.close();
    emit dataChanged();
}

