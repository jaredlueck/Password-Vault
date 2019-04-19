#ifndef PASSWORDDELEGATE_H
#define PASSWORDDELEGATE_H
#include "QAbstractItemDelegate"


class PasswordDelegate : public QAbstractItemDelegate
{
public:
    PasswordDelegate(QObject * parent = 0);
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual ~PasswordDelegate();
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

#endif // PASSWORDDELEGATE_H
