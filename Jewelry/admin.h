#ifndef ADMIN_H
#define ADMIN_H

#include <QtWidgets/QMainWindow>
#include "ui_admin.h"
#include "query_result.h"


QT_BEGIN_NAMESPACE
namespace Ui { class AdminClass; };
QT_END_NAMESPACE

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    Admin(QWidget* parent = nullptr);
    ~Admin();

private slots:
    void product_types_add();
    void materials_add();
    void metal_add();
    void faceting_add();
    void pam_com_add();
    void stages_add();
    void products_add();
    void technologies_add();
    void pas_com_add();
    void equipment_add();
    void stones_add();

    void metal_price_btn_clicked();
    void stones_price_btn_clicked();
    void products_price_btn_clicked();
    void upd_metal_price_btn_clicked();
    void upd_stones_price_btn_clicked();
    void upd_products_price_btn_clicked();

    void product_types_save();
    void materials_save();
    void metal_save();
    void faceting_save();
    void pam_com_save();
    void stages_save();
    void products_save();
    void technologies_save();
    void pas_com_save();
    void equipment_save();
    void stones_save();

    void saveTableToFile(QTableWidget* tableWidget);

private:
    Ui::AdminClass *_ui;
    QueryResult *_products, * _materials, *_metal, *_faceting, *_pam_com, *_stages, *_product_types, *_technologies, *_pas_com, *_equipment, *_stones;
};

#endif