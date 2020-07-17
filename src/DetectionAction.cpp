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

void DetectionAction::renameMCVersions() {

    QString oldname = Mc_path+"versions";
    QString newname = Mc_path+"versions_renamed";
    QDir Dir;

    int result = 0;

    // rename == 0 Renamed
    if (Dir.rename(oldname, newname)) {
        printf("Dir versions not in use!!");
        Dir.rename(newname, oldname);
        result = -1;
    }  
    else {
        printf("Dir versions in use, OK");
        result = 1;
    }
    oldname.clear();
    newname.clear();

    /*
    -1 : Bad
     0 : Error
     1 : Ok
    */

   emit resultValue(result);

    return;
}

void DetectionAction::librariesDir() {
    QString librariesPath = Mc_path + "libraires";

    QList<QString> elements = {
        "/io/github"
    };

    for each (QString path in elements) {
        QString checkpath = librariesPath + path;
        QDir check(checkpath);
        if (check.exists()) {
            qDebug() << "Found: " << checkpath;
        }


    }

}
