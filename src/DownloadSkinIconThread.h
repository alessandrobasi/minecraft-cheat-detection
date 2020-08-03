#pragma once
#include <QThread>
#include <QIcon>

class DownloadSkinIconThread : public QThread {

	Q_OBJECT

public:
	DownloadSkinIconThread(QString username);
	void run();

private:
	QString MCAvatartUrl;
	QString username;
	QString url;

signals:
	  void endWork(QString username, QIcon skin);
};

