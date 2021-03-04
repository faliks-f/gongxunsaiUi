#include "table.h"
#include <QStandardItemModel>
#include <QHeaderView>

Table::Table()
    : QTableView()
{
    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"No.", "Name", "Quantity", "Category"});
    model->setRowCount(15);
    addItem("apple", "fruits");
    model->takeRow(1);
    setModel(model);
    horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void Table::addItem(QString name, QString category)
{
    model->setItem(sequenceNumber, 0, new QStandardItem(QString("%1").arg(sequenceNumber + 1)));
    model->setItem(sequenceNumber, 1, new QStandardItem(name));
    model->setItem(sequenceNumber, 2, new QStandardItem(QString("%1").arg(1)));
    model->setItem(sequenceNumber, 3, new QStandardItem(category));
    sequenceNumber++;
}
