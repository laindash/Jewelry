#include "technologist.h"
#include "database.h"
#include "qmessagebox.h"
#include <QVBoxlayout>
#include <qfiledialog.h>


Technologist::Technologist(QWidget* parent) : QMainWindow(parent), _ui(new Ui::TechnologistClass()) {
	
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

	setupComboBoxes();

	connect(_ui->upd_product_types_table_btn, &QPushButton::clicked, this, &Technologist::product_types_add);
	connect(_ui->upd_materials_table_btn, &QPushButton::clicked, this, &Technologist::materials_add);
	connect(_ui->upd_metal_table_btn, &QPushButton::clicked, this, &Technologist::metal_add);
	connect(_ui->upd_faceting_table_btn, &QPushButton::clicked, this, &Technologist::faceting_add);
	connect(_ui->upd_pam_com_table_btn, &QPushButton::clicked, this, &Technologist::pam_com_add);
	connect(_ui->upd_stages_table_btn, &QPushButton::clicked, this, &Technologist::stages_add);
	connect(_ui->upd_products_table_btn, &QPushButton::clicked, this, &Technologist::products_add);
	connect(_ui->upd_technologies_table_btn, &QPushButton::clicked, this, &Technologist::technologies_add);
	connect(_ui->upd_pas_com_table_btn, &QPushButton::clicked, this, &Technologist::pas_com_add);
	connect(_ui->upd_equipment_table_btn, &QPushButton::clicked, this, &Technologist::equipment_add);
	connect(_ui->upd_stones_table_btn, &QPushButton::clicked, this, &Technologist::stones_add);

	connect(_ui->save_product_types_table_btn, &QPushButton::clicked, this, &Technologist::product_types_save);
	connect(_ui->save_materials_table_btn, &QPushButton::clicked, this, &Technologist::materials_save);
	connect(_ui->save_metal_table_btn, &QPushButton::clicked, this, &Technologist::metal_save);
	connect(_ui->save_faceting_table_btn, &QPushButton::clicked, this, &Technologist::faceting_save);
	connect(_ui->save_pam_com_table_btn, &QPushButton::clicked, this, &Technologist::pam_com_save);
	connect(_ui->save_stages_table_btn, &QPushButton::clicked, this, &Technologist::stages_save);
	connect(_ui->save_products_table_btn, &QPushButton::clicked, this, &Technologist::products_save);
	connect(_ui->save_technologies_table_btn, &QPushButton::clicked, this, &Technologist::technologies_save);
	connect(_ui->save_pas_com_table_btn, &QPushButton::clicked, this, &Technologist::pas_com_save);
	connect(_ui->save_equipment_table_btn, &QPushButton::clicked, this, &Technologist::equipment_save);
	connect(_ui->save_stones_table_btn, &QPushButton::clicked, this, &Technologist::stones_save);

	connect(_ui->stone_availability_btn, &QPushButton::clicked, this, &Technologist::stone_availability_btn_clicked);
	connect(_ui->metal_availability_btn, &QPushButton::clicked, this, &Technologist::metal_availability_btn_clicked);
	connect(_ui->param_search_btn, &QPushButton::clicked, this, &Technologist::param_search_btn_clicked);
}

Technologist::~Technologist() {
	delete _ui;
}


void Technologist::saveTableToFile(QTableWidget* tableWidget) {
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


void Technologist::product_types_save() {
	saveTableToFile(_product_types->_ui->output_table);
}

void Technologist::materials_save() {
	saveTableToFile(_materials->_ui->output_table);
}

void Technologist::metal_save() {
	saveTableToFile(_metal->_ui->output_table);
}

void Technologist::faceting_save() {
	saveTableToFile(_faceting->_ui->output_table);
}

void Technologist::pam_com_save() {
	saveTableToFile(_pam_com->_ui->output_table);
}

void Technologist::stages_save() {
	saveTableToFile(_stages->_ui->output_table);
}

void Technologist::products_save() {
	saveTableToFile(_products->_ui->output_table);
}

void Technologist::technologies_save() {
	saveTableToFile(_technologies->_ui->output_table);
}

void Technologist::pas_com_save() {
	saveTableToFile(_pas_com->_ui->output_table);
}

void Technologist::equipment_save() {
	saveTableToFile(_equipment->_ui->output_table);
}

void Technologist::stones_save() {
	saveTableToFile(_stones->_ui->output_table);
}


void Technologist::product_types_add() {
	QLayoutItem* child;
	while ((child = _ui->product_types_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_product_types = new QueryResult(this);

	sql::ResultSet* result = runQuery("SELECT вид_изделия.`Вид изделия` FROM `вид_изделия`;");
	if (result) {
		_product_types->addDataToTable(result);
		delete result;
	}

	_ui->product_types_layout->addWidget(_product_types);
}


void Technologist::materials_add() {
	QLayoutItem* child;
	while ((child = _ui->materials_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_materials = new QueryResult(this);

	sql::ResultSet* result = runQuery("SELECT дополнительные_материалы.`Дополнительный материал` FROM `дополнительные_материалы`;");
	if (result) {
		_materials->addDataToTable(result);
		delete result;
	}

	_ui->materials_layout->addWidget(_materials);
}


void Technologist::metal_add() {
	QLayoutItem* child;
	while ((child = _ui->metal_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_metal = new QueryResult(this);

	sql::ResultSet* result = runQuery("SELECT металл.`Вид металла`, металл.`Количество на складе, гр`, металл.`Цена за грамм, руб` FROM `металл`;");
	if (result) {
		_metal->addDataToTable(result);
		delete result;
	}

	_ui->metal_layout->addWidget(_metal);
}


void Technologist::faceting_add() {
	QLayoutItem* child;
	while ((child = _ui->faceting_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_faceting = new QueryResult(this);

	sql::ResultSet* result = runQuery("SELECT огранка.`Вид огранки` FROM `огранка`;");
	if (result) {
		_faceting->addDataToTable(result);
		delete result;
	}

	_ui->faceting_layout->addWidget(_faceting);
}


void Technologist::pam_com_add() {
	QLayoutItem* child;
	while ((child = _ui->pam_com_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_pam_com = new QueryResult(this);

	sql::ResultSet* result = runQuery("SELECT изделие.`Название изделия`, дополнительные_материалы.`Дополнительный материал`, связь_изделие_и_дополнительные_материалы.`Количество, гр` "
		"FROM `изделие` INNER JOIN `связь_изделие_и_дополнительные_материалы` ON изделие.`Код изделия` = связь_изделие_и_дополнительные_материалы.`Изделие` "
		"INNER JOIN `дополнительные_материалы` ON дополнительные_материалы.`Код материала` = связь_изделие_и_дополнительные_материалы.`Дополнительный материал`;");
	if (result) {
		_pam_com->addDataToTable(result);
		delete result;
	}

	_ui->pam_com_layout->addWidget(_pam_com);
}


void Technologist::stages_add() {
	QLayoutItem* child;
	while ((child = _ui->stages_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_stages = new QueryResult(this);

	sql::ResultSet* result = runQuery("SELECT стадии.`Стадия` FROM `стадии`;");
	if (result) {
		_stages->addDataToTable(result);
		delete result;
	}

	_ui->stages_layout->addWidget(_stages);
}


void Technologist::products_add() {
	QLayoutItem* child;
	while ((child = _ui->products_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_products = new QueryResult(this);

	sql::ResultSet* result = runQuery("SELECT Изделие.`Название изделия`, вид_изделия.`Вид изделия`, Изделие.`Цена, руб`, Металл.`Вид металла`, Изделие.`Вес металла, гр`, Камни.`Камень`, "
		"Камни.`Карат`, связь_изделие_и_камень.`Количество камней, шт`, Изделие.`Фото изделия` "
		"FROM Металл INNER JOIN Изделие ON Металл.`Код` = Изделие.`Металл` "
		"INNER JOIN вид_изделия ON вид_изделия.`Код` = изделие.`Вид изделия` "
		"INNER JOIN связь_изделие_и_камень ON связь_изделие_и_камень.`Изделие` = Изделие.`Код изделия` "
		"INNER JOIN камни ON связь_изделие_и_камень.`Камень` = камни.`Код`;");
	if (result) {
		_products->addDataToTable(result);
		delete result;
	}

	_ui->products_layout->addWidget(_products);
}


void Technologist::technologies_add() {
	QLayoutItem* child;
	while ((child = _ui->technologies_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_technologies = new QueryResult(this);

	sql::ResultSet* result = runQuery("SELECT изделие.`Название изделия`, стадии.`Стадия`, оборудование.`Оборудование`, технология.`Время, ч`, технология.`Мощность, ватт`, технология.`Температура, °C`, технология.`Цена производства, руб` "
		"FROM `технология` INNER JOIN `изделие` ON изделие.`Код изделия` = технология.`Изделие` "
		"INNER JOIN `стадии` ON стадии.`Номер` = технология.`Стадия` "
		"INNER JOIN `оборудование` ON оборудование.`Код` = технология.`Оборудование`;");

	if (result) {
		_technologies->addDataToTable(result);
		delete result;
	}

	_ui->technologies_layout->addWidget(_technologies);
}


void Technologist::pas_com_add() {
	QLayoutItem* child;
	while ((child = _ui->pas_com_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_pas_com = new QueryResult(this);

	sql::ResultSet* result = runQuery("SELECT изделие.`Название изделия`, камни.`Камень`, связь_изделие_и_камень.`Количество камней, шт` "
		"FROM `изделие` INNER JOIN `связь_изделие_и_камень` ON изделие.`Код изделия` = связь_изделие_и_камень.`Изделие` "
		"INNER JOIN `камни` ON камни.`Код` = связь_изделие_и_камень.`Камень`;");

	if (result) {
		_pas_com->addDataToTable(result);
		delete result;
	}

	_ui->pas_com_layout->addWidget(_pas_com);
}


void Technologist::equipment_add() {
	QLayoutItem* child;
	while ((child = _ui->equipment_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_equipment = new QueryResult(this);

	sql::ResultSet* result = runQuery("SELECT оборудование.`Оборудование` FROM `оборудование`;");

	if (result) {
		_equipment->addDataToTable(result);
		delete result;
	}

	_ui->equipment_layout->addWidget(_equipment);
}


void Technologist::stones_add() {
	QLayoutItem* child;
	while ((child = _ui->stones_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_stones = new QueryResult(this);

	sql::ResultSet* result = runQuery("SELECT камни.`Камень`, камни.`Карат`, камни.`Цена за карат, руб`, огранка.`Вид огранки` "
		"FROM `огранка` INNER JOIN `камни` ON огранка.`Код` = камни.`Вид огранки`;");

	if (result) {
		_stones->addDataToTable(result);
		delete result;
	}

	_ui->stones_layout->addWidget(_stones);
}


void Technologist::stone_availability_btn_clicked() {
	_ui->stone_availability_btn->setEnabled(false);

	std::string sql_query =
		"SELECT Камни.`Камень`, Камни.`Карат`, Огранка.`Вид огранки` "
		"FROM Камни INNER JOIN Огранка ON Камни.`Вид огранки` = Огранка.`Код` ";
	std::string condition = "WHERE ";
	
	QString stone = _ui->stone->currentText();

	if (!stone.isEmpty()) {
		if (condition != "WHERE ") {
			condition += " AND ";
		}
		condition += "Камни.`Камень` LIKE '" + stone.toStdString() + "%'";
	}
	else if (stone.isEmpty()) {
		QMessageBox::critical(this, "Ошибка", "Вы ввели пустое значение!");
		_ui->stone_availability_btn->setEnabled(true);
		return;
	}

	sql_query += condition + ';';

	QLayoutItem* child;
	while ((child = _ui->stones_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_stones = new QueryResult(this);

	sql::ResultSet* result = runQuery(sql_query);

	if (result) {
		_stones->addDataToTable(result);
		delete result;
	}

	_ui->stones_layout->addWidget(_stones);
	_ui->stone_availability_btn->setEnabled(true);
}


void Technologist::metal_availability_btn_clicked() {
	_ui->metal_availability_btn->setEnabled(false);

	std::string sql_query =
		"SELECT Металл.`Вид металла`, Металл.`Количество на складе, гр` "
		"FROM Металл ";
	std::string condition = "WHERE ";

	QString metal = _ui->metal->currentText();

	if (!metal.isEmpty()) {
		if (condition != "WHERE ") {
			condition += " AND ";
		}
		condition += "Металл.`Вид металла` LIKE '" + metal.toStdString() + "%'";
	}
	else if (metal.isEmpty()) {
		QMessageBox::critical(this, "Ошибка", "Вы ввели пустое значение!");
		_ui->metal_availability_btn->setEnabled(true);
		return;
	}

	sql_query += condition + ';';

	QLayoutItem* child;
	while ((child = _ui->metal_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_metal = new QueryResult(this);

	sql::ResultSet* result = runQuery(sql_query);

	if (result) {
		_metal->addDataToTable(result);
		delete result;
	}

	_ui->metal_layout->addWidget(_metal);
	_ui->metal_availability_btn->setEnabled(true);
}


void Technologist::param_search_btn_clicked() {
	_ui->param_search_btn->setEnabled(false);

	std::string sql_query =
		"SELECT изделие.`Название изделия`, стадии.`Стадия`, оборудование.`Оборудование`, технология.`Время, ч`, "
		"технология.`Мощность, ватт`, технология.`Температура, °C`, технология.`Цена производства, руб` "
		"FROM `технология` INNER JOIN `изделие` ON изделие.`Код изделия` = технология.`Изделие` "
		"INNER JOIN `стадии` ON стадии.`Номер` = технология.`Стадия` "
		"INNER JOIN `оборудование` ON оборудование.`Код` = технология.`Оборудование` ";
	std::string condition = "WHERE ";

	if (!_ui->product->currentText().isEmpty()) {
		QString product = _ui->product->currentText();

		if (!product.isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "Изделие.`Название изделия` LIKE '" + product.toStdString() + "%'";
		}
	}

	if (!_ui->stage->currentText().isEmpty()) {
		QString stage = _ui->stage->currentText();

		if (!stage.isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "стадии.`Стадия` LIKE '" + stage.toStdString() + "%'";
		}
	}

	if (!_ui->equipment->currentText().isEmpty()) {
		QString equipment = _ui->equipment->currentText();

		if (!equipment.isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "оборудование.`Оборудование` LIKE '" + equipment.toStdString() + "%'";
		}
	}

	if (!_ui->lower_time->text().isEmpty() || !_ui->higher_time->text().isEmpty()) {
		QString lower_time = _ui->lower_time->text();
		QString higher_time = _ui->higher_time->text();

		if (!_ui->lower_time->text().isEmpty() && !_ui->higher_time->text().isEmpty()) {
			if (lower_time.toDouble() <= higher_time.toDouble()) {
				if (condition != "WHERE ") {
					condition += " AND ";
				}
				condition += "технология.`Время, ч` BETWEEN " + lower_time.toStdString() + " AND " + higher_time.toStdString();
			}
			else {
				QMessageBox::critical(this, "Ошибка", "Введённое минимальное время завершения больше чем максимальное!");
				_ui->param_search_btn->setEnabled(true);
				return;
			}
		}
		else if (!_ui->lower_time->text().isEmpty() && _ui->higher_time->text().isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "технология.`Время, ч` BETWEEN " + lower_time.toStdString() + " AND 100000 ";
		}
		else if (_ui->lower_time->text().isEmpty() && !_ui->higher_time->text().isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "технология.`Время, ч` BETWEEN 0 AND " + higher_time.toStdString();
		}
	}

	if (!_ui->lower_power->text().isEmpty() || !_ui->higher_power->text().isEmpty()) {
		QString lower_power = _ui->lower_power->text();
		QString higher_power = _ui->higher_power->text();

		if (!_ui->lower_power->text().isEmpty() && !_ui->higher_power->text().isEmpty()) {
			if (lower_power.toDouble() <= higher_power.toDouble()) {
				if (condition != "WHERE ") {
					condition += " AND ";
				}
				condition += "технология.`Мощность, ватт` BETWEEN " + lower_power.toStdString() + " AND " + higher_power.toStdString();
			}
			else {
				QMessageBox::critical(this, "Ошибка", "Введённая минимальная мощность больше чем максимальная!");
				_ui->param_search_btn->setEnabled(true);
				return;
			}
		}
		else if (!_ui->lower_power->text().isEmpty() && _ui->higher_power->text().isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "технология.`Мощность, ватт` BETWEEN " + lower_power.toStdString() + " AND 100000 ";
		}
		else if (_ui->lower_power->text().isEmpty() && !_ui->higher_power->text().isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "технология.`Мощность, ватт` BETWEEN 0 AND " + higher_power.toStdString();
		}
	}

	if (!_ui->lower_temp->text().isEmpty() || !_ui->higher_temp->text().isEmpty()) {
		QString lower_temp = _ui->lower_temp->text();
		QString higher_temp = _ui->higher_temp->text();
		if (!_ui->lower_temp->text().isEmpty() && !_ui->higher_temp->text().isEmpty()) {
			if (lower_temp.toDouble() <= higher_temp.toDouble()) {
				if (condition != "WHERE ") {
					condition += " AND ";
				}
				condition += "технология.`Температура, °C` BETWEEN " + lower_temp.toStdString() + " AND " + higher_temp.toStdString();
			}
			else {
				QMessageBox::critical(this, "Ошибка", "Введённая минимальная температура больше чем максимальная!");
				_ui->param_search_btn->setEnabled(true);
				return;
			}
		}
		else if (!_ui->lower_temp->text().isEmpty() && _ui->higher_temp->text().isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "технология.`Температура, °C` BETWEEN " + lower_temp.toStdString() + " AND 100000 ";
		}
		else if (_ui->lower_temp->text().isEmpty() && !_ui->higher_temp->text().isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "технология.`Температура, °C` BETWEEN 0 AND " + higher_temp.toStdString();
		}
	}

	if (!_ui->lower_price->text().isEmpty() || !_ui->higher_price->text().isEmpty()) {
		QString lower_price = _ui->lower_price->text();
		QString higher_price = _ui->higher_price->text();

		if (!_ui->lower_price->text().isEmpty() && !_ui->higher_price->text().isEmpty()) {
			if (lower_price.toDouble() <= higher_price.toDouble()) {
				if (condition != "WHERE ") {
					condition += " AND ";
				}
				condition += "технология.`Цена производства, руб` BETWEEN " + lower_price.toStdString() + " AND " + higher_price.toStdString();
			}
			else {
				QMessageBox::critical(this, "Ошибка", "Введённая минимальная цена производства больше чем максимальная!");
				_ui->param_search_btn->setEnabled(true);
				return;
			}
		}
		else if (!_ui->lower_price->text().isEmpty() && _ui->higher_price->text().isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "технология.`Цена производства, руб` BETWEEN " + lower_price.toStdString() + " AND 100000000000000 ";
		}
		else if (_ui->lower_price->text().isEmpty() && !_ui->higher_price->text().isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "технология.`Цена производства, руб` BETWEEN 0 AND " + higher_price.toStdString();
		}
	}

	if (!(_ui->product->currentText().isEmpty() && _ui->stage->currentText().isEmpty() && _ui->equipment->currentText().isEmpty() &&
		_ui->lower_time->text().isEmpty() && _ui->higher_time->text().isEmpty() && 
		_ui->lower_power->text().isEmpty() && _ui->higher_power->text().isEmpty() &&
		_ui->lower_temp->text().isEmpty() && _ui->higher_temp->text().isEmpty() &&
		_ui->lower_price->text().isEmpty() && _ui->higher_price->text().isEmpty())) {

		sql_query += condition + ';';
	}
	
	
	QLayoutItem* child;
	while ((child = _ui->technologies_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_technologies = new QueryResult(this);

	sql::ResultSet* result = runQuery(sql_query);

	if (result) {
		_technologies->addDataToTable(result);
		delete result;
	}

	_ui->technologies_layout->addWidget(_technologies);
	_ui->param_search_btn->setEnabled(true);
}


void Technologist::setupComboBoxes() {
	std::string sql_query = "SELECT DISTINCT `Название изделия` FROM `Изделие`;";
	QStringList dataList = getDataFromTable(sql_query);
	setupComboBox(_ui->product, dataList);

	sql_query = "SELECT DISTINCT `Оборудование` FROM `Оборудование`;";
	dataList = getDataFromTable(sql_query);
	setupComboBox(_ui->equipment, dataList);

	sql_query = "SELECT DISTINCT `Стадия` FROM `Стадии`;";
	dataList = getDataFromTable(sql_query);
	setupComboBox(_ui->stage, dataList);

	sql_query = "SELECT DISTINCT `Камень` FROM `Камни`;";
	dataList = getDataFromTable(sql_query);
	setupComboBox(_ui->stone, dataList);

	sql_query = "SELECT DISTINCT `Вид металла` FROM `Металл`;";
	dataList = getDataFromTable(sql_query);
	setupComboBox(_ui->metal, dataList);
}
