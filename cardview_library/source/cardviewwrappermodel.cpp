#include "include/cardviewwrappermodel.h"
#include <QHash>


class CardViewWrapperModelPrivate {
    Q_DECLARE_PUBLIC(CardViewWrapperModel)

    CardViewWrapperModel *q_ptr;
    QHash<int, int> role_mapping;
    QHash<int, QVariant> default_role_value;

    CardViewWrapperModelPrivate(CardViewWrapperModel *q) : q_ptr(q) {}
    ~CardViewWrapperModelPrivate() {}
};


CardViewWrapperModel::CardViewWrapperModel(QObject *parent) :
    QIdentityProxyModel(parent),
    d_ptr(new CardViewWrapperModelPrivate(this))
{
}

CardViewWrapperModel::~CardViewWrapperModel()
{
    delete d_ptr;
}

void CardViewWrapperModel::setRoleMapping(int card_model_role, int source_model_role)
{
    Q_D(CardViewWrapperModel);
    d->role_mapping.insert(card_model_role, source_model_role);
}

void CardViewWrapperModel::setRoleMappings(const QHash<int, int> &role_mapping)
{
    Q_D(CardViewWrapperModel);
    d->role_mapping = role_mapping;
}

void CardViewWrapperModel::setDefaultRoleValue(int card_model_role, const QVariant &default_value)
{
    Q_D(CardViewWrapperModel);
    d->default_role_value.insert(card_model_role, default_value);
}

QVariant CardViewWrapperModel::data(const QModelIndex &proxy_index, int role) const
{
    Q_D(const CardViewWrapperModel);
    if (!d->role_mapping.contains(role) && d->default_role_value.contains(role))
        return d->default_role_value.value(role, QVariant());
    return QIdentityProxyModel::data(proxy_index, d->role_mapping.value(role, role));
}
