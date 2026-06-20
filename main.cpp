#include "SecureVault.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SecureVault window;
    window.show();
    return app.exec();
}
