#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AppControlliMC.h"
#include "AzioniControllo.h"

class AppControlliMC : public QMainWindow
{
    Q_OBJECT

public:
    AppControlliMC(QWidget *parent = Q_NULLPTR);
    //void ChangeScreen(wchar_t* uiFilename, void (*f)());
    
private slots:
    void printTest();
//signals:

private:
    Ui::AppControlliMCClass ui;
    AzioniControlloMC* azioniControllo = new AzioniControlloMC();
    void runRenameVersions();
    
};
