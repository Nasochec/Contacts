#include "contacts.h"

Contacts::Contacts(QObject *parent) : QAbstractListModel(parent) {
    m_data = new QVector<ContactListView*>();
}

int Contacts::rowCount(const QModelIndex &parent) const {
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
    return QVariant();
}

void Contacts::setData(QVector<ContactListView*>* data) {
    if(m_data!=NULL &&  m_data->length()>0)
    {
        beginRemoveRows(QModelIndex(),0,m_data->length()-1);
        delete m_data;
        m_data = NULL;
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
    QHash<int, QByteArray> rez;
    for (int i = 0; i < roles.length(); i++)
        rez.insert(Qt::UserRole + i, roles[i].toUtf8());
    return rez;
}
