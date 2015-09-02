#include "commandlist.h"

CommandList::CommandList(QTableWidget *_table, QVector<QString> *_header)
{
    table = _table;
    header = _header;
    table->setRowCount(0);
    table->setColumnCount(header->length());
    table->setHorizontalHeaderLabels(header->toList());
}

CommandList::~CommandList()
{

}

void CommandList::add_to_List(QVector<QString> *record)
{
    table->setRowCount(table->rowCount()+1);
    for (int col = 0; col < record->length(); col++) {
        QString item = record->value(col);
        QTableWidgetItem *newItem = new QTableWidgetItem(item, 0);
        table->setItem(table->rowCount()-1,col,newItem);
    }
}

void CommandList::clear_List()
{
    for(int row = 0; row < table->rowCount(); row++) {
        for (int col = 0; col < table->columnCount(); col++) {
            table->removeCellWidget(row,col);
        }
    }
    table->setRowCount(0);
}

QVector<QString> CommandList::getRecord(int row)
{
    QVector<QString> record;
    for (int col = 0; col < table->columnCount(); col++) {
        record << table->item(row, col)->text();
    }
    return record;
}

QSet<QString> CommandList::getColumnSet(QString name)
{
    QSet<QString> columnSet;
    int col = header->indexOf(name);
    for (int row = 0; row < table->rowCount(); row++) {
        columnSet << table->item(row, col)->text();
    }
    return columnSet;
}

int CommandList::length()
{
    return table->rowCount();
}

int CommandList::lastIndex()
{
    return table->rowCount()-1;
}

QString CommandList::getCommand(int row, QVector<QString> names)
{
    QStringList command;
    for (int col = 0; col < names.length(); col++) {
        command << table->item(row, header->indexOf(names[col]))->text();
    }
    return command.join(' ').replace("/", "\\");
}

int CommandList::rowCount()
{
    return table->rowCount();
}

int CommandList::columnCount()
{
    return table->columnCount();
}

void CommandList::setHeader(QVector<QString> *_header)
{
    header = _header;
}

QVector<QString> *CommandList::getHeader()
{
    return header;
}
