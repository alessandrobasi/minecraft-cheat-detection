#include "MCcheatdetection.h"
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QThread>

using namespace std;

MCcheatdetection::MCcheatdetection(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QList<QPair<QString, void (MCcheatdetection::*)() > > listadicose = {
        QPair("Rename versions\'s Dir", &MCcheatdetection::printTest), // &MCcheatdetection::runRenameVersions
        QPair("Controllare cartella libraries", &MCcheatdetection::printTest),
        QPair("Controllare file launcher profiles", &MCcheatdetection::printTest),
        QPair("Cercare in %TEMP%", &MCcheatdetection::printTest), // jnativehook
        QPair("Cercare in prefetch", &MCcheatdetection::printTest), // autoclicker, vape
        QPair("Cercare nei file recenti", &MCcheatdetection::printTest) // shell:recent
    };

    for each (QPair<QString, void (MCcheatdetection::*)()> pairing in listadicose)
    {
        QListWidgetItem* item = new QListWidgetItem(pairing.first, ui.passaggiEseguire);
        item->setData(Qt::UserRole, pairing.second);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        item->setCheckState(Qt::Checked); // AND initialize check state

    }
    
    connect(ui.iniziaControllo, SIGNAL(clicked()), this, SLOT(printTest()));

}

//void AppControlliMC::ChangeScreen(wchar_t* uiFilename, void (*f)()) {/* TODO: ??? */}

void MCcheatdetection::runRenameVersions(int i) {
    QThread* thread = new QThread();
    connect(thread, SIGNAL(started()), azioniControllo, SLOT(renameMCVersions()));
    connect(thread, SIGNAL(resultValue(int)), this, SLOT(resultThread(int, i)));
    thread->start();
}

void MCcheatdetection::resultThread(int result, int i) {
    qDebug("funzione ritorna :",result , " Con i=" , i);
}

void MCcheatdetection::printTest() {
    ui.iniziaControllo->setStyleSheet("background-color:red;");
    qDebug("start Thread");
    MCcheatdetection::runRenameVersions(1);
}
