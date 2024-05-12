#ifndef TECHNOLOGIST_H
#define TECHNOLOGIST_H


#include <QtWidgets/QMainWindow>
#include "ui_technologist.h"
#include "query_result.h"
#include "technologist_queries.h"


QT_BEGIN_NAMESPACE
namespace Ui { class TechnologistClass; };
QT_END_NAMESPACE

class Technologist : public QMainWindow
{
    Q_OBJECT

public:
    Technologist(QWidget* parent = nullptr);
    ~Technologist();

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
    void technologist_queries_btn_clicked();

private:
    Ui::TechnologistClass* _ui;
    QueryResult* _query_result;
    TechnologistQueries* _technologist_queries;


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
    void enableTechnologistQueriesButton();
};

#endif