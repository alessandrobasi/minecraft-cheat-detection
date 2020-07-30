#include "MCcheatdetection.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QThread>
#include <QDebug>

using namespace std;

// https://wiki.qt.io/New_Signal_Slot_Syntax
// https://doc.qt.io/qt-5/qthread.html#details

MCcheatdetection::MCcheatdetection(QWidget *parent):QMainWindow(parent) {
    // build UI
    ui.setupUi(this);
    QLabel* SBRichText = new QLabel("Improve this program on <a target='_blank' href='https://github.com/alessandrobasi/minecraft-cheat-detection'>GitHub</a>");
    ui.statusBar->addWidget(SBRichText);   // showMessage();

    // list of possible checks
    QList<QPair<QString, int > > itemList = {
        QPair("Rename versions\'s Dir", 0),
        QPair("Check libraries Dir", 1),
        QPair("Check launcher profiles", 2),
        QPair("Search in %TEMP%", 3), // jnativehook
        QPair("Search in Prefetch", 4), // autoclicker, vape
        QPair("Search in Recent Files", 5) // shell:recent
    };

    // populate ui.actionsToDo
    for each (QPair<QString, int > pairing in itemList) {

        QListWidgetItem* item = new QListWidgetItem(pairing.first, ui.actionsToDo);
        
        item->setData(Qt::UserRole, pairing.second);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        item->setCheckState(Qt::Checked); // AND initialize check state

    }
    
    // set class to thread
    azioniControllo->moveToThread(&ActionThread);
    //connect(&ActionThread, &QThread::finished, azioniControllo, &QObject::deleteLater);

    // connect button to start cheats detection
    connect(ui.BeginControll, SIGNAL(clicked()), this, SLOT(BeginCheck()));


}

void MCcheatdetection::closeEvent(QCloseEvent* event) {
    ActionThread.quit();
    ActionThread.wait();
}

// function to change main widget to an other
//void AppControlliMC::ChangeScreen(wchar_t* uiFilename, void (*f)()) {/* TODO: ??? */}

// SLOT start button
void MCcheatdetection::BeginCheck() {
    ui.BeginControll->setDisabled(true);
    //test SLOT
    ui.BeginControll->setStyleSheet("background-color:red;");

    // var checked contains a QList of QListWidgetItem that are checked
    QList<QListWidgetItem*> checked = MCcheatdetection::getCheckedElements(ui.actionsToDo);

    // starts each "functin" in QListWidgetItem.data
    for each (QListWidgetItem* item in checked) {
        // qDebug() << "Run: " << item->text(); // item->data(Qt::UserRole).toInt()
        // setup connection
        MCcheatdetection::runAsThread(item->data(Qt::UserRole));

    }

    connect(azioniControllo, &DetectionAction::resultValue,
        this, &MCcheatdetection::resultThread
    );

    // start all
    qDebug("start Thread");
    ActionThread.setObjectName("ActionThread");
    ActionThread.start();


    /*
    TODO: whait for thread
    */

}

// Start a thread
void MCcheatdetection::runAsThread(QVariant method_call) {
    //qDebug() << method_call.type();

    //QMetaObject::invokeMethod(azioniControllo, method_call.toString(), Qt::QueuedConnection);  ,Q_ARG(int, 1), Q_ARG(int, 1), ...
    
    qDebug() << "Connection on start thread set id: "<< method_call.toInt();
    switch (method_call.toInt()) {
        case 0:
            connect(&ActionThread, &QThread::started, azioniControllo, &DetectionAction::renameMCVersions);
            break;
        case 1:
            connect(&ActionThread, &QThread::started, azioniControllo, &DetectionAction::librariesDir);
            break;
        case 2:
            connect(&ActionThread, &QThread::started, azioniControllo, &DetectionAction::launcherProfiles);
            break;
        case 3:
            connect(&ActionThread, &QThread::started, azioniControllo, &DetectionAction::SearchInTEMP);
            break;
        default:
            break;
    }

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
    qDebug() << "funzione ritorna :" << result << " Con i=" << i;
    
    switch (result) {
    case -1:
        ui.actionsToDo->item(i)->setBackground(QBrush(QColor("red")));
        break;
    case 1:
        ui.actionsToDo->item(i)->setBackground(QBrush(QColor("green")));
        break;
    case 0:
        ui.actionsToDo->item(i)->setBackground(QBrush(QColor("gray")));
        break;
    default:
        ui.actionsToDo->item(i)->setBackground(QBrush(QColor("blue")));
        break;
    }
}

