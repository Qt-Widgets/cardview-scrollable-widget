#include "simplecardentitymodel.h"


SimpleCardEntityModel::SimpleCardEntityModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

SimpleCardEntityModel::~SimpleCardEntityModel()
{
}

int SimpleCardEntityModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_entities.size();
}

QVariant SimpleCardEntityModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
        case Qt::DisplayRole:
        case Qt::ToolTipRole:
        case TitleRole:
            return m_entities.at(index.row()).title;
        case InformativeTextRole:
            return m_entities.at(index.row()).informative_text;
        case PictureRole:
            return m_entities.at(index.row()).picture;
        default:
            break;
    }

    return QVariant();
}

Qt::ItemFlags SimpleCardEntityModel::flags(const QModelIndex &index) const
{
    if (index.row() % 4 == 1)
        return Qt::NoItemFlags;
    return (Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

void SimpleCardEntityModel::setEntities(const QList<SimpleCardEntityModel::SimpleCardEntity> entities)
{
    beginResetModel();
    m_entities = entities;
    endResetModel();
}

void SimpleCardEntityModel::initTestData(int size)
{
    QString title_template = "Card View Entity %1";
    QString informative_text_template =
            "The QIdentityProxyModel class proxies its source model unmodified. "
            "QIdentityProxyModel can be used to forward the structure of a source model exactly, "
            "with no sorting, filtering or other transformation. "
            "This is similar in concept to an identity matrix where A.I = A. "
            "Because it does no sorting or filtering, this class is most suitable to proxy models "
            "which transform the data() of the source model. For example, a proxy model could be "
            "created to define the font used, or the background colour, or the tooltip etc. "
            "This removes the need to implement all data handling in the same class that creates "
            "the structure of the model, and can also be used to create re-usable components. "
            "This also provides a way to change the data in the case where a source model is "
            "supplied by a third party which can not be modified.";
    QPixmap picture_template = QPixmap("://resource/pixmap/cardimage_free_size.jpg");

    QString disabled_title_template = "Disabled card %1";
    QString disabled_informative_text_template =
            "Informative text for disabled card.";
    QPixmap disabled_picture_template = QPixmap("://resource/pixmap/cardimage_300_150.jpg");


    beginResetModel();

    m_entities.clear();

    for (int i = 0; i < size; ++ i) {
        SimpleCardEntity entity;
        if (i % 4 == 1) {
            entity.title = disabled_title_template.arg(i + 1);
            entity.informative_text = disabled_informative_text_template;
            entity.picture = disabled_picture_template;
        }
        else {
            entity.title = title_template.arg(i + 1);
            entity.informative_text = informative_text_template;
            entity.picture = picture_template;
        }

        m_entities.append(entity);
    }

    endResetModel();
}
