// InfoChange.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "InfoChange.h"
#include "MainMenu.h"
#include <QMessageBox>


InfoChange::InfoChange(int index, VaultBinary data, QWidget* parent)
	: QMainWindow(parent), m_index(index)
{
	ui.setupUi(this);

	setWindowModality(Qt::WindowModal);

	if (m_index != -1) {
		ui.website->setText(QString::fromStdString(data.website));
		ui.password->setText(QString::fromStdString(data.password));
		ui.lineEdit->setText(QString::fromStdString(data.note));
	}
}
void InfoChange::on_save_clicked() {
	QString web = ui.website->text().trimmed();
	QString pass = ui.password->text().trimmed();
	QString note = ui.lineEdit->text().trimmed();

	if (web.isEmpty() || pass.isEmpty()) {
		QMessageBox::warning(this, "Warning", "Website and Password fields cannot be empty!");
		return;
	}

	VaultBinary item;
	strncpy(item.website, web.toStdString().c_str(), sizeof(item.website) - 1);
	item.website[sizeof(item.website) - 1] = '\0';

	strncpy(item.password, pass.toStdString().c_str(), sizeof(item.password) - 1);
	item.password[sizeof(item.password) - 1] = '\0';

	strncpy(item.note, note.toStdString().c_str(), sizeof(item.note) - 1);
	item.note[sizeof(item.note) - 1] = '\0';

	try {
		// Сохраняем в бэкенд
		SecureItem::getInstance().saveOrUpdate(item, m_index);

		MainMenu* mainTheme = qobject_cast<MainMenu*>(parentWidget());
		if (mainTheme) {
			mainTheme->updateTable();
		}

		this->close();
	}
	catch (const char* ms) {
		QMessageBox::warning(this, "Error", ms);
	}
}
void InfoChange::on_clean_clicked() {
	auto validation = QMessageBox::question(this, "Clear", "Are you sure you want to clear all fields?", QMessageBox::Yes | QMessageBox::No);
	if (validation == QMessageBox::Yes) {
		ui.website->clear();
		ui.password->clear();
		ui.lineEdit->clear();
	}
}
InfoChange::~InfoChange()
{
}