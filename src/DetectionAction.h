#pragma once
#include <QObject>
#include <stdio.h>
#include <Windows.h>
#include <winbase.h>
#include <Lmcons.h>
#include <string>
#include <QDir>
#include <QDebug>

class DetectionAction : public QObject {

	Q_OBJECT

public:
	DetectionAction();
	
private:
	QString Win_username;
	QString Mc_path;
	

	

public slots:
	void renameMCVersions();
	void librariesDir();

signals:
	void resultValue(int result);
};