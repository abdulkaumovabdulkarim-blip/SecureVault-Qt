// SecureVault.cpp

#include "SecureVault.h"
#include "SignUp.h"
#include "MainMenu.h"

SecureVault::SecureVault(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}
void SecureVault::on_Register_clicked() {
    QString user = ui.Username->text().trimmed();
    QString pass = ui.Password->text().trimmed();

    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Missing Data", "Please fill in all fields!");
        return;
    }

    try {
        SecureItem::getInstance().signIn(user.toStdString(), pass.toStdString());
		QMessageBox::information(this, "Success", "You have successfully signed in!\nWelcome back!");

        MainMenu* mainMenu = new MainMenu();
        mainMenu->setAttribute(Qt::WA_DeleteOnClose);
        mainMenu->show();
        this->hide();
    }
    catch(const char* ms){
        QMessageBox::warning(this, "ERROR", ms);
    }

}
void SecureVault::on_Clean_clicked() {
    auto validation = QMessageBox::question(this, "Validation", "Are you sure you want to clear the fields?", QMessageBox::Yes | QMessageBox::No);

    if (validation == QMessageBox::Yes) {
        ui.Username->clear();
        ui.Password->clear();
    }
}

void SecureVault::on_SignUp_clicked() {
    SignUp* signUp = new SignUp();
    signUp->setAttribute(Qt::WA_DeleteOnClose);
    signUp->show();
    this->hide();
}
SecureVault::~SecureVault()
{}

