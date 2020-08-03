#pragma once

#include <QThread>
#include <stdio.h>
#include <Windows.h>
#include <winbase.h>
#include <Lmcons.h>
#include <QDir>
#include <QDebug>

class DetectionAction : public QThread {

	Q_OBJECT

public:
	DetectionAction(int uniqueID, int pos);
	static QString getUsername();
	void run();
	
private:
	QString Win_username;
	QString Mc_path;
	int pos;
	int method_call;
	QList<QString> lib_elements;
	QString MCAvatartUrl;

	QList<QVariant> getJson(QString file1);
	void DownloadIcon(QString url);
	
public slots:
	void renameMCVersions();
	void librariesDir();
	void launcherProfiles();
	void searchInTEMP();

signals:
	void resultValue(int result, int pos);
};
