#ifndef CARDVIEW_CARDVIEW_H
#define CARDVIEW_CARDVIEW_H

#include <QListView>
#include "cardview_common.h"

class CARDVIEW_EXPORT CardView : public QListView {
    Q_OBJECT
public:
    explicit CardView(QWidget *parent = 0);
    ~CardView();
};

#endif // CARDVIEW_H
