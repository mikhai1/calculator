#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QFile>
#include <QMessageBox>
#include <QToolBar>
#include <QToolButton>
#include <QMenuBar>
#include <QRegExp>
#include <QLineEdit>
#include <fstream>
#include <map>
#include <QTranslator>

#include "calculate.h"

/*!
 * \brief Пользовательский интерфейс
 * \details Пространсво имён для ограничения пользовательского интерфейса
 * \author Borisov Alexander
 * \date 17.10.2017
 * \version 0.0.1
 * \copyright MIT License
 * */
namespace Ui {
    class MainWindow;
}

/*!
 * \brief Пользовательский интерфейс
 * \details Обработка пользовательского интерфеса и взаимодействие с библиотеками
 * \author Borisov Alexander
 * \date 17.10.2017
 * \version 0.0.1
 * \copyright MIT License
 * */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param QWidget *parent
     * \default parent = 0
     */
    explicit MainWindow(QWidget *parent = 0);
    /*!
     * \brief Конструктор
     */
    ~MainWindow();

    /*!
     * \brief Состояние формы(с НДС или Без НДС)
     * \warning Так делать нельзя, это нарушает правила ООП, пре свойства объекта обязаны быть private
     * */
    bool formState;
protected:
    /*!
     * \brief Обработчик событий
     * \param QEvent* event
     * \return void
     * */
    void changeEvent(QEvent *event);

    /*!
     * \brief Создание языкового меню
     * \return void
     * */
    void createLanguageMenu(QMenu *languageMenu);
private slots:
    /*!
     * \brief Событие принажатии кнопки "С НДС"
     * \return void
     */
    void on_action_triggered();

    /*!
     * \brief Событие принажатии кнопки "Без НДС"
     */
    void on_action_2_triggered();

    /*!
     * \brief Событие принажатии кнопки "Конвертировать"
     * \return void
     */
    void action_convert();

    /*!
     * \brief Вызываем messagebox для соответвующей кнопки
     * \return void
     */
    void action_aboutProgram();

    /*!
     * \brief Вызываем messagebox для соответвующей кнопки
     * \return void
     */
    void action_reference();

    /*!
     * \brief Вызываем messagebox для соответвующей кнопки
     * \return void
     */
    void action_language();

    /*!
     * \brief Вызываем messagebox для соответвующей кнопки
     * \return void
     */
    void on_pushButton_clicked();

    /*!
     * \brief Событие при изменении языка программы
     * \param QAction* action
     * \return void
     * */
    void slotLanguageChanged(QAction *action);
private:
    /*!
     * \brief Указатель на экземпляр текущего класса
     */
    Ui::MainWindow *ui;

    /*!
     * \brief Указатель на экземпляр класса "calculate"
     */
    calculate *calc;

    /*!
     * \brief Создание меню
     */
    void createAction();

    /*!
     * \brief Создание таблицы
     */
    void createTableWidget();

    /*!
     * \brief Запрет ввода ненужных символов
     */
    void protectionFromTheFool();

    /*!
     * \brief Словарь с текстом для различных языков
     */
    QTranslator translator;

    /*!
     * \brief Индентификатор для текущего языка
     */
    QString cLang;

    /*!
     * Загрузка языка
     * */
    void loadLanguage(const QString& lang);
};

#endif // MAINWINDOW_H
