#include "customer.h"
#include "database.h"
#include "qmessagebox.h"
#include <QInputDialog>
#include <qfiledialog.h>


Customer::Customer(QWidget* parent) : QMainWindow(parent), _ui(new Ui::CustomerClass()) {
	// Инициализация главного окна
	_ui->setupUi(this);

	// Установка флагов размера окна
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	setWindowFlags(windowFlags() & ~(Qt::WindowFullscreenButtonHint | Qt::WindowMaximizeButtonHint));
	setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
	setWindowModality(Qt::WindowModal);

	products_add();
	setupComboBoxes();

	connect(_ui->upd_products_table_btn, &QPushButton::clicked, this, &Customer::products_add);
	connect(_ui->save_products_table_btn, &QPushButton::clicked, this, &Customer::products_save);

	connect(_ui->param_search_btn, &QPushButton::clicked, this, &Customer::param_search_btn_clicked);
}

Customer::~Customer() {
	delete _ui;
}


void Customer::saveTableToFile(QTableWidget* tableWidget) {
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


void Customer::products_save() {
	saveTableToFile(_products->_ui->output_table);
}


void Customer::products_add() {
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



void Customer::param_search_btn_clicked() {
	_ui->param_search_btn->setEnabled(false);

	std::string sql_query =
		"SELECT Изделие.`Название изделия`, вид_изделия.`Вид изделия`, Изделие.`Цена, руб`, Металл.`Вид металла`, Изделие.`Вес металла, гр`, Камни.`Камень`, "
		"Камни.`Карат`, связь_изделие_и_камень.`Количество камней, шт`, Изделие.`Фото изделия` "
		"FROM Металл INNER JOIN Изделие ON Металл.`Код` = Изделие.`Металл` "
		"INNER JOIN вид_изделия ON вид_изделия.`Код` = изделие.`Вид изделия` "
		"INNER JOIN связь_изделие_и_камень ON связь_изделие_и_камень.`Изделие` = Изделие.`Код изделия` "
		"INNER JOIN камни ON связь_изделие_и_камень.`Камень` = камни.`Код` ";
	std::string condition = "WHERE ";
	
	if (!_ui->product_type->currentText().isEmpty()) {
		QString type = _ui->product_type->currentText();

		if (!type.isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "вид_изделия.`Вид изделия` LIKE '" + type.toStdString() + "%'";
		}
	}

	if (!_ui->stone->currentText().isEmpty()) {
		QString stone = _ui->stone->currentText();

		if (!stone.isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "Камни.`Камень` LIKE '" + stone.toStdString() + "%'";
		}
	}

	if (!_ui->metal->currentText().isEmpty()) {
		QString metal = _ui->metal->currentText();

		if (!metal.isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "Металл.`Вид металла` LIKE '" + metal.toStdString() + "%'";
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
				condition += "изделие.`Цена, руб` BETWEEN " + lower_price.toStdString() + " AND " + higher_price.toStdString();
			}
			else {
				QMessageBox::critical(this, "Ошибка", "Введённая минимальная цена больше чем максимальная!");
				_ui->param_search_btn->setEnabled(true);
				return;
			}
		}
		else if (!_ui->lower_price->text().isEmpty() && _ui->higher_price->text().isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "изделие.`Цена, руб` BETWEEN " + lower_price.toStdString() + " AND 100000000000000 ";
		}
		else if (_ui->lower_price->text().isEmpty() && !_ui->higher_price->text().isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "изделие.`Цена, руб` BETWEEN 0 AND " + higher_price.toStdString();
		}
	}

	if (!(_ui->product_type->currentText().isEmpty() && _ui->stone->currentText().isEmpty() && _ui->metal->currentText().isEmpty() &&
		_ui->lower_price->text().isEmpty() && _ui->higher_price->text().isEmpty())) {
		sql_query += condition + ';';
	}

	QLayoutItem* child;
	while ((child = _ui->products_layout->takeAt(0)) != nullptr) {
		delete child->widget(); // Удаляем виджеты
		delete child; // Освобождаем память после элемента компоновки
	}

	_products = new QueryResult(this);

	sql::ResultSet* result = runQuery(sql_query);

	if (result) {
		_products->addDataToTable(result);
		delete result;
	}

	_ui->products_layout->addWidget(_products);
	_ui->param_search_btn->setEnabled(true);
}


void Customer::setupComboBoxes() {
	std::string sql_query = "SELECT DISTINCT `Вид изделия` FROM `вид_изделия`;";
	QStringList dataList = getDataFromTable(sql_query);
	setupComboBox(_ui->product_type, dataList);

	sql_query = "SELECT DISTINCT `Камень` FROM `Камни`;";
	dataList = getDataFromTable(sql_query);
	setupComboBox(_ui->stone, dataList);

	sql_query = "SELECT DISTINCT `Вид металла` FROM `Металл`;";
	dataList = getDataFromTable(sql_query);
	setupComboBox(_ui->metal, dataList);
}
