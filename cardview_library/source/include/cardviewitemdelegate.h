#ifndef CARDVIEW_CARDVIEWITEMDELEGATE_H
#define CARDVIEW_CARDVIEWITEMDELEGATE_H

#include <QStyledItemDelegate>
#include "cardview_common.h"

class CARDVIEW_EXPORT CardViewItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
protected:
    explicit CardViewItemDelegate(QObject *parent = 0);

    void drawElidedText(QPainter *painter, const QString &text, const QFont &font,
                        const QRect &rect, Qt::TextElideMode elide_mode) const;

    QPixmap scaledPixmap(const QPixmap &pixmap, const QRect &target_rect) const;

    virtual void drawCard(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &card_index) const = 0;
public:
    virtual ~CardViewItemDelegate();
};

#endif // CARDVIEW_CARDVIEWITEMDELEGATE_H
