#ifndef GENDERITEMDELEGATE_H
#define GENDERITEMDELEGATE_H

#include <QItemDelegate>

class GenderItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit GenderItemDelegate(QObject *parent = 0);
    GenderItemDelegate(int genderColumn, QObject *parent = 0);
    
signals:
    
public slots:
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private :
    int genderColumn;
};

#endif // GENDERITEMDELEGATE_H
