#include <QApplication>

#include "cardview.h"
#include <cardviewwrappermodel.h>
#include <cardviewsimpleitemdelegate.h>
#include <cardviewheaderitemdelegate.h>

#include "simplecardentitymodel.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // initializing CardView widget
    CardView *card_view = new CardView();
    card_view->setWindowTitle("Card View Example");
    card_view->setAttribute(Qt::WA_DeleteOnClose);
    card_view->resize(1000, 800);

    // initializing test source model
    SimpleCardEntityModel entity_model;
    entity_model.initTestData(20);

    // creating card view wrapper proxy model
    CardViewWrapperModel *wrapper_model = new CardViewWrapperModel(card_view);

    // set source model
    wrapper_model->setSourceModel(&entity_model);

    // setup mapping between CardWrapperModel and source model roles
    wrapper_model->setRoleMapping(CardViewWrapperModel::TitleTextRole,
                                  SimpleCardEntityModel::TitleRole);
    wrapper_model->setRoleMapping(CardViewWrapperModel::InformativeTextRole,
                                  SimpleCardEntityModel::InformativeTextRole);
    wrapper_model->setRoleMapping(CardViewWrapperModel::PictureRole,
                                  SimpleCardEntityModel::PictureRole);

    // set default value for roles which aren't provided by source model
    wrapper_model->setDefaultRoleValue(CardViewWrapperModel::CardSizeRole,
                                       QSize(300, 300));

    // set wrapper model to CardView
    card_view->setModel(wrapper_model);

    // choose item delegate
//    card_view->setItemDelegate(new CardViewSimpleItemDelegate(card_view));
    card_view->setItemDelegate(new CardViewHeaderItemDelegate(card_view));

    card_view->show();

    return app.exec();
}
