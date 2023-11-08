#include "contacts.h"

Contacts::Contacts(QObject *parent) : QAbstractListModel(parent) {
    m_data = new QVector<ContactListView*>();
}

int Contacts::rowCount(const QModelIndex &parent) const {
    // For list models only the root node (an invalid parent) should return the
    // list's size. For all other (valid) parents, rowCount() should return 0 so
    // that it does not become a tree model.
    if (parent.isValid())
        return 0;
    if(m_data == NULL)
        return 0;
    return m_data->length();
}

QVariant Contacts::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    switch (role) {
    case Qt::UserRole :
        return m_data->at(index.row())->getItemId();
    case Qt::UserRole +1:
        return m_data->at(index.row())->getName();
    case Qt::UserRole +2:
        return m_data->at(index.row())->getStatus();
    default:
        break;
    }
//    case Qt::UserRole :
//        return m_data[index.row()].getItemId();
//    case Qt::UserRole +1:
//        return m_data[index.row()].getFirstName();
//    case Qt::UserRole +2:
//        return m_data[index.row()].getLastName();
//    case Qt::UserRole +3:
//        return m_data[index.row()].getMiddleName();
//    case Qt::UserRole +4:
//        return m_data[index.row()].getPhoneNumber();
//    case Qt::UserRole +5:
//        return m_data[index.row()].getHomeNumber();
//    case Qt::UserRole +6:
//        return m_data[index.row()].getAddress();
//    case Qt::UserRole +7:
//        return m_data[index.row()].getStatus();
//    default:
//        break;
//    }
    return QVariant();
}

void Contacts::setData(QVector<ContactListView*>* data) {
    if(m_data->length()>0)
    {
        beginRemoveRows(QModelIndex(),0,m_data->length()-1);
        delete m_data;
        m_data=NULL;
        endRemoveRows();
    }
    if(data->length()>0){
        beginInsertRows(QModelIndex(),0,data->length()-1);
        m_data = data;
        endInsertRows();
        qDebug()<<data;
    }
}

QHash<int, QByteArray> Contacts::roleNames() const {
    QVector<QString> roles = QVector<QString>{"itemId", "name", "status"};
    //        QVector<QString>{"itemId",      "firstname",  "lastName",
    //        "middleName","phoneNumber", "homeNumber", "address",
    //                         "status"};
    QHash<int, QByteArray> rez;
    for (int i = 0; i < roles.length(); i++)
        rez.insert(Qt::UserRole + i, roles[i].toUtf8());
    return rez;
}
