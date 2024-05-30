#include "admin.h"
#include "database.h"
#include "qmessagebox.h"
#include <qfiledialog.h>


Admin::Admin(QWidget* parent) : QMainWindow(parent), _ui(new Ui::AdminClass()) {
	// Инициализация главного окна
	_ui->setupUi(this);

	// Установка флагов размера окна
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	setWindowFlags(windowFlags() & ~(Qt::WindowFullscreenButtonHint | Qt::WindowMaximizeButtonHint));
	setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
	setWindowModality(Qt::WindowModal);

	product_types_add();
	materials_add();
	metal_add();
	faceting_add();
	pam_com_add();
	stages_add();
	products_add();
	technologies_add();
	pas_com_add();
	equipment_add();
	stones_add();

	connect(_ui->metal_price_btn, &QPushButton::clicked, this, &Admin::metal_price_btn_clicked);
	connect(_ui->stones_price_btn, &QPushButton::clicked, this, &Admin::stones_price_btn_clicked);
	connect(_ui->products_price_btn, &QPushButton::clicked, this, &Admin::products_price_btn_clicked);
	connect(_ui->upd_metal_price_btn, &QPushButton::clicked, this, &Admin::upd_metal_price_btn_clicked);
	connect(_ui->upd_stones_price_btn, &QPushButton::clicked, this, &Admin::upd_stones_price_btn_clicked);
	connect(_ui->upd_products_price_btn, &QPushButton::clicked, this, &Admin::upd_products_price_btn_clicked);

	connect(_ui->upd_product_types_table_btn, &QPushButton::clicked, this, &Admin::product_types_add);
	connect(_ui->upd_materials_table_btn, &QPushButton::clicked, this, &Admin::materials_add);
	connect(_ui->upd_metal_table_btn, &QPushButton::clicked, this, &Admin::metal_add);
	connect(_ui->upd_faceting_table_btn, &QPushButton::clicked, this, &Admin::faceting_add);
	connect(_ui->upd_pam_com_table_btn, &QPushButton::clicked, this, &Admin::pam_com_add);
	connect(_ui->upd_stages_table_btn, &QPushButton::clicked, this, &Admin::stages_add);
	connect(_ui->upd_products_table_btn, &QPushButton::clicked, this, &Admin::products_add);
	connect(_ui->upd_technologies_table_btn, &QPushButton::clicked, this, &Admin::technologies_add);
	connect(_ui->upd_pas_com_table_btn, &QPushButton::clicked, this, &Admin::pas_com_add);
	connect(_ui->upd_equipment_table_btn, &QPushButton::clicked, this, &Admin::equipment_add);
	connect(_ui->upd_stones_table_btn, &QPushButton::clicked, this, &Admin::stones_add);

	connect(_ui->save_product_types_table_btn, &QPushButton::clicked, this, &Admin::product_types_save);
	connect(_ui->save_materials_table_btn, &QPushButton::clicked, this, &Admin::materials_save);
	connect(_ui->save_metal_table_btn, &QPushButton::clicked, this, &Admin::metal_save);
	connect(_ui->save_faceting_table_btn, &QPushButton::clicked, this, &Admin::faceting_save);
	connect(_ui->save_pam_com_table_btn, &QPushButton::clicked, this, &Admin::pam_com_save);
	connect(_ui->save_stages_table_btn, &QPushButton::clicked, this, &Admin::stages_save);
	connect(_ui->save_products_table_btn, &QPushButton::clicked, this, &Admin::products_save);
	connect(_ui->save_technologies_table_btn, &QPushButton::clicked, this, &Admin::technologies_save);
	connect(_ui->save_pas_com_table_btn, &QPushButton::clicked, this, &Admin::pas_com_save);
	connect(_ui->save_equipment_table_btn, &QPushButton::clicked, this, &Admin::equipment_save);
	connect(_ui->save_stones_table_btn, &QPushButton::clicked, this, &Admin::stones_save);
}


Admin::~Admin() {
	delete _ui;
}


void Admin::saveTableToFile(QTableWidget* tableWidget) {
	QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Excel File", "", "Excel Files (*.xml)");

	if (fileName.isEmpty()) {
		return;
	}

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QMessageBox::warning(nullptr, "Save Excel File", "Cannot open file for writing: " + fileName);
		return;
	}

	QTextStream out(&file);

	// Запись заголовков столбцов
	out << "<?xml version=\"1.0\"?>\n";
	out << "<?mso-application progid=\"Excel.Sheet\"?>\n";
	out << "<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\"\n";
	out << "    xmlns:o=\"urn:schemas-microsoft-com:office:office\"\n";
	out << "    xmlns:x=\"urn:schemas-microsoft-com:office:excel\"\n";
	out << "    xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\"\n";
	out << "    xmlns:html=\"http://www.w3.org/TR/REC-html40\">\n";
	out << "  <Worksheet ss:Name=\"Sheet1\">\n";
	out << "    <Table>\n";

	// Запись заголовков столбцов, пропуская столбец с названием "фото изделия"
	out << "      <Row>\n";
	for (int col = 0; col < tableWidget->columnCount(); ++col) {
		QString header = tableWidget->horizontalHeaderItem(col)->data(Qt::DisplayRole).toString();
		if (header != "Фото изделия") {
			out << "        <Cell><Data ss:Type=\"String\">" << header << "</Data></Cell>\n";
		}
	}
	out << "      </Row>\n";

	// Запись данных из таблицы
	for (int row = 0; row < tableWidget->rowCount(); ++row) {
		out << "      <Row>\n";
		for (int col = 0; col < tableWidget->columnCount(); ++col) {
			QString header = tableWidget->horizontalHeaderItem(col)->data(Qt::DisplayRole).toString();
			if (header != "Фото изделия") {
				QTableWidgetItem* item = tableWidget->item(row, col);
				if (item && item->data(Qt::DisplayRole).isValid()) {
					QString cellValue = item->data(Qt::DisplayRole).toString();
					out << "        <Cell><Data ss:Type=\"String\">" << cellValue << "</Data></Cell>\n";
				}
				else {
					out << "        <Cell><Data ss:Type=\"String\"></Data></Cell>\n";
				}
			}
		}
		out << "      </Row>\n";
	}

	out << "    </Table>\n";
	out << "  </Worksheet>\n";
	out << "</Workbook>\n";

	file.close();
	QMessageBox::information(nullptr, "Save Excel File", "Data saved to " + fileName);
}


void Admin::product_types_save() {
	saveTableToFile(_product_types->_ui->output_table);
}

void Admin::materials_save() {
	saveTableToFile(_materials->_ui->output_table);
}

void Admin::metal_save() {
	saveTableToFile(_metal->_ui->output_table);
}

void Admin::faceting_save() {
	saveTableToFile(_faceting->_ui->output_table);
}

void Admin::pam_com_save() {
	saveTableToFile(_pam_com->_ui->output_table);
}

void Admin::stages_save() {
	saveTableToFile(_stages->_ui->output_table);
}

void Admin::products_save() {
	saveTableToFile(_products->_ui->output_table);
}

void Admin::technologies_save() {
	saveTableToFile(_technologies->_ui->output_table);
}

void Admin::pas_com_save() {
	saveTableToFile(_pas_com->_ui->output_table);
}

void Admin::equipment_save() {
	saveTableToFile(_equipment->_ui->output_table);
}

void Admin::stones_save() {
	saveTableToFile(_stones->_ui->output_table);
}


void Admin::product_types_add() {
	QLayoutItem* child;
	while ((child = _ui->product_types_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	QString table_name = "`вид_изделия`", primary_key_column_name = "`Код`";

	_product_types = new QueryResult(this, table_name, primary_key_column_name);

	sql::ResultSet* result = runQuery("SELECT * FROM `вид_изделия`;");
	if (result) {
		_product_types->addDataToTable(result);
		delete result;
	}

	_ui->product_types_layout->addWidget(_product_types);
}


void Admin::materials_add() {
	QLayoutItem* child;
	while ((child = _ui->materials_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	QString table_name = "`дополнительные_материалы`", primary_key_column_name = "`Код материала`";

	_materials = new QueryResult(this, table_name, primary_key_column_name);

	sql::ResultSet* result = runQuery("SELECT * FROM `дополнительные_материалы`;");
	if (result) {
		_materials->addDataToTable(result);
		delete result;
	}

	_ui->materials_layout->addWidget(_materials);
}


void Admin::metal_add() {
	QLayoutItem* child;
	while ((child = _ui->metal_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	QString table_name = "`металл`", primary_key_column_name = "`Код`";

	_metal = new QueryResult(this, table_name, primary_key_column_name);

	sql::ResultSet* result = runQuery("SELECT * FROM `металл`;");
	if (result) {
		_metal->addDataToTable(result);
		delete result;
	}

	_ui->metal_layout->addWidget(_metal);
}


void Admin::faceting_add() {
	QLayoutItem* child;
	while ((child = _ui->faceting_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	QString table_name = "`огранка`", primary_key_column_name = "`Код`";

	_faceting = new QueryResult(this, table_name, primary_key_column_name);

	sql::ResultSet* result = runQuery("SELECT * FROM `огранка`;");
	if (result) {
		_faceting->addDataToTable(result);
		delete result;
	}

	_ui->faceting_layout->addWidget(_faceting);
}


void Admin::pam_com_add() {
	QLayoutItem* child;
	while ((child = _ui->pam_com_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	QString table_name = "`связь_изделие_и_дополнительные_материалы`", primary_key_column_name = "`Связь номер`";

	_pam_com = new QueryResult(this, table_name, primary_key_column_name);

	sql::ResultSet* result = runQuery("SELECT * FROM `связь_изделие_и_дополнительные_материалы`;");
	if (result) {
		_pam_com->addDataToTable(result);
		delete result;
	}

	_ui->pam_com_layout->addWidget(_pam_com);
}


void Admin::stages_add() {
	QLayoutItem* child;
	while ((child = _ui->stages_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	QString table_name = "`стадии`", primary_key_column_name = "`Номер`";

	_stages = new QueryResult(this, table_name, primary_key_column_name);

	sql::ResultSet* result = runQuery("SELECT * FROM `стадии`;");
	if (result) {
		_stages->addDataToTable(result);
		delete result;
	}

	_ui->stages_layout->addWidget(_stages);
}


void Admin::products_add() {
	QLayoutItem* child;
	while ((child = _ui->products_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	QString table_name = "`изделие`", primary_key_column_name = "`Код изделия`";

	_products = new QueryResult(this, table_name, primary_key_column_name);

	sql::ResultSet* result = runQuery("SELECT * FROM `изделие`;");
	if (result) {
		_products->addDataToTable(result);
		delete result;
	}

	_ui->products_layout->addWidget(_products);
}


void Admin::technologies_add() {
	QLayoutItem* child;
	while ((child = _ui->technologies_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	QString table_name = "`технология`", primary_key_column_name = "`Код`";

	_technologies = new QueryResult(this, table_name, primary_key_column_name);

	sql::ResultSet* result = runQuery("SELECT * FROM `технология`;");

	if (result) {
		_technologies->addDataToTable(result);
		delete result;
	}

	_ui->technologies_layout->addWidget(_technologies);
}


void Admin::pas_com_add() {
	QLayoutItem* child;
	while ((child = _ui->pas_com_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	QString table_name = "`связь_изделие_и_камень`", primary_key_column_name = "`Связь номер`";

	_pas_com = new QueryResult(this, table_name, primary_key_column_name);

	sql::ResultSet* result = runQuery("SELECT * FROM `связь_изделие_и_камень`;");

	if (result) {
		_pas_com->addDataToTable(result);
		delete result;
	}

	_ui->pas_com_layout->addWidget(_pas_com);
}


void Admin::equipment_add() {
	QLayoutItem* child;
	while ((child = _ui->equipment_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	QString table_name = "`оборудование`", primary_key_column_name = "`Код`";

	_equipment = new QueryResult(this, table_name, primary_key_column_name);

	sql::ResultSet* result = runQuery("SELECT * FROM `оборудование`;");

	if (result) {
		_equipment->addDataToTable(result);
		delete result;
	}

	_ui->equipment_layout->addWidget(_equipment);
}


void Admin::stones_add() {
	QLayoutItem* child;
	while ((child = _ui->stones_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	QString table_name = "`камни`", primary_key_column_name = "`Код`";

	_stones = new QueryResult(this, table_name, primary_key_column_name);

	sql::ResultSet* result = runQuery("SELECT * FROM `камни`;");

	if (result) {
		_stones->addDataToTable(result);
		delete result;
	}

	_ui->stones_layout->addWidget(_stones);
}


void Admin::metal_price_btn_clicked() {
	_ui->metal_price_btn->setEnabled(false);

	QLayoutItem* child;
	while ((child = _ui->metal_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	std::string sql_query =
		"SELECT металл.`Вид металла`, металл.`Количество на складе, гр`, металл.`Цена за грамм, руб`, металл.`Количество на складе, гр` * металл.`Цена за грамм, руб` AS `Cтоимость всего количества, руб`, "
		"CASE WHEN ROW_NUMBER() OVER (ORDER BY металл.`Вид металла`) = 1 THEN (SELECT SUM(`Количество на складе, гр` * `Цена за грамм, руб`) FROM металл) ELSE NULL END AS `Общая стоимость всех металлов, руб` "
		"FROM металл ;";

	_metal = new QueryResult(this);

	sql::ResultSet* result = runQuery(sql_query);

	if (result) {
		_metal->addDataToTable(result);
		delete result;
	}

	_ui->metal_layout->addWidget(_metal);
	_ui->metal_price_btn->setEnabled(true);
}


void Admin::stones_price_btn_clicked() {
	_ui->stones_price_btn->setEnabled(false);

	QLayoutItem* child;
	while ((child = _ui->stones_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	std::string sql_query =
		"SELECT камни.`Камень`, камни.`Карат`, камни.`Цена за карат, руб`, камни.`Карат` * камни.`Цена за карат, руб` AS `Cтоимость всего количества, руб`, "
		"CASE WHEN ROW_NUMBER() OVER (ORDER BY камни.`Карат`) = 1 THEN (SELECT SUM(камни.`Карат` * камни.`Цена за карат, руб`) FROM камни) ELSE NULL END AS `Общая стоимость всех камней, руб` "
		"FROM камни ;";

	_stones = new QueryResult(this);

	sql::ResultSet* result = runQuery(sql_query);

	if (result) {
		_stones->addDataToTable(result);
		delete result;
	}

	_ui->stones_layout->addWidget(_stones);
	_ui->stones_price_btn->setEnabled(true);
}


void Admin::products_price_btn_clicked() {
	_ui->products_price_btn->setEnabled(false);

	QLayoutItem* child;
	while ((child = _ui->products_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	std::string sql_query =
		"SELECT изделие.`Название изделия`, вид_изделия.`Вид изделия`, изделие.`Цена, руб`, "
		"CASE WHEN ROW_NUMBER() OVER (ORDER BY изделие.`Вид изделия`) = 1 THEN (SELECT SUM(изделие.`Цена, руб`) FROM изделие) ELSE NULL END AS `Общая стоимость всех изделий, руб` "
		"FROM `изделие` INNER JOIN `вид_изделия` ON вид_изделия.`Код` = изделие.`Вид изделия` ;";

	_products = new QueryResult(this);

	sql::ResultSet* result = runQuery(sql_query);

	if (result) {
		_products->addDataToTable(result);
		delete result;
	}

	_ui->products_layout->addWidget(_products);
	_ui->products_price_btn->setEnabled(true);
}


void Admin::upd_metal_price_btn_clicked() {
	_ui->upd_metal_price_btn->setEnabled(false);

	std::string sql_query =
		"UPDATE металл SET металл.`Цена за грамм, руб` = металл.`Цена за грамм, руб` *  ";

	QString multiplier = _ui->metal_multiplier->text();

	if (!multiplier.isEmpty()) {
		sql_query += multiplier.toStdString() + ";";
	}
	else if (multiplier.isEmpty()) {
		QMessageBox::critical(this, "Ошибка", "Вы ввели пустое значение!");
		_ui->upd_metal_price_btn->setEnabled(true);
		return;
	}

	QLayoutItem* child;
	while ((child = _ui->metal_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	runQuery(sql_query);

	sql_query =
		"SELECT металл.`Вид металла`, металл.`Количество на складе, гр`, металл.`Цена за грамм, руб`, металл.`Количество на складе, гр` * металл.`Цена за грамм, руб` AS `Общая стоимость` "
		"FROM металл ;";

	_metal = new QueryResult(this);

	sql::ResultSet* result = runQuery(sql_query);

	if (result) {
		_metal->addDataToTable(result);
		delete result;
	}

	_ui->metal_layout->addWidget(_metal);
	_ui->upd_metal_price_btn->setEnabled(true);
}


void Admin::upd_stones_price_btn_clicked() {
	_ui->upd_stones_price_btn->setEnabled(false);

	std::string sql_query =
		"UPDATE камни SET камни.`Цена за карат, руб` = камни.`Цена за карат, руб` *  ";

	QString multiplier = _ui->stones_multiplier->text();

	if (!multiplier.isEmpty()) {
		sql_query += multiplier.toStdString() + ";";
	}
	else if (multiplier.isEmpty()) {
		QMessageBox::critical(this, "Ошибка", "Вы ввели пустое значение!");
		_ui->upd_stones_price_btn->setEnabled(true);
		return;
	}

	QLayoutItem* child;
	while ((child = _ui->stones_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	runQuery(sql_query);

	sql_query =
		"SELECT камни.`Камень`, камни.`Карат`, камни.`Цена за карат, руб`, камни.`Карат` * камни.`Цена за карат, руб` AS `Общая стоимость` "
		"FROM камни ;";

	_stones = new QueryResult(this);

	sql::ResultSet* result = runQuery(sql_query);

	if (result) {
		_stones->addDataToTable(result);
		delete result;
	}

	_ui->stones_layout->addWidget(_stones);
	_ui->upd_stones_price_btn->setEnabled(true);
}


void Admin::upd_products_price_btn_clicked() {
	_ui->upd_products_price_btn->setEnabled(false);

	std::string sql_query =
		"UPDATE изделие SET изделие.`Цена, руб` = изделие.`Цена, руб` *  ";

	QString multiplier = _ui->products_multiplier->text();

	if (!multiplier.isEmpty()) {
		sql_query += multiplier.toStdString() + ";";
	}
	else if (multiplier.isEmpty()) {
		QMessageBox::critical(this, "Ошибка", "Вы ввели пустое значение!");
		_ui->upd_products_price_btn->setEnabled(true);
		return;
	}

	QLayoutItem* child;
	while ((child = _ui->products_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	runQuery(sql_query);

	sql_query =
		"SELECT изделие.`Название изделия`, вид_изделия.`Вид изделия`, изделие.`Цена, руб` "
		"FROM `изделие` INNER JOIN `вид_изделия` ON вид_изделия.`Код` = изделие.`Вид изделия` ;";

	_products = new QueryResult(this);

	sql::ResultSet* result = runQuery(sql_query);

	if (result) {
		_products->addDataToTable(result);
		delete result;
	}

	_ui->products_layout->addWidget(_products);
	_ui->upd_products_price_btn->setEnabled(true);
}
