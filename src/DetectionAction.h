#pragma once
#include <QObject>
#include <QThread>
#include <stdio.h>
#include <Windows.h>
#include <winbase.h>
#include <Lmcons.h>
#include <string>
#include <QDir>
#include <QDebug>

class DetectionAction : public QThread {

	Q_OBJECT

public:
	DetectionAction(int pos);
	void run();
	
private:
	QString Win_username;
	QString Mc_path;
	int pos;
	
public slots:
	void renameMCVersions();
	void librariesDir();
	void launcherProfiles();
	void searchInTEMP();

signals:
	void resultValue(int result, int pos);
};