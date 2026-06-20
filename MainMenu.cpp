// MainMenu.cpp

#include "MainMenu.h"
#include "SecureVault.h"
#include "SecureItem.h"
#include "InfoChange.h"
#include <QString>

MainMenu::MainMenu(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// Display the current user's username
	if (!SecureItem::getInstance().getUserData().empty()) {
		QString currentUserName = QString::fromStdString(SecureItem::getInstance().getUserData()[0].owner);
		ui.Username->setText("Username: " + currentUserName);
	}
	else {
		ui.Username->setText("Username: Connected");
	}
	// Set up the table widget for displaying websites
	ui.WebsList->setColumnCount(1);
	ui.WebsList->setHorizontalHeaderLabels(QStringList() << "My Websites");
	ui.WebsList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	// Hide the vertical header and grid lines for a cleaner look
	ui.WebsList->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.WebsList->setSelectionMode(QAbstractItemView::SingleSelection);

	updateTable();
}
void MainMenu::updateTable() {
	try {
		ui.WebsList->setRowCount(0); 
		
		std::vector<VaultBinary> data = SecureItem::getInstance().getUserData();

		// Populate the table with the user's websites
		for (size_t i = 0; i < data.size(); ++i) {
			int rowCount = ui.WebsList->rowCount();
			ui.WebsList->insertRow(rowCount);

			// Create a new table item with the website name and set it to be non-editable
			QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(data[i].website));

			
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);

			ui.WebsList->setItem(rowCount, 0, item);
		}
	}
	catch (const char* ms) {
		QMessageBox::warning(this, "ERROR", ms);
	}
}
void MainMenu::on_WebsList_itemDoubleClicked(QTableWidgetItem* item) {
	int selectedRow = ui.WebsList->currentRow();
	if (selectedRow < 0) return;

	try {
		std::vector<VaultBinary> data = SecureItem::getInstance().getUserData();
		if (selectedRow >= data.size()) return;

		VaultBinary selectedRowData = data[selectedRow];

		InfoChange* infoChangeDialog = new InfoChange(selectedRow, selectedRowData, this);
		infoChangeDialog->setAttribute(Qt::WA_DeleteOnClose);
		infoChangeDialog->show();
	}
	catch (const char* ms) {
		QMessageBox::warning(this, "ERROR", ms);
	}
}
void MainMenu::on_LogOut_clicked() {
	SecureItem::getInstance().logOut();
	SecureVault* signIn = new SecureVault();
	signIn->show();
	this->hide();
}
void MainMenu::on_AddNew_clicked() {
	VaultBinary emptyItem{};

	InfoChange* infoChangeDialog = new InfoChange(-1, emptyItem, this);
	infoChangeDialog->setAttribute(Qt::WA_DeleteOnClose);
	infoChangeDialog->show();
}
MainMenu::~MainMenu()
{}

