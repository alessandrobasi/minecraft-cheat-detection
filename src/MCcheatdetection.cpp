#include "MCcheatdetection.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QThread>
#include <QDebug>

using namespace std;

// https://wiki.qt.io/New_Signal_Slot_Syntax
// https://doc.qt.io/qt-5/qthread.html#details
// https://wiki.qt.io/Threads_Events_QObjects

MCcheatdetection::MCcheatdetection(QWidget *parent):QMainWindow(parent) {
    // build UI
    ui.setupUi(this);
    QLabel* SBRichText = new QLabel("Improve this program on <a target='_blank' href='https://github.com/alessandrobasi/minecraft-cheat-detection'>GitHub</a>");
    ui.statusBar->addWidget(SBRichText);   // showMessage();

    // list of possible checks
    // 1. the order of itmes
    // 2. unique int
    MCcheatdetection::mapItems = {
        { "Rename versions\'s Dir", 0 },
        { "Check libraries Dir", 1 },
        { "Check launcher profiles", 2 },
        { "Search in %TEMP%", 3},
        { "Search in Prefetch", 4},
        { "Search in Recent Files", 5}
    };
    /*
    QList<QString> itemList = {
        "Rename versions\'s Dir", // if minecraft is using .minecraft dir
        "Check libraries Dir", // 
        "Check launcher profiles", // load username
        "Search in %TEMP%", // jnativehook
        "Search in Prefetch", // autoclicker, vape
        "Search in Recent Files" // shell:recent
    };
    */
    // populate ui.actionsToDo
    for each (QString pairing in mapItems.keys()) {

        QListWidgetItem* item = new QListWidgetItem(pairing, ui.actionsToDo);
        
        //item->setData(Qt::UserRole, pairing.second);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        item->setCheckState(Qt::Checked); // AND initialize check state

    }
    
    // connect button to start cheats detection
    connect(ui.BeginControll, SIGNAL(clicked()), this, SLOT(BeginCheck()));


}


// function to change main widget to an other
//void AppControlliMC::ChangeScreen(wchar_t* uiFilename, void (*f)()) {/* TODO: ??? */}

// SLOT start button
void MCcheatdetection::BeginCheck() {

    ui.BeginControll->setDisabled(true);
    //test SLOT
    ui.BeginControll->setStyleSheet("background-color:red;");

    // checked contains a QList of QListWidgetItem that are checked
    QList<QListWidgetItem*> checked = MCcheatdetection::getCheckedElements(ui.actionsToDo);

    // starts each "functin" in QListWidgetItem.data
    for each (QListWidgetItem* item in checked) {
        // qDebug() << "Run: " << item->text(); // item->data(Qt::UserRole).toInt()
        // setup connection
        MCcheatdetection::runAsThread(item->text(), item->data(Qt::UserRole));
        
    }
    
    
    
    // start all
    qDebug("start Thread");
    for each (DetectionAction* thread in MCcheatdetection::ThreadList) {
        connect(thread, &DetectionAction::resultValue,
            this, &MCcheatdetection::resultThread
        );
        thread->start();
    }

    

    /*
    TODO: wait for thread
    */

}

// Start a thread
void MCcheatdetection::runAsThread(QString nome, QVariant itemPos) {
    //qDebug() << itemPos.type();
    qDebug() << "id:" << itemPos.toInt() << "added to ThreadList";

    MCcheatdetection::ThreadList.append(new DetectionAction(MCcheatdetection::mapItems[nome], itemPos.toInt()));

    /*
    switch (itemPos.toInt()) {
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
            connect(&ActionThread, &QThread::started, azioniControllo, &DetectionAction::searchInTEMP);
            break;
        default:
            break;
    }
    */

}

// return QList of checked QListWidgetItems
QList<QListWidgetItem*> MCcheatdetection::getCheckedElements(QListWidget* ListWidget) {
    
    QList<QListWidgetItem*> checked;

    for (int i = 0; i < ListWidget->count(); ++i) {

        QListWidgetItem* item = ListWidget->item(i);
        if (item->checkState() == 2) {
            item->setData(Qt::UserRole, i);
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



void addUsername(QString username) {
    
    QListWidgetItem* item = new QListWidgetItem(username, ui.usernameUsed);

    item->

    //item->setData(Qt::UserRole, pairing.second);
    //item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
    //item->setCheckState(Qt::Checked); // AND initialize check state

}