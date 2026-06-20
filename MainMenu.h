#pragma once

#include <QMainWindow>
#include "ui_MainMenu.h"

class MainMenu : public QMainWindow
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = nullptr);
	~MainMenu();
	void updateTable();
private slots:
	void on_WebsList_itemDoubleClicked(QTableWidgetItem* item);
	void on_LogOut_clicked();
	void on_AddNew_clicked();
private:
	Ui::MainMenuClass ui;
};

