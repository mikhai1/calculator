#ifndef CALCULATE_H
#define CALCULATE_H

#include <map>
#include <QString>
#include <cstddef>

/*!
 * \brief Обработка и вычисление данных
 * \details Обработка данных пользователя и конвертация в файл таблицы Excel
 * \author Borisov Alexander
 * \date 17.10.2017
 * \version 0.0.1
 * \copyright MIT License
 * */
class calculate
{
public:
    /*!
     * \brief Конструктор по умолчанию
     * */
    calculate() = default;

    /*!
     * \brief Обработка данных полученных по ссылке
     * \param std::map<QString, QString> &table
     * \return void
     * */
    void calc(std::map<QString, QString> &table);

    /*!
     * \brief Получение определённого параметра по значению
     * \param QString key
     * \return QString
     * */
    QString get(QString key);

private:
    /*!
     * \brief Хранилище данных
     * */
    std::map<QString, QString> table;

    /*!
     * \brief Рассчёт зароботной платы
     * \param int value
     * \return int
     * */
    int payday(int value);
};

#endif
