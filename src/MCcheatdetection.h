#pragma once

#include <QtWidgets/QMainWindow>
#include <QList>
#include "ui_MCcheatdetection.h"
#include "AzioniControllo.h"

class MCcheatdetection : public QMainWindow
{
    Q_OBJECT

public:
    MCcheatdetection(QWidget *parent = Q_NULLPTR);
    //void ChangeScreen(wchar_t* uiFilename, void (*f)());
    
private slots:
    //void printTest(int i);
    void resultThread(int result, int i);
    void printTest();
    void BeginCheck();

    //signals:

private:
    Ui::MCcheatdetectionClass ui;
    AzioniControlloMC* azioniControllo = new AzioniControlloMC();
    void runAsThread(QListWidgetItem* item);
    QList<QListWidgetItem*> getCheckedElements(QListWidget* ListWidget);
    
};
