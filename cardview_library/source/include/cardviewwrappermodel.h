#ifndef CARDVIEW_CARDVIEWWRAPPERMODEL_H
#define CARDVIEW_CARDVIEWWRAPPERMODEL_H

#include <QIdentityProxyModel>
#include "cardview_common.h"

class CardViewWrapperModelPrivate;

class CARDVIEW_EXPORT CardViewWrapperModel : public QIdentityProxyModel {
    Q_OBJECT
    Q_DECLARE_PRIVATE(CardViewWrapperModel)
public:
    enum Role {
        TitleTextRole = 0x1000,                 // QString
        InformativeTextRole,                    // QString
        PictureRole,                            // QPixmap
        CardSizeRole                            // QSize
    };
private:
    CardViewWrapperModelPrivate * const d_ptr;
public:
    explicit CardViewWrapperModel(QObject *parent = 0);
    ~CardViewWrapperModel();

    void setRoleMapping(int card_model_role, int source_model_role);
    void setRoleMappings(const QHash<int, int> &role_mapping);

    void setDefaultRoleValue(int card_model_role, const QVariant &default_value);

    QVariant data(const QModelIndex &proxy_index, int role) const;
};

#endif // CARDVIEW_CARDVIEWWRAPPERMODEL_H
