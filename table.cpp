#include "table.h"
#include <QStandardItemModel>
#include <QHeaderView>
#include <QStandardItem>
#include <QList>
#include <QDebug>

Table::Table()
    : QTableView()
{
    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"序号", "垃圾名称", "数量", "垃圾类别"});
    model->setRowCount(15);
    setModel(model);
    horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void Table::addItem(QString name, QString category)
{
    for (int i = 0; i < sequenceNumber; ++i)
    {
        QStandardItem *rowName = model->item(i, 1);
        qDebug() << rowName->text();
        if (rowName->text() == name)
        {
            QStandardItem *number = model->item(i, 2);
            QString string = number->text();
            number->setText(QString("%1").arg(string.toInt() + 1));
            return;
        }
    }
    QString category_ = QString("【%1】").arg(category);
    model->setItem(sequenceNumber, 0, new QStandardItem(QString("%1").arg(sequenceNumber + 1)));
    model->setItem(sequenceNumber, 1, new QStandardItem(name));
    model->setItem(sequenceNumber, 2, new QStandardItem(QString("%1").arg(1)));
    model->setItem(sequenceNumber, 3, new QStandardItem(category_));
    sequenceNumber++;
}
