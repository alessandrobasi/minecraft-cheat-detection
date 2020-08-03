#pragma once
#include "DetectionAction.h"
#include <QJsonParseError>
#include <QNetworkAccessManager>
#include "MCcheatdetection.h"

DetectionAction::DetectionAction(int uniqueID, int pos) {

    DetectionAction::MCAvatartUrl = "https://cravatar.eu/helmavatar/";
    DetectionAction::pos = pos;
    DetectionAction::method_call = uniqueID;

    DetectionAction::Win_username = DetectionAction::getUsername();
    DetectionAction::Mc_path = "C:/Users/" + DetectionAction::Win_username + "/AppData/Roaming/.minecraft/";
    
    DetectionAction::lib_elements = {
        "/io/github"
    };

}

QString DetectionAction::getUsername() {
    wchar_t userbuf[UNLEN + 1];
    DWORD usersize = UNLEN + 1;
    BOOL status;
    status = GetUserName(userbuf, &usersize);
    if (!status) {
        perror("err:");
        return NULL;
    }
    return QString::fromWCharArray(userbuf);
}

QList<QVariant> DetectionAction::getJson(QString file1) {
    QJsonParseError jsonError;
    QFile file;
    QJsonDocument flowerJson;

    file.setFileName(file1);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    flowerJson = QJsonDocument::fromJson(file.readAll(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << jsonError.errorString();
    }
    return flowerJson.toVariant().toList();
}

void DownloadIcon(QString url) {
    //QNetworkAccessManager* netW = new QNetworkAccessManager();

    //QNetworkReply* reply = netW->get(QNetworkRequest(QUrl(url)));
    //connect(reply, SIGNAL(finished()), MCcheatdetection, SLOT(addUsername()));
    //connect(netW, SIGNAL(finished()), MCcheatdetection, SLOT(addUsername()));

}

/*
   -1 : Bad
    0 : Error
    1 : Ok
*/

void DetectionAction::run() {
    switch (method_call) {
    case 0:
        DetectionAction::renameMCVersions();
        break;
    case 1:
        DetectionAction::librariesDir();
        break;
    case 2:
        DetectionAction::launcherProfiles();
        break;
    case 3:
        DetectionAction::searchInTEMP();
        break;
    default:
        qDebug() << "ID number " << DetectionAction::pos << "not mapped";
        break;
    }
}

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

    

   emit resultValue(result, pos);
}

void DetectionAction::librariesDir() {
    QString librariesPath = Mc_path + "libraires";
    int result = 0;

    for each (QString path in DetectionAction::lib_elements) {
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
    librariesPath.clear();

    emit resultValue(result, pos);
}

void DetectionAction::launcherProfiles() {
    QString usernamesPath = Mc_path + "usercache.json";
    QString launcherProfilesPath = Mc_path + "launcher_profiles.json";
    int result = 0;


    
    QList<QVariant> list = DetectionAction::getJson(usernamesPath);
    // len list = number of user used
    // istanze list[0] list[1] ... 

    for each (QVariant _variant in list) {
        QMap<QString, QVariant> User = _variant.toMap();
        if (User.size() != 3) {
            qDebug() << User["name"].toString() << "Has more/less data in his json";
        }
        // _variant.toMap() = { 
        //      "name" : "...",
        //      "uuid" : "...",
        // "expiresOn" : "..."
        // }
        qDebug() << "Found:" << User["name"].toString();

        //DownloadIcon(DetectionAction::MCAvatartUrl + User["name"].toString());

    }

    usernamesPath.clear();
    launcherProfilesPath.clear();

    emit resultValue(result, pos);
}

void DetectionAction::searchInTEMP() {
    int result = 0;

    // C:\Windows\TEMP
    // %TEMP% default C:\Users\<user>\AppData\Local\Temp
    // %TMP%  by default equal to %TEMP% 

    emit resultValue(result, pos);
}