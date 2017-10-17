#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>

void switchTranslator(QTranslator& translator, const QString& filename)
{
    //! Удаления предыдущего перевода
    qApp->removeTranslator(&translator);

    //! Загрузка нового перевода
    if(translator.load(filename))
    qApp->installTranslator(&translator);
}

/*!
 *\brief Состояния форм
 */
enum {
    //! С НДС
    NDS,
    //! Без НДС
    WITHOUTNDS
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    calc(new calculate)
{
    ui->setupUi(this);    


    //! \brief Чтение файла стилей
    QFile styleF;
    styleF.setFileName(":/qss/style.qss");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();

    //! \brief Подключение стилей
    qApp->setStyleSheet(qssStr);


    //! \brief  Создание Action в MenuBar
    createAction();


    //! \brief  Создаем таблицу
    createTableWidget();

    //! \brief  Защита от дурака
    protectionFromTheFool();
}


void MainWindow::createAction()
{
    //! \brief Создание QAction в menuBar
    QAction* convert = new QAction(this->tr("Конвертировать", "сonvert"), this);
    QAction* aboutProgram = new QAction(this->tr("О программе", "about"), this);
    QAction* reference = new QAction(this->tr("Справка", "help"), this);

    //! \brief Создание QMenu в menuBar
    QMenu* languageMenu = ui->menuBar->addMenu(this->tr("Язык", "language"));

    createLanguageMenu(languageMenu);

    ui->menuBar->addAction(convert);
    ui->menuBar->addAction(aboutProgram);
    ui->menuBar->addAction(reference);

    //! \brief Нажатие на Action
    connect(convert, SIGNAL(triggered()), this, SLOT(action_convert()));
    connect(aboutProgram, SIGNAL(triggered()), this, SLOT(action_aboutProgram()));
    connect(reference, SIGNAL(triggered()), this, SLOT(action_reference()));
}

void MainWindow::createTableWidget()
{
    //  Создаем таблицу
    ui->tableWidget->setRowCount(15);
    ui->tableWidget->setColumnCount(2);

    //  Разрешаем выделение только одного элемента
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    //  Устанавливаем заголовки колонок
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()
                                                  << "Код КБК РФ"
                                                  << "(Атомат)г.руб");
    //  Устанавливаем заголовки строк
    ui->tableWidget->setVerticalHeaderLabels(QStringList()
                                                << "Заработная плата"
                                                << "Начисления выплаты по оплате труда"
                                                << "Прочие выплаты (суточные)"
                                                << "Комунальные услуги"
                                                << "Увеличение стоимости основных средств"
                                                << "Увеличение стоимости материальных запасов"
                                                << "Транспортные услуги"
                                                << "Прочие услуги (прожив., команд.)"
                                                << "Прямые затраты"
                                                <<"Накладные расходы"
                                                << "Себестоисость работы"
                                                << "Прибыль"
                                                << "Сумма без НДС"
                                                << "НДС"
                                                << "Договорная цена с НДС");
     // Графический костыль
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);


    // Вставляем в ячейки QLineEdit
    QRegExp exp("[1-9]{40}");
    QLineEdit *edit;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
          for(int j = 0; j < ui->tableWidget->columnCount(); j++)
          {
            edit = new QLineEdit();
            edit->setAlignment(Qt::AlignCenter);
            edit->setValidator(new QRegExpValidator(exp, this));
            if(j == 0 && i >= 0 && i <= 6)
            {
                edit->setDisabled(true);
                edit->setText("123");
                edit->setStyleSheet("QLineEdit {font-weight: bold; color: #333;}");
            }
            ui->tableWidget->setCellWidget(i, j, edit); // вставляем ячейку
          }
}

void MainWindow::on_action_triggered()
{
    this->formState = WITHOUTNDS;

    //! \brief Показать строку
    ui->tableWidget->setRowHidden(13, false);
    ui->tableWidget->setRowHidden(14, false);

    //! \brief Графический костыль
    ui->tableWidget->setMinimumHeight(330);
    ui->tableWidget->setMaximumHeight(330);

}

void MainWindow::on_action_2_triggered()
{
    this->formState = NDS;

    //! \brief Скрыть строку
    ui->tableWidget->setRowHidden(13, true);
    ui->tableWidget->setRowHidden(14, true);

    //! \brief Графический костыль
    ui->tableWidget->setMinimumHeight(290);
    ui->tableWidget->setMaximumHeight(290);
}

void MainWindow::action_convert()
{
    //! \todo Написать экспорт в файл таблицы Excel
    close();
}

void MainWindow::action_aboutProgram()
{
    QMessageBox msg;
    msg.setText("​Сметный калькулятор работает в двух"
             "режимах: с НДС (по умолчанию) и без"
             "НДС. Сменить режим можно в шапке "
             "программы."
             "Работает с входными данными, "
             "которые вводит пользователь в "
             "основные поля для ввода \"Договорная"
             "цена (с НДС)\" или же \"Сумма без НДС\""
             "а также с учетом других расходов."
             "Кроме того для корректного создания сметы необходимо "
             "ввести контактные данные, такие как: должность "
             "руководителя, наименование, ФИО руководителя "
             "орагинизации; номер договора, руководителя, "
             "подразделение, тему и срок.");
    msg.setWindowTitle("О программе");
    msg.exec();
}

void MainWindow::action_reference()
{
    QMessageBox msg;
    msg.setText("​Сметный калькулятор \n"
                "Версия 1.0.0 \n"
                "\n"
                "Разработано студентами 15-СБК \n"
                "Потом и кровью");
    msg.setWindowTitle("Справка");

    msg.exec();
}

void MainWindow::action_language()
{
    QMessageBox msg;
    msg.setText("​Сметный калькулятор \n"
                "Версия 1.0.0 \n"
                "\n"
                "Разработано студентами 15-СБК \n"
                "Потом и кровью");
    msg.setWindowTitle("Справка");

    msg.exec();
}

void MainWindow::protectionFromTheFool()
{
    //! \brief Только буквы
    QRegExp exp("[a-zA-zа-яА-я ]{40}");

    //! \brief Только цифры
    QRegExp exp2("[1-9]{40}");

    //! \brief Цифры и буквы
    QRegExp exp3("[a-zA-Zа-яА-Я1-9 ]{40}");

    //! \brief Для должности руководителя
    ui->position->setValidator(new QRegExpValidator(exp, this));

    //! \brief Для наименновании организации
    ui->nameCompany->setValidator(new QRegExpValidator(exp3, this));

    //! \brief Фамилия Имя Отчество
    ui->fullName->setValidator(new QRegExpValidator(exp, this));

    //! \brief Номер договора
    ui->contractNumber->setValidator(new QRegExpValidator(exp2, this));

    //! \brief Руководитель
    ui->chief->setValidator(new QRegExpValidator(exp, this));

    //! \brief Подразделение
    ui->subdivision->setValidator(new QRegExpValidator(exp, this));

    //! \brief Тема
    ui->subject->setValidator(new QRegExpValidator(exp, this));

    //! \brief Срок
    ui->time_1->setValidator(new QRegExpValidator(exp2, this));
    ui->time_2->setValidator(new QRegExpValidator(exp2, this));

    //! \brief Главный бухгалтер
    ui->accountant->setValidator(new QRegExpValidator(exp, this));

    //! \brief Руководитель
    ui->manager->setValidator(new QRegExpValidator(exp, this));
}

void MainWindow::loadLanguage(const QString &lang)
{
    if(cLang != lang) {
        cLang = lang;
        QLocale locale = QLocale(cLang);
        QLocale::setDefault(locale);
        QString languageName = QLocale::languageToString(locale.language());
        switchTranslator(translator, QString("TranslationExample_%1.qm").arg(lang));
        ui->statusBar->showMessage(tr("Current Language changed to %1").arg(languageName));
    }
}

void MainWindow::slotLanguageChanged(QAction* action)
{
    if(0 != action) {
        loadLanguage(action->data().toString());
    }
}

void MainWindow::on_pushButton_clicked()
{
    std::map<QString, QString> table;
    table["payday"] = ((QLineEdit *)ui->tableWidget->cellWidget(0,1))->text();

    calc->calc(table);

    ui->time_2->setText(table.at("payday"));

    ui->time_1->setText(calc->get("time"));
}

void MainWindow::createLanguageMenu(QMenu* languageMenu)
{
    connect(languageMenu, SIGNAL(triggered(QAction *)), this, SLOT(slotLanguageChanged(QAction *)));

    /*!
     * \brief Обработка названия системного языка
     * \example "de_DE"
     * */
    QString defaultLocale = QLocale::system().name();

    /*!
     * \example "de"
     * */
    defaultLocale.truncate(defaultLocale.lastIndexOf('_'));

    QString langPath = QApplication::applicationDirPath();
    langPath.append("/languages");
    QDir dir(langPath);
    QStringList fileNames = dir.entryList(QStringList("*.qm"));

    for (int i = 0; i < fileNames.size(); ++i) {
        //! \brief Индентификатор языка
        QString locale = fileNames[i];
        locale.truncate(locale.lastIndexOf('.'));
        locale.remove(0, locale.indexOf('_') + 1);

        QString lang = QLocale::languageToString(QLocale(locale).language());

        QAction *action = new QAction(lang, this);
        action->setCheckable(true);
        action->setData(locale);
        languageMenu->addAction(action);

        //! Установка стандартного перевода и языка
        if(defaultLocale == locale) {
            action->setChecked(true);
        }
    }
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event != 0 && event->type() != QEvent::None) {
        switch(event->type()) {
            //! \brief Событие при окончании загрузки перевода
            case QEvent::LanguageChange:
                ui->retranslateUi(this);
                break;

            //! \brief Событие при смене языка
            case QEvent::LocaleChange:
                QString locale = QLocale::system().name();
                locale.truncate(locale.lastIndexOf('_'));
                loadLanguage(locale);
                break;
        }
    }
    QMainWindow::changeEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}


