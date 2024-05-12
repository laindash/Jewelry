#include "admin.h"
#include "database.h"
#include "qmessagebox.h"


Admin::Admin(QWidget* parent) : QMainWindow(parent), _ui(new Ui::AdminClass()), _query_result(nullptr), _admin_queries(nullptr) {
	// Инициализация главного окна
	_ui->setupUi(this);

	// Установка флагов размера окна
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	setWindowFlags(windowFlags() & ~(Qt::WindowFullscreenButtonHint | Qt::WindowMaximizeButtonHint));
	setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);

	connect(_ui->product_types_btn, &QPushButton::clicked, this, &Admin::product_types_btn_clicked);
	connect(_ui->materials_btn, &QPushButton::clicked, this, &Admin::materials_btn_clicked);
	connect(_ui->metal_btn, &QPushButton::clicked, this, &Admin::metal_btn_clicked);
	connect(_ui->faceting_btn, &QPushButton::clicked, this, &Admin::faceting_btn_clicked);
	connect(_ui->pam_com_btn, &QPushButton::clicked, this, &Admin::pam_com_btn_clicked);
	connect(_ui->stages_btn, &QPushButton::clicked, this, &Admin::stages_btn_clicked);
	connect(_ui->products_btn, &QPushButton::clicked, this, &Admin::products_btn_clicked);
	connect(_ui->technologies_btn, &QPushButton::clicked, this, &Admin::technologies_btn_clicked);
	connect(_ui->pas_com_btn, &QPushButton::clicked, this, &Admin::pas_com_btn_clicked);
	connect(_ui->equipment_btn, &QPushButton::clicked, this, &Admin::equipment_btn_clicked);
	connect(_ui->stones_btn, &QPushButton::clicked, this, &Admin::stones_btn_clicked);
	connect(_ui->admin_queries_btn, &QPushButton::clicked, this, &Admin::admin_queries_btn_clicked);
}

Admin::~Admin() {
	delete _ui;
}


void Admin::product_types_btn_clicked() {
	_ui->product_types_btn->setEnabled(false);
	this->hide();
	QString table_name = "`вид_изделия`", primary_key_column_name = "`Код`";

	_query_result = new QueryResult(this, table_name, primary_key_column_name);
	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Admin::enableProductTypesButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT * FROM `вид_изделия`;");

	if (result) {
		_query_result->addDataToTable(result);
		delete result;
		_query_result->show();
	}
	else {
		QMessageBox::information(this, "Информация", "Данные не найдены!");
		delete _query_result;
		delete result;
		_ui->product_types_btn->setEnabled(true);
		this->show();
	}
}

void Admin::enableProductTypesButton() {
	_ui->product_types_btn->setEnabled(true);
	this->show();
}


void Admin::materials_btn_clicked() {
	_ui->materials_btn->setEnabled(false);
	this->hide();
	QString table_name = "`дополнительные_материалы`", primary_key_column_name = "`Код материала`";

	_query_result = new QueryResult(this, table_name, primary_key_column_name);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Admin::enableMaterialsButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT * FROM `дополнительные_материалы`;");
	if (result) {
		_query_result->addDataToTable(result);
		delete result;
		_query_result->show();
	}
	else {
		QMessageBox::information(this, "Информация", "Данные не найдены!");
		delete _query_result;
		delete result;
		_ui->materials_btn->setEnabled(true);
		this->show();
	}
}

void Admin::enableMaterialsButton() {
	_ui->materials_btn->setEnabled(true);
	this->show();
}


void Admin::metal_btn_clicked() {
	_ui->metal_btn->setEnabled(false);
	this->hide();
	QString table_name = "`металл`", primary_key_column_name = "`Код`";

	_query_result = new QueryResult(this, table_name, primary_key_column_name);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Admin::enableMetalButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT * FROM `металл`;");
	if (result) {
		_query_result->addDataToTable(result);
		delete result;
		_query_result->show();
	}
	else {
		QMessageBox::information(this, "Информация", "Данные не найдены!");
		delete _query_result;
		delete result;
		_ui->metal_btn->setEnabled(true);
		this->show();
	}
}

void Admin::enableMetalButton() {
	_ui->metal_btn->setEnabled(true);
	this->show();
}

void Admin::faceting_btn_clicked() {
	_ui->faceting_btn->setEnabled(false);
	this->hide();
	QString table_name = "`огранка`", primary_key_column_name = "`Код`";

	_query_result = new QueryResult(this, table_name, primary_key_column_name);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Admin::enableFacetingButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT * FROM `огранка`;");
	if (result) {
		_query_result->addDataToTable(result);
		delete result;
		_query_result->show();
	}
	else {
		QMessageBox::information(this, "Информация", "Данные не найдены!");
		delete _query_result;
		delete result;
		_ui->faceting_btn->setEnabled(true);
		this->show();
	}
}

void Admin::enableFacetingButton() {
	_ui->faceting_btn->setEnabled(true);
	this->show();
}

void Admin::pam_com_btn_clicked() {
	_ui->pam_com_btn->setEnabled(false);
	this->hide();
	QString table_name = "`связь_изделие_и_дополнительные_материалы`", primary_key_column_name = "`Связь номер`";

	_query_result = new QueryResult(this, table_name, primary_key_column_name);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Admin::enablePamComButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT * FROM `связь_изделие_и_дополнительные_материалы`;");
	if (result) {
		_query_result->addDataToTable(result);
		delete result;
		_query_result->show();
	}
	else {
		QMessageBox::information(this, "Информация", "Данные не найдены!");
		delete _query_result;
		delete result;
		_ui->pam_com_btn->setEnabled(true);
		this->show();
	}
}

void Admin::enablePamComButton() {
	_ui->pam_com_btn->setEnabled(true);
	this->show();
}

void Admin::stages_btn_clicked() {
	_ui->stages_btn->setEnabled(false);
	this->hide();
	QString table_name = "`стадии`", primary_key_column_name = "`Номер`";

	_query_result = new QueryResult(this, table_name, primary_key_column_name);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Admin::enableStagesButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT * FROM `стадии`;");
	if (result) {
		_query_result->addDataToTable(result);
		delete result;
		_query_result->show();
	}
	else {
		QMessageBox::information(this, "Информация", "Данные не найдены!");
		delete _query_result;
		delete result;
		_ui->stages_btn->setEnabled(true);
		this->show();
	}
}

void Admin::enableStagesButton() {
	_ui->stages_btn->setEnabled(true);
	this->show();
}

void Admin::products_btn_clicked() {
	_ui->products_btn->setEnabled(false);
	this->hide();
	QString table_name = "`изделие`", primary_key_column_name = "`Код изделия`";

	_query_result = new QueryResult(this, table_name, primary_key_column_name);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Admin::enableProductsButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT * FROM `изделие`;");
	if (result) {
		_query_result->addDataToTable(result);
		delete result;
		_query_result->show();
	}
	else {
		QMessageBox::information(this, "Информация", "Данные не найдены!");
		delete _query_result;
		delete result;
		_ui->products_btn->setEnabled(true);
		this->show();
	}
}

void Admin::enableProductsButton() {
	_ui->products_btn->setEnabled(true);
	this->show();
}

void Admin::technologies_btn_clicked() {
	_ui->technologies_btn->setEnabled(false);
	this->hide();
	QString table_name = "`технология`", primary_key_column_name = "`Код`";

	_query_result = new QueryResult(this, table_name, primary_key_column_name);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Admin::enableTechnologiesButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT * FROM `технология`;");

	if (result) {
		_query_result->addDataToTable(result);
		delete result;
		_query_result->show();
	}
	else {
		QMessageBox::information(this, "Информация", "Данные не найдены!");
		delete _query_result;
		delete result;
		_ui->technologies_btn->setEnabled(true);
		this->show();
	}
}

void Admin::enableTechnologiesButton() {
	_ui->technologies_btn->setEnabled(true);
	this->show();
}

void Admin::pas_com_btn_clicked() {
	_ui->pas_com_btn->setEnabled(false);
	this->hide();
	QString table_name = "`связь_изделие_и_камень`", primary_key_column_name = "`Связь номер`";

	_query_result = new QueryResult(this, table_name, primary_key_column_name);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Admin::enablePasComButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT * FROM `связь_изделие_и_камень`;");

	if (result) {
		_query_result->addDataToTable(result);
		delete result;
		_query_result->show();
	}
	else {
		QMessageBox::information(this, "Информация", "Данные не найдены!");
		delete _query_result;
		delete result;
		_ui->pas_com_btn->setEnabled(true);
		this->show();
	}
}

void Admin::enablePasComButton() {
	_ui->pas_com_btn->setEnabled(true);
	this->show();
}

void Admin::equipment_btn_clicked() {
	_ui->equipment_btn->setEnabled(false);
	this->hide();
	QString table_name = "`оборудование`", primary_key_column_name = "`Код`";

	_query_result = new QueryResult(this, table_name, primary_key_column_name);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Admin::enableEquipmentButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT * FROM `оборудование`;");

	if (result) {
		_query_result->addDataToTable(result);
		delete result;
		_query_result->show();
	}
	else {
		QMessageBox::information(this, "Информация", "Данные не найдены!");
		delete _query_result;
		delete result;
		_ui->equipment_btn->setEnabled(true);
		this->show();
	}
}

void Admin::enableEquipmentButton() {
	_ui->equipment_btn->setEnabled(true);
	this->show();
}

void Admin::stones_btn_clicked() {
	_ui->stones_btn->setEnabled(false);
	this->hide();
	QString table_name = "`камни`", primary_key_column_name = "`Код`";

	_query_result = new QueryResult(this, table_name, primary_key_column_name);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Admin::enableStonesButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT * FROM `камни`;");

	if (result) {
		_query_result->addDataToTable(result);
		delete result;
		_query_result->show();
	}
	else {
		QMessageBox::information(this, "Информация", "Данные не найдены!");
		delete _query_result;
		delete result;
		_ui->stones_btn->setEnabled(true);
		this->show();
	}
}

void Admin::enableStonesButton() {
	_ui->stones_btn->setEnabled(true);
	this->show();
}


void Admin::admin_queries_btn_clicked() {
	_ui->admin_queries_btn->setEnabled(false);
	this->hide();
	_admin_queries = new AdminQueries(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_admin_queries, &QObject::destroyed, this, &Admin::enableAdminQueriesButton);
	_admin_queries->setAttribute(Qt::WA_DeleteOnClose); //clear memory
	_admin_queries->show();
}

void Admin::enableAdminQueriesButton() {
	_ui->admin_queries_btn->setEnabled(true);
	this->show();
}