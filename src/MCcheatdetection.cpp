#include "MCcheatdetection.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QThread>
#include <QDebug>

using namespace std;

MCcheatdetection::MCcheatdetection(QWidget *parent):QMainWindow(parent)
{
    azioniControllo = new DetectionAction();
    ui.setupUi(this);
	
	// list of possible checks
    QList<QPair<QString, int > > itemList = {
        QPair("Rename versions\'s Dir", 0),
        QPair("Check libraries Dir", 1),
        QPair("Controllare file launcher profiles", 2),
        QPair("Cercare in %TEMP%", 3), // jnativehook
        QPair("Cercare in prefetch", 4), // autoclicker, vape
        QPair("Cercare nei file recenti", 5) // shell:recent

    // populate ui.passaggiEseguire
    for each (QPair<QString, int > pairing in itemList)
    {
        QListWidgetItem* item = new QListWidgetItem(pairing.first, ui.passaggiEseguire);
        QVariant v;
        v.setValue(pairing.second);
        item->setData(Qt::UserRole, v);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        item->setCheckState(Qt::Checked); // AND initialize check state

    }
    

    azioniControllo->moveToThread(&ActionThread);
    connect(&ActionThread, &QThread::finished, azioniControllo, &QObject::deleteLater);

    // connect button to start cheats detection
    connect(ui.iniziaControllo, SIGNAL(clicked()), this, SLOT(BeginCheck()));

}

void MCcheatdetection::startThreads() {
    qDebug() << "ok5";
    qDebug("start Thread");
    //ActionThread.start();
}


// function to change main widget to an other
//void AppControlliMC::ChangeScreen(wchar_t* uiFilename, void (*f)()) {/* TODO: ??? */}

// SLOT start button
void MCcheatdetection::BeginCheck() {
    //test SLOT
    ui.iniziaControllo->setStyleSheet("background-color:red;");

    // var checked contains a QList of QListWidgetItem that are checked
    QList<QListWidgetItem*> checked = MCcheatdetection::getCheckedElements(ui.passaggiEseguire);

    // starts each "functin" in QListWidgetItem.data
    for each (QListWidgetItem* item in checked) {
        qDebug() << "Run: " << item->data(Qt::UserRole).toInt() << "- " << item->text();
        MCcheatdetection::runAsThread(item->data(Qt::UserRole));

    }
    qDebug() << "ok4";
    MCcheatdetection::startThreads();
}

// Start a thread
void MCcheatdetection::runAsThread(QVariant method_call) {
    qDebug() << method_call.type();

    
    //connect(azioniControllo, &AzioniControlloMC::resultValue, this, &MCcheatdetection::resultThread);
    //ActionThread.start();
    qDebug() << "ok1";
    //QMetaObject::invokeMethod(azioniControllo, method_call.toString(), Qt::QueuedConnection);  ,Q_ARG(int, 1), Q_ARG(int, 1), ...
    switch (method_call.toInt())
    {
    case 0:
		//connect(this, &MCcheatdetection::startThreads, azioniControllo, &AzioniControlloMC::renameMCVersions);
        thread->setObjectName("renameMCVersions");
        connect(thread, SIGNAL(started()), azioniControllo, SLOT(renameMCVersions()));
        //QThread* thread = QThread::create(azioniControllo.renameMCVersions));
        break;
    case 1:
        thread->setObjectName("librariesDir");
        connect(thread, SIGNAL(started()), azioniControllo, SLOT(librariesDir()));
        break;
    default:
        break;
    }

    //connect(thread, SIGNAL(resultValue(int)), this, SLOT(resultThread(int, method_call.toInt())));
    qDebug("start Thread");
    thread->start();

    /*
	qDebug() << "ok2";
    connect(azioniControllo, &AzioniControlloMC::resultValue, 
        [=](int a) { MCcheatdetection::resultThread(a, method_call.toInt()); }
        );
	*/

    // MCcheatdetection::resultThread(int, method_call.toInt())
 
    //connect(thread, SIGNAL(started()), azioniControllo, SLOT(renameMCVersions()));

    //connect(azioniControllo, SIGNAL(resultValue(int)), this, SLOT(resultThread(int, i)));
    qDebug() << "ok3";

    //qDebug("start Thread");
    //ActionThread.start();
    //thread->start();
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

