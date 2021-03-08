#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QTableView>
#include <QString>

class QStandardItemModel;

class Table : public QTableView
{
public:
    explicit Table();

    void addItem(QString name, QString category);

private:
    int sequenceNumber = 0;
    QStandardItemModel *model;
};

#endif // TABLE_H
