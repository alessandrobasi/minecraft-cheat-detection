#include "MCcheatdetection.h"
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QThread>
#include <QDebug>
#include <QMetaObject>

using namespace std;

MCcheatdetection::MCcheatdetection(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    /*
    QList<QPair<QString, int > > itemList = {
        QPair("Rename versions\'s Dir", 1), // &MCcheatdetection::runRenameVersions
        //QPair("Controllare cartella libraries", &azioniControllo->renameMCVersions),
        //QPair("Controllare file launcher profiles", &azioniControllo->renameMCVersions),
        //QPair("Cercare in %TEMP%", &azioniControllo->renameMCVersions), // jnativehook
        //QPair("Cercare in prefetch", &azioniControllo->renameMCVersions), // autoclicker, vape
        //QPair("Cercare nei file recenti", &azioniControllo->renameMCVersions) // shell:recent
    };*/

    /*QList<QPair<QString, void (AzioniControlloMC::*)() > > itemList = {
        QPair("Rename versions\'s Dir", &AzioniControlloMC::renameMCVersions)
    };
    
    QList<QPair<QString, QObject* > > itemList = {
        QPair("Rename versions\'s Dir", [=]() {azioniControllo->renameMCVersions(); })
    };
    */
    QList<QPair<QString, int > > itemList = {
        QPair("Rename versions\'s Dir", 0)
    };

    for each (QPair<QString, int > pairing in itemList)
    {
        QListWidgetItem* item = new QListWidgetItem(pairing.first, ui.passaggiEseguire);
        QVariant v;
        v.setValue(pairing.second);
        item->setData(Qt::UserRole, v);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        item->setCheckState(Qt::Checked); // AND initialize check state

    }
    
    connect(ui.iniziaControllo, SIGNAL(clicked()), this, SLOT(BeginCheck()));

}

//void AppControlliMC::ChangeScreen(wchar_t* uiFilename, void (*f)()) {/* TODO: ??? */}

// SLOT start button
void MCcheatdetection::BeginCheck() {
    //test SLOT
    ui.iniziaControllo->setStyleSheet("background-color:red;");

    // var checked contains a QList of QListWidgetItem that are checked
    QList<QListWidgetItem*> checked = MCcheatdetection::getCheckedElements(ui.passaggiEseguire);

    // starts each "functin" in QListWidgetItem.data
    for each (QListWidgetItem* item in checked) {
        qDebug() << "Run: " << item->text();
        MCcheatdetection::runAsThread(item->data(Qt::UserRole));

    }

}

// Start a thread
void MCcheatdetection::runAsThread(QVariant method_call) {
    qDebug() << method_call.type() << " - " << method_call.toInt();

    QThread* thread = new QThread();

    //QMetaObject::invokeMethod(azioniControllo, method_call.toString(), Qt::QueuedConnection);  ,Q_ARG(int, 1), Q_ARG(int, 1), ...
    switch (method_call.toInt())
    {
    case 0:
        connect(thread, SIGNAL(started()), azioniControllo, SLOT(renameMCVersions()));
        break;
    default:
        break;
    }
    //connect(thread, SIGNAL(started()), azioniControllo, SLOT(renameMCVersions()));
    //connect(thread, SIGNAL(resultValue(int)), this, SLOT(resultThread(int, i)));
    qDebug("start Thread");
    thread->start();
}

// return QList of checked QListWidgetItems
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
