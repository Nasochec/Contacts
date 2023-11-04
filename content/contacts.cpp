#include "contacts.h"

Contacts::Contacts(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant Contacts::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int Contacts::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

bool Contacts::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

bool Contacts::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void Contacts::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

QVariant Contacts::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
