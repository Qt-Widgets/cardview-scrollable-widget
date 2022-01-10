#include <QStyleOptionViewItemV4>
#include <QPainter>
#include <QPainterPath>

#include "include/cardviewwrappermodel.h"
#include "include/cardviewsimpleitemdelegate.h"


class CardViewSimpleItemDelegatePrivate {
    Q_DECLARE_PUBLIC(CardViewSimpleItemDelegate)

    CardViewSimpleItemDelegate *q_ptr;
    QMargins card_margins;
    QMargins card_text_margins;
    QMargins card_picture_margins;

    CardViewSimpleItemDelegatePrivate(CardViewSimpleItemDelegate *q) : q_ptr(q) {}
    ~CardViewSimpleItemDelegatePrivate() {}
};


CardViewSimpleItemDelegate::CardViewSimpleItemDelegate(QObject *parent) :
    CardViewItemDelegate(parent),
    d_ptr(new CardViewSimpleItemDelegatePrivate(this))
{
    Q_D(CardViewSimpleItemDelegate);
    d->card_margins = QMargins(10, 10, 10, 10);
    d->card_text_margins = QMargins(20, 10, 20, 10);
    d->card_picture_margins = QMargins();
}

CardViewSimpleItemDelegate::~CardViewSimpleItemDelegate()
{
    delete d_ptr;
}

void CardViewSimpleItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const
{
    drawCard(painter, option, index);
}

QSize CardViewSimpleItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);

    Q_D(const CardViewSimpleItemDelegate);

    QSize card_size = index.data(CardViewWrapperModel::CardSizeRole).toSize();
    card_size.rwidth() += d->card_margins.left() + d->card_margins.right();
    card_size.rheight() += d->card_margins.top() + d->card_margins.bottom();

    return card_size;
}

void CardViewSimpleItemDelegate::drawCard(QPainter *painter, const QStyleOptionViewItem &option,
                                      const QModelIndex &card_index) const
{
    Q_D(const CardViewSimpleItemDelegate);

    QStyleOptionViewItemV4 view_item_option = option;
    initStyleOption(&view_item_option, card_index);

    // setup fonts and colors
    QFont title_text_font = view_item_option.font;
    title_text_font.setBold(true);
    title_text_font.setPointSize(title_text_font.pointSize() + 6);

    QFont informative_text_font = view_item_option.font;
    informative_text_font.setPointSize(informative_text_font.pointSize() - 1);

    QColor title_font_color = view_item_option.palette.text().color();
    QColor informative_text_color = view_item_option.palette.text().color();

    QBrush card_background_brush = view_item_option.palette.base();
    QBrush card_shadow_brush = QBrush(QColor(0, 0, 0, 50));
    QBrush selection_brush = view_item_option.palette.highlight();
    QBrush disabled_brush = QBrush(QColor(255, 255, 255, 50));

    // calculate sub rectangles
    QRect card_rect = option.rect;
    card_rect.adjust(d->card_margins.left(), d->card_margins.top(),
                     -d->card_margins.right(), -d->card_margins.bottom());

    QRect card_shadow_rect = card_rect.translated(3, 3);

    QRect selection_rect = card_rect.adjusted(-4, -4, 4, 4);

    QRect picture_rect = QRect(card_rect.left(), card_rect.top(),
                               card_rect.width(), card_rect.height() * 0.50);

    QRect title_text_rect = QRect(card_rect.left(), picture_rect.bottom(),
                                  card_rect.width(), card_rect.height() * 0.10);

    QRect informative_text_rect = QRect(card_rect.left(), title_text_rect.bottom(),
                                        card_rect.width(), card_rect.height() * 0.40);
    informative_text_rect.setBottom(card_rect.bottom());


    // apply margins
    title_text_rect.adjust(d->card_text_margins.left(), d->card_text_margins.top(),
                           -d->card_text_margins.right(), -d->card_text_margins.bottom());
    informative_text_rect.adjust(d->card_text_margins.left(), d->card_text_margins.top(),
                                 -d->card_text_margins.right(), -d->card_text_margins.bottom());
    picture_rect.adjust(d->card_picture_margins.left(), d->card_picture_margins.top(),
                        -d->card_picture_margins.right(), -d->card_picture_margins.bottom());

    // draw delegate
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);

    if (view_item_option.state & QStyle::State_Selected) {
        painter->fillRect(selection_rect, selection_brush);
    }
    else {
        QPainterPath card_shadow_rounded_rect;
        card_shadow_rounded_rect.addRoundedRect(card_shadow_rect, 5, 5);
        painter->fillPath(card_shadow_rounded_rect, card_shadow_brush);
    }

    painter->setRenderHint(QPainter::Antialiasing, false);

    painter->fillRect(card_rect, card_background_brush);

    QPixmap card_pixmap = scaledPixmap(card_index.data(CardViewWrapperModel::PictureRole).value<QPixmap>(),
                                       picture_rect);
    painter->drawImage(picture_rect, card_pixmap.toImage());

    painter->setFont(title_text_font);
    painter->setPen(title_font_color);

    drawElidedText(painter, card_index.data(CardViewWrapperModel::TitleTextRole).toString(),
                   title_text_font, title_text_rect, view_item_option.textElideMode);

    painter->setFont(informative_text_font);
    painter->setPen(informative_text_color);

    drawElidedText(painter, card_index.data(CardViewWrapperModel::InformativeTextRole).toString(),
                   informative_text_font, informative_text_rect, view_item_option.textElideMode);

    if ((view_item_option.state & QStyle::State_Enabled) == 0)
        painter->fillRect(card_rect, disabled_brush);

    painter->restore();
}
