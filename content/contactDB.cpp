#include "contactDB.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>

ContactDB* ContactDB::instance = nullptr;

ContactDB* ContactDB::getInstance(){
    if(ContactDB::instance == NULL)
        ContactDB::instance = new ContactDB();
    return ContactDB::instance;
}

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
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("gladkov");
    db.setDatabaseName("contactsdb.sqlite");
    if(db.open())
        db.close();
    else
        qDebug()<<db.isOpenError();
    //    db.setUserName("contacts");.sqlite
    //    db.setPassword("contacts");
}

void ContactDB::createTable()
{
    db.open();
    QSqlQuery q;
    q.prepare("CREATE TABLE IF NOT EXISTS Contacts"
      " ('id' INTEGER PRIMARY KEY NOT NULL,"
      " 'last_name' TEXT NOT NULL,"
      " 'first_name' TEXT NOT NULL,"
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
    QString s="SELECT id, (last_name || ' ' || first_name || ' ' || middle_name) as name,\
        status FROM Contacts";
    if(sort == SortBy::Name)
        s.append(" ORDER BY name");
    else
        s.append(" ORDER BY status");
    QSqlQuery q;
    q.prepare(s);
    qDebug()<<"getData():"<<q.exec();
    QVector<ContactListView*>* rez = new QVector<ContactListView*>();
    while(q.next()){
        rez->append(new ContactListView(nullptr,q.value("id").toInt(),q.value("name").toString(),q.value("status").toString()));
    }
    db.close();
    return rez;
}

void ContactDB::fillModel(){
    QVector<ContactListView*>* data = getData();
    model->setData(data);
    emit modelChanged();
}


QAbstractListModel* ContactDB::getModel(){
    return model;
}

void ContactDB::insertContact(Contact* contact){
    db.open();
    QSqlQuery q;
    q.prepare("INSERT INTO Contacts (first_name,last_name,middle_name,phone_number,home_number,address,status) "
              "VALUES(:first_name,:last_name,:middle_name,:phone_number,:home_number,:address,:status)");
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

qint32 ContactDB::items(){
    db.open();
    QSqlQuery q;
    q.prepare("SELECT COUNT(id) as items, (last_name || ' ' || first_name || ' ' || middle_name) as name\
              FROM Contacts");
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

Contact* ContactDB::getContact(qint32 itemId){
    db.open();
    QSqlQuery q;
    q.prepare("SELECT * from Contacts WHERE id==:id");
    q.bindValue(":id",itemId);
    qDebug() <<"Get contact by id:"<<itemId<< q.exec();
    Contact* contact = nullptr;
    if(q.next()){
        contact=new Contact(
                nullptr,
                q.value("id").value<qint32>(),
                q.value("last_name").value<QString>(),
                q.value("first_name").value<QString>(),
                q.value("middle_name").value<QString>(),
                q.value("phone_number").value<QString>(),
                q.value("home_number").value<QString>(),
                q.value("address").value<QString>(),
                q.value("status").value<QString>()
            );
    }
    db.close();
    return contact;
}

QVector<Contact*>* ContactDB::getByStatus(QString status)
{
    db.open();
    QSqlQuery q;
    q.prepare("SELECT * from Contacts WHERE status==:status");
    q.bindValue(":status",status);
    qDebug() <<"Get contacts by status:"<<status<< q.exec();
    QVector<Contact*>* contact = new QVector<Contact*>();
    if(q.next()){
        contact->append(new Contact(
            nullptr,
            q.value("id").value<qint32>(),
            q.value("last_name").value<QString>(),
            q.value("first_name").value<QString>(),
            q.value("middle_name").value<QString>(),
            q.value("phone_number").value<QString>(),
            q.value("home_number").value<QString>(),
            q.value("address").value<QString>(),
            q.value("status").value<QString>()
            ));
    }
    db.close();
    return contact;
}

void ContactDB::editContact(Contact* contact){
    db.open();
    QSqlQuery q;
    q.prepare("UPDATE Contacts \
            SET first_name=:first_name, last_name=:last_name,\
            middle_name=:middle_name, phone_number=:phone_number,\
            home_number=:home_number, address=:address,\
            status=:status WHERE id==:id");
    q.bindValue(":id",contact->getItemId());
    q.bindValue(":first_name",contact->firstName);
    q.bindValue(":last_name",contact->lastName);
    q.bindValue(":middle_name",contact->middleName);
    q.bindValue(":phone_number",contact->phoneNumber);
    q.bindValue(":home_number",contact->homeNumber);
    q.bindValue(":address",contact->address);
    q.bindValue(":status",contact->status);
    qDebug()<<"Edit Conatct with id:"<<contact->getItemId()<<q.exec();
    db.close();
    emit dataChanged();
}

Contact* ContactDB::getEmptyContact(){
    Contact* contact=new Contact(nullptr,-1,"","","","","","","");
    return contact;
}

void ContactDB::sortByName()
{
    sort = SortBy::Name;
    emit dataChanged();
}

void ContactDB::sortByStatus()
{
    sort = SortBy::Status;
    emit dataChanged();
}

