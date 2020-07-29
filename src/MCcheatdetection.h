#pragma once

#include <QtWidgets/QMainWindow>
#include <QList>
#include "ui_MCcheatdetection.h"
#include "DetectionAction.h"
#include <QThread>

class MCcheatdetection : public QMainWindow
{
    Q_OBJECT
    QThread ActionThread;
public:
    MCcheatdetection(QWidget *parent = Q_NULLPTR);
    //void ChangeScreen(wchar_t* uiFilename, void (*f)());
    
private slots:
    //void printTest(int i);
    void resultThread(int result, int i);
    void BeginCheck();


private:
    Ui::MCcheatdetectionClass ui;
    DetectionAction* azioniControllo = new DetectionAction();

    void runAsThread(QVariant method_call);
    QList<QListWidgetItem*> getCheckedElements(QListWidget* ListWidget);

    
    
};