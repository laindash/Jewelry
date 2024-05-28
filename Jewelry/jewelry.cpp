#include "jewelry.h"
#include <iostream>
#include <qmessagebox.h>


Jewelry::Jewelry(QWidget *parent) : QMainWindow(parent), _ui(new Ui::JewelryClass()), 
	_technologist(nullptr), _admin(nullptr), _customer(nullptr) {

	// Инициализация главного окна
	_ui->setupUi(this);

	// Установка флагов размера окна
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	setWindowFlags(windowFlags() & ~(Qt::WindowFullscreenButtonHint | Qt::WindowMaximizeButtonHint));


	// Подключение сигналов к слотам для кнопок
	connect(_ui->technologist_btn, &QPushButton::clicked, this, &Jewelry::technologist_btn_clicked);
	connect(_ui->admin_btn, &QPushButton::clicked, this, &Jewelry::admin_btn_clicked);
	connect(_ui->customer_btn, &QPushButton::clicked, this, &Jewelry::customer_btn_clicked);
}

Jewelry::~Jewelry() {
    delete _ui;
}


void Jewelry::technologist_btn_clicked() {
	_ui->technologist_btn->setEnabled(false);
	_technologist = new Technologist(this);
	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_technologist, &QObject::destroyed, this, &Jewelry::enableTechnologistButton);
	_technologist->setAttribute(Qt::WA_DeleteOnClose); //clear memory
	_technologist->show();
}

void Jewelry::enableTechnologistButton() {
	_ui->technologist_btn->setEnabled(true);
}


void Jewelry::admin_btn_clicked() {
	_ui->admin_btn->setEnabled(false);
	_admin = new Admin(this);
	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_admin, &QObject::destroyed, this, &Jewelry::enableAdminButton);
	_admin->setAttribute(Qt::WA_DeleteOnClose); //clear memory
	_admin->show();
}

void Jewelry::enableAdminButton() {
	_ui->admin_btn->setEnabled(true);
}


void Jewelry::customer_btn_clicked() {
	_ui->customer_btn->setEnabled(false);
	_customer = new Customer(this);
	// Подключение сигнала destroyed() к слоту, который включает кнопку
	connect(_customer, &QObject::destroyed, this, &Jewelry::enableCustomerButton);
	_customer->setAttribute(Qt::WA_DeleteOnClose); //clear memory
	_customer->show();
}

void Jewelry::enableCustomerButton() {
	_ui->customer_btn->setEnabled(true);
}
