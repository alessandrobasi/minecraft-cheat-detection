#pragma once
#include "DetectionAction.h"

DetectionAction::DetectionAction() {

    wchar_t userbuf[UNLEN + 1];
    DWORD usersize = UNLEN+1;
    BOOL status;

    status = GetUserName(userbuf, &usersize);
    if (!status) {
        perror("err:");

    }
    Win_username = QString::fromWCharArray(userbuf);
    //Mc_path = "C:\\Users\\" + Win_username + "\\AppData\\Roaming\\.minecraft\\";
    Mc_path = "C:/Users/" + Win_username + "/AppData/Roaming/.minecraft/";

}

/*
   -1 : Bad
    0 : Error
    1 : Ok
*/

void DetectionAction::renameMCVersions() {

    QString oldname = Mc_path+"versions";
    QString newname = Mc_path+"versions_renamed";
    QDir Dir;

    int result = 0;

    // rename == 0 Renamed
    if (Dir.rename(oldname, newname)) {
        qDebug() << "Dir versions not in use!!";
        Dir.rename(newname, oldname);
        result = -1;
    }  
    else {
        qDebug() << "Dir versions in use, OK";
        result = 1;
    }
    oldname.clear();
    newname.clear();

    

   emit resultValue(result, 0);
}

void DetectionAction::librariesDir() {
    QString librariesPath = Mc_path + "libraires";
    int result = 0;
    QList<QString> elements = {
        "/io/github"
    };

    for each (QString path in elements) {
        QString checkpath = librariesPath + path;
        QDir check(checkpath);
        if (check.exists()) {
            qDebug() << "Found: " << checkpath;
            if (result >= 0) {
                result = -1;
            }
        }
        else {
            qDebug() << "NOT found: " << checkpath;
            if (result == 0) {
                result = 1;
            }
        }


    }
    emit resultValue(result, 1);
}

void DetectionAction::launcherProfiles() {
    QString usernamesPath = Mc_path + "usercache.json";
    QString launcherProfilesPath = Mc_path + "launcher_profiles.json";
    int result = 0;

    emit resultValue(result, 2);
}

void DetectionAction::SearchInTEMP() {
    int result = 0;

    emit resultValue(result, 3);
}