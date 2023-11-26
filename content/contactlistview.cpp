#include "contactlistview.h"

ContactListView::ContactListView(QObject *parent,qint32 itemId,QString name,QString status)
    : QObject{parent}
{
    m_itemId=itemId;
    m_name=name;
    m_status=status;
}


qint32 ContactListView::getItemId() const { return m_itemId; }

QString ContactListView::getName() const { return m_name; }

QString ContactListView::getStatus() const { return m_status; }
