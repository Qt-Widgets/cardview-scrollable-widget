#include "include/cardview.h"


CardView::CardView(QWidget *parent) :
    QListView(parent)
{
    setFlow(QListView::LeftToRight);
    setResizeMode(QListView::Adjust);
    setWrapping(true);
    viewport()->setBackgroundRole(QPalette::Window);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

CardView::~CardView()
{
}
