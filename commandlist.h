#ifndef TARGETLIST_H
#define TARGETLIST_H

#include <QString>
#include <QVector>
#include <QStringList>
#include <QSet>
#include <QTableWidget>

class CommandList
{
public:
    CommandList(QTableWidget *_table, QVector<QString> *_header);
    ~CommandList();
    void add_to_List(QVector<QString> *record);
    void delete_from_List();
    void clear_List();
    QString getCommand(int index, QVector<QString> names);
    QVector<QString> getRecord(int index);
    QSet<QString> getColumnSet(QString name);
    int length();
    int lastIndex();
    int rowCount();
    int columnCount();
    void setHeader(QVector<QString> *_header);
    QVector<QString> *getHeader();

private:
    void updateSets();

    QTableWidget *table;
    QVector<QString> *header;
};

#endif // TARGETLIST_H
