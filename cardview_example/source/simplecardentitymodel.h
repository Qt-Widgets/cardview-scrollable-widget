#ifndef SIMPLECARDENTITYMODEL_H
#define SIMPLECARDENTITYMODEL_H

#include <QPixmap>
#include <QAbstractListModel>

class SimpleCardEntityModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Role {
        TitleRole = Qt::UserRole,
        InformativeTextRole,
        PictureRole
    };

    struct SimpleCardEntity {
        QString title;
        QString informative_text;
        QPixmap picture;
    };
private:
    QList<SimpleCardEntity> m_entities;
public:
    explicit SimpleCardEntityModel(QObject *parent = 0);
    ~SimpleCardEntityModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void setEntities(const QList<SimpleCardEntity> entities);

    void initTestData(int size = 10);
};

#endif // SIMPLECARDENTITYMODEL_H
