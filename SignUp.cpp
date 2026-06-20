// SignUp.cpp 

#include "SignUp.h"
#include "SecureVault.h"
#include "MainMenu.h"
SignUp::SignUp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}
void SignUp::on_Register_clicked() {
    QString user = ui.Username->text().trimmed();
    QString pass = ui.Password->text().trimmed();

    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Missing Data", "Please fill in all fields!");
        return;
    }

    try {
        SecureItem::getInstance().signUp(user.toStdString(), pass.toStdString());
        SecureItem::getInstance().signIn(user.toStdString(), pass.toStdString());
        QMessageBox::information(this, "Success", "You have successfully registered!\nWelcome to SecureVault!");

        MainMenu* mainMenu = new MainMenu();
        mainMenu->setAttribute(Qt::WA_DeleteOnClose);
        mainMenu->show();
        this->hide();
    }
    catch (const char* ms) {
        QMessageBox::warning(this, "ERROR", ms);
        ui.Password->clear();
    }

}
void SignUp::on_Clean_clicked() {
	auto validation = QMessageBox::question(this, "Validation", "Are you sure you want to clear the fields?", QMessageBox::Yes | QMessageBox::No);

	if (validation == QMessageBox::Yes) {
		ui.Username->clear();
		ui.Password->clear();
	}
}
void SignUp::on_SingIn_clicked() {
	SecureVault* signIn = new SecureVault();
    signIn->setAttribute(Qt::WA_DeleteOnClose);
	signIn->show();
	this->hide();
}
SignUp::~SignUp()
{}