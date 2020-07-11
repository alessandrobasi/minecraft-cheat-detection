#include "MCcheatdetection.h"
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QThread>
#include <QDebug>

using namespace std;

MCcheatdetection::MCcheatdetection(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QList<QPair<QString, void (AzioniControlloMC::*)() > > listadicose = {
        QPair("Rename versions\'s Dir", &AzioniControlloMC::renameMCVersions), // &MCcheatdetection::runRenameVersions
        //QPair("Controllare cartella libraries", &azioniControllo->renameMCVersions),
        //QPair("Controllare file launcher profiles", &azioniControllo->renameMCVersions),
        //QPair("Cercare in %TEMP%", &azioniControllo->renameMCVersions), // jnativehook
        //QPair("Cercare in prefetch", &azioniControllo->renameMCVersions), // autoclicker, vape
        //QPair("Cercare nei file recenti", &azioniControllo->renameMCVersions) // shell:recent
    };

    for each (QPair<QString, void (MCcheatdetection::*)()> pairing in listadicose)
    {
        QListWidgetItem* item = new QListWidgetItem(pairing.first, ui.passaggiEseguire);
        item->setData(Qt::UserRole, pairing.second);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        item->setCheckState(Qt::Checked); // AND initialize check state

    }
    
    connect(ui.iniziaControllo, SIGNAL(clicked()), this, SLOT(BeginCheck()));

}

//void AppControlliMC::ChangeScreen(wchar_t* uiFilename, void (*f)()) {/* TODO: ??? */}

void MCcheatdetection::BeginCheck() {
    //test SLOT
    ui.iniziaControllo->setStyleSheet("background-color:red;");

    // checked contains a QList of QListWidgetItem pointers
    QList<QListWidgetItem*> checked = MCcheatdetection::getCheckedElements(ui.passaggiEseguire);

    // starts each functin in QListWidgetItem.data
    for each (QListWidgetItem* item in checked) {
        qDebug() << "nome: " << item->text();
        qDebug("start Thread");
        MCcheatdetection::runAsThread(item);

    }

}

void MCcheatdetection::runAsThread(QListWidgetItem* item) {
    QThread* thread = new QThread();
    connect(thread, SIGNAL(started()), azioniControllo, SLOT(item.data(Qt::UserRole)));
    connect(thread, SIGNAL(resultValue(int)), this, SLOT(resultThread(int, i)));
    thread->start();
}

QList<QListWidgetItem*> MCcheatdetection::getCheckedElements(QListWidget* ListWidget) {
    
    QList<QListWidgetItem*> checked;

    for (int i = 0; i < ListWidget->count(); ++i) {

        QListWidgetItem* item = ListWidget->item(i);
        if (item->checkState() == 2) {
            checked.append(item);
        }
    }

    return checked;
}

void MCcheatdetection::resultThread(int result, int i) {
    qDebug("funzione ritorna :",result , " Con i=" , i);
}

void MCcheatdetection::printTest() {
    ui.iniziaControllo->setStyleSheet("background-color:red;");
    qDebug("start Thread");
    //MCcheatdetection::runAsThread();
}
