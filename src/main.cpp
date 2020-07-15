#include "MCcheatdetection.h"
#include "AzioniControllo.h"
#include <QtWidgets/QApplication>
#include <QMetaType>

int main(int argc, char *argv[])
{

    QApplication Application(argc, argv);
    MCcheatdetection window;
    
    window.show();
    return Application.exec();
}
