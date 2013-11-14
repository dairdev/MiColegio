#ifndef GENDERCELLDELEGATE_H
#define GENDERCELLDELEGATE_H

#include <QModelIndex>
#include <QSqlRelationalDelegate>
#include <QPainter>
#include <QStaticText>
#include <QTextOption>

QT_FORWARD_DECLARE_CLASS(QPainter)

class GenderCellDelegate : public QSqlRelationalDelegate
{
public:
    GenderCellDelegate(int genderColumn,QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private:
    int genderColumn;
};

#endif // GENDERCELLDELEGATE_H
