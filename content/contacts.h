#ifndef CONTACTS_H
#define CONTACTS_H

#include <QAbstractListModel>
#include "contactlistview.h"

class Contacts : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit Contacts(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setData(QVector<ContactListView*>* data);
signals:
private:
    QVector<ContactListView*>* m_data;
};

#endif // CONTACTS_H
