#ifndef CARDVIEW_CARDVIEWHEADERITEMDELEGATE_H
#define CARDVIEW_CARDVIEWHEADERITEMDELEGATE_H

#include "cardview_common.h"
#include "cardviewitemdelegate.h"

class CardViewHeaderItemDelegatePrivate;

class CARDVIEW_EXPORT CardViewHeaderItemDelegate : public CardViewItemDelegate {
    Q_OBJECT
    Q_DECLARE_PRIVATE(CardViewHeaderItemDelegate)

    CardViewHeaderItemDelegatePrivate * const d_ptr;
public:
    explicit CardViewHeaderItemDelegate(QObject *parent = 0);
    ~CardViewHeaderItemDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    void drawCard(QPainter *painter,
                  const QStyleOptionViewItem &option,
                  const QModelIndex &card_index) const;
};

#endif // CARDVIEW_CARDVIEWHEADERITEMDELEGATE_H
