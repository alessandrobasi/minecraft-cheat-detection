#include "AppControlliMC.h"
#include "AzioniControllo.h"
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QThread>

using namespace std;

AppControlliMC::AppControlliMC(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    std::vector<std::pair<QString, void (AppControlliMC::*)() > > listadicose = {
        std::make_pair("Rinominare cartella versions", &AppControlliMC::runRenameVersions),
        std::make_pair("Controllare cartella libraries", &AppControlliMC::printTest),
        std::make_pair("Controllare file launcher profiles", &AppControlliMC::printTest),
        std::make_pair("Cercare in %TEMP%", &AppControlliMC::printTest), // jnativehook
        std::make_pair("Cercare in prefetch", &AppControlliMC::printTest), // autoclicker, vape
        std::make_pair("Cercare nei file recenti", &AppControlliMC::printTest) // shell:recent
    };

    for each (auto pairing in listadicose)
    {
        QListWidgetItem* item = new QListWidgetItem(pairing.first, ui.passaggiEseguire);
        item->setData(Qt::UserRole, pairing.second);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        item->setCheckState(Qt::Checked); // AND initialize check state

    }
    
    connect(ui.iniziaControllo, SIGNAL(clicked()), this, SLOT(printTest()));

}

//void AppControlliMC::ChangeScreen(wchar_t* uiFilename, void (*f)()) {/* TODO: ??? */}

void AppControlliMC::runRenameVersions() {
    QThread* thread = new QThread();
    connect(thread, SIGNAL(started()), azioniControllo, SLOT(renameMCVersions()));
    thread->start();
}

void AppControlliMC::printTest() {
    ui.iniziaControllo->setStyleSheet("background-color:red;");
    qDebug("start Thread");
    AppControlliMC::runRenameVersions();
}
