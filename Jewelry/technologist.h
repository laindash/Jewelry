#ifndef TECHNOLOGIST_H
#define TECHNOLOGIST_H


#include <QtWidgets/QMainWindow>
#include "ui_technologist.h"
#include "query_result.h"


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

    void stone_availability_btn_clicked();
    void metal_availability_btn_clicked();
    void param_search_btn_clicked();

    void saveTableToFile(QTableWidget* tableWidget);
    void setupComboBoxes();

private:
    Ui::TechnologistClass* _ui;
    QueryResult* _products = nullptr, * _materials = nullptr, * _metal = nullptr, * _faceting = nullptr, * _pam_com = nullptr, 
        * _stages = nullptr, * _product_types = nullptr, * _technologies = nullptr, * _pas_com = nullptr, * _equipment = nullptr, * _stones = nullptr;
};

#endif