#include "gendercelldelegate.h"

GenderCellDelegate::GenderCellDelegate(int genderColumn, QObject *parent)
    : QSqlRelationalDelegate(parent)
{
    this->genderColumn=genderColumn;
}

void GenderCellDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == genderColumn) {
        const QAbstractItemModel *auxmodel = index.model();
        if (auxmodel->data(index,Qt::DisplayRole).toInt()==0){
            painter->drawText(option.rect, tr("Masculino"));
        } else {
            painter->drawText(option.rect, tr("Femenino"));
        }
    } else {
        QSqlRelationalDelegate::paint(painter, option, index);
    }
}



void GenderCellDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.column() == genderColumn) {
        const QAbstractItemModel *auxmodel = index.model();
        if (auxmodel->data(index,Qt::DisplayRole).toInt()==0){
            model->setData(index, "Masculino");
        } else {
            model->setData(index, "Femenino");
        }
    } else {
        QSqlRelationalDelegate::setModelData(editor, model, index);
    }
}



