#include <QFontMetrics>
#include <QTextLayout>
#include <QPainter>
#include "include/cardviewitemdelegate.h"


CardViewItemDelegate::CardViewItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void CardViewItemDelegate::drawElidedText(QPainter *painter, const QString &text,
                                              const QFont &font, const QRect &rect,
                                              Qt::TextElideMode elide_mode) const
{
    QTextLayout text_layout(text, font);
    QFontMetrics font_metrics(font);

    int line_top_offset = rect.top();

    text_layout.beginLayout();

    forever {
        QTextLine text_line = text_layout.createLine();
        if (!text_line.isValid())
            break;

        text_line.setLineWidth(rect.width());

        if (rect.bottom() >= (line_top_offset + font_metrics.lineSpacing() * 2)) {
            text_line.draw(painter, QPoint(rect.left(), line_top_offset));
            line_top_offset += font_metrics.lineSpacing();
        }
        else {
            QString last_line = text_layout.text().mid(text_line.textStart());
            QString elided_last_line =
                    font_metrics.elidedText(last_line, elide_mode, rect.width());
            painter->drawText(QPoint(rect.left(), line_top_offset + font_metrics.ascent()),
                              elided_last_line);
            break;
        }
    }
}

QPixmap CardViewItemDelegate::scaledPixmap(const QPixmap &pixmap, const QRect &target_rect) const
{
    return pixmap.scaled(target_rect.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
}

CardViewItemDelegate::~CardViewItemDelegate()
{
}
