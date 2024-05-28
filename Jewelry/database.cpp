﻿#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <QString>
#include <QStringList>
#include <QComboBox>
#include <QLineEdit>
#include <QCompleter>
#include <qabstractitemview.h>


// Константы для подключения к серверу
const std::string server = "tcp://localhost:3306";
const std::string username = "root";
const std::string database = "jewelry";
const std::string password = "2281";


sql::ResultSet* runQuery(const std::string& query_data) {
    sql::Driver* driver{};
    sql::Connection* con{};
    sql::Statement* query{};
    sql::ResultSet* res{};

    try {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        con->setSchema(database);

        query = con->createStatement();
        res = query->executeQuery(query_data);

        // Возвращаем результат запроса
        return res;
    }
    catch (sql::SQLException e) {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        return nullptr;
    }
}


// Функция для извлечения данных из таблицы
QStringList getDataFromTable(const std::string& query) {
    QStringList dataList;
    sql::ResultSet* result = runQuery(query);

    if (result) {
        while (result->next()) {
            dataList << QString::fromStdString(result->getString(1));
        }
        delete result;
    }
    return dataList;
}

QComboBox* createComboBox(const QStringList& dataList) {
    QComboBox* comboBox = new QComboBox();
    comboBox->setEditable(true);
    comboBox->addItems(dataList);

    // Создание QCompleter для автозаполнения
    QCompleter* completer = new QCompleter(dataList, comboBox);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    comboBox->setCompleter(completer);

    return comboBox;
}


void setupComboBox(QComboBox* comboBox, const QStringList& dataList) {
    comboBox->clear();
    comboBox->setEditable(true);

    // Добавляем элементы в comboBox
    comboBox->addItems(dataList);

    // Настройка комплитера
    QCompleter* completer = new QCompleter(dataList, comboBox);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    comboBox->setCompleter(completer);

    // Установка ширины выпадающего списка
    comboBox->view()->setMinimumWidth(comboBox->minimumSizeHint().width());

    // Установка политики размера, чтобы текст полностью отображался в поле ввода
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Очистка текста и установка текущего индекса на -1, чтобы не было значения по умолчанию
    comboBox->setCurrentIndex(-1);
    comboBox->lineEdit()->clear();
}