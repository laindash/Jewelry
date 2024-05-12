#include "technologist.h"
#include "database.h"
#include "qmessagebox.h"


Technologist::Technologist(QWidget* parent) : QMainWindow(parent), _ui(new Ui::TechnologistClass()), 
	_query_result(nullptr), _technologist_queries(nullptr) {
	
	// Инициализация главного окна
	_ui->setupUi(this);

	// Установка флагов размера окна
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	setWindowFlags(windowFlags() & ~(Qt::WindowFullscreenButtonHint | Qt::WindowMaximizeButtonHint));
	setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);

	connect(_ui->product_types_btn, &QPushButton::clicked, this, &Technologist::product_types_btn_clicked);
	connect(_ui->materials_btn, &QPushButton::clicked, this, &Technologist::materials_btn_clicked);
	connect(_ui->metal_btn, &QPushButton::clicked, this, &Technologist::metal_btn_clicked);
	connect(_ui->faceting_btn, &QPushButton::clicked, this, &Technologist::faceting_btn_clicked);
	connect(_ui->pam_com_btn, &QPushButton::clicked, this, &Technologist::pam_com_btn_clicked);
	connect(_ui->stages_btn, &QPushButton::clicked, this, &Technologist::stages_btn_clicked);
	connect(_ui->products_btn, &QPushButton::clicked, this, &Technologist::products_btn_clicked);
	connect(_ui->technologies_btn, &QPushButton::clicked, this, &Technologist::technologies_btn_clicked);
	connect(_ui->pas_com_btn, &QPushButton::clicked, this, &Technologist::pas_com_btn_clicked);
	connect(_ui->equipment_btn, &QPushButton::clicked, this, &Technologist::equipment_btn_clicked);
	connect(_ui->stones_btn, &QPushButton::clicked, this, &Technologist::stones_btn_clicked);
	connect(_ui->technologist_queries_btn, &QPushButton::clicked, this, &Technologist::technologist_queries_btn_clicked);
}

Technologist::~Technologist() {
	delete _ui;
}


void Technologist::product_types_btn_clicked() {
	_ui->product_types_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Technologist::enableProductTypesButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT вид_изделия.`Вид изделия` FROM `вид_изделия`;");

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

void Technologist::enableProductTypesButton() {
	_ui->product_types_btn->setEnabled(true);
	this->show();
}


void Technologist::materials_btn_clicked() {
	_ui->materials_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Technologist::enableMaterialsButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT дополнительные_материалы.`Дополнительный материал` FROM `дополнительные_материалы`;");
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

void Technologist::enableMaterialsButton() {
	_ui->materials_btn->setEnabled(true);
	this->show();
}


void Technologist::metal_btn_clicked() {
	_ui->metal_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Technologist::enableMetalButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT металл.`Вид металла`, металл.`Количество на складе, гр`, металл.`Цена за грамм, руб` FROM `металл`;");
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

void Technologist::enableMetalButton() {
	_ui->metal_btn->setEnabled(true);
	this->show();
}

void Technologist::faceting_btn_clicked() {
	_ui->faceting_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Technologist::enableFacetingButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT огранка.`Вид огранки` FROM `огранка`;");
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

void Technologist::enableFacetingButton() {
	_ui->faceting_btn->setEnabled(true);
	this->show();
}

void Technologist::pam_com_btn_clicked() {
	_ui->pam_com_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Technologist::enablePamComButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT изделие.`Название изделия`, дополнительные_материалы.`Дополнительный материал`, связь_изделие_и_дополнительные_материалы.`Количество, гр` "
		"FROM `изделие` INNER JOIN `связь_изделие_и_дополнительные_материалы` ON изделие.`Код изделия` = связь_изделие_и_дополнительные_материалы.`Изделие` "
		"INNER JOIN `дополнительные_материалы` ON дополнительные_материалы.`Код материала` = связь_изделие_и_дополнительные_материалы.`Дополнительный материал`;");
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

void Technologist::enablePamComButton() {
	_ui->pam_com_btn->setEnabled(true);
	this->show();
}

void Technologist::stages_btn_clicked() {
	_ui->stages_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Technologist::enableStagesButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT стадии.`Стадия` FROM `стадии`;");
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

void Technologist::enableStagesButton() {
	_ui->stages_btn->setEnabled(true);
	this->show();
}

void Technologist::products_btn_clicked() {
	_ui->products_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Technologist::enableProductsButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT Изделие.`Название изделия`, вид_изделия.`Вид изделия`, Изделие.`Цена, руб`, Металл.`Вид металла`, Изделие.`Вес металла, гр`, Камни.`Камень`, "
		"Камни.`Карат`, связь_изделие_и_камень.`Количество камней, шт`, Изделие.`Фото изделия` "
		"FROM Металл INNER JOIN Изделие ON Металл.`Код` = Изделие.`Металл` "
		"INNER JOIN вид_изделия ON вид_изделия.`Код` = изделие.`Вид изделия` "
		"INNER JOIN связь_изделие_и_камень ON связь_изделие_и_камень.`Изделие` = Изделие.`Код изделия` "
		"INNER JOIN камни ON связь_изделие_и_камень.`Камень` = камни.`Код`;");
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

void Technologist::enableProductsButton() {
	_ui->products_btn->setEnabled(true);
	this->show();
}

void Technologist::technologies_btn_clicked() {
	_ui->technologies_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Technologist::enableTechnologiesButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT изделие.`Название изделия`, стадии.`Стадия`, оборудование.`Оборудование`, технология.`Время, ч`, технология.`Мощность, ватт`, технология.`Температура, °C`, технология.`Цена производства, руб` "
		"FROM `технология` INNER JOIN `изделие` ON изделие.`Код изделия` = технология.`Изделие` "
		"INNER JOIN `стадии` ON стадии.`Номер` = технология.`Стадия` "
		"INNER JOIN `оборудование` ON оборудование.`Код` = технология.`Оборудование`;");

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

void Technologist::enableTechnologiesButton() {
	_ui->technologies_btn->setEnabled(true);
	this->show();
}

void Technologist::pas_com_btn_clicked() {
	_ui->pas_com_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Technologist::enablePasComButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT изделие.`Название изделия`, камни.`Камень`, связь_изделие_и_камень.`Количество камней, шт` "
		"FROM `изделие` INNER JOIN `связь_изделие_и_камень` ON изделие.`Код изделия` = связь_изделие_и_камень.`Изделие` "
		"INNER JOIN `камни` ON камни.`Код` = связь_изделие_и_камень.`Камень`;");

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

void Technologist::enablePasComButton() {
	_ui->pas_com_btn->setEnabled(true);
	this->show();
}

void Technologist::equipment_btn_clicked() {
	_ui->equipment_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Technologist::enableEquipmentButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT оборудование.`Оборудование` FROM `оборудование`;");

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

void Technologist::enableEquipmentButton() {
	_ui->equipment_btn->setEnabled(true);
	this->show();
}

void Technologist::stones_btn_clicked() {
	_ui->stones_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Technologist::enableStonesButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT камни.`Камень`, камни.`Карат`, камни.`Цена за карат, руб`, огранка.`Вид огранки` "
		"FROM `огранка` INNER JOIN `камни` ON огранка.`Код` = камни.`Вид огранки`;");

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

void Technologist::enableStonesButton() {
	_ui->stones_btn->setEnabled(true);
	this->show();
}


void Technologist::technologist_queries_btn_clicked() {
	_ui->technologist_queries_btn->setEnabled(false);
	this->hide();
	_technologist_queries = new TechnologistQueries(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_technologist_queries, &QObject::destroyed, this, &Technologist::enableTechnologistQueriesButton);
	_technologist_queries->setAttribute(Qt::WA_DeleteOnClose); //clear memory
	_technologist_queries->show();
}

void Technologist::enableTechnologistQueriesButton() {
	_ui->technologist_queries_btn->setEnabled(true);
	this->show();
}
