#pragma once
#include "DownloadSkinIconThread.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QPixmap>


DownloadSkinIconThread::DownloadSkinIconThread(QString username) {
	DownloadSkinIconThread::MCAvatartUrl = "https://cravatar.eu/helmavatar/";
    DownloadSkinIconThread::username = username;
    
    DownloadSkinIconThread::url = DownloadSkinIconThread::MCAvatartUrl + username;

}

void DownloadSkinIconThread::run() {
    QNetworkAccessManager* netW = new QNetworkAccessManager();

    QNetworkReply* reply = netW->get(QNetworkRequest(QUrl(DownloadSkinIconThread::url)));
    QEventLoop loop;

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();


    QByteArray imgData = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(imgData);

    delete reply;
    delete netW;

    emit endWork(DownloadSkinIconThread::username, QIcon(pixmap));
}