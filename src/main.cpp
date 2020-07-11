#include "AppControlliMC.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication Finestra(argc, argv);
    AppControlliMC SchermataMain;
    SchermataMain.show();
    return Finestra.exec();
}
