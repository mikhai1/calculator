#include "calculate.h"

void calculate::calc(std::map<QString, QString> &data)
{
    table = data;
    table.insert({"time", QString::number(payday(table["payday"].toInt()))});
}

QString calculate::get(QString key)
{
    return (table.find(key) != table.end()) ?
                table[key] :
                QString();
}

int calculate::payday(int value)
{
    /*!
     * \todo Разработать вычисление заработной платы
     * */
    return value * value;
}
