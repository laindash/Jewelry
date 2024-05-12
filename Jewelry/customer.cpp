#include "customer.h"
#include "database.h"
#include "qmessagebox.h"
#include <QInputDialog>


Customer::Customer(QWidget* parent) : QMainWindow(parent), _ui(new Ui::CustomerClass()), _query_result(nullptr) {
	// Инициализация главного окна
	_ui->setupUi(this);

	// Установка флагов размера окна
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	setWindowFlags(windowFlags() & ~(Qt::WindowFullscreenButtonHint | Qt::WindowMaximizeButtonHint));
	setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);

	connect(_ui->products_btn, &QPushButton::clicked, this, &Customer::products_btn_clicked);
	connect(_ui->product_types_btn, &QPushButton::clicked, this, &Customer::product_types_btn_clicked);
	connect(_ui->stones_btn, &QPushButton::clicked, this, &Customer::stones_btn_clicked);
	connect(_ui->metal_btn, &QPushButton::clicked, this, &Customer::metal_btn_clicked);
	connect(_ui->param_search_btn, &QPushButton::clicked, this, &Customer::param_search_btn_clicked);
}

Customer::~Customer() {
	delete _ui;
}


void Customer::products_btn_clicked() {
	_ui->products_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Customer::enableProductsButton);
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

void Customer::enableProductsButton() {
	_ui->products_btn->setEnabled(true);
	this->show();
}


void Customer::product_types_btn_clicked() {
	_ui->product_types_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Customer::enableProductTypesButton);
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

void Customer::enableProductTypesButton() {
	_ui->product_types_btn->setEnabled(true);
	this->show();
}


void Customer::stones_btn_clicked() {
	_ui->stones_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Customer::enableStonesButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT камни.`Камень` "
		"FROM `камни`;");

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

void Customer::enableStonesButton() {
	_ui->stones_btn->setEnabled(true);
	this->show();
}


void Customer::metal_btn_clicked() {
	_ui->metal_btn->setEnabled(false);
	this->hide();
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Customer::enableMetalButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery("SELECT металл.`Вид металла` FROM `металл`;");
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

void Customer::enableMetalButton() {
	_ui->metal_btn->setEnabled(true);
	this->show();
}


void Customer::param_search_btn_clicked() {
	_ui->param_search_btn->setEnabled(false);
	this->hide();
	std::string sql_query =
		"SELECT Изделие.`Название изделия`, вид_изделия.`Вид изделия`, Изделие.`Цена, руб`, Металл.`Вид металла`, Изделие.`Вес металла, гр`, Камни.`Камень`, "
		"Камни.`Карат`, связь_изделие_и_камень.`Количество камней, шт`, Изделие.`Фото изделия` "
		"FROM Металл INNER JOIN Изделие ON Металл.`Код` = Изделие.`Металл` "
		"INNER JOIN вид_изделия ON вид_изделия.`Код` = изделие.`Вид изделия` "
		"INNER JOIN связь_изделие_и_камень ON связь_изделие_и_камень.`Изделие` = Изделие.`Код изделия` "
		"INNER JOIN камни ON связь_изделие_и_камень.`Камень` = камни.`Код` ";
	std::string condition = "WHERE ";
	

	if (_ui->type_check->isChecked()) {
		bool ok;
		QString type = QInputDialog::getText(this, "Введите вид изделия", "Вид изделия:", QLineEdit::Normal, "", &ok);

		if (ok && !type.isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "вид_изделия.`Вид изделия` = '" + type.toStdString() + "'";
		}
		else if (!ok) {
			_ui->param_search_btn->setEnabled(true);
			this->show();
			return;
		}
		else if (type.isEmpty()) {
			QMessageBox::critical(this, "Ошибка", "Вы ввели пустое значение!");
			_ui->param_search_btn->setEnabled(true);
			this->show();
			return;
		}
	}

	if (_ui->stone_check->isChecked()) {
		bool ok;
		QString stone = QInputDialog::getText(this, "Введите камень", "Название камня:", QLineEdit::Normal, "", &ok);

		if (ok && !stone.isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "Камни.`Камень` = '" + stone.toStdString() + "'";
		}
		else if (!ok) {
			_ui->param_search_btn->setEnabled(true);
			this->show();
			return;
		}
		else if (stone.isEmpty()) {
			QMessageBox::critical(this, "Ошибка", "Вы ввели пустое значение!");
			_ui->param_search_btn->setEnabled(true);
			this->show();
			return;
		}
	}

	if (_ui->metal_check->isChecked()) {
		bool ok;
		QString metal = QInputDialog::getText(this, "Введите металл", "Название металла:", QLineEdit::Normal, "", &ok);

		if (ok && !metal.isEmpty()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "Металл.`Вид металла` = '" + metal.toStdString() + "'";
		}
		else if (!ok) {
			_ui->param_search_btn->setEnabled(true);
			this->show();
			return;
		}
		else if (metal.isEmpty()) {
			QMessageBox::critical(this, "Ошибка", "Вы ввели пустое значение!");
			_ui->param_search_btn->setEnabled(true);
			this->show();
			return;
		}
	}

	if (_ui->price_check->isChecked()) {
		bool ok;

		QString lower_price = QInputDialog::getText(this, "Введите минимальную цену", "Минимальная цена:", QLineEdit::Normal, "", &ok);
		if (!ok) {
			_ui->param_search_btn->setEnabled(true);
			this->show();
			return;
		}
		else if (lower_price.isEmpty()) {
			QMessageBox::critical(this, "Ошибка", "Вы ввели пустое значение!");
			_ui->param_search_btn->setEnabled(true);
			this->show();
			return;
		}

		QString higher_price = QInputDialog::getText(this, "Введите максимальную цену", "Максимальная цена:", QLineEdit::Normal, "", &ok);
		if (!ok) {
			_ui->param_search_btn->setEnabled(true);
			this->show();
			return;
		}
		else if (higher_price.isEmpty()) {
			QMessageBox::critical(this, "Ошибка", "Вы ввели пустое значение!");
			_ui->param_search_btn->setEnabled(true);
			this->show();
			return;
		}

		if (lower_price.toDouble() <= higher_price.toDouble()) {
			if (condition != "WHERE ") {
				condition += " AND ";
			}
			condition += "изделие.`Цена, руб` BETWEEN " + lower_price.toStdString() + " AND " + higher_price.toStdString();
		}
		else {
			QMessageBox::critical(this, "Ошибка", "Введённая минимальная цена больше чем максимальная!");
			_ui->param_search_btn->setEnabled(true);
			this->show();
			return;
		}
	}

	if (!(_ui->metal_check->isChecked() || _ui->stone_check->isChecked() || _ui->type_check->isChecked() || _ui->price_check->isChecked())) {
		QMessageBox::warning(this, "Предупреждение", "Вы не выбрали ни один из параметров для поиска!");
		_ui->param_search_btn->setEnabled(true);
		this->show();
		return;
	}

	sql_query += condition + ';';
	_query_result = new QueryResult(this);

	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_query_result, &QObject::destroyed, this, &Customer::enableParamSearchButton);
	_query_result->setAttribute(Qt::WA_DeleteOnClose); //clear memory

	sql::ResultSet* result = runQuery(sql_query);
	if (result) {
		_query_result->addDataToTable(result);
		delete result;
		_query_result->show();
	}
	else {
		QMessageBox::information(this, "Информация", "Данные не найдены!");
		delete _query_result;
		delete result;
		_ui->param_search_btn->setEnabled(true);
		this->show();
	}
}

void Customer::enableParamSearchButton() {
	_ui->param_search_btn->setEnabled(true);
	this->show();
}