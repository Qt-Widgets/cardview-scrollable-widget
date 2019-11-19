#ifndef CARDVIEW_CARDVIEWSIMPLEITEMDELEGATE_H
#define CARDVIEW_CARDVIEWSIMPLEITEMDELEGATE_H

#include "cardview_common.h"
#include "cardviewitemdelegate.h"

class CardViewSimpleItemDelegatePrivate;

class CARDVIEW_EXPORT CardViewSimpleItemDelegate : public CardViewItemDelegate {
    Q_OBJECT
    Q_DECLARE_PRIVATE(CardViewSimpleItemDelegate)

    CardViewSimpleItemDelegatePrivate * const d_ptr;
public:
    explicit CardViewSimpleItemDelegate(QObject *parent = 0);
    ~CardViewSimpleItemDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    void drawCard(QPainter *painter,
                  const QStyleOptionViewItem &option,
                  const QModelIndex &card_index) const;
};

#endif // CARDVIEW_CARDVIEWSIMPLEITEMDELEGATE_H
