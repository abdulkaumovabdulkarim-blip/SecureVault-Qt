// InfoChange.h

#pragma once

#include <QMainWindow>
#include "ui_InfoChange.h"
#include "SecureItem.h"

class InfoChange : public QMainWindow
{
	Q_OBJECT

public:
	InfoChange(int index = -1, VaultBinary data = VaultBinary(), QWidget* parent = nullptr);
	~InfoChange();
private slots:
	void on_save_clicked();
	void on_clean_clicked();
private:
	Ui::InfoChangeClass ui;
	int m_index;
};

