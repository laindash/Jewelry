#ifndef ADMIN_H
#define ADMIN_H

#include <QtWidgets/QMainWindow>
#include "ui_admin.h"
#include "query_result.h"
#include "admin_queries.h"


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
    void product_types_btn_clicked();
    void materials_btn_clicked();
    void metal_btn_clicked();
    void faceting_btn_clicked();
    void pam_com_btn_clicked();
    void stages_btn_clicked();
    void products_btn_clicked();
    void technologies_btn_clicked();
    void pas_com_btn_clicked();
    void equipment_btn_clicked();
    void stones_btn_clicked();
    void admin_queries_btn_clicked();

private:
    Ui::AdminClass* _ui;
    QueryResult* _query_result;
    AdminQueries* _admin_queries;
    
    void enableProductTypesButton();
    void enableMaterialsButton();
    void enableMetalButton();
    void enableFacetingButton();
    void enablePamComButton();
    void enableStagesButton();
    void enableProductsButton();
    void enableTechnologiesButton();
    void enablePasComButton();
    void enableEquipmentButton();
    void enableStonesButton();
    void enableAdminQueriesButton();
};

#endif