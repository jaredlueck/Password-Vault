#include "passworddelegate.h"
#include <QPen>
#include <QPainter>

PasswordDelegate::PasswordDelegate(QObject* parent)
{

}

void PasswordDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index)const
{
    QRect rect = option.rect;

    QPen linePen(QColor::fromRgb(211,211,211), 1, Qt::SolidLine);

    painter->setPen(linePen);
    painter->drawLine(rect.topLeft(),rect.topRight());
    painter->drawLine(rect.topRight(),rect.bottomRight());
    painter->drawLine(rect.bottomLeft(),rect.bottomRight());
    painter->drawLine(rect.topLeft(),rect.bottomLeft());

    QPen fontPen(QColor::fromRgb(51,51,51), 1, Qt::SolidLine);

    painter->setPen(fontPen);

    QString username = index.data(Qt::DisplayRole).toString();
    QString password = index.data(Qt::UserRole + 1).toString();
    QString website = index.data(Qt::UserRole + 2).toString();

    QRect r = option.rect.adjusted(10,5, -10 , -30);
    painter->setFont( QFont( "Lucida Grande", 11, QFont::Normal ) );
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignLeft, "Website: " + website, &r);

    r = option.rect.adjusted(10, 25, -10, 20);
    painter->setFont( QFont( "Lucida Grande", 11, QFont::Normal ) );
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignLeft, "usename: " + username, &r);


    r = option.rect.adjusted(10, 45, -10, 70);
    painter->setFont( QFont( "Lucida Grande", 11, QFont::Normal ) );
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignLeft, "password: " + password, &r);

    bool hover = option.state & QStyle::State_MouseOver;
    if (hover) {
        painter->fillRect(rect, QColor(0,0,0,10));
    }


}

QSize PasswordDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const{
        return QSize(100, 80);
}

PasswordDelegate::~PasswordDelegate(){}

