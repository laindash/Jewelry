#ifndef JEWELRY_H
#define JEWELRY_H

#include <QtWidgets/QMainWindow>
#include "ui_jewelry.h"
#include "technologist.h"
#include "admin.h"
#include "customer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class JewelryClass; };
QT_END_NAMESPACE

class Jewelry : public QMainWindow
{
    Q_OBJECT

public:
    Jewelry(QWidget *parent = nullptr);
    ~Jewelry();

private slots:
    void technologist_btn_clicked();
    void admin_btn_clicked();
    void customer_btn_clicked();

private:
    Ui::JewelryClass* _ui;
    Technologist* _technologist;
    Admin* _admin;
    Customer* _customer;

    void enableTechnologistButton();
    void enableAdminButton();
    void enableCustomerButton();
};

#endif