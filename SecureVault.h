#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SecureVault.h"
#include <QString>
#include <QMessageBox>
#include "SecureItem.h"
#include "SignUp.h"

class SecureVault : public QMainWindow {
    Q_OBJECT

public:
    SecureVault(QWidget* parent = nullptr);
    ~SecureVault();
private slots:
    void on_Register_clicked();
    void on_Clean_clicked();
    void on_SignUp_clicked();
private:
    Ui::SecureVaultClass ui;
};

