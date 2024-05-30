#ifndef CUSTOMER_H
#define CUSTOMER_H


#include <QtWidgets/QMainWindow>
#include "ui_customer.h"
#include "query_result.h"


QT_BEGIN_NAMESPACE
namespace Ui { class CustomerClass; };
QT_END_NAMESPACE

class Customer : public QMainWindow
{
    Q_OBJECT

public:
    Customer(QWidget* parent = nullptr);
    ~Customer();

private slots:
    void products_save();
    void products_add();
   
    void param_search_btn_clicked();
    void saveTableToFile(QTableWidget* tableWidget);
    void setupComboBoxes();

private:
    Ui::CustomerClass* _ui;
    QueryResult* _products = nullptr;

    void enableProductsButton();
    void enableProductTypesButton();
    void enableStonesButton();
    void enableMetalButton();
    void enableParamSearchButton();
};

#endif