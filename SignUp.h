#pragma once

#include <QMainWindow>
#include "ui_SignUp.h"

class SignUp : public QMainWindow
{
	Q_OBJECT

public:
	SignUp(QWidget *parent = nullptr);
	~SignUp();
private slots:
	void on_Register_clicked();
	void on_Clean_clicked();
	void on_SingIn_clicked();
private:
	Ui::SignUpClass ui;
};

