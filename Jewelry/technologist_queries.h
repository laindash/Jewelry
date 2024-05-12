#ifndef TECHNOLOGIST_QUERIES_H
#define TECHNOLOGIST_QUERIES_H


#include <QtWidgets/QMainWindow>
#include "ui_technologist_queries.h"
#include "query_result.h"


QT_BEGIN_NAMESPACE
namespace Ui { class TechnologistQueriesClass; };
QT_END_NAMESPACE

class TechnologistQueries : public QMainWindow
{
    Q_OBJECT

public:
    TechnologistQueries(QWidget* parent = nullptr);
    ~TechnologistQueries();

private slots:
    void stone_availability_btn_clicked();
    void metal_availability_btn_clicked();
    void param_search_btn_clicked();

private:
    Ui::TechnologistQueriesClass* _ui;
    QueryResult* _query_result;


    void enableStoneAvailabilityButton();
    void enableMetalAvailabilityButton();
    void enableParamSearchButton();
};

#endif