#include "actions.h"
#include "contactDB.h""
#include <QFile>
#include <QDebug>
#include <QFlags>
#include <string>
#include <string.h>

Actions::Actions(QObject *parent)
    : QObject{parent}
{

}


Contact* Actions::getEmptyContact(){
    Contact* contact=new Contact(nullptr,-1,"","","","","","","");
    return contact;
}

void Actions::invite(QString status,QString eventName){
    ContactDB* db = ContactDB::instance;
    QVector<Contact*>* contacts = db->getByStatus(status);
    for(int i=0;i<contacts->size();++i){
        Contact* contact = contacts->at(i);
        QFile* f = new QFile(std::to_string(i).append(".txt").c_str());
        qDebug()<<std::to_string(i).append(".txt").c_str();
        f->open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(f);
        out << "Здравствуйте, " << contact->firstName<<" "<<contact->middleName<<" "<<contact->lastName
            <<". Приглашаю вас на"<<eventName << ".";

        f->close();
    }

}
