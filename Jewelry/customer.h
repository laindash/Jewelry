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
    void products_btn_clicked();
    void product_types_btn_clicked();
    void stones_btn_clicked();
    void metal_btn_clicked();
    void param_search_btn_clicked();

private:
    Ui::CustomerClass* _ui;
    QueryResult* _query_result;

    void enableProductsButton();
    void enableProductTypesButton();
    void enableStonesButton();
    void enableMetalButton();
    void enableParamSearchButton();
};

#endif