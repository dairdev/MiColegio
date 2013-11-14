#include "genderitemdelegate.h"

#include <Qt/qcombobox.h>

GenderItemDelegate::GenderItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

GenderItemDelegate::GenderItemDelegate(int genderColumn, QObject *parent):
    QItemDelegate(parent)
{
    this->genderColumn=genderColumn;
}

void GenderItemDelegate::setEditorData (QWidget * editor, const QModelIndex & index ) const {
    if(index.column() == genderColumn) {
        QComboBox *combobox = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(combobox);
        if(index.data().toString() == "0") {
           combobox->setCurrentIndex(0);
        } else {
           combobox->setCurrentIndex(1);
        }
    } else {
        QItemDelegate::setEditorData(editor, index);
    }
}

void GenderItemDelegate::setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const {
    if(index.column() == genderColumn) {
        QComboBox *combobox = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(combobox);
        if(combobox->currentIndex() == 0) {
           model->setData(index, "Masculino");
        } else {
           model->setData(index, "Femenino");
        }
    } else {
        QItemDelegate::setModelData(editor, model, index);
    }
}
