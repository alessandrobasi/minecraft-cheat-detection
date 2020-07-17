#include "MCcheatdetection.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{

    QApplication Application(argc, argv);
    MCcheatdetection window;
    
    window.show();
    return Application.exec();
}
